set(LIBRARY_NAME database)

project(${LIBRARY_NAME})

find_package(SQLite3 REQUIRED)

set(SOURCE sqlite3.cpp)
foreach(item IN LISTS SOURCE)
  list(APPEND SOURCE src/${item})
  list(REMOVE_ITEM SOURCE ${item})
endforeach(item IN LISTS SOURCE)

set(HEADER database.hpp sqlite3.hpp)
foreach(item IN LISTS HEADER)
  list(APPEND HEADER include/${LIBRARY_NAME}/${item})
  list(REMOVE_ITEM HEADER ${item})
endforeach()

add_library(${LIBRARY_NAME} STATIC ${SOURCE} ${HEADER})

target_include_directories(
  ${LIBRARY_NAME}
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
          $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>)

target_include_directories(
  ${LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include>)

target_link_libraries(${LIBRARY_NAME} SQLite::SQLite3)
