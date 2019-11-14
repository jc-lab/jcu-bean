/**
 * @file	bean-factory.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_BEAN_FACTORY_H__
#define __JCU_BEAN_BEAN_FACTORY_H__

#include <string>
#include <memory>
#include <functional>

#include "intl/bean-object-context-impl.h"

namespace jcu {
    namespace bean {
        class BeanBuilder;

        class BeanFactory
        {
        public:
            static BeanFactory *getInstance();

            virtual void start() = 0;
            virtual void stop() = 0;

            /**
             * Bean registration with bean initialization.
             *
             * @param beanBuilder
             * @param beanName
             */
            virtual void initializeBean(BeanBuilder &bean_builder, const char *bean_name) = 0;

            /**
             * Only Autowired and BeanInitialize handlers work without bean registration.
             *
             * @param beanBuilder
             */
            virtual void autowireBean(BeanBuilder &bean_builder) = 0;

            template<class T>
            BeanBuilder _beginRegisterBean(std::shared_ptr<T> existing_bean, const char *bean_name = NULL)
            {
                std::shared_ptr<intl::BeanObjectContextBase> bean_ctx(new intl::BeanObjectContextImpl<T>(existing_bean));
                return _beginRegisterBeanImpl(bean_ctx, bean_name);
            }

            template<class T>
            T *autowire()
            {
                std::string reg_name("T");
                reg_name.append(typeid(T).name());
                intl::BeanObjectContextBase *bean_ctx = findBeanContext(reg_name);
                if(bean_ctx)
                    return (T*)bean_ctx->getPtr();
                return nullptr;
            }

            template<class T>
            T *autowire(const std::string& bean_name)
            {
                intl::BeanObjectContextBase *bean_ctx = findBeanContext("B" + bean_name);
                if(bean_ctx)
                    return (T*)bean_ctx->getPtr();
                return nullptr;
            }

        protected:
            virtual intl::BeanObjectContextBase *findBeanContext(const std::string& reg_name) = 0;
            virtual BeanBuilder _beginRegisterBeanImpl(std::shared_ptr<intl::BeanObjectContextBase> bean_ctx, const char *bean_name) = 0;
        };
    }
}

#endif //__JCU_BEAN_BEAN_FACTORY_H__
