set(TEST_NAME CloudStorageTest)
project(${TEST_NAME})

if (BUILD_TEST)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        )
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    find_package(CURL REQUIRED)

    add_executable(GoogleDriveTest upload.cpp)
    target_link_libraries(GoogleDriveTest gtest_main cloud_storage CURL::libcurl)
    gtest_discover_tests(GoogleDriveTest)
endif()
