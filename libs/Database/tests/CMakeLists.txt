set(TEST_NAME DatabaseTest)
project(${TEST_NAME})

if(${BUILD_TEST})
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)

  add_executable(SQLite3Test sqlite3.cpp)
  target_link_libraries(SQLite3Test gtest_main database)
  gtest_discover_tests(SQLite3Test)

  set(TEST_FILES connect_existing.db)
  foreach(item IN LISTS TEST_FILES)
    set(CURRENT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/${item})
    if(EXISTS ${CURRENT_FILE})
      file(COPY ${CURRENT_FILE}
           DESTINATION ${CMAKE_BINARY_DIR}/libs/Database/tests/data)
    else()
      message("${item} file not found")
    endif()
  endforeach()
endif()
