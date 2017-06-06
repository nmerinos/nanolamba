/*
NSP_BASE_API.H

Provides API functions

*/

#ifndef __NSP_BASE_API_H__
#define __NSP_BASE_API_H__

#ifdef _WIN32
#define EXPORT_DLL __declspec(dllexport) //For exporting to DLL 
#endif
#if defined(__linux__) || defined(__APPLE__)
#define EXPORT_DLL __attribute__((visibility("default")))
#endif

#include "nsp_base_exceptions.h"

#ifdef __cplusplus
extern "C"{ 
#endif

// function prefix: bs - Base System

/**
* \brief Convert error code to string
*
* This function returns one string for a specific error code.
*
* \code
*   int error_code = cc_ec_no_device_in_system;
*   char* error_string = bsGetErrorString(error_code);
* \endcode
*
* \param error_code - error code which defined in 'nsp_error_codes.h' [IN]
*
* \return
* Returns one numeric value of:
* - error string
* 
* \sa 
* \note_nsp_base_api
*/
EXPORT_DLL char* bsGetErrorString(int error_code);

#ifdef __cplusplus
}
#endif

#endif // __NSP_BASE_API_H__
