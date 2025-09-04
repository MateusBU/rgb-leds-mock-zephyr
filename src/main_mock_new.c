
/*--------INCLUDES--------*/
#include "main_mock_new.h"

/*--------DEFINES--------*/
#define NO_ERROR 0

/*--------APPLICATION--------*/
int pwm_set_pulse_dt_mock(const struct pwm_dt_spec * spec, uint32_t pulse){
    printk("%s, pulse %ld\n", spec->dev->name, pulse);
    return NO_ERROR;
}

bool pwm_is_ready_dt_mock(const struct pwm_dt_spec * spec){
    printk("PWM %s is ready\n", spec->dev->name);
    return true;
}

pwm_dt_spec * pwm_dt_spec_get(int node_id){
    printk("node_id %d\n", node_id);
}
