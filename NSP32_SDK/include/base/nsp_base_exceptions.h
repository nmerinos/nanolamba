/*
NSP_BASE_EXCEPTION.H

Contains base exception class

*/


#ifndef __NSP_BASE_EXCPETIONS_H__
#define __NSP_BASE_EXCPETIONS_H__

#include "nsp_base_def.h"

/*!
This is the exception class for the NSP API/SDK. 
Try, catch statments should be used to catch any exceptions that can be thrown
If exceptions are not caught it will produce a runtime error and terminate the application. 

This class inherits from std::exception. Catching std::exception will also catch this class
and any other exception thrown by std library
*/
class EXPORT_DLL nsp_base_exception: public std::exception {
	
public:

    nsp_base_exception(NSP_ERROR_CODE error_code_input); 

	//! The what() function will return the description of the error as a string 
	const char* what() const throw(); //const throw() gurantees no exceptions are thrown
	NSP_ERROR_CODE error_code; 

};


const char* nsp_base_exception_message(NSP_ERROR_CODE error_code);

#endif // __NSP_BASE_EXCPETIONS_H__