#include "mpy_LvObject.h"

extern "C" {
#include <stdio.h>
#include <string.h>

#include "py/obj.h"
#include "py/runtime.h"
}

/***
 * 
 * 
 * 
*/
void mpy_LvObject::addLvObjectStyle(const cJSON *properties)
{
    cJSON *iterator = NULL;

    //printf("Properties: %s\r\n", cJSON_Print(properties));

    cJSON_ArrayForEach(iterator, properties)
    {
       // printf("Property %s\r\n", iterator->string);
        

        if (strcmp(iterator->string, "size")==0)
        {
            this->setSize(iterator);
        }

        if (strcmp(iterator->string, "pad-all")==0)
        {
            this->setPadAll(iterator);
        }

        if (strcmp(iterator->string, "label")==0)
        {
            this->setLabel(iterator);
        }
    }
};




/**
 * 
 * 
 * 
*/
void mpy_LvObject::setSize(const cJSON *properties)
{
    int height = this->getIntStyleProperty(properties, "height");
    int width = this->getIntStyleProperty(properties, "width");
    lv_obj_set_size(lvObject, width,  height);
};

/**
 * 
 * 
 * 
*/
void mpy_LvObject::setPadAll(const cJSON *properties)
{
    int size = this->getIntStyleProperty(properties, "size");
    lv_style_set_pad_all(&style, size);
    lv_obj_add_style(lvObject, &style, 0);
};


/**
 * 
 * 
 * 
*/
int mpy_LvObject::getIntStyleProperty(const cJSON *properties, const char *name)
{

    cJSON* obj = cJSON_GetObjectItem(properties, name);
    if (obj != NULL)
    {
        return obj->valueint;
    }
    mp_raise_TypeError(MP_ERROR_TEXT("Property is required"));
    return 0;
};


/***
 * 
 * 
 * 
*/
char *mpy_LvObject::getStringStyleProperty(const cJSON *properties, const char *name)
{
    cJSON* obj = cJSON_GetObjectItem(properties, name);
    if (obj != NULL)
    {
        return obj->valuestring;
    }
    mp_raise_TypeError(MP_ERROR_TEXT("property is required"));
    return NULL;
};
