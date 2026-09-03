cmake_minimum_required(VERSION 3.20)
project(FlowsInGraphs)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")
add_library(graph_generator STATIC ${SOURCES})
target_include_directories(graph_generator PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_executable(graph-example examples/main.cpp)
target_link_libraries(graph-example PRIVATE 
    graph_generator
    MPI::MPI_CXX
    OpenMP::OpenMP_CXX)
