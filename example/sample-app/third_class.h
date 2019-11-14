//
// Created by jichan on 2019-11-14.
//

#ifndef __SAMPLE_APP_THIRD_CLASS_HPP__
#define __SAMPLE_APP_THIRD_CLASS_HPP__

#include <jcu-bean/bean.h>

class FirstClass;
class SecondClass;
class ThirdClass : public jcu::bean::BeanInitializer {
JCU_BEAN_OBJECT_DECL();

private:
    FirstClass *first_class_;
    SecondClass *second_class_;

public:
    ThirdClass();
    virtual ~ThirdClass();
    void jcbPostConstruct() override;
    void jcbPreDestroy() override;

    void run();
};

#endif //__SAMPLE_APP_THIRD_CLASS_HPP__
