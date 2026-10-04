idf_component_register(SRCS "potentiometer-servo-control.c" "potentiometer.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES esp_timer log esp_adc)