#ifndef __MPY_LV_OBJECT_FACTORY_H__
#define __MPY_LV_OBJECT_FACTORY_H__

#include <stdio.h>
#include <string.h>

#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

#include <iostream>
#include <sstream>


#include "mpy_LvObject.h"
#include "mpy_LvObjectFactory.h"


class mpy_LvObjectFactory {

    public:
        virtual mpy_LvObject* create(const char * type, mpy_LvObject* parent);
};


void add_LvObjectFactory(mpy_LvObjectFactory *f);

//
//
extern std::list<mpy_LvObjectFactory *> lvObjectFactories;

//
// List of all objects created named or not.
extern std::vector<mpy_LvObject *> g_lvObjectList;

//
// For objects that have a name tag, store a pointer to that element here
extern std::map<const char *, mpy_LvObject *> g_namedObject;


#endif