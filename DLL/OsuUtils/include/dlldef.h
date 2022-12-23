#ifndef _DLL_DEF_H
#define _DLL_DEF_H

#ifdef OSUUTILS_EXPORTS
#define OSU_API __declspec(dllexport)
#else
#define OSU_API __declspec(dllimport)
#endif

#endif