import JSONForms_LVGL_Driver
from JSONForms_Style import JSONForms_Style

#
#
#
class JSONForms_Driver:
    
    @staticmethod
    def init_JSONForms_Screen()->object:
        return JSONForms_LVGL_Driver.init_screen()

    @staticmethod
    def create_JSONForms_Object(objType, scope, name, properties, parent) -> object:
        
        styles:dict = JSONForms_Style.buildCompositeStyle(objType, scope, name, properties )
        
        if (not scope): scope=""
        if (not name): name=""
        
        objInfo = {
            "type": objType,
            "scope": scope,
            "name":  name
        }
        
        tObjStr =  str(objInfo);
        tObjStr = tObjStr.replace("'", '"');

        tStyleStr = str(styles)
        tStyleStr = tStyleStr.replace("'", '"');
        return JSONForms_LVGL_Driver.create_LvObject(tObjStr, tStyleStr, parent)

#
#
#
class JSONForms_MockDriver(JSONForms_Driver):

    def __init__():
        pass

    def init_JSONForms_Screen()->object:
        print("Init LVGL Screen")
        return "root-screen"


    def create_JSONForms_Object(type, scope, name, properties, parent) -> object:
        styles:dict = JSONForms_Style.buildCompositeStyle(type, scope, name, properties )

        fqon:str = f"Type:{type}-Scope:{scope}-Name:{name}"
        
        print(f"\r\n---------------------------------------------------")
        print(f"Creating LV Object, {fqon}")
        print(f"Style Data: {styles}")
        print(f"---------------------------------------------------\r\n")
        return fqon

        

    def set_FormObject_Style(self, style:dict):
        pass



