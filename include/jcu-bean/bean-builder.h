/**
 * @file	bean-builder.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_BEAN_BUILDER_H__
#define __JCU_BEAN_BEAN_BUILDER_H__

#include <string>
#include <memory>

#include "intl/bean-object-context-impl.h"

namespace jcu {
    namespace bean {
        class BeanFactory;

        class BeanBuilder {
        private:
            std::shared_ptr<intl::BeanObjectContextBase> bean_ctx_;

            BeanBuilder(const BeanBuilder&) = delete;

        public:
            BeanBuilder(BeanBuilder&&) = default;

            BeanBuilder(std::shared_ptr<intl::BeanObjectContextBase> bean_ctx)
                : bean_ctx_(bean_ctx) { }

            template<class T>
            static BeanBuilder prepare(std::shared_ptr<T> existingBean)
            {
                std::shared_ptr<intl::BeanObjectContextBase> bean_ctx(new intl::BeanObjectContextImpl<T>(existingBean));
                return BeanBuilder(bean_ctx);
            }

            template<class T>
            static BeanBuilder prepare(T* existingBean)
            {
                std::shared_ptr<intl::BeanObjectContextBase> bean_ctx(new intl::BeanObjectContextImpl<T>(existingBean));
                return BeanBuilder(bean_ctx);
            }

            template<typename T, typename U>
            BeanBuilder &withAutowiredObject(U *T::*member, bool isLazy, const char *beanName = NULL) {
                std::string mapName;
                size_t varOffset = ((char*)&((T*)nullptr->*member) - (char*)nullptr);
                if (beanName)
                {
                    mapName = "B";
                    mapName.append(beanName);
                } else {
                    mapName = "T";
                    mapName.append(typeid(U).name());
                }

                bean_ctx_->addAutowiring(intl::AutowiringObjectContext(mapName, varOffset, isLazy));

                return *this;
            }

            std::shared_ptr<intl::BeanObjectContextBase> getBeanCtx() {
                return bean_ctx_;
            }
        };
    }
}

#endif //__JCU_BEAN_BEAN_BUILDER_H__
