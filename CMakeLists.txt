cmake_minimum_required(VERSION 3.16)

project(jbgl C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(jbgl STATIC
    src/jbgl.c
 )

target_include_directories(jbgl
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb
)


find_package(glfw3 3.4 QUIET)

if (NOT glfw3_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        glfw3
        URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
    )

    FetchContent_MakeAvailable(glfw3)
endif()

find_package(OpenGL REQUIRED)

add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)

add_subdirectory(vendor/cglm EXCLUDE_FROM_ALL)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
    GIT_TAG VER-2-13-3
)

FetchContent_MakeAvailable(freetype)

target_link_libraries(jbgl
    PUBLIC
        freetype
        cglm_headers
        glfw
        glad
        OpenGL::GL
)



# Tests
add_executable(jbgl_test
    test/main.c
)

target_link_libraries(jbgl_test
    PRIVATE
        jbgl
)

set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

add_custom_command(TARGET jbgl_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCE_DIR}"
        "$<TARGET_FILE_DIR:jbgl_test>/resources"
)