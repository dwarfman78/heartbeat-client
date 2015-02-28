cmake_minimum_required(VERSION 2.8.4)
project(heartbeat_client)
include_directories("${PROJECT_SOURCE_DIR}/extlibs/SFML-2.2/include")
#link_directories("${PROJECT_SOURCE_DIR}/../../dev/SFML-2.2/bin/lib")

link_directories("${PROJECT_SOURCE_DIR}/extlibs/SFML-2.2/build/lib")
link_directories("${CMAKE_FIND_ROOT_PATH}/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp sha256.cpp)
add_executable(heartbeat_client ${SOURCE_FILES})

target_link_libraries(heartbeat_client sfml-system)
target_link_libraries(heartbeat_client sfml-network)


