/**
 * @file	bean-object-context-base.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_INTL_BEAN_OBJECT_CONTEXT_BASE_H__
#define __JCU_BEAN_INTL_BEAN_OBJECT_CONTEXT_BASE_H__

#include <string>

#include "autowiring-object-context.h"

#include <list>

namespace jcu {
    namespace bean {
        namespace intl {
            class BeanObjectContextBase {
            protected:
                int inited_;
                std::string class_name_;
                std::string bean_name_;
                bool bean_locked_;

                /**
                 * dependencies
                 */
                std::list<AutowiringObjectContext> autowirings_;

                BeanObjectContextBase() : inited_(0), bean_locked_(false) { }
                virtual ~BeanObjectContextBase() {}

            public:
                virtual void *getPtr() = 0;
                virtual void callPostConstruct() = 0;
                virtual void callPreDestroy() = 0;

                void setLock() {
                    bean_locked_ = true;
                }
                void setBeanName(const std::string &bean_name) {
                    if(bean_locked_)
                        return ;
                    bean_name_ = bean_name;
                }
                void setInited(int value) {
                    inited_ = value;
                }
                void addAutowiring(const AutowiringObjectContext &autowiring_object_context) {
                    if(bean_locked_)
                        return ;
                    autowirings_.emplace_back(autowiring_object_context);
                }

                int getInited() const {
                    return inited_;
                }
                const std::string &getClassName() const {
                    return class_name_;
                }
                const std::string &getBeanName() const {
                    return bean_name_;
                }
                std::list<AutowiringObjectContext> &getAutowirings() {
                    return autowirings_;
                }
            };
        }
    }
}

#endif //__JCU_BEAN_INTL_BEAN_OBJECT_CONTEXT_BASE_H__
