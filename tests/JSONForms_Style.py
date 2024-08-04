import json

class JSONForms_Style:

    styles:dict = {}

    @staticmethod
    def parseStyleDefinition(definitionIn:dict) -> None:
        for name in definitionIn:
            styleDef=definitionIn[name]
            if ("properties" in styleDef):
                properties = styleDef["properties"]
                styles = styleDef["properties"]
                JSONForms_Style.styles[name]=styles

    @staticmethod
    def parseStyleDefinitionFromJSONFile(filename:str) -> None:
        with open(filename) as f:
            definition = json.load(f)
            JSONForms_Style.parseStyleDefinition(definition)

    @staticmethod
    def addStyleToDict(properties:dict, style:dict) -> None:
        for key in style:
            properties[key]=style[key]

    @staticmethod
    def buildCompositeStyle(type:str=None, scope:str=None, name:str=None, propertiesIn:dict={} ) -> dict:
        
        properties = {}

        if type and (type in JSONForms_Style.styles):
            JSONForms_Style.addStyleToDict(properties, JSONForms_Style.styles[type])

        if scope and (scope in JSONForms_Style.styles):
            JSONForms_Style.addStyleToDict(properties, JSONForms_Style.styles[scope])

        if name and (name in JSONForms_Style.styles) :
            JSONForms_Style.addStyleToDict(properties, JSONForms_Style.styles[name])

        if propertiesIn and len(propertiesIn):
            for key in propertiesIn:
                properties[key]=propertiesIn[key];

        return properties;


    @classmethod
    def dumpParsedStyles():
        print (JSONForms_Style.styles)

