/**
 * @file	bean.h
 * @author	Joseph Lee <development@jc-lab.net>
 * @date	2019/11/14
 * @copyright Copyright (C) 2019 jichan.\n
 *            This software may be modified and distributed under the terms
 *            of the Apache License 2.0.  See the LICENSE file for details.
 */

#ifndef __JCU_BEAN_BEAN_H__
#define __JCU_BEAN_BEAN_H__

#include <string>
#include <memory>

#include "bean-factory.h"
#include "bean-builder.h"
#include "bean-initializer.h"

#define JCU_BEAN_OBJECT_DECL() \
	public: \
		static void __jcubean_objectInit()

#define JCU_BEAN_BEGIN(CLASS, ...) \
	struct _JsCPPBeanClassLoader1_ ## CLASS { \
		_JsCPPBeanClassLoader1_ ## CLASS() { CLASS::__jcubean_objectInit(); } \
	} __t_JsCPPBeanClassLoader1_ ## CLASS; \
	void CLASS::__jcubean_objectInit() { \
		::jcu::bean::BeanFactory *beanFactory = ::jcu::bean::BeanFactory::getInstance(); \
		std::shared_ptr<CLASS> object(new CLASS()); \
		::jcu::bean::BeanBuilder beanBuilder(beanFactory->_beginRegisterBean(object, __VA_ARGS__));

#define JCU_BEAN_BEGIN_SUPPLIER(CLASS, SUPPLIER, ...) \
	struct _JsCPPBeanClassLoader1_ ## CLASS { \
		_JsCPPBeanClassLoader1_ ## CLASS() { CLASS::__jcubean_objectInit(); } \
	} __t_JsCPPBeanClassLoader1_ ## CLASS; \
	void CLASS::__jcubean_objectInit() { \
		::jcu::bean::BeanFactory *beanFactory = ::jcu::bean::BeanFactory::getInstance(); \
		std::shared_ptr<CLASS> object = SUPPLIER(); \
		::jcu::bean::BeanBuilder beanBuilder = beanFactory->_beginRegisterBean(object, #CLASS, __VA_ARGS__);

#define JCU_BEAN_AUTOWIRED_LAZY(TARGETCLASS, VARNAME, ...) \
		beanBuilder.withAutowiredObject<TARGETCLASS>(&TARGETCLASS::VARNAME, true, __VA_ARGS__);

#define JCU_BEAN_AUTOWIRED(TARGETCLASS, VARNAME, ...) \
		beanBuilder.withAutowiredObject<TARGETCLASS>(&TARGETCLASS::VARNAME, false, __VA_ARGS__);

#define JCU_BEAN_END() }

#endif //__JCU_BEAN_BEAN_H__
