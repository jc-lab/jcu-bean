/**
 * @file	bean-exception.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_EXCEPTIONS_BEAN_EXCEPTION_H__
#define __JCU_BEAN_EXCEPTIONS_BEAN_EXCEPTION_H__

#include <exception>

namespace jcu {
    namespace bean {
        namespace exceptions {
			template<int buf_size>
			struct FixedString {
				char buf[buf_size];

				FixedString() {
					buf[0] = 0;
				}
				void copyFrom(const char* text) {
					const int max_size = buf_size - 1;
					const char* ps = text;
					char* pd = buf;
					for (int i = 0; *ps && (i < max_size); i++) {
						*pd = *ps;
						pd++; ps++;
					}
					*pd = 0;
				}
				FixedString(const char* text) {
					copyFrom(text);
				}
				FixedString(const std::string& text) : FixedString(text.c_str()) { }
				FixedString& operator=(const char* text) {
					copyFrom(text);
				}
				FixedString& operator=(const std::string& text) {
					copyFrom(text.c_str());
				}
				const char* c_str() const {
					return buf;
				}
			};

            class BeanException : public std::exception {
            protected:
				FixedString<256> message_;

            public:
                BeanException() {}
				BeanException(const char* const message) : message_(message) {
					std::exception info(message_.c_str());
					this->operator=(info);
				}
                BeanException(const std::string& message) : message_(message) {
					std::exception info(message_.c_str());
					this->operator=(info);
				}
                BeanException(const char *const message, int code) : message_(message) {
					std::exception info(message_.c_str(), code);
					this->operator=(info);
				}
                BeanException(std::string& message, int code) : message_(message) {
					std::exception info(message_.c_str(), code);
					this->operator=(info);
				}
                BeanException(const exception &other) : exception(other) {}
            };
        }
    }
}

#endif //__JCU_BEAN_EXCEPTIONS_BEAN_EXCEPTION_H__
