# FranticDreamer 2022

# ---
# Editor Files
# ---

# Header files
SET(GLOB EDITOR_HEADERFILES

	#Main
	Editor/Source/EditorMain.hpp

	#Base Nodeboard
	Editor/Source/Nodeboard/Nodeboard.hpp
	)

# Source files
FILE(GLOB EDITOR_SOURCEFILES

	#Main
    Editor/Source/EditorMain.cpp

	#Base Nodeboard
    Editor/Source/Nodeboard/Nodeboard.cpp
    )