cmake_minimum_required(VERSION 3.21)
project(SimpleBLE_Test CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(simpleble CONFIG REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)

add_executable(SimpleBLE_Test 
    SimpleBLE_Test/src/main.cpp
    SimpleBLE_Test/src/network/bluetooth.cpp
    SimpleBLE_Test/src/network/websocket.cpp
    SimpleBLE_Test/src/storage/storage.cpp
)

target_include_directories(SimpleBLE_Test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleBLE_Test/src
)

target_link_libraries(SimpleBLE_Test PRIVATE
    nlohmann_json::nlohmann_json
    simpleble::simpleble 
    ixwebsocket::ixwebsocket 
)

if(WIN32)
    target_link_libraries(SimpleBLE_Test PRIVATE 
        Bcrypt
        Crypt32
        Ws2_32
    )
endif()