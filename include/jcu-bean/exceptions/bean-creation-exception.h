/**
 * @file	bean-creation-exception.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_EXCEPTIONS_BEAN_CREATION_EXCEPTION_H__
#define __JCU_BEAN_EXCEPTIONS_BEAN_CREATION_EXCEPTION_H__

#include "bean-exception.h"

namespace jcu {
    namespace bean {
        namespace exceptions {
            class BeanCreationException : public BeanException {
            public:
                BeanCreationException() {}
                BeanCreationException(const char *const message) : BeanException(message) {}
                BeanCreationException(const std::string &message) : BeanException(message) {}
                BeanCreationException(const char *const message, int code) : BeanException(message, code) {}
                BeanCreationException(std::string &message, int code) : BeanException(message, code) {}
                BeanCreationException(const exception &other) : BeanException(other) {}
            };
    }
    }
}

#endif //__JCU_BEAN_EXCEPTIONS_BEAN_CREATION_EXCEPTION_H__
