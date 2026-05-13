cmake_minimum_required(VERSION 3.8)

project(Pelmishki)


add_subdirectory(SDL_game/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(SDL_game/SDL_image EXCLUDE_FROM_ALL)


add_executable(Pelmishki SDL_game/main.cpp)
target_link_libraries(Pelmishki PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)


if (WIN32)

    add_custom_command(TARGET Pelmishki POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:Pelmishki>)

    add_custom_command(TARGET Pelmishki POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3_image::SDL3_image>
    $<TARGET_FILE_DIR:Pelmishki>)

endif()