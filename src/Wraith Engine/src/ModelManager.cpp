#include "ModelManager.h"
#include <cassert>
#include <exception>
#include "File.h"

ModelManager* ModelManager::pModelManagerInstance = nullptr;

//-----------------------------------------------------------------------------------------------------------------------------
// Get Model Manager
//-----------------------------------------------------------------------------------------------------------------------------
ModelManager& ModelManager::GetInstance()
{
	if (pModelManagerInstance == nullptr)
	{
		pModelManagerInstance = new ModelManager();
	}
	assert(pModelManagerInstance);
	return *pModelManagerInstance;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Instantiating Model Manager
//-----------------------------------------------------------------------------------------------------------------------------
ModelManager::ModelManager()
{
	ModelManager::DebugPrint("Default Constructor called");
	privSetDefaultPath("Models/");
	loadDefaultModels();
	ModelManager::DebugPrint("");
}

void ModelManager::loadDefaultModels()
{
	privLoadModelAndAssignKey(Model::PreMadeModels::UnitSquareXY, getDefaultModelKey(DefaultModel::SPRITE));
}

//-----------------------------------------------------------------------------------------------------------------------------
// Setting Default Path
//-----------------------------------------------------------------------------------------------------------------------------
void ModelManager::privSetDefaultPath(const std::string& defaultPath)
{
	ModelManager::DebugPrint("Setting Default Path to \"" + defaultPath + "\"");
	_defaultPath = defaultPath;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Loading Models
//-----------------------------------------------------------------------------------------------------------------------------
void ModelManager::privLoadModelAndAssignKey(const Model::PreMadeModels preMadeModel, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	Model* pModel = new Model(preMadeModel);
	_modelStorageMap.insert(std::make_pair(key, pModel));

	printModelLoadedSuccessfully(preMadeModel);
}

void ModelManager::privLoadModelAndAssignKey(const std::string& fileName, const MapKey& key)
{
	if (hasKeyBeenAssigned(key)) printKeyAssignedErrorAndTerminate(key);

	const std::string filePath = ModelManager::_defaultPath + fileName;
	if (!isFilePathValid(filePath)) printFileNameErrorAndTerminate(fileName);

	Model* pModel = new Model(filePath.c_str());
	_modelStorageMap.insert(std::make_pair(key, pModel));

	printModelLoadedSuccessfully(fileName);
}

// Loading Models helper functions
bool ModelManager::hasKeyBeenAssigned(const MapKey& key) const
{
	return _modelStorageMap.find(key) != _modelStorageMap.end();
}

void ModelManager::printKeyAssignedErrorAndTerminate(const MapKey& key) const
{
	Trace::out("KEY - %s - for MODEL has been used. Use another KEY name\n", key.c_str());
	throw std::exception();
	//std::terminate();
}

bool ModelManager::isFilePathValid(const std::string& filePath) const
{
	FileHandle fileHandle;
	FileError result = File::open(fileHandle, filePath.c_str(), FileMode::FILE_READ);
	File::close(fileHandle);
	return result == FileError::FILE_SUCCESS;
}

void ModelManager::printFileNameErrorAndTerminate(const std::string& fileName) const
{
	Trace::out("FILE NAME - %s - for MODEL cannot be found. Check FILE NAME or ensure that model file is in the MODELS FOLDER\n", fileName.c_str());
	throw std::exception();
	//std::terminate();
}

void ModelManager::printModelLoadedSuccessfully(const Model::PreMadeModels& preMadeModel) const
{
	switch (preMadeModel)
	{
	case Model::PreMadeModels::UnitSquareXY:
		printModelLoadedSuccessfully("Unit Square Premade Model");
		break;
	case Model::PreMadeModels::UnitBox_WF:
		printModelLoadedSuccessfully("Unit Box Premade Model");
		break;
	case Model::PreMadeModels::UnitSphere:
		printModelLoadedSuccessfully("Unit Sphere Premade Model");
		break;
	}
}

void ModelManager::printModelLoadedSuccessfully(const std::string& fileName) const
{
	Trace::out("Model Manager: %s loaded successfully\n", fileName.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------
// Getting Models
//-----------------------------------------------------------------------------------------------------------------------------
Model* ModelManager::getDefaultModel(DefaultModel defaultModel) const
{
	return getModel(getDefaultModelKey(defaultModel));
}

Model* ModelManager::getModel(const MapKey& key) const
{
	return tryToGetModel(key);
}

// Getting Models helper function
Model* ModelManager::tryToGetModel(const MapKey& key) const
{
	try
	{
		return _modelStorageMap.at(key);
	}
	catch (std::out_of_range exception)
	{
		Trace::out("INVALID key - \"%s\" - for MODEL storage map. CHECK if key is misspelled or if model was loaded\n", key.c_str());
		throw exception;
		//std::terminate();
	}
}

ModelManager::MapKey ModelManager::getDefaultModelKey(DefaultModel defaultModel) const
{
	MapKey key;
	switch (defaultModel)
	{
	case ModelManager::DefaultModel::SPRITE:
		key = "SpriteModel";
		break;
	default:
		break;
	}
	return key;
}

//-----------------------------------------------------------------------------------------------------------------------------
// Deleting Models
//-----------------------------------------------------------------------------------------------------------------------------
void ModelManager::Delete()
{
	Trace::out("Model Manager: Deleting Model Manager\n");
	delete pModelManagerInstance;
	pModelManagerInstance = nullptr;
}

ModelManager::~ModelManager()
{
	ModelManager::DebugPrint("Destructor is called");
	deleteAllModels();
	ModelManager::DebugPrint("");
}

void ModelManager::deleteAllModels()
{
	ModelManager::DebugPrint("Deleting all Models");
	for (auto& pair : _modelStorageMap)
	{
		ModelManager::DebugPrint("Deleting \"" + pair.first + "\" Model");
		Model* pModel = pair.second;
		delete pModel;
	}
	ModelManager::DebugPrint("All Models have been deleted");
	_modelStorageMap.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------
// For personal debugging
//-----------------------------------------------------------------------------------------------------------------------------
const std::string ModelManager::DEBUG_TITLE_MESSAGE = "ModelManager_DEBUG: ";

void ModelManager::DebugPrint(const std::string& message)
{
	(void(message));
#if ModelManager_DEBUG
	if (message.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = ModelManager::DEBUG_TITLE_MESSAGE + message + std::string("\n");
		Trace::out("%s", finalMessage.c_str());
	}
#endif ModelManager_DEBUG
}