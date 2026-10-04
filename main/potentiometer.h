#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#define READ_PERIOD UINT64_C(100000)
#define PIN_ADC 4
#define ATTENUATION ADC_ATTEN_DB_12
#define BITWIDTH ADC_BITWIDTH_DEFAULT
#define ADC_LEVELS 4096

void setup_potentiometer();

int read_potentiometer();

#endif