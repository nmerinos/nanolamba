import ctypes
import string
import sys

def get_num_of_valid_filters(pSpecCore):
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
    ret = pSpecCore.csGetNumOfValidFilters()

    if ret <=0:
        print ("[PythonPrismError] Failed to get num of Valid Filters!")
        return -1;
    else:
        print ("[PythonPrism] Num of Valid Filters: !", ret)
        return ret