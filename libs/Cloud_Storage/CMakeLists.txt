project(cloud_storage)

set(LIBRARY_NAME cloud_storage)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
FetchContent_MakeAvailable(googletest)

set(SOURCE google_drive.cpp)
foreach(item IN LISTS SOURCE)
  list(APPEND SOURCE src/${item})
  list(REMOVE_ITEM SOURCE ${item})
endforeach()

set(HEADER storage.hpp google_drive.hpp)
foreach(item IN LISTS HEADER)
  list(APPEND HEADER include/cloud_storage/${item})
  list(REMOVE_ITEM HEADER ${item})
endforeach()

add_library(${LIBRARY_NAME} STATIC ${SOURCE} ${HEADER})
target_link_libraries(${LIBRARY_NAME} database)

target_include_directories(
  ${LIBRARY_NAME}
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
          $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>)

target_include_directories(
  ${LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include>)

add_subdirectory(tests)
