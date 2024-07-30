JSONForms_MOD_DIR := $(USERMOD_DIR)

LVGL_DIR_ = $(USERMOD_DIR)../../../lv_micropython/lib/lv_bindings/lvgl
LVGL_DIR = $(abspath $(LVGL_DIR_))


# Add all C files to SRC_USERMOD.
define SRC_USERMOD +=      
    $(JSONForms_MOD_DIR)/mpy/mpy_main.c
    $(JSONForms_MOD_DIR)/cJSON/cJSON.c
    $(JSONForms_MOD_DIR)/cJSON/cJSON_Utils.c
endef


define SRC_USERMOD_CXX +=      
    $(JSONForms_MOD_DIR)/arch/unix/display_thread.cpp
    $(JSONForms_MOD_DIR)/mpy/mpy_lv_functions.cpp
    $(JSONForms_MOD_DIR)/object-mgr/mpy_LvObjectFactory.cpp
    $(JSONForms_MOD_DIR)/object-mgr/mpy_LvObject.cpp
    $(JSONForms_MOD_DIR)/object-mgr/cJSON_helpers.cpp
endef

$(info  LVGL_DIR )
$(info $(LVGL_DIR))


LDFLAGS_USERMOD += -lstdc++ 

CFLAGS_USERMOD += -I $(LVGL_DIR) -I $(JSONForms_MOD_DIR)
$(info $(CFLAGS_USERMOD))

FROZEN_MANIFEST += ${JSONForms_MOD_DIR}/manifest.py

