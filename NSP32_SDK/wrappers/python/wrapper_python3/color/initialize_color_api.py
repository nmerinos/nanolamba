import ctypes
import sys
import os


def initialize_color_api(pSpecCore):
    """Initializing Color API

    This function will initialize Color API

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
    """

    ret = pSpecCore.acInitialize()

    if ret <=0:
        print ("[PythonPrismError] CrystalColor API Initialization  Failed!")
        return -1;
    else:
        print ("[PythonPrism] CrystalColor API Initializated Successfully!")
        return ret