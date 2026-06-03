cmake_minimum_required(VERSION 3.8)
project(Pelmishki)

set(CMAKE_CXX_STANDARD 17)

# Пути к библиотекам
set(SDL3_DIR "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3-3.4.10/cmake")
set(SDL3_image_DIR "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_image-3.4.4/cmake")
set(SDL3_ttf_DIR "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_ttf-3.2.2/cmake")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# Собираем все исходные файлы
file(GLOB_RECURSE GAME_SRC 
    "SDL_game/Source Files/*.cpp"
)

add_executable(Pelmishki ${GAME_SRC})

# Добавляем пути к заголовочным файлам
target_include_directories(Pelmishki PRIVATE 
    "SDL_game/Header Files"
)

# Линкуем библиотеки
target_link_libraries(Pelmishki PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)

# Копирование DLL и ресурсов после сборки
if(WIN32)
    # Копирование DLL из lib/x64
    add_custom_command(TARGET Pelmishki POST_BUILD
        COMMENT "Copying SDL3.dll..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3-3.4.10/lib/x64/SDL3.dll"
            $<TARGET_FILE_DIR:Pelmishki>
        
        COMMENT "Copying SDL3_image.dll..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_image-3.4.4/lib/x64/SDL3_image.dll"
            $<TARGET_FILE_DIR:Pelmishki>
        
        COMMENT "Copying SDL3_ttf.dll..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_ttf-3.2.2/lib/x64/SDL3_ttf.dll"
            $<TARGET_FILE_DIR:Pelmishki>
        
        COMMENT "Copying assets folder..."
        COMMAND ${CMAKE_COMMAND} -E remove_directory
            $<TARGET_FILE_DIR:Pelmishki>/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/assets"
            "$<TARGET_FILE_DIR:Pelmishki>/assets"
        
        COMMENT "All files copied successfully!"
    )
endif()

# Устанавливаем стартовый проект
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Pelmishki)