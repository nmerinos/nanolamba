/*
nsp_device_interface.h

Adds extra functionality to nsp_device_interface_base

*/
#ifndef __NSP_DEVICE_INTERFACE_H__
#define __NSP_DEVICE_INTERFACE_H__

#include "nsp_base_def.h"

#include "nsp_device_interface_base.h"
#include "nsp_base_exceptions.h"
#include "lusb.h"

class EXPORT_DLL nsp_device_interface
{
public:
	nsp_device_interface();
	~nsp_device_interface();

	/*!
		initialize nsp_device_interface
	*/
	void initialize();
	int initialize(unsigned int iDeviceId);

	/*!
		finalize nsp_device_interface
	*/
	void finalize(unsigned int iDeviceId=0);

	/*!
		reconnect device
	*/
	int reconnect_device(unsigned int& iDeviceId, std::string dark_data_file, struct libusb_device *pDev, libusb_context *lctx, bool detach);

	/*
		Returns true if nsp_device_interface is initialized, false if not. 
	*/
	bool is_initialized(unsigned int iDeviceId=0);

	void enable_spatial_filtering(bool bEnable, int iSize, unsigned int iDeviceId=0);

	/*!
		Do frame moving average by buffering a specified number of frames
		to improve frame rate.
	*/
	void enable_frame_moving_average(bool bEnable, unsigned int iDeviceId=0);

	/*!
		Set AE parameters (target DN)
	*/
	void set_auto_exposure_parameters(int target_DN, unsigned int iDeviceId=0);
	void set_auto_exposure_parameters(int target_DN, int upper_DN, int lower_DN, int mean_DN, int max_integ_DN, unsigned int iDeviceId=0);

	/*!
		Get raw signal and background filter data from device.
	*/
    double get_filter_data(FLOAT64_TYPE *filter_buffer, int for_num_averages, int dark_correction_mode, int useContAcq=0, unsigned int iDeviceId=0);
	void get_background_filter_data( FLOAT64_TYPE *filter_buffer, int frame_average=1, int iDeviceId=0 );

    /*!
        Get raw filter data from device with averaging value for_num_averages. Results are stored in filter_buffer which has the size the same as the number of filters, 
		given by get_num_filters() function.
		@see get_num_filters()

    */
	double get_filter_data(std::vector<double>& filter_data, int average, int darkcorrectionMode=0, bool useAE=false, int deviceId=0, int useContAcq=0);
	int get_filter_data_2048(std::vector<char>& filter_data, int deviceId = 0);

	int	 get_adc_range(unsigned int iDeviceId=0);
	std::string get_sensor_id(unsigned int iDeviceId=0);

	/*!
		Change acquisition mode(continuous, ping-pong, time-interval, s/w and h/w triggers)
	*/
	void set_acq_mode(int acq_mode );
	void get_acq_mode(int* acq_mode );

	/*!
		Retun minimum filter ouptut (zero value)
		@see get_max_filter_out()
	*/
	 FLOAT64_TYPE get_min_filter_out(unsigned int iDeviceId=0); 

	
	/*!
		Retun maximu filter ouptut (saturation value)
		@see get_min_filter_out()
	*/
	 FLOAT64_TYPE get_max_filter_out(unsigned int iDeviceId=0); 

    /*!
		Return the number of filters
    */
	 int get_num_filters(unsigned int iDeviceId=0);

    /*!
        Get current shutter speed.

		@param shutter integer value for shutter speed value will be set here 
		@see get_shutter_speed() 
    */
     int get_shutter_speed(unsigned int iDeviceId=0);

	/*!
		Convert shutter speed to exposure time (ms).
	
		@param MCLK - master clock from MCU to sensor (IN)
		@param shutter - shutter speed value (IN)
		@param exposure_time_val - double pointer to exposure time value (OUT)
	*/
	int shutter_to_exposure_time_ms(int MCLK, int shutter, double* exposure_time_val);

	/*!
		Convert exposure time (ms) to shutter speed.
	
		@param MCLK - master clock from MCU to sensor (IN)
		@param exposure_time_val - exposure time value (IN)
		@param shutter - integer pointer to shutter speed value (OUT)
	*/
	int exposure_tim_ms_to_shutter(int MCLK, double exposure_time_val, int *shutter);


    /*!
        Change shutter speed to set_shutter. 


		@param set_shutter integer number for shutter speed. Maximum and minimum possible value is indicated
			by get_min_shutter_speed() and get_max_shutter_speed()
		@see get_shutter_speed()
	*/
     void set_shutter_speed(int set_shutter, unsigned int iDeviceId=0);

    /*!
		Return optimal shutter speed
		@see find_optimal_shutter_speed()
    */
	int find_optimal_shutter_speed(std::vector<int>& valid_filter_list, std::vector<double>& background_data, int saturation_value, int sleep_time=1000, unsigned int iDeviceId=0);


    /*!
		Return minimum shutter speed
		@see get_max_shutter_speed()
    */
	int get_min_shutter_speed(unsigned int iDeviceId=0);

    /*!
		Return maximum shutter speed
		@see get_min_shutter_speed()
    */
	 int get_max_shutter_speed(unsigned int iDeviceId=0);


    /*!
		Change blank time
		@see get_blank_time()
    */
	void set_blank_time(int blank_time, unsigned int iDeviceId=0);

	/*!
		Get blank time
		@see set_blank_time(int blank_time)
    */
	int get_blank_time(unsigned int iDeviceId=0);


	/*!
		Get starting wavlength in nanometers of spectrum output 
    */
	FLOAT64_TYPE get_start_lambda();

    /*!
		Get ending wavlength in nanometers of spectrum output  
    */
	FLOAT64_TYPE get_end_lambda();

    /*!
		Get interval wavlength in nanometers of spectrum output 
    */
	FLOAT64_TYPE get_interval();

    /*!
		Get the resolution, or number of points, in spectrum output 
    */
    int get_resolution();

	/*!
		Get six letter sensor ID , char must be array of length six
	*/
	void get_sensor_id(char *sensor_id, unsigned int iDeviceId=0);
	void get_sensor_id(char* lot_char, short* lot_id, short* wafer_id, short* x_coord, short* y_coord, short* sensor_type, unsigned int iDeviceId=0 );
	std::string decode_sensor_id(char* sensor_id, unsigned int iDeviceId=0);

	 /*!
		Return a list of abnormal filters ( saturated filters at SS=1)
	 */
	 std::vector<int> get_abnormal_filters(unsigned int iDeviceId=0);

	/*!
		Test device for operation 
	*/
	bool test_device(unsigned int iDeviceId=0);

	/*!
		Control LED, each element in on_array of size num_LED represents the LED's status on (true) or off(false) 
	*/
	bool set_led_state( bool* on_array, int num_LED, int intensity, unsigned int iDeviceId=0 );
	bool set_led_opmode( int iOpMode, int iToggleIntervalTime, unsigned int iDeviceId=0 );
	void set_led_module_op_mode(int op_mode, unsigned int iDeviceId=0);

   /*!
        Implementation of set_adc_settings() virtual function in nsp_device_interface class
    */
	void set_adc_settings(unsigned char adc_range_index, unsigned char gain);
	void set_adc_settings(unsigned char adc_range_index, unsigned char gain, unsigned char res, unsigned int iDeviceId=0);
	void get_adcsettings(unsigned char* adc_range_index, unsigned char* gain, unsigned char* res, unsigned int iDeviceId=0);

	unsigned int get_total_devices();
	void activate_device(unsigned int deviceid);

	void set_frame_acquisition_conditions( SDataAcqCondition& AcqCond, int deviceId=0 );

	int	num_valid_filters(unsigned int iDeviceId=0) { return 1024; }

	/*!
		On-board processing
	*/
	int set_onboard_frame_average(unsigned char average_count, unsigned int device_id);
	int get_onboard_frame_average(unsigned int device_id);
	int set_onboard_dark_correction(bool bEnable, unsigned int device_id);
	int get_onboard_dark_correction(unsigned int device_id);
	int get_onboard_dark_frame(unsigned int device_id);
	int get_poi_info(std::vector<int>& poi, unsigned int iDeviceId=0);
	int set_poi_info(std::vector<int>& poi, unsigned int iDeviceId=0);
	int get_poi_filter_data(std::vector<int>& poi_filter_buffer, int poi_size, std::vector<double>& poi_background, unsigned int iDeviceId=0);

	/*
	LED driver
	*/
	int leddriver_isopen();
	int leddriver_close( );
	int leddriver_set_led_state( bool* on_array, int num_LED, int intensity );
	int leddriver_turn_off_all();

private:
	nsp_device_interface_base*		m_device_interface_base;
	bool							m_interface_is_initialized;


};

#endif // __NSP_DEVICE_INTERFACE_H__