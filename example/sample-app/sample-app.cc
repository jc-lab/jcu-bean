#include <iostream>

#include <jcu-bean/bean-factory.h>

#include "third_class.h"

int main(int argc, char *argv[]) {
    jcu::bean::BeanFactory *bean_factory = jcu::bean::BeanFactory::getInstance();
    bean_factory->start();

	std::cout << "BEAN INITIALIZE FINISH! APP START" << std::endl;
	std::cout << std::endl;

    {
        ThirdClass *third_class = bean_factory->autowire<ThirdClass>();
        third_class->run();
    }

    return 0;
}
