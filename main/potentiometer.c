#include "potentiometer.h"
#include <esp_adc/adc_oneshot.h>
#include <hal/adc_types.h>
#include <stdint.h>

static adc_oneshot_unit_handle_t adc_handle;
static adc_unit_t unit;
static adc_channel_t channel;

void setup_potentiometer() {
  ESP_ERROR_CHECK(adc_oneshot_io_to_channel(PIN_ADC, &unit, &channel));

  const adc_oneshot_unit_init_cfg_t config = {
      .unit_id = unit,
  };
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&config, &adc_handle));

  const adc_oneshot_chan_cfg_t channel_config = {
      .bitwidth = BITWIDTH,
      .atten = ATTENUATION,
  };

  ESP_ERROR_CHECK(
      adc_oneshot_config_channel(adc_handle, channel, &channel_config));
}

int read_potentiometer() {
  int raw;
  ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, channel, &raw));

  return raw;
}