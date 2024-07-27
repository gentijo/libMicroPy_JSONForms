#include <stdio.h>

#include "py/runtime.h"
#include "py/obj.h"

#include "lvgl.h"
#include "mpy_lv_functions.h"
#include <thread>
#include <chrono>
#include "display_thread.h"


/***
 * 
 * 
 * 
*/
void run_display_loop()
{
  //mp_thread_init(pxTaskGetStackStart(NULL), MICROPY_TASK_STACK_SIZE / sizeof(uintptr_t));


  while (1)
  {
    int timerTaskDelay = 0;
    // raise the task priority of LVGL and/or reduce the handler period can
    // improve the performance
    std::this_thread::sleep_for (std::chrono::milliseconds(5));
    lv_tick_inc(5);

    // The task running lv_timer_handler should have lower priority than that
    // running `lv_tick_inc`

    lv_task_handler();

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
mp_obj_t mp_init_display()
{
  init_LvObjectFactory();

  static std::thread thread_obj(run_display_loop);

  return mp_const_none;
}

