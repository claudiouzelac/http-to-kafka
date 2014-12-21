cmake_minimum_required(VERSION 2.8)
ENABLE_TESTING()

EXTERNALPROJECT_ADD(
    googletest
    GIT_REPOSITORY git clone https://chromium.googlesource.com/external/googletest
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/gtest
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)

EXTERNALPROJECT_ADD(
    fakeit
    GIT_REPOSITORY git@github.com:eranpeer/FakeIt.git
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/fakeit
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
)
SET(GOOGLE_TEST_INC ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/gtest/include)
SET(FAKE_IT_INC ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/fakeit/include)
SET(FAKE_IT_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/fakeit/config/gtest)
include_directories(. ${GOOGLE_TEST_INC} ${FAKE_IT_INC} ${FAKE_IT_CONFIG})
add_executable (http-kafka-tests tests.cc)
add_dependencies(http-kafka-tests googletest fakeit)
target_link_libraries(http-kafka-tests
    ${Boost_LIBRARIES}
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/gtest/libgtest.a
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/gtest/libgtest_main.a
)
add_test(http-kafka-tests ${CMAKE_CURRENT_BINARY_DIR}/http-kafka-tests)