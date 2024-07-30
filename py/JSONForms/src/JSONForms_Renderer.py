import json
from JSONForms_Driver import JSONForms_Driver, JSONForms_MockDriver

from JSONForms_Style import JSONForms_Style
from JSONForms_Driver import JSONForms_Driver

class JSONForms_Renderer:
    driver:JSONForms_Driver = JSONForms_Driver
#
#
#
    @staticmethod
    def enableTestMode():
        print("Entering test mode")
        JSONForms_Renderer.driver = JSONForms_MockDriver

#
#
#
    @staticmethod
    def parseLayoutDefinitionFromJSONFile(filename:str) -> None:
        print(filename)    
        with open(filename) as f:
            definition = json.load(f)
            print(definition)
            JSONForms_Renderer.parseLayoutDefinition(definition)
#
#
#
    @staticmethod
    def parseLayoutDefinition(definition:dict):
        screen = JSONForms_Driver.init_JSONForms_Screen()
        parentObjects:list = []
        parentObjects.append(screen);
        JSONForms_Renderer.parseFormObject(definition, parentObjects)

#
#
#
    @staticmethod
    def parseFormObject(schema:dict, parentLvObjects:list=None) -> object:

        print("\r\n\nParse Form Object\r\n")
        objType:str = None
        name:str = None
        scope:str = None
        properties:dict = {}
        elements:dict = {}

        if 'type' in schema:
            objType= schema['type']

        if 'name' in schema:
            name= schema['name']
        
        if 'scope' in schema:
            scope= schema['scope']
            
        if 'properties' in schema:
            properties= schema['properties']

        if 'elements' in schema:
            elements= schema['elements']

        parent = None
        if len(parentLvObjects) > 0:
            parent = parentLvObjects[-1]
            
        print("Parent Object size: ", len(parentLvObjects), parent)
        
        lvObject = JSONForms_Renderer.driver.create_JSONForms_Object(objType, scope, name, properties, parent)
        parentLvObjects.append(lvObject)
        print("Parent Objects ", parentLvObjects)

        for element in elements:
            JSONForms_Renderer.parseFormObject(element, parentLvObjects)

        del parentLvObjects[-1]
