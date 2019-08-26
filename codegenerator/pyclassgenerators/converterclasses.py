# converterclasses.py
# 
# created 06.07.17
# 
# autor: Sebastian Buerger @ SurgiTAIX AG
#
# this collection contains modules to generate the content of the C++ converter classes. 
# These classes are used to convert the API types generated by the pyCodeGen or by GLS to the types generated by XSD // xerces
 

# ConvertFromCDM header
class CppConvertFromCDMClassDeclarationBuilder(object):
    def __init__(self):
        self.__nonBasetype = ''
        self.__basetype = ''
        
    def addNonBasetype(self, typeName, abstractBool):
        if not abstractBool:
            self.__nonBasetype = self.__nonBasetype + '\tstatic ' + typeName +' convert(const CDM::' + typeName + ' & source);\n'
        
    def getNonBasetypeCoverterFunctionsDeclarations(self):
        return self.__nonBasetype
    
    def getBasetypeCoverterFunctionsDeclarations(self):
        return self.__basetype


# Separate class for EnumConverterFunctions for ConvertFromCDM
class CppConvertFromCDMClassEnumConverterFunctionBuilder(object):    
    def __init__(self, typeName):
        self.__type_name = typeName
        self.__content = self.__type_name + ' ConvertFromCDM::convert(const CDM::' + self.__type_name + ' & source) {\n\tswitch (source) {\n'
    
    def addConvertEnumEntry(self, enum_name):
        self.__content = self.__content + '\t\tcase CDM::' + self.__type_name +  '::' + enum_name +': return ' + self.__type_name + '::' + enum_name + ';\n'
        
    def getEnumConverterFunction(self):
        return self.__content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.__type_name + '\");\n}\n\n'
        

# ConvertFromCDM definition
class CppConvertFromCDMClassDefinitionBuilder(object):
    def __init__(self, basetype_map):
        self.__enums = ''
        self.__includes = ''
        self.__complex = ''
        self.__itemList = ''
        self.__baseTypes = ''
        self.__basetype_map = basetype_map
    
    def addComplexType(self, typeName, abstractBool):
        if not abstractBool:
            self.__complex = self.__complex + typeName + ' ConvertFromCDM::convert(const CDM::' + typeName +' & source) {\n\treturn ' + typeName + '(source);\n}\n\n'
            self.__includes = self.__includes + '#include \"SDCLib/Data/SDC/MDIB/'+ typeName + '.h\"\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.__enums = self.__enums + enumConverterFunction_string;
        
    def addItemList(self,simpleTypeName):
        self.__itemList = self.__itemList + simpleTypeName + ' ConvertFromCDM::convert(const CDM::' + simpleTypeName + ' & source) {\n\t' + simpleTypeName + ' list;\n' + '\tfor (const auto & element : source) {\n\t\tlist.push_back(element);\n\t}\n\treturn list;\n}\n\n'

    def getEnumsAsString(self):
        return self.__enums;
    
    def getIncludesAsString(self):
        return self.__includes
    
    def getComplexTypeFuctionsAsString(self):
        return self.__complex
    
    def getItemListAsString(self):
        return self.__itemList
    
    def getBaseTypesAsString(self):
        return self.__baseTypes
    
    
# ConvertToCDM header - simpleTypes only. complex types are transformed only in the definition via template method
class CppConvertToCDMClassDeclarationBuilder(object):
    def __init__(self):
        self.__nonBasetype = ''
        self.__basetype = ''
        
    def addNonBasetype(self, typeName):
        self.__nonBasetype = self.__nonBasetype + '\tstatic CDM::' + typeName +' convert(const ' + typeName + ' & source);\n'
        
    def getNonBasetypeCoverterFunctionsDeclarations(self):
        return self.__nonBasetype
    
    def getBasetypeCoverterFunctionsDeclarations(self):
        return self.__basetype

    
# Separate class for EnumConverterFunctions for ConvertToCDM
class CppConvertToCDMClassEnumConverterFunctionBuilder(object):    
    def __init__(self, typeName):
        self.__type_name = typeName
        self.__content = 'CDM::' + self.__type_name + ' ConvertToCDM::convert(const ' + self.__type_name + ' & source) {\n\tswitch (source) {\n'
    
    def addConvertEnumEntry(self, enum_name):
        self.__content = self.__content + '\t\tcase ' + self.__type_name +  '::' + enum_name +': return CDM::' + self.__type_name + '::' + enum_name + ';\n'
        
    def getEnumConverterFunction(self):
        return self.__content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.__type_name + '\");\n}\n\n'
    

# ConvertToCDM definition
class CppConvertToCDMClassDefinitionBuilder(object):
    def __init__(self):
        self.__enums = ''
        self.__includes = ''
        self.__complex = ''
        self.__itemList = ''
        self.__baseTypes = ''
    
    def addComplexType(self, typeName, abstractBool):
        if not abstractBool:
            self.__includes = self.__includes + '#include \"SDCLib/Data/SDC/MDIB/'+ typeName + '.h\"\n'
            self.__complex = self.__complex + 'template\nstd::unique_ptr<typename ' + typeName + '::WrappedType> ConvertToCDM::convert(const '+ typeName + ' & source);\n\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.__enums = self.__enums + enumConverterFunction_string;

    def addItemList(self,simpleTypeName):
        self.__itemList = self.__itemList + 'CDM::' + simpleTypeName + ' ConvertToCDM::convert(const ' + simpleTypeName + ' & source) {\n\tCDM::' + simpleTypeName + ' list;\n' + '\tfor (const auto & element : source) {\n\t\tlist.push_back(element);\n\t}\n\treturn list;\n}\n\n'

    def getEnumsAsString(self):
        return self.__enums;
    
    def getIncludesAsString(self):
        return self.__includes
    
    def getComplexAsString(self):
        return self.__complex

    def getItemListAsString(self):
        return self.__itemList
    
    def getBasetype(self):
        return self.__baseTypes
