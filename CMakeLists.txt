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

# copying shaders to build directory
configure_file("${CMAKE_SOURCE_DIR}/assets/shaders/vertex.vert" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/shaders/vertex.vert" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/shaders/fragment.frag" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/shaders/fragment.frag" COPYONLY)


# Copying all textures to build directory
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/2.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/2.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/4.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/4.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/8.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/8.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/16.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/16.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/32.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/32.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/64.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/64.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/128.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/128.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/256.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/256.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/512.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/512.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/1024.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/1024.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/2048.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/2048.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/4096.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/4096.png" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/assets/textures/8192.png" "${CMAKE_SOURCE_DIR}/build/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/textures/8192.png" COPYONLY)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)

add_library(Random-lib
    vendor/Random/RandomClass/src/Random.cpp
)

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/glad.c
    src/renderer/renderer.cpp
    src/renderer/Shader.cpp
    src/2048.cpp
    src/board.cpp
    vendor/stb_image/stb_image.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    src/
    include/
    vendor/glfw/include/
    vendor/glm/glm
    vendor/stb_image
    vendor/Random/RandomClass/src/
)

target_link_directories(${PROJECT_NAME} PUBLIC 
    vendor/glfw/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glm
    Random-lib
)