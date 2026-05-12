cmake_minimum_required(VERSION 3.8)

project(Pelmishki)

add_subdirectory(SDL_game/SDL3)
add_executable(Pelmishki SDL_game/main.cpp)
target_link_libraries(Pelmishki PRIVATE SDL3::SDL3)

if (WIN32)
    add_custom_command(TARGET Pelmishki POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:Pelmishki>)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Pelmishki PROPERTY CXX_STANDARD 20)
endif()
