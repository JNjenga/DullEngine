#pragma once

#ifdef DE_EXPORTS_
    #ifdef _WIN32
	    #define DE_API __declspec(dllexport)
	#elif __linux__
	    #define DE_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _WIN32
	    #define DE_API __declspec(dllimport)
	#elif __linux__
	    #define DE_API
    #endif
#endif

