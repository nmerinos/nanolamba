import ctypes
import string
import sys

def calculate_spectrum(pSpecCore,filter_data,shutter_speed):
    """Calculate Spectrum

    * This function returns a calculated spectrum and wavelength data with input filter data.

    * \brief Calculate spectrum
    *
    * This function returns a calculated spectrum and wavelength data with input filter data.
    *
    * \code
    *   int cur_ss = 50;
    *   double filter_data[SENSOR_DATA_SIZE];
    *   // acquire raw filter data from device(sensor) with shutter speed 'cur_ss'
    *
    *   // get spectrum length
    *   int spectrum_length = csGetSpectrumLength();
    *   double* spectrum_data = (double*)malloc(sizeof(double)*spectrum_length);
    *   double* wavelength_data = (double*)malloc(sizeof(double)*spectrum_length);
    *   int ret_value = csCalculateSpectrum(filter_data, cur_ss, spectrum_data, wavelength_data );
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric value of:
    * - spectrum data size(length) (>0)
    """

    specDataBuffer = ctypes.c_double * pSpecCore.csGetSpectrumLength()
    wavelengthDataBuffer = ctypes.c_double * pSpecCore.csGetSpectrumLength()
    specData = specDataBuffer()
    wavelengthData = wavelengthDataBuffer()

    ret = pSpecCore.csCalculateSpectrum(filter_data,shutter_speed, ctypes.byref(specData),ctypes.byref(wavelengthData))

    if ret <=0:
        print "[PythonPrismError] Calculating Spectrum Data Failed!"
        return (-1,-1,-1)
    else:
        print "[PythonPrism] Successfully Calculated Spectrum "
        return (ret,specData,wavelengthData)