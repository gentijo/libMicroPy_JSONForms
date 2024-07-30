#ifndef __MPY_LV_FUNCTIONS_H__
#define __MPY_LV_FUNCTIONS_H__


#include <stdio.h>
#include <string.h>

#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

#include <iostream>
#include <sstream>

#include "object-mgr/mpy_LvBaseObjects.h"
#include "object-mgr/mpy_LvObjectFactory.h"

#include "mpy/mpy_lv_functions.h"
#include "object-mgr/cJSON_helpers.h"

//
// HAndle to the LCD Display
lv_disp_t *g_display = NULL;
lv_obj_t  *g_ui_Screen = NULL;

mp_obj_t mpy_init_screen() {
  
    //printf("Init lvgl screen\r\n");
    mpy_init_LvObjectFactory();

    // lv_theme_t *theme = lv_theme_default_init(
    //   g_display, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
    //   false, LV_FONT_DEFAULT);
    
    // lv_disp_set_theme(g_display, theme);
  
    g_ui_Screen = lv_obj_create(NULL);
    printf("(screen) lv_obj_create(NULL); = [%p]\r\n",  g_ui_Screen);
    lv_obj_clear_flag(g_ui_Screen, LV_OBJ_FLAG_SCROLLABLE); 
    lv_obj_set_size (g_ui_Screen, 800, 480);/// Flags

    lv_obj_set_x(g_ui_Screen, 0);
    lv_obj_set_y(g_ui_Screen, 0);
        
    static lv_style_t style;
    lv_style_init(&style);
    // //lv_style_set_radius(&style, 3);
    lv_style_set_outline_width(&style, 0);
    lv_style_set_outline_pad(&style, 0);

    lv_style_set_pad_all(&style, 1);

    lv_obj_add_style(g_ui_Screen, &style, 0);
    
    lv_obj_set_style_border_color(g_ui_Screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(g_ui_Screen, 0, LV_PART_MAIN);
    lv_obj_set_align(g_ui_Screen, LV_ALIGN_CENTER);

    mpy_LvObject* mpy_LvObj = new mpy_LvObject(g_ui_Screen);
    g_lvObjectList.push_back(mpy_LvObj);

    lv_disp_load_scr(g_ui_Screen);

    const void * address = static_cast<const void*>(mpy_LvObj);
    std::stringstream ss;
    ss << address;  
    std::string str = ss.str(); 
    printf("Init Lv Screen complete: Lv[%p] [%p] mpyObj[%p] str[%s]\r\n", g_ui_Screen, mpy_LvObj->lvObject, mpy_LvObj,  str.c_str());
    mp_obj_t mp_str_ptr = mp_obj_new_str(str.c_str(), str.size());

    return mp_str_ptr;
}

mp_obj_t mpy_load_screen() {

    lv_disp_load_scr(g_ui_Screen);
    return mp_const_none;

}

/**
 * 
 * 
 * 
 */
void  mpy_init_LvObjectFactory() {
    //printf("Obj Fac Init\r\n");
    mpy_LvObjectFactory *f = new mpy_LvObjectFactory();
    add_LvObjectFactory(f);
}

/**
 *
 *
 *
 */
mp_obj_t mpy_create_LvObject(const mp_obj_t objInfoIn, const mp_obj_t propertiesIn, const mp_obj_t parentIn)
{    
    char emptyString[2] = "";

    cJSON *cJSONObjInfo = NULL;
    if (&mp_type_str != mp_obj_get_type(objInfoIn) && mp_const_none != objInfoIn)
    {
        mp_raise_TypeError(MP_ERROR_TEXT("ObjInfo field must be a string"));
        return mp_const_none;
    }
    else if (mp_const_none != objInfoIn)
    {
        const char* c = mp_obj_str_get_str(objInfoIn);
        if ((c != NULL) && (strlen(c)>0)) {

            cJSONObjInfo = cJSON_Parse(c);
            if (cJSONObjInfo == NULL) {
                mp_raise_ValueError(MP_ERROR_TEXT("Error parsing ObjInfo"));
                return mp_const_none;           
            }
        }
        else 
        {
            mp_raise_TypeError(MP_ERROR_TEXT("ObjInfo field must be a string"));
            return mp_const_none;           
        }
    }

//
//
    const char *cType = NULL;
    if (!getcJSON_StringProperty(cJSONObjInfo, "type", &cType) || (NULL == cType) || (strlen(cType) ==0)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Type property in ObjInfo is required"));
        return mp_const_none;
    }

    const char *cScope = NULL;
    getcJSON_StringProperty(cJSONObjInfo, "scope", &cScope);
    if (cScope == NULL) cScope=emptyString;

    const char *cName = NULL;
    getcJSON_StringProperty(cJSONObjInfo, "name", &cName);
    if (cName == NULL) cName=emptyString;


  //
  //
    cJSON *cJSONProps = NULL;
   
    if (&mp_type_str != mp_obj_get_type(propertiesIn) && mp_const_none != propertiesIn)
    {
        mp_raise_TypeError(MP_ERROR_TEXT("Properties field must be a string"));
        return mp_const_none;
    }
    else if (mp_const_none != propertiesIn)
    {
        const char *cProperties = mp_obj_str_get_str(propertiesIn);
        //printf("Properties %s\r\n", cProperties);
        cJSONProps = cJSON_Parse(cProperties);
    }

//
//

    // For safety, let's validate that the parent object is an object we created in the past.
    mpy_LvObject *cParent = NULL;

    const char *cParentStr = emptyString;

    if (parentIn != mp_const_none) {
        cParentStr = mp_obj_str_get_str(parentIn);
        //printf("PArent str addr %s\r\n", cParentStr);

        std::stringstream ss;
        ss << cParentStr;
        void* tmp;
        ss >> tmp ;

        //printf("Parent ptr %p\r\n", tmp);
        cParent = reinterpret_cast<mpy_LvObject*>(tmp);
    }
    else {
        printf("Parent Object is NULL\r\n");
    }

    //
    // Object type was not a base object, so let's other Factories if they know this object
    mpy_LvObject *mpy_lvobj = NULL;
    std::_List_iterator<mpy_LvObjectFactory*> it;
    for (it = lvObjectFactories.begin(); it != lvObjectFactories.end(); ++it)
    {   
        mpy_LvObjectFactory* f = *it;
        mpy_lvobj = f->create(cType, cParent);
        if (mpy_lvobj != NULL) break;
    }

    if (mpy_lvobj == NULL)
    {
        mp_raise_TypeError(MP_ERROR_TEXT("Unknown Element type"));
        return mp_const_none;
    }

    //printf("Adding Ob Style\r\n");
    mpy_lvobj->addLvObjectStyle(cJSONProps);

    if (cName != NULL)
    {
        g_namedObject[cName] = mpy_lvobj;
    }

    //printf("Adding to object list\r\n");
    g_lvObjectList.push_back(mpy_lvobj);

    cJSON_Delete(cJSONProps);

    if (mpy_lvobj != NULL)
    {
        const void * address = static_cast<const void*>(mpy_lvobj);
        std::stringstream ss;
        ss << std::hex << address;  
        std::string str = ss.str(); 

        printf("Create Lv Object complete: Lv[%p] str[%s]\r\n", mpy_lvobj, str.c_str());
        mp_obj_t mp_str_ptr = mp_obj_new_str(str.c_str(), str.size());
        return mp_str_ptr;
    }
    else return mp_const_none;
};


#endif