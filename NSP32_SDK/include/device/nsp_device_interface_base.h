/*
nsp_device_interface_base.h

Implementation of nsp_device_interface_base for the apollo (SF MD Sensor) 
*/

#ifndef __NSP_DEVICE_INTERFACE_BASE_H__
#define __NSP_DEVICE_INTERFACE_BASE_H__

#include "nsp_base_def.h"
#include "nsp_sdk_common.h"
#include "nsp_device_interface_stm_usb.h"

class nsp_device_interface_base
{
public :

	nsp_device_interface_base(unsigned int iDeviceId=0); 
	~nsp_device_interface_base();

	virtual void initialize();
	virtual int initialize(unsigned int iDeviceId);
	virtual bool is_initialized(unsigned int iDeviceId=0);

	virtual void finalize(unsigned int iDeviceId=0);

	virtual int reconnect_device(unsigned int& iDeviceId, std::string dark_data_file, struct libusb_device *pDev, libusb_context *lctx, bool detach);

	virtual void enable_spatial_filtering(bool bEnable=true, int iSize=3, unsigned int iDeviceId=0);
	
    /*!
		Find optimal shutter speed
		@see 
    */
	virtual int find_optimal_shutter_speed(std::vector<int>& valid_filter_list, std::vector<double>& background_data, int saturation_value, int sleep_time=1000, unsigned int iDeviceId=0);
	/*!
		Set AE parameters (target DN)
	*/
	virtual void set_auto_exposure_parameters(int target_DN, unsigned int iDeviceId=0);

	virtual void set_auto_exposure_parameters(int target_DN, int upper_DN, int lower_DN, int mean_DN, int max_integ_DN, unsigned int iDeviceId=0);

	/*!
		Do frame moving average by buffering a specified number of frames
		to improve frame rate.
	*/
	virtual void enable_frame_moving_average(bool bEnable, unsigned int iDeviceId=0);

	/*!
		Get background raw filter data from device.
	*/
	virtual void get_background_filter_data( FLOAT64_TYPE *filter_buffer, int frame_average=1, int deviceId=0 );

    /*!
        Get raw filter data from device with averaging value for_num_averages. Results are stored in filter_buffer which has the size the same as the number of filters, 
		given by get_num_filters() function.
		@see get_num_filters()

    */
    virtual double get_filter_data(FLOAT64_TYPE *filter_buffer, int for_num_averages, int dark_correction_mode, int useContAcq=0, unsigned int iDeviceId=0);
	virtual double get_filter_data(std::vector<double>& filter_data, int average, int darkcorrectionMode=0, bool useAE=false, int deviceId=0, int useContAcq=0);
	virtual int get_filter_data_2048(std::vector<char>& filter_data, int deviceId = 0);


	/*!
		Change acquisition mode(continuous, ping-pong, time-interval, s/w and h/w triggers)
	*/
	void set_acq_mode(int acq_mode );
	void get_acq_mode(int* acq_mode );

	/*=====================================================================================*/
	/*							Sensor register access functions						*/
	/*=====================================================================================*/
	std::string get_sensor_id(unsigned int iDeviceId=0);

    /*!
        Get current shutter speed.

		@param shutter integer value for shutter speed value will be set here 
		@see get_shutter_speed() 
    */
     virtual int get_shutter_speed(unsigned int iDeviceId=0);

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
		@see get_min_shutter_speed()
		@see get_max_shutter_speed()
	*/
    virtual void set_shutter_speed(int set_shutter, unsigned int iDeviceId=0);

    /*!
		Change blank time
		@see get_blank_time(unsigned int iDeviceId=0)
    */
	virtual void set_blank_time(int blank_time, unsigned int iDeviceId=0);

	/*!
		Get blank time
		@see set_blank_time(int blank_time, unsigned int iDeviceId=0)
    */
	virtual int get_blank_time(unsigned int iDeviceId=0);

   /*!
        Implementation of set_adc_settings() virtual function in nsp_device_interface_base class
    */
	void set_adc_settings(unsigned char adc_range_index, unsigned char gain);
	void set_adc_settings(unsigned char adc_range_index, unsigned char gain, unsigned char res, unsigned int iDeviceId=0);
	void get_adcsettings(unsigned char* adc_range_index, unsigned char* gain, unsigned char* res, unsigned int iDeviceId=0);
	int	 get_adc_range(unsigned int iDeviceId=0) { return m_adc_range; }

	/*=====================================================================================*/
	/*							Utility functions						*/
	/*=====================================================================================*/
    /*!
		Return minimum shutter speed
		@see get_max_shutter_speed()
    */
	 virtual int get_min_shutter_speed(unsigned int iDeviceId=0);

    /*!
		Return maximum shutter speed
		@see get_min_shutter_speed()
    */
	 virtual int get_max_shutter_speed(unsigned int iDeviceId=0);

	/*!
		Retun minimum filter ouptut (zero value)
		@see get_max_filter_out()
	*/
	 virtual FLOAT64_TYPE get_min_filter_out(unsigned int iDeviceId=0); 
	
	/*!
		Retun maximu filter ouptut (saturation value)
		@see get_min_filter_out()
	*/
	 virtual FLOAT64_TYPE get_max_filter_out(unsigned int iDeviceId=0); 

    /*!
		Return the number of filters
    */
	 virtual int get_num_filters(unsigned int iDeviceId=0);

	 /*!
		Return a list of abnormal filters ( saturated filters at SS=1)
	 */
	 virtual std::vector<int> get_abnormal_filters(unsigned int iDeviceId=0);

	/*
		Test device
	*/
	void test_device(bool& bSensorBoardOk, bool& bControllerBoardOk, unsigned int iDeviceId=0);


	/*!
		Control LED
	*/
	virtual void set_led_module_op_mode(int op_mode, unsigned int iDeviceId=0);
	bool set_led_state( bool* on_array, int num_LED, int intensity, unsigned int iDeviceId=0 );
	bool set_led_opmode( int iOpMode, int iToggleIntervalTime, unsigned int iDeviceId=0 );

	void set_frame_acquisition_conditions( SDataAcqCondition& AcqCond, int deviceId=0 );

	unsigned int get_total_devices();
	void activate_device(unsigned int deviceid);

	//
	void get_sensor_id(char* sensor_id, unsigned int iDeviceId=0);
	void get_sensor_id(char* lot_char, short* lot_id, short* wafer_id, short* x_coord, short* y_coord, short* sensor_type, unsigned int iDeviceId=0 );
	std::string decode_sensor_id(char* sensor_id, unsigned int iDeviceId=0);

	/*!
		On-board processing
	*/
	virtual int set_onboard_frame_average(unsigned char average_count, unsigned int device_id);
	virtual int get_onboard_frame_average(unsigned int device_id);
	virtual int set_onboard_dark_correction(bool bEnable, unsigned int device_id) ;
	virtual int get_onboard_dark_correction(unsigned int device_id) { return m_bEnableOBDC; }
	virtual int get_onboard_dark_frame(unsigned int device_id);
	virtual int get_poi_info(std::vector<int>& poi, unsigned int iDeviceId=0);
	virtual int set_poi_info(std::vector<int>& poi, unsigned int iDeviceId=0);
	virtual int get_poi_filter_data(std::vector<int>& poi_filter_buffer, int poi_size, std::vector<double>& poi_background, unsigned int iDeviceId=0);

	/*
	LED driver
	*/
	virtual int leddriver_isopen();
	virtual int leddriver_close( );
	virtual int leddriver_set_led_state( bool* on_array, int num_LED, int intensity );
	virtual int leddriver_turn_off_all();

protected:

	bool				m_interface_is_initialized;

	double				m_dark_average_val;

	FLOAT64_TYPE		m_current_filter_data[1024];
	FLOAT64_TYPE		m_current_dark_map[1024];

	int					m_ShutterSpeed2;	// 2'nd shutter speed for double-frame acquisition
	int					m_adc_range;
	int					m_adc_gain;
	int					m_adc_res;
	std::string			m_sensor_id;

	bool				m_bEnableOBDC;
	bool				m_bFilterDataAtSS1IsReady;	// flag for SS1 filter data validity

	std::map<int, SDataAcqCondition > m_AcqCond;
};

#endif // __NSP_DEVICE_INTERFACE_BASE_H__