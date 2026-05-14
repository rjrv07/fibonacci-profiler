cmake_minimum_required(VERSION 4.3.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        sc
        GIT_REPOSITORY https://github.com/roelofrossouw/simply-cpp.git
        GIT_TAG origin/main # Or a specific tag to stay stable #
        GIT_SHALLOW TRUE
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(sc)

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

FetchContent_Declare(
        matplotlib_cpp
        GIT_REPOSITORY https://github.com/lava/matplotlib-cpp
        GIT_TAG master
)
FetchContent_MakeAvailable(matplotlib_cpp)

if (APPLE)
        execute_process(COMMAND sed -i ""
                "/select_npy_type<long long>/d"
                "${matplotlib_cpp_SOURCE_DIR}/matplotlibcpp.h")
        execute_process(COMMAND sed -i ""
                "/select_npy_type<unsigned long long>/d"
                "${matplotlib_cpp_SOURCE_DIR}/matplotlibcpp.h")
endif ()

project(benchmark)
add_executable(${PROJECT_NAME} benchmark.cpp)
target_link_libraries(${PROJECT_NAME} sc-timer)

project(verify)
add_executable(${PROJECT_NAME} verify.cpp)
target_link_libraries(${PROJECT_NAME} sc-timer)

project(plot)
add_executable(${PROJECT_NAME} plot.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${matplotlib_cpp_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} matplotlib_cpp sc-timer)
