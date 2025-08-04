#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include "sensor_data_collector.h"

LOG_MODULE_REGISTER(SENSOR_DATA, CONFIG_SENSOR_LOG_LEVEL);

const struct device *get_icm42688_sensor(void)
{
	const struct device *const dev = DEVICE_DT_GET_ONE(invensense_icm42688);

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: icm42688 device not found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
	return dev;
}

static const char *now_str(void)
{
	static char buf[16]; /* ...HH:MM:SS.MMM */
	uint32_t now = k_uptime_get_32();
	unsigned int ms = now % MSEC_PER_SEC;
	unsigned int s;
	unsigned int min;
	unsigned int h;

	now /= MSEC_PER_SEC;
	s = now % 60U;
	now /= 60U;
	min = now % 60U;
	now /= 60U;
	h = now;

	snprintf(buf, sizeof(buf), "%u:%02u:%02u.%03u",
		 h, min, s, ms);
	return buf;
}

void icm42688_log_readings(const struct sensorsreadings *readings)
{
    LOG_INF("[%s]:%.3f Cel | accel %.3f %.3f %.3f m/s/s | gyro %.3f %.3f %.3f rad/s\n",
        now_str(),
        sensor_value_to_double(&readings->temp),
        sensor_value_to_double(&readings->accel[0]),
        sensor_value_to_double(&readings->accel[1]),
        sensor_value_to_double(&readings->accel[2]),
        sensor_value_to_double(&readings->gyro[0]),
        sensor_value_to_double(&readings->gyro[1]),
        sensor_value_to_double(&readings->gyro[2]));
}

int icm42688_fetch_and_get_all(const struct device *dev, sensorsreadings *readings)
{
    int rc = sensor_sample_fetch(dev);
        
    if (rc == 0) {
        rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, readings->accel);
    }
    if (rc == 0) {
        rc = sensor_channel_get(dev, SENSOR_CHAN_GYRO_XYZ, readings->gyro);
    }
    if (rc == 0) {
        rc = sensor_channel_get(dev, SENSOR_CHAN_DIE_TEMP, &readings->temp);
    }

    return rc;
}
