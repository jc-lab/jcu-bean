cmake_minimum_required (VERSION 2.8)
set(PROJECT_VERSION 1.0.0)
if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
    project(sample-app VERSION ${PROJECT_VERSION} LANGUAGES CXX)
else()
    project(sample-app CXX)
endif (POLICY CMP0048)

add_executable(${PROJECT_NAME}
        sample-app/sample-app.cc
        sample-app/first_class.h
        sample-app/first_class.cc
        sample-app/second_class.h
        sample-app/second_class.cc
        sample-app/third_class.h
        sample-app/third_class.cc
        )

target_link_libraries(${PROJECT_NAME} jcu-bean)
