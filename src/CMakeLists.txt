cmake_minimum_required(VERSION 2.8)
INCLUDE_DIRECTORIES(.)
SET(Boost_FIND_REQUIRED TRUE)
SET(Boost_USE_MULTITHREADED TRUE)
FIND_PACKAGE(Boost REQUIRED COMPONENTS
	iostreams
	filesystem
	date_time
	system
	program_options
	atomic
	chrono
	thread
)
ADD_DEFINITIONS(-DBoost_USE_STATIC_LIBS=ON)
EXTERNALPROJECT_ADD(
  librdkafka
  GIT_REPOSITORY https://github.com/edenhill/librdkafka.git
  GIT_TAG 094ae5c44efd6b1468f1d219ea4fd93f0d0052fb
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/librdkafka
  CONFIGURE_COMMAND ./configure --prefix=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install 
)
EXTERNALPROJECT_ADD(
  rapidjson
  GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
  GIT_TAG 879def80f2e466cdf4c86dc7e53ea2dd4cafaea0
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/rapidjson
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
EXTERNALPROJECT_ADD(
  cppnetlib
  GIT_REPOSITORY https://github.com/cpp-netlib/cpp-netlib.git
  GIT_TAG 9f123b3459e23eb0cba22050b7058191b631047a
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/cpp-netlib
  INSTALL_COMMAND ""
)
SET(CPP_NETLIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/cpp-netlib)
SET(KAFKA_CPP_INC ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/librdkafka/src-cpp)
SET(RAPID_JSON_INC ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/rapidjson/include)
ADD_EXECUTABLE(http-to-kafka main.cc)
ADD_DEPENDENCIES(http-to-kafka cppnetlib rapidjson librdkafka)
INCLUDE_DIRECTORIES(${KAFKA_CPP_INC} ${CPP_NETLIB_HEADERS} ${RAPID_JSON_INC})
LINK_DIRECTORIES(
     ${CMAKE_INSTALL_PREFIX}/lib
)
TARGET_LINK_LIBRARIES(http-to-kafka
    ${Boost_LIBRARIES}
    librdkafka.a
    librdkafka++.a
    libssl.a
    ${CRYPTO_LIBRARIES}
)