# FranticDreamer 2022

# ---
# Engine Files
# ---

# Header files
SET(GLOB ENGINE_HEADERFILES

	#Main
	Engine/Source/EngineMain.hpp
	
	#Utilities
    Engine/Source/Core/Utilities/Utilities.hpp

	#Containers
	Engine/Source/Core/Containers/*.hpp

	#Nodes
	Engine/Source/Nodes/*.hpp
   )

# Source files
FILE(GLOB ENGINE_SOURCEFILES

	#Main
    Engine/Source/EngineMain.cpp
	
	#Utilities
	Engine/Source/Core/Utilities/Utilities.cpp

	#Containers
	Engine/Source/Core/Containers/*.cpp
	
	#Nodes
	Engine/Source/Nodes/*.cpp
    )

include_directories("Engine/Source")