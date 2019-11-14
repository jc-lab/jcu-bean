//
// Created by jichan on 2019-11-14.
//

#include "first_class.h"
#include "second_class.h"

#include <iostream>

JCU_BEAN_BEGIN(FirstClass)
	// JCU_BEAN_AUTOWIRED(FirstClass, second_class_) // Cause exception because Circular reference
	JCU_BEAN_AUTOWIRED_LAZY(FirstClass, second_class_)
JCU_BEAN_END()

FirstClass::FirstClass() {
    std::cout << "FirstClass CREATED this = " << this << std::endl;
	std::cout << std::endl;
}

FirstClass::~FirstClass() {

}

void FirstClass::jcbPostConstruct() {
    std::cout << "FirstClass jcbPostConstruct called" << std::endl;
    std::cout << "\tsecond_class = " << second_class_ << std::endl;
	std::cout << std::endl;
}
void FirstClass::jcbPreDestroy() {
    std::cout << "FirstClass jcbPreDestroy called" << std::endl;
	std::cout << std::endl;
}

void FirstClass::test() {
    std::cout << "FirstClass test method called" << std::endl;
	std::cout << std::endl;
}
