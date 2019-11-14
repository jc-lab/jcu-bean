/**
 * @file	no-such-bean-exception.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_EXCEPTIONS_NO_SUCH_BEAN_EXCEPTION_H__
#define __JCU_BEAN_EXCEPTIONS_NO_SUCH_BEAN_EXCEPTION_H__

#include "bean-exception.h"

namespace jcu {
    namespace bean {
        namespace exceptions {
            class NoSuchBeanDefinitionException : public BeanException {
            public:
                NoSuchBeanDefinitionException() {}
                NoSuchBeanDefinitionException(const char *const message) : BeanException(message) {}
                NoSuchBeanDefinitionException(const std::string &message) : BeanException(message) {}
                NoSuchBeanDefinitionException(const char *const message, int code) : BeanException(message, code) {}
                NoSuchBeanDefinitionException(std::string &message, int code) : BeanException(message, code) {}
                NoSuchBeanDefinitionException(const exception &other) : BeanException(other) {}
            };
        }
    }
}

#endif //__JCU_BEAN_EXCEPTIONS_NO_SUCH_BEAN_EXCEPTION_H__
