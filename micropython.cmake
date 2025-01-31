# Create an INTERFACE library for our C module.
add_library(libMicroPy_JSONForms INTERFACE)


get_filename_component(MICROPY_JSONForms_DIR ../../../../modules/libMicroPy_JSONForms ABSOLUTE)


set (LVGL_DRIVER_SRC 
    ${MICROPY_JSONForms_DIR}/lvgl_drivers/ESP32/ESP32S3_8048S050C/bsp.c
)

set (LVGL_DRIVER_INC 
    ${MICROPY_JSONForms_DIR}/lvgl_drivers/ESP32/ESP32S3_8048S050C
)

set (MICROPY_JSONForms_SRC
    ${MICROPY_JSONForms_DIR}/main.c
    ${MICROPY_JSONForms_DIR}/mpy_lv_functions.cpp
    ${MICROPY_JSONForms_DIR}/object-mgr/mpy_LvObjectFactory.cpp
    ${MICROPY_JSONForms_DIR}/object-mgr/mpy_LvObject.cpp
    ${MICROPY_JSONForms_DIR}/object-mgr/cJSON_helpers.cpp
    ${LVGL_DRIVER_SRC}

)

list(APPEND MICROPY_FROZEN_MANIFEST
    ${MICROPY_JSONForms_DIR}/manifest.py
)

message("FROZEN CONTENT: ${MICROPY_FROZEN_MANIFEST}")


set (MICROPY_JSONForms_INC  
    "."
    ${MICROPY_JSONForms_DIR}/object-mgr
    ${MICROROS_INC_DIR}/std_msgs
    ${MICROROS_INC_DIR}/sensor_msgs
    ${MICROROS_INC_DIR}/rosidl_typesupport_introspection_c
    ${LVGL_DRIVER_INC}
)

# Add our source files to the lib
target_sources(libMicroPy_JSONForms INTERFACE
    ${MICROPY_JSONForms_SRC}
)

# Add the current directory as an include directory.
target_include_directories(libMicroPy_JSONForms INTERFACE
    ${MICROPY_JSONForms_INC}
)

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE libMicroPy_JSONForms)

