from ctypes import *
import string
import sys

def get_valid_filters(pSpecCore):
    """Close Core API

    This function will return num of valid filters.
    /**
    * \brief Get number of valid filters
    *
    * This function returns the number of valid filters among 1024 filters.
    *
    * \code
    *   int num_of_valid_filters;
    *   num_of_valid_filters = csGetNumOfValidFilters();
    * \endcode
    *
    * \param void
    *
    * \return
    * Returns one numeric value of:
    * - the number of valid filters (>0)
    * - NSP_RETURN_VALUE_FAILURE (-1)
    """

    valid_filters_buffer= c_int()
    valid_filters = pointer(valid_filters_buffer)
    valid_filters = pSpecCore.csGetValidFilters()
    ret = 1
    if ret <=0:
        print "[PythonPrismError] Failed to get Valid Filters!"
        return -1;
    else:
        print "[PythonPrism] Valid Filters Got successfully !"
        return valid_filters