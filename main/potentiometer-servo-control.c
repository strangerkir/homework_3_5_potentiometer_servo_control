#include <stdint.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "FreeRTOSConfig.h"
#include "potentiometer.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "servo.h"

#define CHECK_INTERVAL (10 * 1000)

static uint16_t raw_to_angle(const int raw)
{
    return ((uint16_t)raw * POTENTIOMETER_MAX_ANGLE) / ADC_LEVELS;
}

void app_main()
{
    uint64_t last_checked_at = 0;

    setup_potentiometer();
    setup_servo();

    int raw = 0;
    int prev_raw = raw;
    uint64_t now = esp_timer_get_time();
    uint16_t angle = 0;

    while (1) {
        now = esp_timer_get_time();

        if (now - last_checked_at >= CHECK_INTERVAL) {
            prev_raw = raw;
            raw = read_potentiometer();
            last_checked_at = now;

            if(raw != prev_raw) {
                angle = raw_to_angle(raw);
                ESP_LOGI("potentiometer", "raw: %d, angle: %d", raw, angle);
                servo_set_angle(angle);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
