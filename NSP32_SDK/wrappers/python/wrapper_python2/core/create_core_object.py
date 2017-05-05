import ctypes
import string
import sys

def create_core_object(pSpecCore):
    """Close Core API

    This function will create the core object.

    * \brief Initialize Core Spectrum C API.
    *
    * This function create a core spectrum object.
    *
    * \code
    * int ret_val = csCreate();
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric values of NSP_RETURN_VALUE_SUCCESS, NSP_RETURN_VALUE_FAILURE, or exception.
    * - NSP_RETURN_VALUE_SUCCESS.
    * - NSP_RETURN_VALUE_FAILURE.
    """
    ret = pSpecCore.csCreate()

    if ret <=0:
        print "[PythonPrismError] Core Object Initialization Failed!"
        return -1;
    else:
        print "[PythonPrism] Successfully created the core object!"
        return ret