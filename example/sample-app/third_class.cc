//
// Created by jichan on 2019-11-14.
//

#include "third_class.h"
#include "first_class.h"
#include "second_class.h"

#include <iostream>

JCU_BEAN_BEGIN(ThirdClass)
    JCU_BEAN_AUTOWIRED(ThirdClass, first_class_)
    JCU_BEAN_AUTOWIRED(ThirdClass, second_class_)
JCU_BEAN_END()

ThirdClass::ThirdClass() {
    std::cout << "ThirdClass CREATED" << std::endl;
	std::cout << std::endl;
}

ThirdClass::~ThirdClass() {

}

void ThirdClass::jcbPostConstruct() {
    std::cout << "ThirdClass jcbPostConstruct called" << std::endl;
    std::cout << "\tfirst_class = " << first_class_ << std::endl;
    std::cout << "\tsecond_class = " << second_class_ << std::endl;
    std::cout << std::endl;
}
void ThirdClass::jcbPreDestroy() {
    std::cout << "ThirdClass jcbPreDestroy called" << std::endl;
	std::cout << std::endl;
}

void ThirdClass::run() {
    std::cout << "ThirdClass run" << std::endl;
	std::cout << std::endl;

    first_class_->test();
    second_class_->test();
}
