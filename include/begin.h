#pragma once
#include <stdlib.h>

#ifdef WIN32
#define PUBLIC __declspec( dllexport )
#else
#define PUBLIC
#endif

