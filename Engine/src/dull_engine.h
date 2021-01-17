#pragma once

#ifdef DE_EXPORTS_
	#define DE_API __declspec(dllexport)
#else
	#define DE_API __declspec(dllimport)
#endif

