#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task.h"

#include "bsp.h"
#include "esp3d_log.h"

#include "esp_task.h"
#include "mpconfigport.h"
#include "mpthreadport.h"

#include "lvgl.h"
#include "sdkconfig.h"

#define MP_LV_TASK_PRIORITY (ESP_TASK_PRIO_MIN)


TaskHandle_t mp_lcd_display_task_handle;


/***
 * 
 * 
 * 
*/
void run_display_loop()
{
  mp_thread_init(pxTaskGetStackStart(NULL), MICROPY_TASK_STACK_SIZE / sizeof(uintptr_t));

  while (1)
  {
    int timerTaskDelay = 0;
    // raise the task priority of LVGL and/or reduce the handler period can
    // improve the performance
    vTaskDelay(pdMS_TO_TICKS(10));

    // The task running lv_timer_handler should have lower priority than that
    // running `lv_tick_inc`
    lv_tick_inc(10);
    // lv_task_handler();

    if ((timerTaskDelay++ % 3) == 0)
    {
      lv_timer_handler();
    }
  }
}


/**
 * 
 * 
 * 
*/
void init_display_thread() {

  xTaskCreate(run_display_loop, "mpy_lcd_task",
              MICROPY_TASK_STACK_SIZE / sizeof(StackType_t), NULL, MP_LV_TASK_PRIORITY,
              &mp_lcd_display_task_handle);

}

