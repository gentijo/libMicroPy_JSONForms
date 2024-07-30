#include <map>
#include <string>
#include <vector>
#include <list>


extern "C" {

#include "cJSON/cJSON.h"

}

#include "mpy_LvObjectFactory.h"
#include "mpy_LvBaseObjects.h"
//
//
std::list<mpy_LvObjectFactory *> lvObjectFactories;

//
// List of all objects created named or not.
std::vector<mpy_LvObject *> g_lvObjectList;

//
// For objects that have a name tag, store a pointer to that element here
std::map<const char *, mpy_LvObject *> g_namedObject;


void add_LvObjectFactory(mpy_LvObjectFactory *f)
{
    if (f != NULL)
    {
        lvObjectFactories.push_front(f);
    }
}

/**
 * 
 * 
 * 
*/
mpy_LvObject *mpy_LvObjectFactory::create(const char *type, mpy_LvObject *parent)
{
    printf("Type: %s\r\n", type);
    if (strcmp(type, "HorizontalLayout")==0)
    {
        return new mpy_LvHorizontalLayout(parent);
    }

    if (strcmp(type, "VerticalLayout")==0)
    {
        return new mpy_LvVerticalLayout(parent);
    }

    if (strcmp(type, "Container")==0)
    {
        return new mpy_LvContainer(parent);
    }

    if (strcmp(type, "Button")==0)
    {
        return new mpy_LvButton(parent);
    }
    return NULL;
};

 