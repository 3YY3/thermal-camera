#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "softpower.h"
#include "display/gui/gui.h"
#include "display/render.h"
#include "driver/adc.h"
#include "include/user_task.h"
#include "esp_partition.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"

/*
 * This task handles interaction from the user via the touch screen/buttons.
 */

static const char* TAG = "UserTask";

void user_task()
{
  bool DeadBatt = false;
  int16_t MinBatt = 418; // Value 512 equals to 2.2V (4.4V before voltage divider), there comes value 418 (1.8V or 3.6V respectively)

  // Add a LOW BATT sign component
  gui_comp_t* batt_pip_comp = malloc(sizeof(gui_comp_t));
  batt_pip_comp->visible = false;
  batt_pip_comp->left = 124;
  batt_pip_comp->top = 5;
  batt_pip_comp->text = malloc(sizeof(gui_comp_text_t));
  strcpy(batt_pip_comp->text->text, "LOW BATT!");
  ESP_LOGW(TAG, "Battery voltage low!");
  batt_pip_comp->text->colour = RGB_TO_16BIT(255, 0, 0);
  batt_pip_comp->rectangle = NULL;
  gui_add_comp(batt_pip_comp);

  for(;;) {

    #if !CONFIG_NO_SOFTPOWER
    // Sniff the power switch state
    if(!softpower_get_desired_state()) {
      // The power switch is off, immediately go into deep sleep...
      ESP_LOGW(TAG, "power switch has entered state <0> - going to deep sleep");
      softpower_pf_off();
      softpower_deep_sleep();
    }
    #endif

    // Check battery voltage
    if (adc1_get_raw(ADC1_CHANNEL_6) < MinBatt && DeadBatt == false) {
      batt_pip_comp->visible = true;
      DeadBatt = true;
    }
  }
}
