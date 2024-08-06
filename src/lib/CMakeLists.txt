file(GLOB sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/lib/*.c")
file(GLOB sources_cpp CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/lib/*.cpp")
file(GLOB headers CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")

add_library(emu STATIC ${sources} ${sources_cpp} ${headers})

target_include_directories(emu PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (WIN32)
  target_include_directories(emu PUBLIC "${PROJECT_SOURCE_DIR}/../windows_deps/sdl2/include")
  target_include_directories(emu PUBLIC ${PROJECT_SOURCE_DIR}/../windows_deps/sdl2_ttf/include)
else()
  target_include_directories(emu PUBLIC ${SDL2_INCLUDE_DIR})
endif()

target_link_libraries(emu PUBLIC ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} stdc++)
