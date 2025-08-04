#
# Copyright (c) 2019 TDK Invensense
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(dog_watch)

target_include_directories(app PRIVATE inc)
target_sources(app PRIVATE
    src/main.c
    src/sensor_helpers.c
)
target_sources_ifdef(CONFIG_APP_SENSOR_MODE_POLLING app PRIVATE
    src/sensor_data_collector.c
    src/sensor_data_consumer.c
)
