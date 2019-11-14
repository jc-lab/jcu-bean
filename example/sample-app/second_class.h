//
// Created by jichan on 2019-11-14.
//

#ifndef __SAMPLE_APP_SECOND_CLASS_H__
#define __SAMPLE_APP_SECOND_CLASS_H__

#include <jcu-bean/bean.h>

class FirstClass;
class SecondClass : public jcu::bean::BeanInitializer {
JCU_BEAN_OBJECT_DECL();

private:
    FirstClass *first_class_;

public:
    SecondClass();
    virtual ~SecondClass();
    void jcbPostConstruct() override;
    void jcbPreDestroy() override;

    void test();
};

#endif //__SAMPLE_APP_SECOND_CLASS_H__
