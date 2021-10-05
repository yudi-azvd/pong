cmake_minimum_required(VERSION 3.5)

# Quem sabe dá alguma luz
# https://dane-bulat.medium.com/cmake-building-sfml-and-game-projects-on-linux-3947b3ba6e8

project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# try_compile(HAS_FS "${CMAKE_BINARY_DIR}/temp" 
# "${CMAKE_SOURCE_DIR}/tests/has_filesystem.cc" 
#             CMAKE_FLAGS -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED=ON
#             LINK_LIBRARIES stdc++fs)
# if(HAS_FS)
#     message(STATUS "Compiler has filesystem support")
# else()
# #   .... You could also try searching for boost::filesystem here.
#     message(FATAL_ERROR "Compiler is missing filesystem capabilities")
# endif(HAS_FS)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS OFF)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
# target_include_directories(
#   includes
#   PRIVATE
#   ${PROJECT_SOURCE_DIR}/src
# )

