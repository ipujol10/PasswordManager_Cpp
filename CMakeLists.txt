cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME PasswordManager)

project(${PROJECT_NAME} VERSION 1.0)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/fltk")
    message("Install FLTK...")
    message("Downloading FLTK..")
    execute_process(
        COMMAND git clone https://github.com/fltk/fltk.git external/FLTK
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

else()
    message("FLTK is already installed.")
endif()

set(FLTK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/fltk/")

find_package(FLTK REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} fltk)
