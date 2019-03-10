cmake_minimum_required(VERSION 3.5)

if (TARGET sml_spike_test)
    return()
endif (TARGET sml_spike_test)

project(sml_spike_test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)
list(APPEND ${PROJECT_NAME}_LIBS gtest_main gmock)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib/sml/include")

file(GLOB_RECURSE SOURCE_FILES
    "*.cpp"
    "*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
list(REVERSE ${PROJECT_NAME}_LIBS)
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})
