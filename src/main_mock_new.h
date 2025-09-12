#ifndef MAIN_MOCK_NEW_H
#define MAIN_MOCK_NEW_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <zephyr/kernel.h>

#define PWM_NSEC(x) (x)
#define PWM_USEC(x) ((x) * 1000UL)

#define PWM_POLARITY_NORMAL   0
#define PWM_POLARITY_INVERTED 1

typedef uint16_t pwm_flags_t;

/* Mock da struct pwm_dt_spec */
struct pwm_dt_spec {
    const char *dev_name;
    uint32_t channel;
    uint32_t period;
    pwm_flags_t flags;
};

/* Mock da função que checa se o device está pronto */
static inline bool pwm_is_ready_dt(const struct pwm_dt_spec *spec)
{
    (void)spec;
    return true;
}

/* Mock do pwm_set_pulse_dt */
static inline int pwm_set_pulse_dt(const struct pwm_dt_spec *spec, uint32_t pulse)
{
    printf("[MOCK] dev=%s, ch=%u, period=%u, pulse=%u, flags=%u\n",
           spec->dev_name, spec->channel, spec->period, pulse, spec->flags);
    return 0;
}

/* Mock do PWM_DT_SPEC_GET (ignora node_id e retorna vazio) */
static inline struct pwm_dt_spec pwm_dt_spec_get(int dummy)
{
    struct pwm_dt_spec spec = {0};
    return spec;
}

// /* Mock do k_sleep */
// #define K_SECONDS(x) ((x) * 1000UL)
// #define k_sleep(ms) sleep((ms)/1000)

#endif /* MAIN_MOCK_NEW_H */
