cmake_minimum_required(VERSION 3.15)
project(Pelmishki)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку FindPkgConfig для автоматического поиска библиотек
include(FindPkgConfig)

# Поиск SDL3 библиотек в стандартных системных путях
# (без жесткой привязки к локальной папке)
find_package(SDL3 CONFIG QUIET)
find_package(SDL3_image CONFIG QUIET) 
find_package(SDL3_ttf CONFIG QUIET)

# Если CONFIG режим не сработал, пробуем pkg-config
if(NOT SDL3_FOUND)
    pkg_check_modules(SDL3 REQUIRED sdl3)
    pkg_check_modules(SDL3_image REQUIRED SDL3_image)
    pkg_check_modules(SDL3_ttf REQUIRED SDL3_ttf)
endif()

# Альтернативный ручной поиск для Linux/macOS
if(NOT SDL3_FOUND AND NOT WIN32)
    find_path(SDL3_INCLUDE_DIR SDL3/SDL.h)
    find_library(SDL3_LIBRARY SDL3)
    find_path(SDL3_image_INCLUDE_DIR SDL3_image/SDL_image.h)
    find_library(SDL3_image_LIBRARY SDL3_image)
    find_path(SDL3_ttf_INCLUDE_DIR SDL3_ttf/SDL_ttf.h)
    find_library(SDL3_ttf_LIBRARY SDL3_ttf)
endif()

# Собираем все исходные файлы (используем GLOB_RECURSE но с предупреждением)
file(GLOB_RECURSE GAME_SRC 
    "SDL_game/Source Files/*.cpp"
)

# Добавляем предупреждение, если не найдены файлы
if(NOT GAME_SRC)
    message(WARNING "No source files found! Check path: SDL_game/Source Files/*.cpp")
    # Пробуем альтернативные пути
    file(GLOB_RECURSE GAME_SRC 
        "Source Files/*.cpp"
        "src/*.cpp"
        "*.cpp"
    )
endif()

add_executable(Pelmishki ${GAME_SRC})

# Добавляем пути к заголовочным файлам
target_include_directories(Pelmishki PRIVATE 
    "SDL_game/Header Files"
    "Header Files"
    "include"
)

# Линкуем библиотеки (универсальный способ)
if(SDL3_FOUND)
    target_link_libraries(Pelmishki PRIVATE SDL3::SDL3)
elseif(SDL3_LIBRARY)
    target_include_directories(Pelmishki PRIVATE ${SDL3_INCLUDE_DIR})
    target_link_libraries(Pelmishki PRIVATE ${SDL3_LIBRARY})
elseif(PKG_CONFIG_FOUND)
    target_link_libraries(Pelmishki PRIVATE ${SDL3_LIBRARIES})
    target_include_directories(Pelmishki PRIVATE ${SDL3_INCLUDE_DIRS})
endif()

if(SDL3_image_FOUND)
    target_link_libraries(Pelmishki PRIVATE SDL3_image::SDL3_image)
elseif(SDL3_image_LIBRARY)
    target_include_directories(Pelmishki PRIVATE ${SDL3_image_INCLUDE_DIR})
    target_link_libraries(Pelmishki PRIVATE ${SDL3_image_LIBRARY})
endif()

if(SDL3_ttf_FOUND)
    target_link_libraries(Pelmishki PRIVATE SDL3_ttf::SDL3_ttf)
elseif(SDL3_ttf_LIBRARY)
    target_include_directories(Pelmishki PRIVATE ${SDL3_ttf_INCLUDE_DIR})
    target_link_libraries(Pelmishki PRIVATE ${SDL3_ttf_LIBRARY})
endif()
# Копирование DLL и ресурсов после сборки (только для Windows)
if(WIN32)
    # Пытаемся найти DLL в стандартных местах
    find_file(SDL3_DLL NAMES SDL3.dll PATHS
        ${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3-3.4.10/lib/x64
        ${CMAKE_SOURCE_DIR}/SDL3.dll
        ${CMAKE_PREFIX_PATH}/bin
        $ENV{VCPKG_ROOT}/installed/x64-windows/bin
        "C:/SDL3/lib/x64"
    )
    
    find_file(SDL3_image_DLL NAMES SDL3_image.dll PATHS
        ${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_image-3.4.4/lib/x64
        ${CMAKE_SOURCE_DIR}/SDL3_image.dll
        $ENV{VCPKG_ROOT}/installed/x64-windows/bin
        "C:/SDL3_image/lib/x64"
    )
    
    find_file(SDL3_ttf_DLL NAMES SDL3_ttf.dll PATHS
        ${CMAKE_SOURCE_DIR}/SDL_game/Resourses/SDL3_ttf-3.2.2/lib/x64
        ${CMAKE_SOURCE_DIR}/SDL3_ttf.dll
        $ENV{VCPKG_ROOT}/installed/x64-windows/bin
        "C:/SDL3_ttf/lib/x64"
    )
    
    # Копирование найденных DLL
    if(SDL3_DLL)
        add_custom_command(TARGET Pelmishki POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL3_DLL}"
                $<TARGET_FILE_DIR:Pelmishki>
        )
    else()
        message(WARNING "SDL3.dll not found! Please install SDL3 properly.")
    endif()
    
    if(SDL3_image_DLL)
        add_custom_command(TARGET Pelmishki POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL3_image_DLL}"
                $<TARGET_FILE_DIR:Pelmishki>
        )
    endif()
    
    if(SDL3_ttf_DLL)
        add_custom_command(TARGET Pelmishki POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL3_ttf_DLL}"
                $<TARGET_FILE_DIR:Pelmishki>
        )
    endif()
    
    # Копирование папки assets
    if(EXISTS "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/assets")
        add_custom_command(TARGET Pelmishki POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
                $<TARGET_FILE_DIR:Pelmishki>/assets
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/SDL_game/Resourses/assets"
                "$<TARGET_FILE_DIR:Pelmishki>/assets"
        )
    elseif(EXISTS "${CMAKE_SOURCE_DIR}/assets")
        add_custom_command(TARGET Pelmishki POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory
                $<TARGET_FILE_DIR:Pelmishki>/assets
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/assets"
                "$<TARGET_FILE_DIR:Pelmishki>/assets"
        )
    else()
        message(WARNING "Assets folder not found!")
    endif()
endif()

# Устанавливаем стартовый проект
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Pelmishki)

# Вывод информации о найденных библиотеках
message(STATUS "SDL3 found: ${SDL3_FOUND}")
message(STATUS "SDL3_image found: ${SDL3_image_FOUND}")
message(STATUS "SDL3_ttf found: ${SDL3_ttf_FOUND}")
