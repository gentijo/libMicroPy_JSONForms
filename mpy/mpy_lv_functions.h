#ifndef __MPY_LV_FUNCS_H__
#define __MPY_LV_FUNCS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "py/runtime.h"
#include "py/obj.h"

extern lv_disp_t *g_display;

mp_obj_t mpy_init_screen();

void     mpy_init_LvObjectFactory();

mp_obj_t mpy_create_LvObject(
    const mp_obj_t objInfoIn, 
    const mp_obj_t propertiesIn, 
    const mp_obj_t parentIn);

mp_obj_t mpy_load_screen();

#ifdef __cplusplus
}
#endif

#endif


