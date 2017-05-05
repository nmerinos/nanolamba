// examples_main.cpp : Defines the entry point for the console application.
// This console application is to show how programmer can create, use, and destroy of device object.
//
// (c) nanolamda 2012~2017

#include <stdio.h>
#include <stdlib.h>

#include <string>
using namespace std;

/*
	NSP (nanoLambda Spectrum Processor) API examples
	- device interface: nsp_device_interface, nsp_device_api
	- spectrum core interface: nsp_core_spectrum, nsp_spectrum_api
	- application (color): nsp_app_color, nsp_app_color_api
*/

int				g_ss = 1;
bool			g_bVerbos = true;

// Examples for Low-Level API
extern int examples_spectrum_core_api(bool dump_to_file);

int main(int argc, char** argv)
{
	printf("=> Press any key to start ........\n"); getchar();
	printf("===============================================================================\n");

	int	ret_val = 0;
	bool dump_to_file = true;

	// Low-Level API (simple spectrum core interface test)
	ret_val = examples_spectrum_core_api(dump_to_file);

	printf("===============================================================================\n");
	printf("=> Press any key to exit........\n");
	getchar();

	return 1;
}