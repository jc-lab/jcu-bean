cmake_minimum_required (VERSION 2.8)

set(PROJECT_VERSION 1.0.0)

if (POLICY CMP0048)
	cmake_policy(SET CMP0048 NEW)
	project(jcu-bean VERSION ${PROJECT_VERSION} LANGUAGES CXX)
else()
	project(jcu-bean CXX)
endif (POLICY CMP0048)

option(WITH_EXAMPLE "Build example." OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SRC_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/src/bean-factory.cc
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/bean-factory.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/bean-builder.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/bean.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/bean-initializer.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/intl/autowiring-object-context.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/intl/bean-object-context-base.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/intl/bean-object-context-impl.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/exceptions/bean-exception.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/exceptions/bean-creation-exception.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/jcu-bean/exceptions/no-such-bean-definition-exception.h
		)

add_library(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

if(WITH_EXAMPLE)
	add_subdirectory(example)
endif()
