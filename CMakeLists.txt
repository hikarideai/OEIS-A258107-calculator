cmake_minimum_required(VERSION 2.8)
project(OEIS_A258107_calculator)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(project_VERSION_MAJOR 1)
set(project_VERSION_MINOR 0)

set(SOURCE_FILES
    scr/BigInteger.cpp
    scr/Application.cpp
    scr/Application.hpp
    scr/main.cpp)

set(EXECUTABLE_NAME "OEIS_A258107_calculator")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(SFML_ROOT ${CMAKE_SOURCE_DIR})

find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include/BigInteger)
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${project_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${project_VERSION_MINOR}")
include(CPack)