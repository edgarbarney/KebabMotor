# FranticDreamer 2022

# ---
# Engine Files
# ---

# Header files
SET(GLOB ENGINE_HEADERFILES

	#Main
	Engine/Source/EngineMain.hpp
	
	#Utilities
    Engine/Source/Utilities/Utilities.hpp

	#Containers
	Engine/Source/Containers/*.hpp

	#Nodes
	Engine/Source/Nodes/*.hpp
   )

# Source files
FILE(GLOB ENGINE_SOURCEFILES

	#Main
    Engine/Source/EngineMain.cpp
	
	#Utilities
	Engine/Source/Utilities/Utilities.cpp

	#Nodes
	Engine/Source/Nodes/*.cpp

	#Containers
	Engine/Source/Containers/*.cpp
    )

include_directories("Engine/Source")