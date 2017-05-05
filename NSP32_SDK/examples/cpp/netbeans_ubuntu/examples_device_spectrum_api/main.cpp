// examples_main.cpp : Defines the entry point for the console application.
// This console application is to show how programmer can create, use, and destroy of device object.
//
// (c) nanolamda 2012~2017

#include <stdio.h>
#include <stdlib.h>

#include <string>
using namespace std;

/*
	NSP32 (nanoLambda Spectrum Processor) API examples
*/
char* g_str_sensor_id = "sensor_Y8585-1-14-21-0";								// put your sensor ID
char* g_sensor_cal_file_path = "./config/sensor_Y8585-1-14-21-0.dat";		// modify with your sensor ID

int				g_ss = 1;
bool			g_bVerbos = true;

// Examples for Low-Level API
extern int examples_device_spectrum_api(bool dump_to_file);
extern int examples_devices_spectrum_api(bool dump_to_file);

int main(int argc, char** argv)
{
	printf("=> Press any key to start ........\n"); getchar();
	printf("===============================================================================\n");

	int	ret_val = 0;
	bool dump_to_file = true;

	// Low-Level API (simple device and spectrum core interfaces test)
	ret_val = examples_device_spectrum_api(dump_to_file);
	//ret_val = examples_devices_spectrum_api(dump_to_file);

	printf("===============================================================================\n");
	printf("=> Press any key to exit........\n");
	getchar();

	return 1;
}
