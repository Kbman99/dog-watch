#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/sensor_data_types.h>

#include "sensor_helpers.h"
#include "sensor_data_collector.h"

#ifdef CONFIG_APP_SENSOR_MODE_INTERRUPT
static struct sensor_trigger data_trigger;

static void handle_icm42688_drdy(const struct device *dev,
				 const struct sensor_trigger *trig)
{
	printk("interrupt triggered");
	sensorsreadings value;

	int ret = icm42688_fetch_and_get_all(dev, &value);
	if (ret != 0) {
		printk("failed to fetch and get sensor data: %d\n", ret);
		return;
	}
	
	icm42688_log_readings(&value);
}
#endif

int main(void)
{
	#ifdef CONFIG_APP_SENSOR_MODE_INTERRUPT
	const struct device *const dev_icm42688 = get_icm42688_sensor();

	if (dev_icm42688 == NULL) {
        return 0;
    }

	data_trigger = (struct sensor_trigger) {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ALL,
	};

	int res = sensor_trigger_set(dev_icm42688, &data_trigger, handle_icm42688_drdy);
	if (res < 0) {
		printk("Cannot configure data trigger!!!\n");
		return 0;
	}

	printk("Configured for triggered sampling.\n");

	#else

	while (1) {
		k_sleep(K_FOREVER);
	}

	#endif

	return 0;
}
