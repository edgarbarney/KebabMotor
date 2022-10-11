// FranticDreamer 2022
// Platform Specific Definitions

#pragma once

#if defined _KEBABMOTOR_ENGINE


#define GAME_DLLEXP		__declspec( dllimport )

#define ENG_DLLEXP		__declspec( dllexport )
#define ENG_EXTERN		extern
#define ENG_EXPONLY		


#elif defined _KEBABMOTOR_LAUNCHER


#define GAME_DLLEXP __declspec( dllimport )

#define ENG_DLLEXP  __declspec( dllimport )
#define ENG_EXTERN 
#define ENG_EXPONLY	__declspec( dllimport )


#elif defined _KEBABMOTOR_GAME


#define GAME_DLLEXP __declspec( dllexport )

#define ENG_DLLEXP  __declspec( dllimport )
#define ENG_EXTERN 
#define ENG_EXPONLY	__declspec( dllimport )


#elif defined _KEBABMOTOR_EDITOR


#define GAME_DLLEXP __declspec( dllimport )

#define ENG_DLLEXP  __declspec( dllimport )
#define ENG_EXTERN 
#define ENG_EXPONLY	__declspec( dllimport )


#endif

// For Flat Defnitions. Please use with caution.
#define SHR_DLLEXP __declspec( dllexport )
#define SHR_DLLIMP __declspec( dllimport )

