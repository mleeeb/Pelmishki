cmake_minimum_required(VERSION 3.8)

project(Pelmishki)


add_subdirectory(SDL_game/Resourses/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(SDL_game/Resourses/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(SDL_game/Resourses/SDL_ttf EXCLUDE_FROM_ALL)


add_executable(Pelmishki 
"SDL_game/Source Files/main.cpp"
"SDL_game/Source Files/Game.cpp"
"SDL_game/Source Files/PlayerHUD.cpp"
"SDL_game/Source Files/Player.cpp"
"SDL_game/Source Files/Health.cpp"

"SDL_game/Header Files/Game.h"
"SDL_game/Header Files/PlayerHUD.h"
"SDL_game/Header Files/Player.h"
"SDL_game/Header Files/Health.h"
)


target_include_directories(Pelmishki PRIVATE 
"SDL_game/Header Files"
"SDL_game/Source Files"
)


target_link_libraries(Pelmishki PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
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

    add_custom_command(TARGET Pelmishki POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3_ttf::SDL3_ttf>
    $<TARGET_FILE_DIR:Pelmishki>)

endif()