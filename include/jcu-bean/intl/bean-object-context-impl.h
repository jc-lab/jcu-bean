/**
 * @file	bean-object-context-impl.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_INTL_BEAN_OBJECT_CONTEXT_IMPL_H__
#define __JCU_BEAN_INTL_BEAN_OBJECT_CONTEXT_IMPL_H__

#include <string>
#include <memory>
#include <list>

#include "bean-object-context-base.h"

#include "../bean-initializer.h"

namespace jcu {
    namespace bean {
        namespace intl {
            template<class T>
            class BeanObjectContextImpl : public BeanObjectContextBase {
            private:
                void *ptr_;
                std::shared_ptr<T> object_;

            public:
                virtual ~BeanObjectContextImpl() {}

				explicit BeanObjectContextImpl(T *existingObject) : ptr_(existingObject) {
                    class_name_ = typeid(T).name();
                }

                explicit BeanObjectContextImpl(std::shared_ptr<T> existingObject) : object_(existingObject) {
                    class_name_ = typeid(T).name();
                    ptr_ = object_.get();
                }

                void *getPtr() override { return ptr_; };

				template<int avail>
				void callPostConstructChecked();

				template<>
				void callPostConstructChecked<false>() {}

				template<>
				void callPostConstructChecked<true>() {
                    BeanInitializer *bean_initializer = dynamic_cast<BeanInitializer*>(object_.get());
                    if(bean_initializer) {
                        bean_initializer->jcbPostConstruct();
                    }
                }

				template<int avail>
				void callPreDestroyChecked();

				template<>
				void callPreDestroyChecked<false>() {}

				template<>
				void callPreDestroyChecked<true>() {
                    BeanInitializer *bean_initializer = dynamic_cast<BeanInitializer*>(object_.get());
                    if(bean_initializer) {
                        bean_initializer->jcbPreDestroy();
                    }
				}

                void callPostConstruct() override {
					callPostConstructChecked< std::is_base_of<BeanInitializer, T>::value>();
                }

                void callPreDestroy() override {
					callPreDestroyChecked< std::is_base_of<BeanInitializer, T>::value>();
                }
            };
        }
    }
}

#endif //__JCU_BEAN_INTL_BEAN_OBJECT_CONTEXT_IMPL_H__
