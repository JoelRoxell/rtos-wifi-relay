#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0 5
#define GPIO_OUTPUT_PIN_SEL ((1ULL << GPIO_OUTPUT_IO_0))

void app_main()
{
    gpio_config_t io_config;
    io_config.intr_type = GPIO_INTR_DISABLE;
    io_config.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_config.mode = GPIO_MODE_OUTPUT;

    gpio_config(&io_config);

    int cnt = 0;

    for (;; cnt++)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0, cnt % 2);
        printf("%d", cnt);
        fflush(stdout);
    }
}

void print_sys_info()
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    printf("This is ESP8266 chip with %d CPU cores, WiFi, ",
           chip_info.cores);

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    fflush(stdout);
}