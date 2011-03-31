/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */
 
#ifndef RPBDB_FILE_SETTINGS_CONTROLLER
	#define RPBDB_FILE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_FileSettingsController*				RPbdb_FileSettingsController_new(													RPbdb_SettingsController*			settings_controller );

	void										RPbdb_FileSettingsController_free(													RPbdb_FileSettingsController**		file_settings_controller );
	RPbdb_Environment*					RPbdb_FileSettingsController_parentEnvironment(							RPbdb_FileSettingsController*		file_settings_controller );
																																	
	char*										RPbdb_FileSettingsController_intermediateDirectoryMode(								RPbdb_FileSettingsController*		file_settings_controller );
	void										RPbdb_FileSettingsController_setIntermediateDirectoryMode(							RPbdb_FileSettingsController*		file_settings_controller, 
																																	const char*							mode );
																																	
	char*										RPbdb_FileSettingsController_tempDirectory(											RPbdb_FileSettingsController*		file_settings_controller );
	void										RPbdb_FileSettingsController_setTempDirectory(										RPbdb_FileSettingsController*		file_settings_controller, 
																																	const char*							temp_directory );
																																	
	int										RPbdb_FileSettingsController_permitEnvironmentBasedFileNaming(						RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOn(				RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOff(				RPbdb_FileSettingsController*		file_settings_controller );

	int	 	   								RPbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming(			RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOn(		RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOff(		RPbdb_FileSettingsController*		file_settings_controller );
																														
	int	 	   								RPbdb_FileSettingsController_createIfNecessary(										RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnCreateIfNecessaryOn(								RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnCreateIfNecessaryOff(								RPbdb_FileSettingsController*		file_settings_controller );
																																	
	int	 	   								RPbdb_FileSettingsController_isErrorIfDBExistsBeforeCreate(							RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOn(					RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOff(					RPbdb_FileSettingsController*		file_settings_controller );
																																	
	int	 	   								RPbdb_FileSettingsController_openReadOnly(											RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnOpenReadOnlyOn(									RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnOpenReadOnlyOff(									RPbdb_FileSettingsController*		file_settings_controller );
																																	
	int										RPbdb_FileSettingsController_forceRemoval(											RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnForceRemovalOn(									RPbdb_FileSettingsController*		file_settings_controller );
	void 										RPbdb_FileSettingsController_turnForceRemovalOff(									RPbdb_FileSettingsController*		file_settings_controller );
																																	
	int											RPbdb_FileSettingsController_fileCreationMode(										RPbdb_FileSettingsController*		file_settings_controller );
	void										RPbdb_FileSettingsController_setFileCreationMode(									RPbdb_FileSettingsController*		file_settings_controller,
	 											   																					int									mode	);
												   																														
	RPbdb_FileVerbositySettingsController*		RPbdb_FileSettingsController_verbositySettingsController(							RPbdb_FileSettingsController*		file_settings_controller );

#endif

