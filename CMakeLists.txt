cmake_minimum_required(VERSION 3.5)

project (bitblit)

find_package(SDL2 2 REQUIRED)

set(PROJECT_SOURCE_DIR src)

set(SOURCES
    src/main/main.c
    src/main/log.c
)

add_executable(bitblit ${SOURCES})

target_include_directories(bitblit
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(bitblit PRIVATE SDL2::SDL2-static)