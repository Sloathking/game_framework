cmake_minimum_required(VERSION 3.20)

# set the output for built objects this makes sure the dynamic library goes into build dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system dirs
#set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

# declare the project
project(game_framework)
set(CMAKE_CXX_STANDARD 20)

# Add CPM for package management
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.43.1/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=1c40fc102ce9625d7de7eb14f541cab30cc3138dca627f0b0ec40293ce6c2934
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# create list to iterate over
set(LIBS)

# SDL
CPMAddPackage("gh:libsdl-org/SDL#147a8ee")
list(APPEND LIBS SDL3::SDL3)

# SDL_tff
set(SDLTTF_VENDORED ON)
CPMAddPackage("gh:libsdl-org/SDL_ttf#a1ce367")
list(APPEND LIBS SDL3_ttf::SDL3_ttf)

## SDL_mixer
set(SDLMIXER_MIDI_NATIVE OFF)
set(SDLMIXER_GME OFF)
set(SDLMIXER_WAVPACK OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_MOD_XMP OFF)
set(SDLMIXER_OPUS OFF)
set(SDLMIXER_MP3_MPG123 OFF)
set(SDLMIXER_VORBIS_VORBISFILE OFF)
set(SDLMIXER_FLAC_LIBFLAC OFF)
set(SDLMIXER_VENDORED ON)   # tell SDL_mixer to build its own dependencies
CPMAddPackage("gh:libsdl-org/SDL_mixer#72a8186")
list(APPEND LIBS SDL3_mixer::SDL3_mixer)

# SDL_image
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPG OFF)
set(SDLIMAGE_WEBP OFF)
set(SDLIMAGE_PNG_LIBPNG OFF)
set(SDLIMAGE_VENDORED ON)
CPMAddPackage("gh:libsdl-org/SDL_image#bec9134")
list(APPEND LIBS SDL3_image::SDL3_image)

# DirectXShaderCompiler
#CPMAddPackage(
#        NAME DirectXShaderCompiler
#        VERSION 1.10.2605.37
#        URL "https://github.com/microsoft/DirectXShaderCompiler/releases/download/v1.10.2605.37/dxc_2026_08_11.zip"
#        URL_HASH SHA256=18da85ccac4d1736209bad960f0a124928a5c5a6046882e331c605d66744a889
#        DOWNLOAD_ONLY TRUE
#)

# SDL_shadercross
#set(DirectXShaderCompiler_ROOT "${PROJECT_SOURCE_DIR}/external/dxc")
#set(SDLSHADERCROSS_STATIC OFF)
#set(SDLSHADERCROSS_SHARED ON)
#set(SDLSHADERCROSS_CLI OFF)
#set(SDLSHADERCROSS_INSTALL_RUNTIME ON)
#set(DirectXShaderCompiler_ROOT "${DirectXShaderCompiler_SOURCE_DIR}"
#set(SDLSHADERCROSS_VENDORED ON)
#CPMAddPackage("gh:libsdl-org/SDL_shadercross#e55cf5e")
#list(APPEND LIBS SDL3_shadercross::SDL3_shadercross)

# define main
add_executable(${PROJECT_NAME} main.cpp)

#link CPM libs
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

# add Engine and Game dirs, so I don't have to make this CMAKE giant
add_subdirectory(Engine)
add_subdirectory(Game)
target_link_libraries(${PROJECT_NAME} PRIVATE Game)
