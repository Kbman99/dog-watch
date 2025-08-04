#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

#include "sensor_data_collector.h"
#include "sensor_helpers.h"

#define SENSOR_THREAD_PRIORITY	7
#define SENSOR_THREAD_STACKSIZE 1024

K_MSGQ_DEFINE(sensor_readings_queue, sizeof(sensorsreadings), 16, 4);

int sensor_data_collector(void)
{
    const struct device *dev_icm42688 = get_icm42688_sensor();

    if (dev_icm42688 == NULL) {
        return 0;
    }

    while (1) {
        sensorsreadings value;

        int ret = icm42688_fetch_and_get_all(dev_icm42688, &value);
        if (ret != 0) {
            printk("failed to fetch and get sensor data: %d\n", ret);
            k_msleep(50);
            continue;
        }

        ret = k_msgq_put(&sensor_readings_queue, &value, K_NO_WAIT);
        if (ret) {
			printk("Return value from k_msgq_put = %d\n", ret);
		}						   
		k_msleep(50);
    }
}

struct k_msgq *get_sensor_readings_queue(void)
{
	return &sensor_readings_queue;
}

K_THREAD_DEFINE(sensor_data_collector_id, SENSOR_THREAD_STACKSIZE, sensor_data_collector, NULL,
		NULL, NULL, SENSOR_THREAD_PRIORITY, 0, 1000);
