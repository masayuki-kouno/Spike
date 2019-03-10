cmake_minimum_required(VERSION 3.5)

if (TARGET sml_spike)
    return()
endif (TARGET sml_spike)

project(sml_spike)

add_subdirectory(src)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/D_ENABLE_EXTENDED_ALIGNED_STORAGE>")
