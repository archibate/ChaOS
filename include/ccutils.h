#pragma once

#ifdef __GNUC__
#define __ATTRIBUTE(...)	__attribute__((__VA_ARGS__))
#else
#define __ATTRIBUTE(...)	__declspec(__VA_ARGS__)
#endif

#define _WEAK			__ATTRIBUTE(weak)
#define _PACKED			__ATTRIBUTE(packed)
#define _UNUSED			__ATTRIBUTE(unused)
#define _NORETURN		__ATTRIBUTE(noreturn)
#define _ALIGNED(x)		__ATTRIBUTE(aligned(x))
#define _VOLATILE		__ATTRIBUTE(volatile)
#define _CONSTRUCTOR	__ATTRIBUTE(constructor)
#define _DESTRUCTOR		__ATTRIBUTE(destructor)
#define _SECTION(x)		__ATTRIBUTE(section(x))
#define _DLLIMPORT		__ATTRIBUTE(dllimport)
#define _DLLEXPORT		__ATTRIBUTE(dllexport)
#define _DEPRECATED		__ATTRIBUTE(deprecated)
#define _FASTCALL		__ATTRIBUTE(fastcall)
#define _STDCALL		__ATTRIBUTE(stdcall)
#define _PURE			__ATTRIBUTE(const)
#define _CDECL			__ATTRIBUTE(cdecl)
#define _NAKED			__ATTRIBUTE(naked)
#define _FORMAT(...)	__ATTRIBUTE(format(__VA_ARGS__))

#define PACKED			_PACKED
#define UNUSED			_UNUSED
#define VOLATILE		_VOLATILE
#define ALIGNED(x)		_ALIGNED(x)
#define NORETURN		_NORETURN
#define __section(x)	_SECTION(x)
#define __aligned(x)	_ALIGNED(x)
#ifndef __cdecl
#define __cdecl			_CDECL
#endif
#ifndef __stdcall
#define __stdcall		_STDCALL
#endif
#ifndef __fastcall
#define __fastcall		_FASTCALL
#endif

#if defined(__GNUC__)// && !defined(_MINGW) // TODO: check gcc version here
#define __BUILTIN(x)		__builtin_##x
#else
#define __BUILTIN(x)		/* nothing */
#endif

#if defined(__GNUC__) && !defined(_MINGW) // TODO: check gcc version here
#define UNREACHABLE()		__BUILTIN(unreachable())
#else
#define UNREACHABLE()		for (;;)
#endif

#ifdef __GNUC__
#define _EXPECT(x, y)		__BUILTIN(expect(x, y))
#else
#define _EXPECT(x, y)		(x)
#endif

#define likely(x)			(_EXPECT(!!(x), 1))
#define unlikely(x)			(_EXPECT(!!(x), 0))
