//
// Created by jichan on 2019-11-14.
//

#include "second_class.h"
#include "first_class.h"

#include <iostream>

JCU_BEAN_BEGIN(SecondClass)
    JCU_BEAN_AUTOWIRED(SecondClass, first_class_)
JCU_BEAN_END()

SecondClass::SecondClass() {
    std::cout << "SecondClass CREATED this = " << this << std::endl;
	std::cout << std::endl;
}

SecondClass::~SecondClass() {

}

void SecondClass::jcbPostConstruct() {
    std::cout << "SecondClass jcbPostConstruct called" << std::endl;
    std::cout << "\tfirst_class = " << first_class_ << std::endl;
    std::cout << std::endl;
}
void SecondClass::jcbPreDestroy() {
    std::cout << "SecondClass jcbPreDestroy called" << std::endl;
	std::cout << std::endl;
}

void SecondClass::test() {
    std::cout << "SecondClass test method called" << std::endl;
	std::cout << std::endl;
}
