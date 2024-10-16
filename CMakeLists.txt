cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
project(crypt_tool)

include_directories(libs)

set(SOURCES
source/main.c
source/cryptkey.c
)


add_executable(crypt_tool ${SOURCES})
find_package(OpenSSL REQUIRED)
target_link_libraries(crypt_tool OpenSSL::Crypto)
