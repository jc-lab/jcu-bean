/**
 * @file	bean-factory.cc
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#include "jcu-bean/bean-factory.h"
#include "jcu-bean/bean-builder.h"

#include "jcu-bean/exceptions/bean-exception.h"
#include "jcu-bean/exceptions/bean-creation-exception.h"
#include "jcu-bean/exceptions/no-such-bean-definition-exception.h"

#include <mutex>
#include <map>

namespace jcu {
    namespace bean {
        class BeanFactoryImpl : public BeanFactory
        {
        private:
            std::mutex beans_mutex_;

            // Prefix
            // T{name} : typeid(class).name()
            // B{name} : User Bean Name
            std::map<std::string, std::shared_ptr<intl::BeanObjectContextBase> > beans_;

            void findAllDependency(intl::BeanObjectContextBase *bean_ctx) {
                std::list<intl::AutowiringObjectContext> &autowirings = bean_ctx->getAutowirings();

                // Find all dependencies
                for (auto iter_aw = autowirings.begin(); iter_aw != autowirings.end(); iter_aw++)
                {
                    auto found_bean = beans_.find(iter_aw->getMapName());
                    if (found_bean == beans_.end()) {
                        // could not find bean
                        throw exceptions::NoSuchBeanDefinitionException("Could not find bean: " + iter_aw->getMapName());
                    }
                    iter_aw->setBeanCtx(found_bean->second.get());
                }
            }
            void initializeBeanImpl(intl::BeanObjectContextBase *bean_ctx, std::list<intl::BeanObjectContextBase *> &call_bean_stack) {
                if (bean_ctx->getInited() == 0)
                {
                    const std::list<intl::AutowiringObjectContext> &autowirings = bean_ctx->getAutowirings();

                    void *clsPtr = (char*)bean_ctx->getPtr();
                    bean_ctx->setInited(1);
                    call_bean_stack.push_back(bean_ctx);
                    for (auto iter = autowirings.cbegin(); iter != autowirings.cend(); iter++)
                    {
                        intl::BeanObjectContextBase *iter_bean_ctx = iter->getBeanCtx();
                        bool alreadyResolved = false;
                        for (auto stack_iter = call_bean_stack.begin(); stack_iter != call_bean_stack.end(); stack_iter++)
                        {
                            if (*stack_iter == iter->getBeanCtx())
                            {
                                alreadyResolved = true;
                                break;
                            }
                        }
                        if (!iter->isLazy())
                        {
                            if(alreadyResolved)
                                throw exceptions::BeanCreationException("Circular reference detected: " + iter->getMapName());
                            else
                                initializeBeanImpl(iter_bean_ctx, call_bean_stack);
                            *((void**)((char*)clsPtr + iter->getVarOffset())) = (iter_bean_ctx->getPtr());
                        }
                    }
                    call_bean_stack.pop_back();
                }
            }

        protected:
            intl::BeanObjectContextBase *findBeanContext(const std::string& reg_name) override {
                std::unique_lock<std::mutex> lock(beans_mutex_);
                auto iter = beans_.find(reg_name);
                if(iter != beans_.end()) {
                    return iter->second.get();
                }
                return nullptr;
            }

            BeanBuilder _beginRegisterBeanImpl(std::shared_ptr<intl::BeanObjectContextBase> bean_ctx, const char *bean_name) override {
                beans_["T" + bean_ctx->getClassName()] = bean_ctx;
                if (bean_name)
                {
                    bean_ctx->setBeanName(bean_name);
                    beans_["B" + bean_ctx->getBeanName()] = bean_ctx;
                }
                return BeanBuilder(bean_ctx);
            }

        public:
            void start() override {
                // Find all dependencies
                for (auto iter_bean = beans_.begin(); iter_bean != beans_.end(); iter_bean++)
                {
                    findAllDependency(iter_bean->second.get());
                }

                // initialize beans
                for (auto iter_bean = beans_.begin(); iter_bean != beans_.end(); iter_bean++)
                {
                    intl::BeanObjectContextBase *bean_ctx = iter_bean->second.get();
                    std::list<intl::BeanObjectContextBase *> call_bean_stack;
                    initializeBeanImpl(bean_ctx, call_bean_stack);
                }

                // Lazy initialize beans
                for (auto iter_bean = beans_.begin(); iter_bean != beans_.end(); iter_bean++)
                {
                    intl::BeanObjectContextBase *bean_ctx = iter_bean->second.get();
                    if (bean_ctx->getInited() < 2) {
                        void* clsPtr = (char*)bean_ctx->getPtr();
                        std::list<intl::AutowiringObjectContext>& autowirings = bean_ctx->getAutowirings();
                        for (auto iter_aw = autowirings.begin(); iter_aw != autowirings.end(); iter_aw++)
                        {
                            *((void**)((char*)clsPtr + iter_aw->getVarOffset())) = (iter_aw->getBeanCtx()->getPtr());
                        }
                        bean_ctx->callPostConstruct();
                        bean_ctx->setInited(2);
                    }
                }
            }

            void stop() override {
                for (auto iter_bean = beans_.begin(); iter_bean != beans_.end(); )
                {
                    iter_bean->second->callPreDestroy();
                    iter_bean = beans_.erase(iter_bean);
                }
            }

            void autowireBean(BeanBuilder &bean_builder) override {
                std::list<intl::BeanObjectContextBase *> call_bean_stack;
                std::shared_ptr<intl::BeanObjectContextBase> bean_ctx(bean_builder.getBeanCtx());
                {
                    std::unique_lock<std::mutex> lock(beans_mutex_);
                    findAllDependency(bean_ctx.get());
                    initializeBeanImpl(bean_ctx.get(), call_bean_stack);
                    bean_ctx->callPostConstruct();
                }
            }

            void initializeBean(BeanBuilder &bean_builder, const char *bean_name) override {
                std::list<intl::BeanObjectContextBase *> call_bean_stack;
                std::shared_ptr<intl::BeanObjectContextBase> bean_ctx(bean_builder.getBeanCtx());
                {
                    std::unique_lock<std::mutex> lock(beans_mutex_);
                    if(bean_name) {
                        bean_ctx->setBeanName(bean_name);
                        beans_["B" + bean_ctx->getBeanName()] = bean_ctx;
                    }
                    initializeBeanImpl(bean_ctx.get(), call_bean_stack);
                    beans_["T" + bean_ctx->getClassName()] = bean_ctx;
                    bean_ctx->setLock();
                    bean_ctx->callPostConstruct();
                }
            }
        };

        BeanFactory* BeanFactory::getInstance() {
            static std::unique_ptr<BeanFactory> singletone(new BeanFactoryImpl());
            return singletone.get();
        }

    }
}

