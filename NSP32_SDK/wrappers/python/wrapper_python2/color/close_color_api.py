import sys
import os
import ctypes


def close_color_api(pSpecCore):
    """Closing Color API

    *This function will close color API.

    * \brief Finalize color API.
    *
    * Finalize C API for color application.
    *
    * \param void
    *
    * \return
    * Returns one numeric value:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    """

    ret = pSpecCore.acFinalize()

    if ret <=0:
        print "[PythonPrismError] Color API Closing Failed!"
        return -1;
    else:
        print "[PythonPrism] Color API Closed Successfully!"
        return ret