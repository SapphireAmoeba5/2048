cmake_minimum_required(VERSION 3.21.3 FATAL_ERROR)

project(2048)

if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)      # 64 Bit mode
    if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/x64/release")
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/x64/debug")    
    endif()


elseif(${CMAKE_SIZEOF_VOID_P} EQUAL 4)  # 32 Bit mode
    if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/x86/release")
    elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/x86/debug")    
    endif()
endif()

add_compile_options(
    -Wall
    -lpthread

    $<$<CONFIG:Release>:-O2>

    $<$<CONFIG:Debug>:-O0>
)

 add_link_options(
     $<$<CONFIG:Release>:-s>
)


add_subdirectory(vendor/glfw)
add_executable(${PROJECT_NAME} src/main.cpp src/glad.c)

target_include_directories(${PROJECT_NAME}
PUBLIC
    src/
    include/
    vendor/glfw/include/
)

target_link_directories(${PROJECT_NAME}
    PUBLIC vendor/glfw/src
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    glfw
)