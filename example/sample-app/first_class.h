//
// Created by jichan on 2019-11-14.
//

#ifndef __SAMPLE_APP_FIRST_CLASS_H__
#define __SAMPLE_APP_FIRST_CLASS_H__

#include <jcu-bean/bean.h>

class SecondClass;
class FirstClass : public jcu::bean::BeanInitializer {
    JCU_BEAN_OBJECT_DECL();

private:
    SecondClass* second_class_;

public:
    FirstClass();
    virtual ~FirstClass();
    void jcbPostConstruct() override;
    void jcbPreDestroy() override;

    void test();
};

#endif //__SAMPLE_APP_FIRST_CLASS_H__
