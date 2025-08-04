Get temperature, acceleration, and angular velocity from an ICM42605 sensor 
(polling & trigger mode).

Description
***********

This application can either poll periodically or setup a data ready trigger 
(interrupt driven) to retrieve sensor data from the ICM42688.

The two options can be configured by setting either of the following two options
in the `prj.conf`:
* `CONFIG_APP_SENSOR_MODE_INTERRUPT``: for interrupt driven sensor data reading
* `CONFIG_APP_SENSOR_MODE_POLLING``: for polling based sensor data reading.

`CONFIG_APP_POLLING_INTERVAL_MS` is not yet wired into the application, so 
it does nothing.

Sample Output
=============

.. code-block:: console

  *** Booting nRF Connect SDK v3.0.2-89ba1294ac9b ***
  *** Using Zephyr OS v4.0.99-f791c49f492c ***
  [01:13:29.779,846] <inf> SENSOR_DATA: [1:13:29.779]:23.770 Cel | accel -0.029 3.946 9.055 m/s/s | gyro 0.017 0.002 -0.010 rad/s

  [01:13:29.830,261] <inf> SENSOR_DATA: [1:13:29.830]:23.762 Cel | accel -0.014 3.941 9.069 m/s/s | gyro 0.012 0.002 -0.009 rad/s

  [01:13:29.880,676] <inf> SENSOR_DATA: [1:13:29.880]:23.732 Cel | accel -0.029 3.950 9.055 m/s/s | gyro 0.015 0.002 -0.010 rad/s

<repeats endlessly>
