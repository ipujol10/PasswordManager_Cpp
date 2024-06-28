cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME PasswordManager)

project(${PROJECT_NAME} VERSION 1.0)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/fltk")
    message("Install FLTK...")
    message("Downloading FLTK..")
    execute_process(
        COMMAND git clone https://github.com/fltk/fltk.git external/fltk
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    execute_process(
        COMMAND git checkout release-1.3.9
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk
    )

    message("Building FLTK...")
    execute_process(
        COMMAND mkdir build
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk
    )
    execute_process(
        COMMAND cmake 
            -DFLTK_BUILD_TEST=OFF 
            -DFLTK_BUILD_HTML_DOCS=OFF 
            -DFLTK_BUILD_PDF_DOCS=OFF 
            ..
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk/build
    )
    execute_process(
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk/build
    )

else()
    message("FLTK is already installed.")
endif()

set(FLTK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/fltk/build")

find_package(FLTK REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} fltk)
