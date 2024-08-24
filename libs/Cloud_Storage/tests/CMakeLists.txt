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

  set(TEST_FILES test_settings.db)
  foreach(item IN LISTS TEST_FILES)
    set(CURRENT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/${item})
    if(EXISTS ${CURRENT_FILE})
      file(COPY ${CURRENT_FILE}
           DESTINATION ${CMAKE_BINARY_DIR}/libs/Cloud_Storage/tests/data)
    else()
      message("${item} file not found")
    endif()
  endforeach()
endif()
