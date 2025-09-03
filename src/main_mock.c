/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM-based RGB LED control
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

/*--------LOCAL DEFINES--------*/
#define MOCK 1
#define STEP_SIZE PWM_USEC(1000)
#define NO_ERROR 0

/*--------LOCAL VARIABLES--------*/
#if MOCK
    static const struct device mock_red_pwm = {
        .name = "PWM_RED_MOCK",
    };

    static const struct device mock_green_pwm = {
        .name = "PWM_GREEN_MOCK",
    };

    static const struct device mock_blue_pwm = {
        .name = "PWM_BLUE_MOCK",
    };

    struct pwm_dt_spec red_pwm_led = {
        .dev = &mock_red_pwm,
        .channel = 0,
        .period = 40000000,
        .flags = PWM_POLARITY_INVERTED,
    };

    struct pwm_dt_spec green_pwm_led = {
        .dev = &mock_green_pwm,
        .channel = 1,
        .period = 20000000,
        .flags = PWM_POLARITY_INVERTED,
    };

    struct pwm_dt_spec blue_pwm_led = {
        .dev = &mock_blue_pwm,
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


/*--------LOCAL FUNCTIONS--------*/
bool pwm_is_ready_dt_mock(const struct pwm_dt_spec * spec);
int pwm_set_pulse_dt_mock(const struct pwm_dt_spec * spec, uint32_t pulse);

/*--------LOCAL APPLICATIONS--------*/
int main(void)
{
    uint32_t pulse_red, pulse_green, pulse_blue; /* pulse widths */
    int ret;

    printk("PWM-based RGB LED control %ld\n", STEP_SIZE);

    #if MOCK
        if (!pwm_is_ready_dt_mock(&red_pwm_led) ||
            !pwm_is_ready_dt_mock(&green_pwm_led) ||
            !pwm_is_ready_dt_mock(&blue_pwm_led)) {
            printk("Error: one or more PWM devices not ready\n");
            return 0;
        }

    #else
        if (!pwm_is_ready_dt(&red_pwm_led) ||
            !pwm_is_ready_dt(&green_pwm_led) ||
            !pwm_is_ready_dt(&blue_pwm_led)) {
            printk("Error: one or more PWM devices not ready\n");
            return 0;
        }
    #endif


    while (1) {
        for (pulse_red = 0U; pulse_red <= red_pwm_led.period;
            pulse_red += STEP_SIZE) {

            #if MOCK
                ret = pwm_set_pulse_dt_mock(&red_pwm_led, pulse_red);
            #else
                ret = pwm_set_pulse_dt(&red_pwm_led, pulse_red);
            #endif
            if (ret != NO_ERROR) {
                    printk("Error %d: red write failed\n", ret);
                return 0;
            }

            for (pulse_green = 0U;
                pulse_green <= green_pwm_led.period;
                pulse_green += STEP_SIZE) {

                #if MOCK
                    ret = pwm_set_pulse_dt_mock(&green_pwm_led, pulse_green);
                #else
                    ret = pwm_set_pulse_dt(&green_pwm_led, pulse_green);
                #endif
                if (ret != NO_ERROR) {
                    printk("Error %d: green write failed\n",
                        ret);
                    return 0;
                }

                for (pulse_blue = 0U;
                    pulse_blue <= blue_pwm_led.period;
                    pulse_blue += STEP_SIZE) {

                    #if MOCK
                        ret = pwm_set_pulse_dt_mock(&blue_pwm_led, pulse_blue);
                    #else
                        ret = pwm_set_pulse_dt(&blue_pwm_led, pulse_blue);
                    #endif
                    if (ret != NO_ERROR) {
                        printk("Error %d: "
                            "blue write failed\n",
                            ret);
                        return 0;
                    }
                    k_sleep(K_MSEC(100));
                }
            }
        }
    }
    return 0;
}

int pwm_set_pulse_dt_mock(const struct pwm_dt_spec * spec, uint32_t pulse){

    printk("%s, pulse %ld\n", spec->dev->name, pulse);
    return NO_ERROR;
}

bool pwm_is_ready_dt_mock(const struct pwm_dt_spec * spec){
    printk("PWM %s is ready\n", spec->dev->name);
    return true;
}
