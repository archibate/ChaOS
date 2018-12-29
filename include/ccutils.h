#pragma once

#if defined __GNUC__
#define __DECLSPEC(...)	__attribute__((__VA_ARGS__))
#define __PRAGMA(...)	/* nothing */
#define __BUILTIN(x)	__builtin_##x
#elif defined MSC_VER || defined _MSC_VER
#ifndef MSC_VER
#define MSC_VER _MSC_VER
#endif
#define __DECLSPEC(...)	__declspec(__VA_ARGS__)
#define __PRAGMA(...)	__progma(__VA_ARGS__)
#define __BUILTIN(x)		/* nothing */
#else
#define __DECLSPEC(...)	/* nothing */
#define __BUILTIN(x)		/* nothing */
#endif

#ifdef _CC_HAS_WEAK
#define _WEAK			__DECLSPEC(weak)
#else
#define _WEAK			_WARNING("weak not impelemented on current compiler")
#endif
#define _ERROR(x)		__PRAGMA(error(x))
#define _WARNING(x)		__PRAGMA(warning(x))
#define _PACKED			__DECLSPEC(packed)
#define _UNUSED			__DECLSPEC(unused)
#define _NORETURN		__DECLSPEC(noreturn)
#define _ALIGNED(x)		__DECLSPEC(aligned(x))
#define _VOLATILE		__DECLSPEC(volatile)
#define _CONSTRUCTOR	__DECLSPEC(constructor)
#define _DESTRUCTOR		__DECLSPEC(destructor)
#define _SECTION(x)		__DECLSPEC(section(x))
#define _DLLIMPORT		__DECLSPEC(dllimport)
#define _DLLEXPORT		__DECLSPEC(dllexport)
#define _DEPRECATED		__DECLSPEC(deprecated)
#define _FASTCALL		__DECLSPEC(fastcall)
#define _STDCALL		__DECLSPEC(stdcall)
#define _PURE			__DECLSPEC(const)
#define _CDECL			__DECLSPEC(cdecl)
#define _NAKED			__DECLSPEC(naked)
#ifdef _CC_HAS_DECLSPEC_FORMAT
#define _FORMAT(...)	__DECLSPEC(format(__VA_ARGS__))
#else
#define _FORMAT(...)	__DECLSPEC(format(__VA_ARGS__))
#endif

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

#ifdef _CC_HAS_UNREACHABLE
#define UNREACHABLE()		__BUILTIN(unreachable())
#else
#define UNREACHABLE()		for (;;)
#endif

#ifdef _CC_HAS_EXPECT
#define _EXPECT(x, y)		__BUILTIN(expect(x, y))
#else
#define _EXPECT(x, y)		(x)
#endif

#define likely(x)			(_EXPECT(!!(x), 1))
#define unlikely(x)			(_EXPECT(!!(x), 0))
