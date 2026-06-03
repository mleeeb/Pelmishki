cmake_minimum_required(VERSION 3.8)
project(Pelmishki)

set(CMAKE_CXX_STANDARD 17)


set(SDL3_DIR "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3-3.4.10/cmake")
set(SDL3_image_DIR "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_image-3.4.4/cmake")
set(SDL3_ttf_DIR "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_ttf-3.2.2/cmake")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

file(GLOB_RECURSE GAME_SRC 
    "SDL_game/Source Files/*.cpp"
)

add_executable(Pelmishki ${GAME_SRC})

target_include_directories(Pelmishki PRIVATE 
    "SDL_game/Header Files"
)

target_link_libraries(Pelmishki PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)

if(WIN32)
    add_custom_command(TARGET Pelmishki POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_DIR}/../bin/SDL3.dll"
            $<TARGET_FILE_DIR:Pelmishki>
    )
    add_custom_command(TARGET Pelmishki POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_image_DIR}/../bin/SDL3_image.dll"
            $<TARGET_FILE_DIR:Pelmishki>
    )
    add_custom_command(TARGET Pelmishki POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_ttf_DIR}/../bin/SDL3_ttf.dll"
            $<TARGET_FILE_DIR:Pelmishki>
    )
endif()
if(WIN32)
    add_custom_command(TARGET Pelmishki POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_DIR}/../bin/SDL3.dll"
            $<TARGET_FILE_DIR:Pelmishki>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_image_DIR}/../bin/SDL3_image.dll"
            $<TARGET_FILE_DIR:Pelmishki>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_ttf_DIR}/../bin/SDL3_ttf.dll"
            $<TARGET_FILE_DIR:Pelmishki>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_image_DIR}/../bin/libpng16.dll"
            $<TARGET_FILE_DIR:Pelmishki>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL3_image_DIR}/../bin/zlib.dll"
            $<TARGET_FILE_DIR:Pelmishki>
    )
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Pelmishki)