#ifndef __CONFIG_H
#define __CONFIG_H

#define _STRINGIFY(x)      #x
#define STRINGIFY(x)      _STRINGIFY(x)

#define DEBUG                   1
#ifdef DEBUG
	// Enable DBG(...) globally:
	#define TOOLS_LOG_DEBUG

	// Or per file:

	// Specific parts:
	#define DEBUG_INTERVAL_MS		250
#endif

#define GUI_KEYPAD

#define VERSION                BUILD_DATETIME
#define VERSIONSTR_LONG        STRINGIFY(GIT_BRANCH-VERSION)
#define VERSIONSTR_SHORT       STRINGIFY(VERSION)

// #define DEBUG_INTERVAL_MS		100
#define BOOTSCREEN_TIMEOUT_MS	1000
#define MAIN_LOOP_MS			100
#define SETTINGS_DELAY_SAVE		10E3            // Settings will automatically be saved to NVM after 10 sec
#define GRAPH_POINTS	        240             // Amount of points in graph
#define GRAPH_SCALE_ROUND		5			    // scale min/max is rounded to a multiple of this
#define GRAPH_MULTIPLIER		10			    // Graph scale precision for calculation(10 = 1 decimal)
#define GRAPH_XDIVS             9
#define GRAPH_YDIVS             5
#define GRAPH_XTICKS            5

// Settings defaults
#define DEFAULT_SENSOR_LOOP_MS  1000
#define DEFAULT_GRAPH_DELTA_MS	60E3		    // Time between graph points

#define NUMBER_OF_CHANNELS      2
#define PID_PAR_MIN			    0
#define PID_PAR_MAX			    9
#define PID_PAR_PRECISION		2

#define PID1_NAME                   "Temperature"
#define PID1_UNIT_TEXT			    "C"
#define PID1_SETPOINT_MIN		    -20
#define PID1_SETPOINT_MAX		    60
#define PID1_SETPOINT_PRECISION     1
#define PID1_DEFAULT_F  		    0.0
#define PID1_DEFAULT_P  		    1.0
#define PID1_DEFAULT_I  		    0.0
#define PID1_DEFAULT_D  		    0.0
#define PID1_DEFAULT_MODE           PIDLoop::MODE_ZP
#define PID1_DEFAULT_SETPOINT	    20.0
#define PID1_DEFAULT_OFILTER        0.0             // PID Output filter, 0 = no filter
#define PID1_DEFAULT_DFILTER        0.0             // PID D-Term filter
#define PID1_DEFAULT_TBH            0
#define PID1_DEFAULT_LOOPTIME_MS    1000           // time between each pid-loop iteration
#define PID1_DEFAULT_WINDOWTIME     5000      		// soft-pwm time-window size in ms
#define PID1_DEFAULT_MAX_OUTPUT     1.0            // Factor max output, between 0..1
#define PID1_DEFAULT_LOCK_WINDOW    5                         
#define PID1_DEFAULT_LOCK_TIME_MS   60000

#define PID2_NAME                   "Humidity"
#define PID2_UNIT_TEXT			    "%RH"
#define PID2_SETPOINT_MIN	        0
#define PID2_SETPOINT_MAX	        100
#define PID2_SETPOINT_PRECISION	    0
#define PID2_DEFAULT_F  		    0.0
#define PID2_DEFAULT_P  		    1.0
#define PID2_DEFAULT_I  		    0.0
#define PID2_DEFAULT_D  		    0.0
#define PID2_DEFAULT_MODE           PIDLoop::MODE_ZP
#define PID2_DEFAULT_SETPOINT	    50.0
#define PID2_DEFAULT_OFILTER        0.0             // PID Output filter, 0 = no filter
#define PID2_DEFAULT_DFILTER        0.0             // PID D-Term filter
#define PID2_DEFAULT_TBH            0
#define PID2_DEFAULT_LOOPTIME_MS    1000            // time between each pid-loop iteration
#define PID2_DEFAULT_WINDOWTIME     5000      		// soft-pwm time-window size in ms
#define PID2_DEFAULT_MAX_OUTPUT     1.0             // Factor max output, between 0..1
#define PID2_DEFAULT_LOCK_WINDOW    5 
#define PID2_DEFAULT_LOCK_TIME_MS   60000

// #define DISPLAY_WIDTH			320
// #define DISPLAY_HEIGHT			240
// #define LV_BUF_SIZE				(DISPLAY_WIDTH*DISPLAY_WIDTH/10)

//// PINS 
#define PIN_SDA					GPIO_NUM_21
#define PIN_SCL					GPIO_NUM_22

#define PIN_SPEAKER				GPIO_NUM_25
#define PIN_BACKLIGHT			GPIO_NUM_32

#define PIN_BTN_A				GPIO_NUM_39
#define PIN_BTN_B				GPIO_NUM_38
#define PIN_BTN_C				GPIO_NUM_37

#ifdef M5STACK_CORE
#endif

#ifdef ARDUINO_M5Stack_Core_ESP32
#define PIDLOOP_PORTS_LIST	\
	{GPIO_NUM_2, 	"IO2", 	"GPIO2"},	\
	{GPIO_NUM_12, 	"IO12", "GPIO12"},	\
	{GPIO_NUM_13, 	"IO13", "GPIO13"},	\
	{GPIO_NUM_15, 	"IO15", "GPIO15"},	\
	{GPIO_NUM_26, 	"IO26", "GPIO26"},   \
    {GPIO_NUM_5,    "IO5",  "GPIO5"},   \
    {GPIO_NUM_16,   "IO16", "GPIO16"},  \
    {GPIO_NUM_17,   "IO17", "GPIO17"}    
#endif

#ifdef ARDUINO_M5Stack_Core2_ESP32
#define PIDLOOP_PORTS_LIST	\
	{GPIO_NUM_2, 	"IO2", 	"GPIO2"},	\
	{GPIO_NUM_12, 	"IO12", "GPIO12"},	\
	{GPIO_NUM_13, 	"IO13", "GPIO13"},	\
	{GPIO_NUM_15, 	"IO15", "GPIO15"},	\
	{GPIO_NUM_26, 	"IO26", "GPIO26"}   
#endif // M5CORE2

#endif // __CONFIG_H