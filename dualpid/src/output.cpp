#include "output.h"

#include "globals.h"
#include "config.h"
#include "pidloop.h"
#include "tools-log.h"

#include "freertos/task.h"

bool OutputDriver::begin(int32_t channel_id)
{
    return _begin_ok = true;
};

bool SlowPWMDriver::begin(int32_t channel_id)
{
    PIDLoop::settings_t pidset;
    switch(channel_id)
    {
        case 1: pidset = settings.pid1; break;
        case 2: pidset = settings.pid2; break;
        default:
            ERROR("Unsupported channel-id.");
            return false;
    };

    // _pin_n = static_cast<gpio_num_t>(_settings.pin_n);
	// _pin_n = GPIO_NUM_NC;
    _pin_p = static_cast<gpio_num_t>(pidset.pin_p);
    DBG("channel %d, pin = %x", channel_id, _pin_p);

	// We need atleast a pin..
	if(_pin_p == GPIO_NUM_NC)
	{
		WARNING("OutputDriver SlowPWMDriver not configured (pin_p)");
		return false;
	};

    // config hardware
  	// pinMode(_pin_n, OUTPUT);
  	pinMode(_pin_p, OUTPUT);
	// digitalWrite(_pin_n, LOW);
	digitalWrite(_pin_p, LOW);

	// _window_start = millis();
	_window_len = pidset.windowtime;
    // _window_low = 0;

    // start the output task
    _task_running = true;
    _channel_id = channel_id;
    
    uint32_t core = xPortGetCoreID();
    uint32_t taskcore = (core + 1) & 0x01;
    DBG("Main process running on core %d, so starting SlowPWM task on core %d", core, taskcore);

    xTaskCreatePinnedToCore(
        task,               // pcTaskCode
        "SlowPWM",          // const char *const pcName, 
        2048,               // ulStackDepth,
        this,               // pvParameters, 
        8,                  // uxPriority, 
        &_taskh,            // pvCreatedTask
        taskcore            // xCoreID
    );

	return OutputDriver::begin(channel_id);
};

void SlowPWMDriver::off()
{
    // digitalWrite(_pin_n, LOW);
    if(_pin_p != GPIO_NUM_NC)
    {
        // DBG("ch%d: off, pin = %x", _channel_id, _pin_p);
    	digitalWrite(_pin_p, LOW);
    };

    // make sure task doesn't turn it on and also set lowtime low so task responds fast
    _window_lowtime = 100;
    _window_hightime = 0;
};

void SlowPWMDriver::set(float percent)
{
    float duty = percent / 100.0;

    _window_hightime = duty * _window_len;
    _window_lowtime = (1-duty) * _window_len;
    // DBG("set duty = %.2f, low = %d, high = %d", duty, _window_lowtime, _window_hightime);
};

void SlowPWMDriver::task(void* ptr)
{       
    SlowPWMDriver* me = static_cast<SlowPWMDriver*>(ptr);

    DBG("ch%dtask: Starting up on core %d", me->_channel_id, xPortGetCoreID());

    me->_state = LOW;
    me->_window_lowtime = 100;
    me->_window_hightime = 0;
    
    while(me->_task_running)
    {
        if(me->_pin_p == GPIO_NUM_NC)
        {
            delay(100);
            continue;
        };

        time_t now = millis();
        switch(me->_state)
        {
            case HIGH:
                // set pin LOW
                digitalWrite(me->_pin_p, LOW);

                // DBG("ch%d, %lu: set LOW, wait %d", 
                //     me->_channel_id, now, me->_window_lowtime);

                // state LOW only if there is high_time to prevent glitches
                if(me->_window_hightime)
                    me->_state = LOW;

                // delay = low_time = (1-percent)*windowtime
                delay(me->_window_lowtime);

                break;
            case LOW:
                // set pin HIGH
                digitalWrite(me->_pin_p, HIGH);

                // DBG("ch%d, %lu: set HIGH, wait %d",
                //     me->_channel_id, now, me->_window_hightime);

                // state HIGH only if there is LOW_time
                if(me->_window_lowtime)
                    me->_state = HIGH;

                // delay = high_time = percent*windowtime
                delay(me->_window_hightime);

                break;
        };
    };
};
void SlowPWMDriver::loop()
{
    // Process timewindow valve depending on PID Output
    time_t now = millis();
    if (now - _window_start > _window_len)
    { //time to shift the Relay Window
        _window_start += _window_len;
    };

    // Set output
    // uint8_t N = LOW;
    uint8_t P = LOW;

	// Always MODE_ZP since 01-2024
	if((now - _window_start) > _window_low)
		P = HIGH;
    digitalWrite(_pin_p, P);
};

// bool FastPWMDriver::begin()
// {
//     ledcSetup(_id, 1, 10);
//     ledcAttachPin(_pin_p, _id);
//     ledcWrite(_id, 0);
// };

// void FastPWMDriver::off()
// {
//     ledcWrite(_id, 0);
//     return;
// };

// void FastPWMDriver::set(float percent)
// {
//     ledcWrite(_id, _output_value * 1024 / 100);
//     return;
// };