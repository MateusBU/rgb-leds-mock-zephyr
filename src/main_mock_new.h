
/*--------INCLUDES--------*/
#include <zephyr/kernel.h>

#define PWM_NSEC(x) (x)
#define PWM_USEC(x) (PWM_NSEC(x) * 1000UL)

#define PWM_DT_SPEC_GET(node_id)  pwm_dt_spec_get(node_id)

/*--------STRUCT--------*/
struct pwm_dt_spec {
	/** PWM device instance. */
	const struct device *dev;
	/** Channel number. */
	uint32_t channel;
	/** Period in nanoseconds. */
	uint32_t period;
	/** Flags. */
	pwm_flags_t flags;
};


/*--------FUNCTIONS--------*/
int pwm_set_pulse_dt_mock(const struct pwm_dt_spec * spec, uint32_t pulse);
bool pwm_is_ready_dt(const struct pwm_dt_spec * spec);
pwm_dt_spec * pwm_dt_spec_get(node_id);
