#ifndef SENSOR_HELPERS_H
#define SENSOR_HELPERS_H

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#include "sensor_data_collector.h"

const struct device *get_icm42688_sensor(void);

int icm42688_fetch_and_get_all(const struct device *dev, sensorsreadings *readings);

void icm42688_log_readings(const struct sensorsreadings *readings);

#endif /* SENSOR_HELPERS_H */
