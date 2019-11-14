/**
 * @file	autowiring-object-context.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_INTL_AUTOWIRING_OBJECT_CONTEXT_H__
#define __JCU_BEAN_INTL_AUTOWIRING_OBJECT_CONTEXT_H__

#include <string>

namespace jcu {
    namespace bean {
        namespace intl {
            class BeanObjectContextBase;

            class AutowiringObjectContext {
            private:
                std::string map_name_;
                BeanObjectContextBase *bean_ctx_;

                size_t var_offset_;
                bool lazy_;

            public:
                AutowiringObjectContext(const std::string& map_name, size_t var_offset, bool lazy)
                : bean_ctx_(NULL) {
                    this->map_name_ = map_name;
                    this->var_offset_ = var_offset;
                    this->lazy_ = lazy;
                }
                AutowiringObjectContext(const AutowiringObjectContext& o) = default;

                void setBeanCtx(BeanObjectContextBase *bean_ctx) {
                    if(bean_ctx_)
                        return ;
                    bean_ctx_ = bean_ctx;
                }

                const std::string &getMapName() const {
                    return map_name_;
                }
                BeanObjectContextBase *getBeanCtx() const {
                    return bean_ctx_;
                }
                size_t getVarOffset() const {
                    return var_offset_;
                }
                bool isLazy() const {
                    return lazy_;
                }
            };
        }
    }
}

#endif //__JCU_BEAN_INTL_AUTOWIRING_OBJECT_CONTEXT_H__
