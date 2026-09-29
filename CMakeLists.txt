cmake_minimum_required(VERSION 3.21)
project(vestSDK CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(simpleble CONFIG REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)

add_executable(vestSDK
    SimpleBLE_Test/src/main.cpp
    SimpleBLE_Test/src/network/bluetooth.cpp
    SimpleBLE_Test/src/network/websocket.cpp
    SimpleBLE_Test/src/storage/storage.cpp
)

target_include_directories(vestSDK PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleBLE_Test/src
)

target_link_libraries(vestSDK PRIVATE
    nlohmann_json::nlohmann_json
    simpleble::simpleble 
    ixwebsocket::ixwebsocket 
)

if(WIN32)
    target_link_libraries(vestSDK PRIVATE
        Bcrypt
        Crypt32
        Ws2_32
    )

    add_custom_command(TARGET vestSDK POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:vestSDK>
            $<TARGET_FILE_DIR:vestSDK>
        COMMAND_EXPAND_LISTS
    )
endif()