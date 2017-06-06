import sys
import ctypes
import string

def initialize_core_api(crystal_core_library_path):
    """Initializing Core API

    This function will initialize Core API
    """ 
    pSpecCore = ctypes.CDLL(crystal_core_library_path)

    print "[PythonPrism] CrystalCore Library Loaded Successfully!"

    return pSpecCore