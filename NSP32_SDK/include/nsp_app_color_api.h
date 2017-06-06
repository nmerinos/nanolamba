/*
NSP_APP_COLOR_API.H

Provides API functions

*/

#ifndef __NSP_APP_COLOR_API_H__
#define __NSP_APP_COLOR_API_H__

#ifdef _WIN32
#define EXPORT_DLL __declspec(dllexport) //For exporting to DLL 
#endif
#if defined(__linux) || defined(__APPLE__) || defined(__CYGWIN__)
#define EXPORT_DLL __attribute__((visibility("default")))
#endif


#ifdef __cplusplus
extern "C"{ 
#endif

// function prefix: ac - Application Color

/**
* \brief Initialize color API to calculate color information.
*
* Initialize C API to calculate color information.
*
* \param void
*
* \return
* Returns one numeric value as below:
* - NSP_RETURN_VALUE_SUCCESS (1)
* - NSP_RETURN_VALUE_FAILURE (-1)
* - cc_ec_fail_to_initialize_color_object
*
* \note_app_color_api_initialize
* 
* \sa acFinalize
*/
EXPORT_DLL  int acInitialize(void);

/**
* \brief Finalize color API.
*
* Finalize C API for color application.
*
* \param void
*
* \return
* Returns one numeric value:
* - NSP_RETURN_VALUE_SUCCESS (1)
*
* \note_app_color_api_finalize
* 
* \sa acInitialize
*/
EXPORT_DLL  int acFinalize(void);

/**
* \brief Get color information of current spectrum data.
*
* Calculate color information and returns in \p X, \p Y, \p Z, \p r, \p g, \p b,
* \p x, \p y, \p z, \p cct.
*
* \code
*	double	*spectrum_data;		// from csCalculateSpectrum() function
*	double	*wavelength_data;	// from csCalculateSpectrum() function
*	int		spectrum_length;	// from csCalculateSpectrum() function
*   double	X, Y, Z;
*   double	r, g, b;
*   double	x, y, z;
*	double	cct;
*   int ret_value = acCalculateColor(spectrum_data, wavelength_data, spectrum_length,
*									&X, &Y, &Z, &r, &g, &b, &x, &y, &z, &cct);
* \endcode

* \param spectrum - Spectrum data [IN]
* \param wavelength - Wavelength data [IN]
* \param spectrum_length - Spectrum length [IN]
* \param X - Pointer to a double which the numerical value for color (X) is returned [OUT]
* \param Y - Pointer to a double which the numerical value for color (Y) is returned [OUT]
* \param Z - Pointer to a double which the numerical value for color (Z) is returned [OUT]
* \param r - Pointer to a double which the numerical value for color (R) is returned [OUT]
* \param g - Pointer to a double which the numerical value for color (G) is returned [OUT]
* \param b - Pointer to a double which the numerical value for color (B) is returned [OUT]
* \param x - Pointer to a double which the numerical value for color (x) is returned [OUT]
* \param y - Pointer to a double which the numerical value for color (y) is returned [OUT]
* \param z - Pointer to a double which the numerical value for color (z) is returned [OUT]
* \param cct - Pointer to a double which the numerical value for CCT is returned [OUT]
*
* \return
* - NSP_RETURN_VALUE_FAILURE
* - NSP_RETURN_VALUE_SUCCESS
* - cc_ec_color_object_is_null
* - cc_ec_memory_for_spectrum_data_buffer_is_null
* - cc_ec_memory_for_wavelength_data_buffer_is_null
* \note_app_color_api_calc_color
* 
* \sa csGetSpectrumLength, csCalculateSpectrum
*/
EXPORT_DLL int acCalculateColor(double* spectrum,  double* wavelength, int spectrum_length, double* X, double* Y, double* Z, double* r, double* g, double* b, double* x, double*y, double* z, double* cct);

#ifdef __cplusplus
}
#endif

#endif // __NSP_APP_COLOR_API_H__
