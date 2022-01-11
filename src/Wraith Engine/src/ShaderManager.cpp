#include "ShaderManager.h"
#include <cassert>
#include <exception>
#include "File.h"
#include "ShaderObject.h"

ShaderManager* ShaderManager::pShaderManagerInstance = nullptr;

//-----------------------------------------------------------------------------------------------------------------------------
// Gettng Shader Manager
//-----------------------------------------------------------------------------------------------------------------------------
ShaderManager& ShaderManager::GetInstance()
{
	if (pShaderManagerInstance == nullptr)
	{
		pShaderManagerInstance = new ShaderManager();
	}
	assert(pShaderManagerInstance);
	return *pShaderManagerInstance;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Instaniating Shader Manager
//-----------------------------------------------------------------------------------------------------------------------------
ShaderManager::ShaderManager()
{
	ShaderManager::DebugPrint("Default Constructor called");
	privSetDefaultPath("Shaders/");
	loadDefaultShaders();
	ShaderManager::DebugPrint("");
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setting Default Path
//-----------------------------------------------------------------------------------------------------------------------------
void ShaderManager::privSetDefaultPath(const std::string defaultPath)
{
	ShaderManager::DebugPrint("Setting Default Path to \"" + defaultPath + "\"");
	_defaultPath = defaultPath;
}

// Instaniating helper function
void ShaderManager::loadDefaultShaders()
{
	ShaderManager::DebugPrint("Loading default shaders");
	privLoadShaderAndAssignKey("textureFlatRender", getDefaultShaderKey(DefaultShader::TEXTURE));
	privLoadShaderAndAssignKey("textureLightRender", getDefaultShaderKey(DefaultShader::LIGHTED_TEXTURE));
	privLoadShaderAndAssignKey("colorConstantRender", getDefaultShaderKey(DefaultShader::CONSTANT_COLOR));
	
	privLoadShaderAndAssignKey("spriteRender", getDefaultShaderKey(DefaultShader::SPRITE));
}

//-----------------------------------------------------------------------------------------------------------------------------
// Loading Shaders
//-----------------------------------------------------------------------------------------------------------------------------
void ShaderManager::privLoadShaderAndAssignKey(const std::string& fileName, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	const std::string filePath = ShaderManager::_defaultPath + fileName;
	if (!isFilePathValid(filePath)) printFileNameErrorAndTerminate(fileName);

	ShaderObject* pShaderObject = new ShaderObject(filePath.c_str());
	_shaderStorageMap.insert(std::make_pair(key, pShaderObject));

	printShaderLoadedSuccessfully(fileName);
}

// Loading Shaders helper functions
bool ShaderManager::hasKeyBeenAssigned(const MapKey& key) const
{
	return _shaderStorageMap.find(key) != _shaderStorageMap.end();
}

void ShaderManager::printKeyAssignedErrorAndTerminate(const MapKey& key) const
{
	Trace::out("KEY - %s - for SHADER has been used. Use another KEY name\n", key.c_str());
	throw std::exception();
	//std::terminate();
}

bool ShaderManager::isFilePathValid(const std::string& filePath) const
{
	const std::string filePathWithShaderExtension = filePath + +".fs.glsl";

	FileHandle fileHandle;
	FileError result = File::open(fileHandle, filePathWithShaderExtension.c_str(), FileMode::FILE_READ);
	File::close(fileHandle);

	return result == FileError::FILE_SUCCESS;
}

void ShaderManager::printFileNameErrorAndTerminate(const std::string& fileName) const
{
	Trace::out("FILE NAME - \"%s\" - for SHADER cannot be found. Check FILE NAME or ensure that SHADER file is in the SHADERS FOLDER\n", fileName.c_str());
	throw std::exception();
	//std::terminate();
}

void ShaderManager::printShaderLoadedSuccessfully(const std::string& fileName) const
{
	Trace::out("Shader Manager: %s loaded successfully\n", fileName.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Shaders
//-----------------------------------------------------------------------------------------------------------------------------
ShaderObject* ShaderManager::privGetDefaultShader(const DefaultShader defaultShader) const
{
	return privGetShader(getDefaultShaderKey(defaultShader));
}

ShaderObject* ShaderManager::privGetShader(const MapKey& key) const
{
	return tryToGetShader(key);
}

// Getting Shaders helper functions
const ShaderManager::MapKey ShaderManager::getDefaultShaderKey(const DefaultShader defaultShader) const
{
	MapKey key;
	switch (defaultShader)
	{
	case DefaultShader::TEXTURE:
		key = "texture";
		break;
	case DefaultShader::LIGHTED_TEXTURE:
		key = "lightedTexture";
		break;
	case DefaultShader::CONSTANT_COLOR:
		key = "constantColor";
		break;
	case DefaultShader::SPRITE:
		key = "spriteRender";
		break;
	default:
		key = "INVALID_DEFAULT_SHADER_ENUM";
		break;
	}
	return key;
}

ShaderObject* ShaderManager::tryToGetShader(const MapKey& key) const
{
	try
	{
		return _shaderStorageMap.at(key);
	}
	catch (std::out_of_range exception)
	{
		Trace::out("INVALID key - \"%s\" - for SHADER storage map\n", key.c_str());
		throw exception;
		//std::terminate();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// Deleting Shaders
//-----------------------------------------------------------------------------------------------------------------------------
void ShaderManager::Delete()
{
	Trace::out("Shader Manager: Deleting Shader Manager\n");
	delete pShaderManagerInstance;
	pShaderManagerInstance = nullptr;
}

ShaderManager::~ShaderManager()
{
	ShaderManager::DebugPrint("Destructor is called");
	deleteAllShaders();
	ShaderManager::DebugPrint("");
}

void ShaderManager::deleteAllShaders()
{
	ShaderManager::DebugPrint("Deleting all shaders");
	for (auto pair : _shaderStorageMap)
	{
		ShaderManager::DebugPrint("Deleting \"" + pair.first + "\" shader");
		ShaderObject* pShaderObject = pair.second;
		delete pShaderObject;
	}
	ShaderManager::DebugPrint("All shaders have been deleted");
	_shaderStorageMap.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------
const std::string ShaderManager::DEBUG_TITLE_MESSAGE = "ShaderManager_DEBUG: ";

void ShaderManager::DebugPrint(const std::string& message)
{
	(void(message));
#if ShaderManager_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = ShaderManager::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif ShaderManager_DEBUG
}