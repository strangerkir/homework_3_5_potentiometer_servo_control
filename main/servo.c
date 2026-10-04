#include "servo.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_DUTY_RES LEDC_TIMER_14_BIT
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define SERVO_GPIO 16

#define SERVO_MAX_ANGLE 180
#define SERVO_MIN_ANGLE 0

#define SERVO_MAX_DUTY (1u << 14)
#define SERVO_PERIOD_US 20000u

#define SERVO_MIN_US 400
#define SERVO_MAX_US 2600

void setup_servo() {
  const ledc_timer_config_t t = {
      .speed_mode = LEDC_MODE,
      .timer_num = LEDC_TIMER,
      .duty_resolution = LEDC_DUTY_RES,
      .freq_hz = 50,
      .clk_cfg = LEDC_AUTO_CLK,
  };
  ESP_ERROR_CHECK(ledc_timer_config(&t));

  const ledc_channel_config_t c = {
      .gpio_num = SERVO_GPIO,
      .speed_mode = LEDC_MODE,
      .channel = LEDC_CHANNEL,
      .timer_sel = LEDC_TIMER,
      .duty = 0,
      .hpoint = 0,
  };
  ESP_ERROR_CHECK(ledc_channel_config(&c));
}

static void servo_set_us(uint32_t us) {
  if (us < SERVO_MIN_US) {
    us = SERVO_MIN_US;
  }

  if (us > SERVO_MAX_US) {
    us = SERVO_MAX_US;
  }

  const uint32_t duty = us * SERVO_MAX_DUTY / SERVO_PERIOD_US;

  ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
}

void servo_set_angle(float angle) {

  if (angle > SERVO_MAX_ANGLE) {
    angle = SERVO_MAX_ANGLE;
  }

  if (angle < SERVO_MIN_ANGLE) {
    angle = SERVO_MIN_ANGLE;
  }

  const uint32_t us = SERVO_MIN_US + (uint32_t)((angle / 180.0f) *
                                                (SERVO_MAX_US - SERVO_MIN_US));
  servo_set_us(us);

  ESP_LOGI("servo: ", "Angle %f", angle);
}