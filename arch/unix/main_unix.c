#include <stdio.h>

#include "py/runtime.h"
#include "py/obj.h"

#include "lvgl.h"
#include "mpy_lv_functions.h"
#include "display_thread.h"

/**
 * Create MP objects that can be registered with Micropython from MicroROS
 * This will represent the microros builtin class, with the functions that make up the MicroROS SDK
 *
 */
MP_DEFINE_CONST_FUN_OBJ_0(init_display_obj, mp_init_display);
MP_DEFINE_CONST_FUN_OBJ_3(create_LvObject_obj, create_LvObject);
MP_DEFINE_CONST_FUN_OBJ_0(display_lvgl_screen_obj, display_lvgl_screen);



const mp_rom_map_elem_t mp_gui_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_JSONForms_LVGL_Driver)},
    {MP_ROM_QSTR(MP_QSTR_init_display), MP_ROM_PTR(&init_display_obj)},
    {MP_ROM_QSTR(MP_QSTR_create_LvObject), MP_ROM_PTR(&create_LvObject_obj)},
    {MP_ROM_QSTR(MP_QSTR_display_lvgl_screen), MP_ROM_PTR(&display_lvgl_screen_obj)},

};

MP_DEFINE_CONST_DICT(mp_gui_module_globals, mp_gui_module_globals_table);

const mp_obj_module_t mp_gui_cmodule = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&mp_gui_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_MicroPy_JSONForms, mp_gui_cmodule);
