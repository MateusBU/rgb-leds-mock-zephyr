/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM-based RGB LED control
 */

#define USE_MOCK 1

#if USE_MOCK == 1
    #define USE_MOCK_PWM
#else
    #include <zephyr/kernel.h>
    #include <zephyr/device.h>
    #include <zephyr/drivers/pwm.h>
#endif

#ifdef USE_MOCK_PWM
    #include "main_mock_new.h"
#endif

#include <zephyr/sys/printk.h>

#if USE_MOCK == 1

    struct pwm_dt_spec red_pwm_led = {
        .dev_name = "PWM_RED_MOCK",
        .channel = 0,
        .period = 40000000,
        .flags = PWM_POLARITY_INVERTED,
    };

    struct pwm_dt_spec green_pwm_led = {
        .dev_name = "PWM_GREEN_MOCK",
        .channel = 1,
        .period = 20000000,
        .flags = PWM_POLARITY_INVERTED,
    };

    struct pwm_dt_spec blue_pwm_led = {
        .dev_name = "PWM_BLUE_MOCK",
        .channel = 2,
        .period = 10000000,
        .flags = PWM_POLARITY_NORMAL,
    };
#else
    static const struct pwm_dt_spec red_pwm_led =
        PWM_DT_SPEC_GET(DT_ALIAS(red_pwm_led));
    static const struct pwm_dt_spec green_pwm_led =
        PWM_DT_SPEC_GET(DT_ALIAS(green_pwm_led));
    static const struct pwm_dt_spec blue_pwm_led =
        PWM_DT_SPEC_GET(DT_ALIAS(blue_pwm_led));
#endif


#define STEP_SIZE PWM_USEC(2000)

int main(void)
{
	uint32_t pulse_red, pulse_green, pulse_blue; // pulse widths
	int ret;

	printk("PWM-based RGB LED control\n");

	if (!pwm_is_ready_dt(&red_pwm_led) ||
	    !pwm_is_ready_dt(&green_pwm_led) ||
	    !pwm_is_ready_dt(&blue_pwm_led)) {
		printk("Error: one or more PWM devices not ready\n");
		return 0;
	}

	while (1) {
		for (pulse_red = 0U; pulse_red <= red_pwm_led.period;
		     pulse_red += STEP_SIZE) {
			ret = pwm_set_pulse_dt(&red_pwm_led, pulse_red);
			if (ret != 0) {
				printk("Error %d: red write failed\n", ret);
				return 0;
			}

			for (pulse_green = 0U;
			     pulse_green <= green_pwm_led.period;
			     pulse_green += STEP_SIZE) {
				ret = pwm_set_pulse_dt(&green_pwm_led,
						       pulse_green);
				if (ret != 0) {
					printk("Error %d: green write failed\n",
					       ret);
					return 0;
				}

				for (pulse_blue = 0U;
				     pulse_blue <= blue_pwm_led.period;
				     pulse_blue += STEP_SIZE) {
					ret = pwm_set_pulse_dt(&blue_pwm_led,
							       pulse_blue);
					if (ret != 0) {
						printk("Error %d: "
						       "blue write failed\n",
						       ret);
						return 0;
					}
					k_sleep(K_SECONDS(1));
				}
			}
		}
	}
	return 0;
}
