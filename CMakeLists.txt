cmake_minimum_required(VERSION 3.27)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32_garage_sensor)
include_directories(
        ${IDF_PATH}/components/freertos/FreeRTOS-Kernel/include
        ${IDF_PATH}/components/esp_system/include
        ${IDF_PATH}/components/esp_event/include
        ${IDF_PATH}/components/esp_netif/include
        ${IDF_PATH}/components/esp_wifi/include
        ${IDF_PATH}/components/nvs_flash/include
        ${IDF_PATH}/components/protocol_examples_common/include
        ${IDF_PATH}/components/driver/include
        ${IDF_PATH}/components/hal/include
        ${IDF_PATH}/components/esp_http_client/include
        ${IDF_PATH}/components/esp_interface/include
        ${IDF_PATH}/components/esp_driver_gpio/include
        ${IDF_PATH}/components/esp_hw_support/include
        ${IDF_PATH}/components/esp_common/include
        ${IDF_PATH}/components/esp_wifi/include
        ${IDF_PATH}/examples/common_components/protocol_examples_common/include
        ${CMAKE_SOURCE_DIR}/cmake-build-debug/config
)

add_executable(${PROJECT_NAME} main.c)
