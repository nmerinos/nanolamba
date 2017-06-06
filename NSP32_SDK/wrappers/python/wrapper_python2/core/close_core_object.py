import ctypes
import string
import sys

def close_core_object(pSpecCore):
    """Close Core API

    This function will close a core spectrum object.

    * brief Finalize Core Spectrum C API.
    *
    * This function finalize a core spectrum object.
    *
    * \code
    *   int ret_val = csFinalize();
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric value of NSP_RETURN_VALUE_SUCCESS.
    * - NSP_RETURN_VALUE_SUCCESS.
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """
    ret = pSpecCore.csDestroy()

    if ret <=0:
        print "[PythonPrismError] Core API Closing Failed!"
        return -1;
    else:
        print "[PythonPrism] Core API Closed Successfully!"
        return ret