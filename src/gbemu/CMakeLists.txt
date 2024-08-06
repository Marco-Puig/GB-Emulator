cmake_minimum_required(VERSION 3.10)

project(gbemu C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib)

set(MAIN_SOURCES
    main.cpp
    ../lib/emu.cpp 
    ../lib/cart.cpp
    ../lib/cpu.c
    ../lib/ppu.c
    ../lib/timer.c
    ../lib/bus.c
)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")

add_executable(gbemu ${HEADERS} ${MAIN_SOURCES})

target_link_libraries(gbemu emu)
target_include_directories(gbemu PUBLIC ${PROJECT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(gbemu ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

message(STATUS "SDL Libraries: ${SDL2_LIBRARIES} - ${SDL2_LIBRARY}")
message(STATUS "SDL TTF Libraries: ${SDL2_TTF_LIBRARIES} - ${SDL2_TTF_LIBRARY}")

install(TARGETS gbemu
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/fonts/NotoSansMono-Medium.ttf
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)

if (WIN32)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/lib/x64/SDL2.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x64/SDL2_ttf.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x64/zlib1.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x64/libfreetype-6.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
    else ()
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/lib/x86/SDL2.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x86/SDL2_ttf.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x86/zlib1.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/lib/x86/libfreetype-6.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
    endif ()
endif ()
