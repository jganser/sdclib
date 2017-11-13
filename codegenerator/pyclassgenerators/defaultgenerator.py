# defaultgenerator.py
# 
# created 20.76.17
# 
# autor: Sebastian Buerger @ SurgiTAIX AG
#
# These classes generate the default.h/cpp, files that contain default values for each types. 
# The resulting file is not compilable and needs further editing. 


class DefaultDeclarationBuilder(object):
    def __init__(self):
        self.__functionDeclarations = ''

        
    def addFunction(self,complexTypeName, abstractBool):
        if not abstractBool:
            self.__functionDeclarations = self.__functionDeclarations + '\tstatic CDM::' + complexTypeName + ' * ' + complexTypeName + '();\n'
        
    def getContent(self):
        return self.__functionDeclarations 
    

class DefaultDefinitionBuilder(object):
    def __init__(self):
        self.__functionDefinition = ''
        self.__includes = ''
        
    def addFunction(self, complexTypeName, abstractBool):
        if not abstractBool:
            self.__includes = self.__includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ complexTypeName + '.h\"\n'
            self.__functionDefinition = self.__functionDefinition + 'CDM::' + complexTypeName + '  * Defaults::' + complexTypeName + '() {\n\treturn new CDM::' + complexTypeName + '();\n}\n\n'
                
    def getContent(self):
        return self.__functionDefinition 
    
    def getIncludes(self):
        return self.__includes + '\n\n'