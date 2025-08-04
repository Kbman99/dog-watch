#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <zephyr/drivers/sensor.h>

struct k_msgq *get_sensor_readings_queue(void);

typedef struct sensorsreadings {
    struct sensor_value temp;
    struct sensor_value gyro[3];
    struct sensor_value accel[3];
} sensorsreadings;

#endif /* SENSOR_DATA_H */
