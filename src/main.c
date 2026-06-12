/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

// /* The devicetree node identifier for the "led0" alias. */
// #define LED0_NODE DT_ALIAS(led0)
// #define LED1_NODE DT_ALIAS(led1)
// #define LED2_NODE DT_ALIAS(led2)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
// static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
// static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
// static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

/* Get LED device pointers (led0, led1, led2 from devicetree aliases) */
static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led0), gpios, {0});
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led1), gpios, {0});
static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET_OR(DT_ALIAS(led2), gpios, {0});

int main(void)
{
	// int ret;

	if (!gpio_is_ready_dt(&red_led) || !gpio_is_ready_dt(&green_led) || !gpio_is_ready_dt(&blue_led)) {
		return 0;
	}

	// ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	// if (ret < 0) {
	// 	return 0;
	// }

	// while (1) {
	// 	ret = gpio_pin_toggle_dt(&led);
	// 	if (ret < 0) {
	// 		return 0;
	// 	}
	// 	k_msleep(SLEEP_TIME_MS);
	// }
	// return 0;

	/* Configure pins as outputs */
    gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_INACTIVE);

    while (1) {
        /* Turn ON Red, turn OFF others */
        gpio_pin_set_dt(&red_led, 0);
        gpio_pin_set_dt(&green_led, 1);
        gpio_pin_set_dt(&blue_led, 1);
        k_msleep(SLEEP_TIME_MS);

        /* Turn ON Green, turn OFF others */
        gpio_pin_set_dt(&red_led, 1);
        gpio_pin_set_dt(&green_led, 0);
        gpio_pin_set_dt(&blue_led, 1);
        k_msleep(SLEEP_TIME_MS);

        /* Turn ON Blue, turn OFF others */
        gpio_pin_set_dt(&red_led, 1);
        gpio_pin_set_dt(&green_led, 1);
        gpio_pin_set_dt(&blue_led, 0);
        k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
