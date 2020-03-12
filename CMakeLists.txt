cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set (CMAKE_CXX g++)
set (CMAKE_PREFIX_PATH /usr/local/lib/cmake/)
project(app)
find_package(Poco REQUIRED COMPONENTS Util Net XML JSON Foundation)



SET(Poco_INCLUDE_DIRS "/usr/local/include/Poco")
SET(Json_INCLUDE_DIRS "/nlohmann")
link_directories(/build_libs/usr/local/lib)

include_directories (
    ${Poco_INCLUDE_DIRS}
    ${Json_INCLUDE_DIRS}

)

add_executable(pocotest pocotest.cpp)
target_link_libraries(pocotest PUBLIC Poco::Net Poco::Util Poco::JSON  Poco::XML Poco::JSON Poco::Foundation curl curlpp)

add_executable(jsontest jsontest.cpp)

add_executable(curlpptest curlpptest.cpp)
target_link_libraries(curlpptest PUBLIC curl curlpp)
