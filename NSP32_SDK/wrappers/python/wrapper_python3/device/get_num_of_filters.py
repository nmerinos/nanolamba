import ctypes
import string
import sys

def get_num_of_filters(pSpecDevice):
    """Getting Num of Filters

    This function returns the total number of nano-filters in a physical device(sensor).

    * \brief Get total number of nano-filters
    *
    * This function returns the total number of nano-filters in a physical device(sensor).
    *
    * \code
    *   int num_of_filters = 0;
    *   int ret_value = duGetNumOfFilters(&num_of_filters);
    * \endcode
    *
    * \param num_filter - int pointer to the number of nano-filters [OUT]
    *
    * \return
    * Returns one numeric value of:
    * - NSP_RETURN_VALUE_SUCCESS (1)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """


    num_of_filters   = ctypes.c_int()

    ret = pSpecDevice.duGetNumOfFilters(ctypes.byref(num_of_filters))

    if ret <=0:
        print ("[PythonPrismError] Getting Num of Filter Failed")
        return -1;
    else:
        print ("[PythonPrism] Num of Filters: ", num_of_filters.value)
        return num_of_filters.value