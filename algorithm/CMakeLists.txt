cmake_minimum_required(VERSION 3.25)
project(Algorithm)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(AlgKit_DIR "F:/0github/Project-Simulation/c++/algkit/install/lib/cmake/AlgKit")
find_package(AlgKit REQUIRED)

file(
  GLOB_RECURSE AlgorithmSources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(Algorithm ${AlgorithmSources})

target_link_libraries(Algorithm PRIVATE AlgKit::AlgKit)
target_include_directories(Algorithm PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(Algorithm PRIVATE cxx_std_20)

target_precompile_headers(Algorithm PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/precomp.h")
