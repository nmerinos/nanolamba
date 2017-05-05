import ctypes
import string
import sys

def calculate_color_data(pSpecCore,specData,wavelengthData,specSize):
    """
    Get color information of current spectrum data.

    * Calculate color information and returns in \p X, \p Y, \p Z, \p r, \p g, \p b,
    * \p x, \p y, \p z, \p cct.
    *
    * \code
    *   double  *spectrum_data;     // from csCalculateSpectrum() function
    *   double  *wavelength_data;   // from csCalculateSpectrum() function
    *   int     spectrum_length;    // from csCalculateSpectrum() function
    *   double  X, Y, Z;
    *   double  r, g, b;
    *   double  x, y, z;
    *   double  cct;
    *   int ret_value = acCalculateColor(spectrum_data, wavelength_data, spectrum_length,
    *                                   &X, &Y, &Z, &r, &g, &b, &x, &y, &z, &cct);
    * \endcode
    *
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
    """

    Color_Red    = ctypes.c_double()
    Color_Green  = ctypes.c_double()
    Color_Blue   = ctypes.c_double()
    large_X      = ctypes.c_double()
    large_Y      = ctypes.c_double()
    large_Z      = ctypes.c_double()
    small_x      = ctypes.c_double()
    small_y      = ctypes.c_double()
    small_z      = ctypes.c_double()
    CCT          = ctypes.c_double()

    ret = pSpecCore.acCalculateColor(specData, wavelengthData, specSize ,
                                               ctypes.byref(large_X),ctypes.byref(large_Y),ctypes.byref(large_Z),
                                              ctypes.byref(Color_Red),ctypes.byref(Color_Green),ctypes.byref(Color_Blue),
                                              ctypes.byref(small_x),ctypes.byref(small_y),ctypes.byref(small_z),
                                              ctypes.byref(CCT))

    if ret <=0:
        print "[PythonPrismError] Calculating Color Data Failed!"
        return (-1,-1,-1,-1,-1,-1,-1,-1,-1,-1);
    else:
        print "[PythonPrism] (R , G , B) : (",Color_Red.value, " , ", Color_Green.value, " , ", Color_Blue.value, " )"
        print "[PythonPrism] (X , Y , Z) : (",large_X.value, " , ", large_Y.value, " , ", large_Z.value, " )"
        print "[PythonPrism] (x , y , z) : (",small_x.value, " , ", small_y.value, " , ", small_z.value, " )"
        print "[PythonPrism] (CCT) : (",CCT.value, " )"
        return (Color_Red.value,Color_Green.value,Color_Blue.value,large_X.value,large_Y.value,large_Z.value,small_x.value,small_y.value,small_z.value,CCT.value)