# FranticDreamer 2022

# ---
# Engine Libraries
# ---

# ---
# OpenGL
# ---

# Imgui needs this.
# Use SFML calls. Do not use OGL ones if you aren't 100% sure what you're doing.

find_package(OpenGL REQUIRED)
set (Libs_OGL opengl32)

# ---
# SFML
# ---

if (PROJECT_ARCH STREQUAL "x64")
	link_directories("Engine/Libraries/SFML/Win64/lib")
else()
	link_directories("Engine/Libraries/SFML/Win32/lib")
endif()

if (PROJECT_CONF STREQUAL "release")
	set(Libs_SFML sfml-main sfml-system sfml-window sfml-graphics)
else()
	set(Libs_SFML sfml-main-d sfml-system-d sfml-window-d sfml-graphics-d)
endif()

include_directories("Engine/Libraries/SFML/include")

# ---
# Dear ImGui
# ---

FILE(GLOB IMGUI_HEADERFILES
	Engine/Libraries/imgui/*.h
	Engine/Libraries/imgui/*.hpp
)

FILE(GLOB IMGUI_SOURCEFILES
	Engine/Libraries/imgui/*.cpp
)

FILE(GLOB IMGUI_SFML_HEADERFILES
	Engine/Libraries/imgui/ImGui-SFML/*.h
)

FILE(GLOB IMGUI_SFML_SOURCEFILES
	Engine/Libraries/imgui/ImGui-SFML/*.cpp
)

FILE(GLOB IMGUI_NODES_HEADERFILES
	Engine/Libraries/imgui/ImGui-Node-Editor/*.h
)

FILE(GLOB IMGUI_NODES_SOURCEFILES
	Engine/Libraries/imgui/ImGui-Node-Editor/*.cpp
)

include_directories("Engine/Libraries/imgui")
include_directories("Engine/Libraries/imgui/ImGui-SFML")
include_directories("Engine/Libraries/imgui/ImGui-Node-Editor")

add_library (dear_imgui STATIC ${IMGUI_SOURCEFILES} ${IMGUI_SFML_SOURCEFILES} ${IMGUI_NODES_SOURCEFILES})
target_link_libraries(dear_imgui ${Libs_OGL})

# ---
# NLOHMANN JSON
# ---

FILE(GLOB JSONLIB_HEADERFILES
	Engine/Libraries/json/json.hpp
)

