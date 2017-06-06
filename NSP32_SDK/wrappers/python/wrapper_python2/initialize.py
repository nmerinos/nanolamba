import ctypes
import sys

def initialize(crystal_base_library_path):
    """Initialize Function

    This function loaded the needed libraries
    """
    if sys.platform == 'win32':
        ctypes.CDLL("..\Libs\pthreadVC2.dll")

    ctypes.CDLL(crystal_base_library_path)
    print "[PythonPrism] CrystalBase Library Loaded Successfully!"

    return 1
