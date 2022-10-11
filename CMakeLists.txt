# FranticDreamer 2022
# CMakeLists file for CMake Configuration

# Minimum is 3.21 because C++20
cmake_minimum_required (VERSION 3.21)

set (CMAKE_CXX_STANDARD 20) # Set C++20 Standard

set (CURDIR ${CMAKE_CURRENT_SOURCE_DIR})
set (copylibscriptdir ${CURDIR}/_External/CopyLibsUtil.exe)
file (TO_NATIVE_PATH ${copylibscriptdir} copylibscriptdir)

project ("KebabMotor")

set (PROJECT_GAME_NAME "MyGameName")

if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64 Bit
set (PROJECT_ARCH "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4) # 32 Bit
set (PROJECT_ARCH "x86")
endif()

string (TOLOWER ${CMAKE_BUILD_TYPE} LOWERCASE_BUILDTYPE)
if (LOWERCASE_BUILDTYPE MATCHES ".*debug") # Debug
set (PROJECT_CONF "debug")
message(STATUS "Configured Debug Build.")
else() # Release
set (PROJECT_CONF "release")
message(STATUS "Configured Release Build.")
endif()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Build/${PROJECT_CONF}_${PROJECT_ARCH})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Debug
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Windows only pre-processor defines
if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)

	# Unicode Program
	add_compile_definitions(_UNICODE UNICODE)
endif()

# Put shared libraries also in the EngineLibraries.cmake

include ("CmakeMacros.cmake")

include ("Files_EngineLibraries.cmake")
include ("Files_Engine.cmake")

include ("Files_GameLibraries.cmake")
include ("Files_Game.cmake")

include ("Files_Launcher.cmake")

#include ("Files_EditorLibraries.cmake")
include ("Files_Editor.cmake")

# Add engine library include directory for every project
# Maybe use target_include_directories for this too?
include_directories("Engine/Libraries")

# Engine DLL
add_library (KebabMotor_Engine SHARED ${ENGINE_SOURCEFILES})
target_compile_definitions(KebabMotor_Engine PRIVATE _KEBABMOTOR_ENGINE)
target_link_libraries(KebabMotor_Engine
	${Libs_SFML}
	dear_imgui
)
#target_include_directories(KebabMotor_Game PRIVATE "Engine/Libraries")
add_custom_command(TARGET KebabMotor_Engine POST_BUILD COMMAND 
	${copylibscriptdir} "Win32" ${PROJECT_ARCH} ${PROJECT_CONF}
)

# Game DLL
add_library (KebabMotor_Game SHARED ${GAME_SOURCEFILES})
target_compile_definitions(KebabMotor_Game PRIVATE _KEBABMOTOR_GAME)
target_link_libraries(KebabMotor_Game
	KebabMotor_Engine
	dear_imgui
)
target_include_directories(KebabMotor_Game PRIVATE "Game/Libraries")

# Launcher
add_executable (KebabMotor_Launcher ${LAUNCHER_SOURCEFILES})
target_compile_definitions(KebabMotor_Launcher PRIVATE _KEBABMOTOR_LAUNCHER)
target_link_libraries(KebabMotor_Launcher
	KebabMotor_Engine
	KebabMotor_Game
)
#target_include_directories(KebabMotor_Game PRIVATE "Launcher/Libraries")

#Set Launcher Executable output name to the game name 
set_target_properties(KebabMotor_Launcher PROPERTIES OUTPUT_NAME ${PROJECT_GAME_NAME})


# Editor
add_executable (KebabMotor_Editor ${EDITOR_SOURCEFILES})
target_compile_definitions(KebabMotor_Editor PRIVATE _KEBABMOTOR_EDITOR)
target_link_libraries(KebabMotor_Editor
	KebabMotor_Engine
	KebabMotor_Game
	${Libs_SFML}
	dear_imgui
)

#target_include_directories(KebabMotor_Game PRIVATE "Editor/Libraries")