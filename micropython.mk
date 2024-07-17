JSONForms_MOD_DIR := $(USERMOD_DIR)

LVGL_DIR_ = $(USERMOD_DIR)../../../lv_micropython/lib/lv_bindings/lvgl/src
LVGL_DIR = $(abspath $(LVGL_DIR_))

MICROPY_JSONForms_INC = -I$(JSONForms_MOD_DIR)/object-mgr -I$(JSONForms_MOD_DIR)/cJSON 

$(info  LVGL_DIR )
$(info $(LVGL_DIR))

# Add all C files to SRC_USERMOD.
define SRC_USERMOD +=      
    $(JSONForms_MOD_DIR)/arch/unix/main_unix.c 
    $(JSONForms_MOD_DIR)/cJSON/cJSON.c
    $(JSONForms_MOD_DIR)/cJSON/cJSON_Utils.c
endef

CFLAGS_USERMOD += -I$(JSONForms_MOD_DIR) -I$(LVGL_DIR) $(MICROPY_JSONForms_INC)

define SRC_USERMOD_CXX +=      
    $(JSONForms_MOD_DIR)/arch/unix/display_thread.cpp
    $(JSONForms_MOD_DIR)/mpy_lv_functions.cpp 
    $(JSONForms_MOD_DIR)/object-mgr/mpy_LvObjectFactory.cpp 
    $(JSONForms_MOD_DIR)/object-mgr/mpy_LvObject.cpp 
    $(JSONForms_MOD_DIR)/object-mgr/cJSON_helpers.cpp 
endef

# Add our module directory to the include path.
CXXFLAGS_USERMOD += $(CFLAGS_USERMOD) -std=c++11 -lstdc++.11


MICROPY_FROZEN_MANIFEST += ${MICROPY_JSONForms_DIR}/manifest.py

