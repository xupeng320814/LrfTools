cmake_minimum_required(VERSION 3.15...4.0)
project(LrfTools VERSION 1.0
                  DESCRIPTION "LrfTools Projects"
                  LANGUAGES CXX)

add_library(LrfToolsTime STATIC ${CMAKE_SOURCE_DIR}/src/Lt_time.cpp)
target_include_directories(LrfToolsTime PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(LrfToolsTime PRIVATE $<$<CONFIG:Release>:/O2>)

add_library(LrfToolsClass STATIC ${CMAKE_SOURCE_DIR}/src/Lt_class.cpp)
target_include_directories(LrfToolsClass PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(LrfToolsClass PRIVATE $<$<CONFIG:Release>:/O3>)

add_executable(LrfToolsTest ${CMAKE_SOURCE_DIR}/apps/main.cpp)
target_link_libraries(LrfToolsTest PUBLIC LrfToolsClass LrfToolsTime)
target_include_directories(LrfToolsTest PUBLIC ${CMAKE_SOURCE_DIR}/include)
#因为Debug 会和O3/O2优化冲突，需要特别指定当Release时才进行O3优化
target_compile_options(LrfToolsTest PRIVATE $<$<CONFIG:Release>:/O3>)