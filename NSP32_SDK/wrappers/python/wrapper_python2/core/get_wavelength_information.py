import ctypes
import string
import sys

def get_wavelength_information(pSpecCore):
    """Calculate Spectrum

     This function returns wavelength range information for spectrum data.

    * \brief Get wavelength information data.
    *
    * This function returns wavelength range information for spectrum data.
    *
    * \code
    *   double start_wavelength, end_wavelength, wavelength_interval;
    *   int ret_val = csGetWavelengthInfo(&start_wavelength, &end_wavelength, &wavelength_interval);
    * \endcode
    *
    * \param start_wavelength - double pointer to start wavelength [OUT]
    * \param end_wavelength - double pointer to end wavelength [OUT]
    * \param wavelength_interval - double pointer to wavelength interval[OUT]
    *
    * \return
    * Returns one numeric value of NSP_RETURN_VALUE_SUCCESS.
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    Start_Wavelength= ctypes.c_double()
    End_Wavelength= ctypes.c_double()
    Interval_Wavelength= ctypes.c_double()

    ret = pSpecCore.csGetWavelengthInfo(ctypes.byref(Start_Wavelength),ctypes.byref(End_Wavelength),ctypes.byref(Interval_Wavelength))

    if ret <=0:
        print "[PythonPrismError] Getting Wavelength Information Failed!"
        return (-1,-1,-1)
    else:
        print "[PythonPrism] (StartWL, EndWL , IntervalWL) : (",Start_Wavelength.value, " , ", End_Wavelength.value, " , ", Interval_Wavelength.value, " )"
        return (Start_Wavelength, End_Wavelength, Interval_Wavelength)