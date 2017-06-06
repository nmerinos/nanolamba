import ctypes
import string
import sys

def set_background_data(pSpecCore,filter_data):
    """set background Data

    This function will set the background data. Background data is a data which is acquired with Shutter Speed 1.

    * \brief Set background filter data
    *
    * This function set input filter data as background data.
    * Background data will be used to correct background signal before spectrum calculation.
    *
    * \code
    *   double filter_data[SENSOR_DATA_SIZE];
    *   // acquire raw filter data at SS=1
    *
    *   int ret_value = csSetBackground((double *)filter_data);
    * \endcode
    *
    * \param background_data - double pointer to raw filter data [IN]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    ret = pSpecCore.csSetBackground(filter_data)

    if ret <=0:
        print ("[PythonPrismError] Setting Background data Failed!")
        return ret
    else:
        print ("[PythonPrism] Successfully Set the Background Data!")
        return ret