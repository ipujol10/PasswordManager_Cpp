cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME PasswordManager)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} VERSION 1.0)

set(FLTK_DIR /opt/fltk/build/)

find_package(FLTK REQUIRED NO_MODULE)

add_subdirectory(libs)

add_executable(${PROJECT_NAME} src/PasswordManager.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} fltk GUI)
