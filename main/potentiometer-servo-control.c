#include <stdint.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "FreeRTOSConfig.h"
#include "potentiometer.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define CHECK_INTERVAL (10 * 1000)

void app_main()
{
    uint64_t last_checked_at = 0;

    setup_potentiometer();
    int raw = 0;
    int prev_raw = raw;
    uint64_t now = esp_timer_get_time();

    while (1) {
        now = esp_timer_get_time();

        if (now - last_checked_at >= CHECK_INTERVAL) {
            prev_raw = raw;
            raw = read_potentiometer();
            last_checked_at = now;

            if(raw != prev_raw) {
                ESP_LOGI("potentiometer", "raw: %d", raw);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
