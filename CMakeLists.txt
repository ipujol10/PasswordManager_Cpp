cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME PasswordManager)

project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk)
  message("Install FLTK...")
  message("Downloading FLTK..")
  execute_process(
    COMMAND git clone https://github.com/fltk/fltk.git external/FLTK
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  execute_process(COMMAND git checkout release-1.3.9
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/FLTK)

  message("Building FLTK...")
  execute_process(COMMAND mkdir build
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/FLTK)
  execute_process(
    COMMAND
      cmake -DFLTK_BUILD_TEST=OFF -DFLTK_BUILD_HTML_DOCS=OFF
      -DFLTK_BUILD_PDF_DOCS=OFF
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/external/fltk ..
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/FLTK/build)
  execute_process(
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/FLTK/build)

  message("Installing FLTK...")
  execute_process(
    COMMAND make install
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/FLTK/build)

  message("Deleting FLTK build directory..")
  execute_process(COMMAND rm -r FLTK
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external)

  message("FLTK installed")
else()
  message("FLTK is already installed.")
endif()

set(FLTK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/fltk/share/fltk)

find_package(FLTK REQUIRED NO_MODULE)

add_subdirectory(libs)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} fltk)
