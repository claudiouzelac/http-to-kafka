INCLUDE_DIRECTORIES(.)
EXTERNALPROJECT_ADD(
  project_librdkafka
  GIT_REPOSITORY https://github.com/edenhill/librdkafka.git
  GIT_TAG 094ae5c44efd6b1468f1d219ea4fd93f0d0052fb
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/librdkafka
  CONFIGURE_COMMAND ./configure --prefix=${CMAKE_BINARY_DIR}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
)
EXTERNALPROJECT_ADD(
    rapidjson
    GIT_REPOSITORY git@github.com:miloyip/rapidjson.git
    GIT_TAG 879def80f2e466cdf4c86dc7e53ea2dd4cafaea0
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/rapidjson
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
EXTERNALPROJECT_ADD(
    cppnetlib
    URL http://storage.googleapis.com/cpp-netlib-downloads/0.11.1/cpp-netlib-0.11.1-final.tar.gz
    URL_HASH MD5=905887ca44af34f5d4befa0a74be128c
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/cpp-netlib
)
SET(LIB_DIR /usr/local/lib/)
SET(CPP_NETLIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/cpp-netlib)
SET(KAFKA_CPP_INC ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/librdkafka/src-cpp)
SET(RAPID_JSON_INC ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/rapidjson/include)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
ADD_EXECUTABLE(http-to-kafka main.cc)
INCLUDE_DIRECTORIES(${KAFKA_CPP_INC} ${CPP_NETLIB_HEADERS} ${RAPID_JSON_INC})
LINK_DIRECTORIES(
     ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/librdkafka/src
     ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/librdkafka/src-cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/gtest/DebugLibs
     ${LIB_DIR}
)
TARGET_LINK_LIBRARIES(http-to-kafka
    ${Boost_LIBRARIES}
    librdkafka.a
    librdkafka++.a
    libssl.a
    libcppnetlib-uri.a
    libcppnetlib-server-parsers.a
    libcppnetlib-client-connections.a
    crypto
)