import ctypes
import string
import sys

def get_resolution(pSpecCore):
    """Calculate Spectrum

    This function returns spectrum resolution information.

    * \brief Get spectrum resolution.
    *
    * This function returns spectrum resolution information.
    *
    * \code
    *   double spectrum_resolution;
    *   int ret_val = csGetResolution(&spectrum_resolution);
    * \endcode
    *
    * \param spectrum_resolution - double pointer to spectrum resolution [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """


    resolution = ctypes.c_double()

    ret = pSpecCore.csGetResolution(ctypes.byref(resolution))

    if ret <=0:
        print ("[PythonPrismError] Getting Resolution Failed!")
        return -1
    else:
        print ("[PythonPrism] Resolution:  ", resolution.value)
        return resolution.value