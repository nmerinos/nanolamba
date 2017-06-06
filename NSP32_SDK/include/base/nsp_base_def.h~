#ifndef	__NSP_BASE_DEF_H__
#define	__NSP_BASE_DEF_H__

#ifdef _WIN32
#pragma warning(disable:4819)
#pragma warning(disable:4251)
#endif

#include "nsp_base_types.h"
#include "nsp_error_codes.h"

#include <iostream>
using namespace std;

#ifdef _WIN32
    #define EXPORT_DLL __declspec(dllexport)
    //! this is standard machine precision for 32 bit floats
    #define MACHINE_PRECISION    5.96e-08
#elif defined(__linux__) || defined(__APPLE__)
    #include <stdint.h>
    #define EXPORT_DLL  __attribute__((dllexport))
    //#define HANDLE  int
    #define BOOL    bool
//    #define LARGE_INTEGER   int64_t
    #define DWORD   unsigned long 
    //! this is standard machine precision for 32 bit floats
    #define MACHINE_PRECISION    5.96e-08
#else
    #include <stdint.h>
    #define EXPORT_DLL  __attribute__((dllexport))
    #define HANDLE  int
    #define BOOL    bool
//    #define LARGE_INTEGER   int64_t
    #define DWORD   unsigned long 
    //! this is standard machine precision for 32 bit floats
    #define MACHINE_PRECISION    5.96e-08
#endif

#ifndef M_PI
#define M_PI        3.14159265358979323846  /* pi */
#endif

#define IS_NAN(x) (((x) < 0) == ((x) >= 0))

#ifdef __APPLE__
#define roundMac(x) (x<0?ceil((x)-0.5):floor((x)+0.5))
#else
#define round(x) (x<0?ceil((x)-0.5):floor((x)+0.5))
#endif

#define round_prec(x,y) (float) (floor(x*(1.0f/y) + 0.5)/(1.0f/y));
#if defined(__linux__) || defined(__APPLE__)
#define SLASH_CHAR		'/'
#define SLASH_STR		"/"
#endif // _LINUX
#ifdef _WIN32
#define SLASH_CHAR		'\\'
#define SLASH_STR		"\\"
#endif // _WIN32

#define CONTROLLER_BOARD_STM
#undef CONTROLLER_BOARD_STM

#define	RANGE_FROM_SATURATION			50
#define FILTER_VALUE_OF_SATURATION		DEVICE_MAX_FILTER_OUT - RANGE_FROM_SATURATION

//----------------------------------------------------------------------
#define AE_FUNC_PIXEL_VARIATION_SIZE	100
#define	AE_FUNC_SATURATION_LIMIT		DEVICE_MAX_FILTER_OUT-AE_FUNC_PIXEL_VARIATION_SIZE
#define	AE_FUNC_MESSAGE_LIGHT_TOO_LOW		-1
#define	AE_FUNC_MESSAGE_LIGHT_TOO_STRONG	-2

#ifndef	SENSOR_ID_STRING_LENGTH
#define	SENSOR_ID_STRING_LENGTH			26
#endif

#endif	 // __NSP_BASE_DEF_H__
