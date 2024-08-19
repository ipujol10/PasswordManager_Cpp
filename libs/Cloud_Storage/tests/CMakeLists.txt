set(TEST_NAME CloudStorageTest)
project(${TEST_NAME})

if(${BUILD_TEST})
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)

  find_package(CURL REQUIRED)

  add_executable(GoogleDriveTest google_drive.cpp)
  target_link_libraries(GoogleDriveTest gtest_main cloud_storage CURL::libcurl)
  gtest_discover_tests(GoogleDriveTest)

  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/test_settings.db
       DESTINATION ${CMAKE_BINARY_DIR}/libs/Cloud_Storage/tests/data/)
endif()
