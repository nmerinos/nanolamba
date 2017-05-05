// examples_device_api.cpp : Defines the entry point for the console application.
// This console application is to show how programmer can create, use, and destroy of device object.
//
// (c) nanolamda 2012~2017

#include <stdio.h>
#include <stdlib.h>

#include "nsp_core_common.h"
#include "nsp_device_api.h"
#include "nsp_device_interface_stm_usb.h"
#include "nsp_base_exceptions.h"

/*
	Example: NSP32 device API

	This example shows how user can use API to control device.
*/

int examples_device_api(bool dump_to_file)
{
	int			current_device_index = 0;
	int			total_num_of_sensors = 0;
	int			return_value = 0;
	int			new_shutter_speed = 50;
	char**		sensor_list = NULL;

	try{
		// open(connect) device (sensor)
		int	total_num_of_sensors = duConnect();
		if( total_num_of_sensors <= 0 ){
			printf("[examples_device_api] Device is not connected.\n");
			return NSP_RETURN_VALUE_FAILURE;
		}

		// another function to have total count of sensor
		total_num_of_sensors = duGetTotalSensors();

		// get sensor ID list from sensor calibration data container.
		sensor_list = duGetSensorList();

		char str_sensor_id[SENSOR_ID_STRING_LENGTH];
		double sensor_data_buf1[SENSOR_DATA_SIZE];
		double sensor_data_buf2[SENSOR_DATA_SIZE];
		int	frame_averages = 10;

		for(int i=0;i<total_num_of_sensors;i++){
			int	current_device_index = i;

			// activate a specific device(sensor)
			return_value = duActivateSensorWithIndex(current_device_index);
			if( return_value == cc_ec_undefined_fail )
				return (int)cc_ec_undefined_fail;

			// get sensor id of currently activated device(sensor)
			return_value = duGetSensorID(str_sensor_id);
			if( return_value == NSP_RETURN_VALUE_SUCCESS )
				printf("[examples_device_api] sensor index: %d, Sensor ID: %s\n", current_device_index, str_sensor_id);

			// get current shutter speed from device(sensor)
			// note: after sensor open (initialized), shutter speed is always 1.
			int old_shutter_speed = duGetShutterSpeed(); 
			old_shutter_speed = 30;

			// convert shutter speed to exposure time (ms) for your reference.
			int	master_clock = NSP_DEVICE_MASTER_CLOCK;
			double	exposure_time_val = 0;
			return_value = duShutterSpeedToExposureTime(master_clock, old_shutter_speed, &exposure_time_val);

			// set/change shutter speed of device(sensor)
			return_value = duSetShutterSpeed(old_shutter_speed);
			printf("[examples_device_api] current shutter speed: %d (exposure time = %.3f)\n", old_shutter_speed, exposure_time_val);

			// get one filter output (sensor data)
			return_value = duGetFilterData(sensor_data_buf1, frame_averages);
			printf("[examples_device_api] sensor data at SS = %d\n", old_shutter_speed);
			for(int j=0;j<SENSOR_DATA_SIZE;j++){
				if( j != 0 && j % 15 == 0 )	printf("\n");
				printf("%*.2f, ", 7, sensor_data_buf1[j]);
			}
			printf("\n");

			// set/change shutter speed of device(sensor)
			return_value = duSetShutterSpeed(new_shutter_speed);
			
			// get one filter output (sensor data)
			return_value = duGetFilterData(sensor_data_buf2, frame_averages);
			printf("[examples_device_api] sensor data at SS = %d\n", new_shutter_speed);
			/*
			for(int j=0;j<SENSOR_DATA_SIZE;j++){
				if( j != 0 && j % 15 == 0 )	printf("\n");
				printf("%*.2f, ", 7, sensor_data_buf2[j]);
			}
			printf("\n");
			*/
			// dump related information and data to CSV format file.
			if( dump_to_file == true ){
				// saving spectrumdata to csv
				std::string outputFileName = "examples_device_api_" + std::string(str_sensor_id) + "_result.csv";
				fstream filestream;
				filestream.open(outputFileName.c_str(), ofstream::out);
				if (filestream.is_open() == true) {
					filestream << "Sensor ID, " << str_sensor_id << endl;
					filestream << "Sensor data at SS=" << old_shutter_speed << endl;
					for (int i = 0; i < SENSOR_DATA_SIZE; i++) {
						filestream << sensor_data_buf1[i];
						if (i != (SENSOR_DATA_SIZE - 1))
							filestream << ",";
					}
					filestream << endl;

					filestream << "Sensor data at SS=" << new_shutter_speed << endl;
					for (int i = 0; i < SENSOR_DATA_SIZE; i++) {
						filestream << sensor_data_buf2[i];
						if (i != (SENSOR_DATA_SIZE - 1))
							filestream << ",";
					}
					filestream << endl;
					filestream.close();
				}
				printf("[examples_device_api] raw data dump to \"%s\" -- done!\n", outputFileName.c_str());
			}
		}
		// close(disconnect) device(sensor)
		duDisconnect();

		if( sensor_list ){
			for(int i=0;i<total_num_of_sensors;i++){
				free((void *)sensor_list[i]);
			}
			free((void *)sensor_list);
		}

		return NSP_RETURN_VALUE_SUCCESS;
	}
	catch(nsp_base_exception &e){
		if( sensor_list ){
			for(int i=0;i<total_num_of_sensors;i++){
				free((void *)sensor_list[i]);
			}
			free((void *)sensor_list);
		}

		printf("[examples_device_api] NSP_BASE_EXCEPTION happened: %s\n", e.what());
		return (int)-e.error_code; 
	}
	catch(...){
		if( sensor_list ){
			for(int i=0;i<total_num_of_sensors;i++){
				free((void *)sensor_list[i]);
			}
			free((void *)sensor_list);
		}
		printf("[examples_device_api] std::exception happed !!\n");
		return NSP_RETURN_VALUE_FAILURE;
	}
}