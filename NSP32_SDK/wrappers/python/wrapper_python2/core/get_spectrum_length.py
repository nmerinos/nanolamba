import ctypes
import string
import sys

def get_spectrum_length(pSpecCore):
    """Get Spectrum Length

    This function returns the size(length) of spectrum data.

    * \brief Get size of spectrum data
    *
    * This function returns the size(length) of spectrum data.
    *
    * \code
    *   int spectrum_length;
    *   spectrum_length = csGetSpectrumLength();
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric value of:
    * - spectrum data size(length) (>0)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    ret = pSpecCore.csGetSpectrumLength()

    if ret <=0:
        print "[PythonPrismError] Getting Spectrum Length Failed!"
        return ret
    else:
        print "[PythonPrism] SpectrumLength: ", ret
        return ret