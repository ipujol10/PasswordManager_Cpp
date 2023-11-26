project(GUI)

set(LIBRARY_NAME GUI)

set(FLTK_DIR /opt/fltk/build/)

find_package(FLTK REQUIRED CONFIG)

set(SOURCE windows.cpp)
foreach (item IN LISTS SOURCE)
    list(APPEND SOURCE src/${item})
    list(REMOVE_ITEM SOURCE ${item})
endforeach()

set(HEADER windows.hpp)
foreach (item IN LISTS HEADER)
    list(APPEND HEADER include/GUI/${item})
    list(REMOVE_ITEM HEADER ${item})
endforeach()

add_library(${LIBRARY_NAME} STATIC ${SOURCE} ${HEADER})

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
    )

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

target_include_directories(${LIBRARY_NAME} PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(${LIBRARY_NAME} fltk)
