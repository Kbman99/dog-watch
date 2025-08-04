#include <zephyr/kernel.h>

#include "sensor_data_collector.h"
#include "sensor_helpers.h"

#define STORAGE_THREAD_STACKSIZE 1024
#define STORAGE_THREAD_PRIORITY	 7

static void sensor_data_consumer(void)
{
	struct k_msgq *sensor_queue;
	sensorsreadings value;

	sensor_queue = get_sensor_readings_queue();
	if (sensor_queue == NULL) {
		printkk("Error getting samples queue\n");
	}
	while (1) {

		int ret = k_msgq_get(sensor_queue, &value, K_FOREVER);
		if (ret) {
			printk("Return value from k_msgq_get = %d\n", ret);
		}
		
        icm42688_log_readings(&value);
	}
}

K_THREAD_DEFINE(sensor_data_consumer_id, STORAGE_THREAD_STACKSIZE, sensor_data_consumer, NULL, NULL,
		NULL, STORAGE_THREAD_PRIORITY, 0, 2000);
