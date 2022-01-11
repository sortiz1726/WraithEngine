#ifndef _ModelManager
#define _ModelManager

#include <string>
#include <map>
#include "Model.h"

/**********************************************************************************************//**
 * <summary> Manager for models. 
 * 			 For loading models and accessing them within user defined games object
 * 			 </summary>
 *
 * <remarks> </remarks>
 **************************************************************************************************/

class ModelManager
{
	friend class ModelManagerAttorney;
public:
	/**********************************************************************************************//**
	 * <summary> Values that represent default models.</summary>
	 *\ingroup MODELRESOURCES
	 * <remarks> To be used  in ModelManager::GetDefaultModel(). </remarks>
	 **************************************************************************************************/
	enum class DefaultModel
	{
		SPRITE
	};

private:
	typedef std::string MapKey;
	typedef std::map<MapKey, Model*> ModelMap;

private:
	static ModelManager* pModelManagerInstance;

	// Big Six
	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	ModelManager(const ModelManager&&) = delete;
	ModelManager& operator=(ModelManager&&) = delete;
	~ModelManager();

	// Getting Model Manager
	static ModelManager& GetInstance();
	
	// Instatiating helper
	void loadDefaultModels();

	// Setting Default Path
	void privSetDefaultPath(const std::string& defaultPath);

	// Loading Models
	void privLoadModelAndAssignKey(const Model::PreMadeModels, const MapKey& key);
	void privLoadModelAndAssignKey(const std::string& fileName, const MapKey& key);

	// ---> Loading Models helper
	bool hasKeyBeenAssigned(const MapKey& key) const;
	void printKeyAssignedErrorAndTerminate(const MapKey& key) const;

	bool isFilePathValid(const std::string& fileName) const;
	void printFileNameErrorAndTerminate(const std::string& fileName) const;
	
	void printModelLoadedSuccessfully(const Model::PreMadeModels& preMadeModel) const;
	void printModelLoadedSuccessfully(const std::string& fileName) const;
	
	// Getting Models
	Model* getModel(const MapKey& key) const;
	Model* getDefaultModel(DefaultModel) const;

	// ---> Getting Models helpers
	Model* tryToGetModel(const MapKey& key) const;
	MapKey getDefaultModelKey(DefaultModel) const;
	
	// Termination
	static void Delete();

	// ---> Termination helper
	void deleteAllModels();

public:
	/**********************************************************************************************//**
	 * <summary> Sets default file path to access model files.</summary>
	 * \ingroup MODELRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="defaultPath"> The default file path.</param>
	 **************************************************************************************************/
	static void SetDefaultPath(const std::string& defaultPath)
	{
		GetInstance().privSetDefaultPath(defaultPath);
	}

	/**********************************************************************************************//**
	 * <summary> Loads model from azul file and assigns a user define key.</summary>
	 * \ingroup MODELRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="fileName"> name of azul model file.</param>
	 * <param name="key">	   user define key to associate with model.</param>
	 **************************************************************************************************/
	static void LoadModelAndAssignKey(const std::string& fileName, const MapKey& key)
	{
		ModelManager::GetInstance().privLoadModelAndAssignKey(fileName, key);
	}

	/**********************************************************************************************//**
	 * <summary> Loads model a premade model and assigns it to a user define key.  </summary>
	 * \ingroup MODELRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="preMadeModel"> The premade model.</param>
	 * <param name="key">		   user define key to associate with model.</param>
	 **************************************************************************************************/
	static void LoadModelAndAssignKey(const Model::PreMadeModels preMadeModel, const MapKey& key)
	{
		ModelManager::GetInstance().privLoadModelAndAssignKey(preMadeModel, key);
	}

	/**********************************************************************************************//**
	 * <summary> Gets a default preloaded model.</summary>
	 * \ingroup MODELRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="defaultModel"> The default model.</param>
	 *
	 * <returns> A default model.</returns>
	 **************************************************************************************************/
	static Model* GetDefaultModel(DefaultModel defaultModel)
	{
		return ModelManager::GetInstance().getDefaultModel(defaultModel);
	}

	/**********************************************************************************************//**
	 * <summary> Gets a model with user defined key.</summary>
	 * \ingroup MODELRESOURCES
	 * <remarks> </remarks>
	 *
	 * <param name="key"> The user defined key associated to a model.</param>
	 *
	 * <returns> A model.</returns>
	 **************************************************************************************************/
	static Model* GetModel(const MapKey& key)
	{
		return ModelManager::GetInstance().getModel(key);
	}

private:
	std::string _defaultPath;

	ModelMap _modelStorageMap;

	// For personal debugging
private:
	static void DebugPrint(const std::string& message);
	
	template<typename ...Args>
	static void DebugPrintf(const char* format, Args... args);

	static const std::string DEBUG_TITLE_MESSAGE;
};

// For personal debugging
#ifndef ModelManager_DEBUG
#define ModelManager_DEBUG false
#endif !ModelManager_DEBUG

template<typename... Args>
void ModelManager::DebugPrintf(const char* format, Args... args)
{
#if ModelManager_DEBUG
	std::string stringFormat = std::string(format);
	if (stringFormat.size() == 0)
	{
		Trace::out("\n");
	}
	else
	{
		std::string finalMessage = ModelManager::DEBUG_TITLE_MESSAGE + stringFormat + "\n";
		Trace::out(finalMessage.c_str(), args...);
	}
#endif ModelManager_DEBUG
}

#endif _ModelManager

//-----------------------------------------------------------------------------------------------------------------------------
// ModelManager Comment Template
//-----------------------------------------------------------------------------------------------------------------------------