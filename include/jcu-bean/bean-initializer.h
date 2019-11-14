/**
 * @file	bean-initializer.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_BEAN_INITIALIZER_H__
#define __JCU_BEAN_BEAN_INITIALIZER_H__

#include <memory>

#include "intl/bean-object-context-impl.h"

namespace jcu {
    namespace bean {
        class BeanInitializer {
        public:
            virtual ~BeanInitializer() {}
            virtual void jcbPostConstruct() {}
            virtual void jcbPreDestroy() {}
        };
    }
}

#endif //__JCU_BEAN_BEAN_INITIALIZER_H__
