/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */
 
#ifndef Rbdb_FILE_SETTINGS_CONTROLLER
	#define Rbdb_FILE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_FileSettingsController*				Rbdb_FileSettingsController_new(													Rbdb_SettingsController*			settings_controller );

	void										Rbdb_FileSettingsController_free(													Rbdb_FileSettingsController**		file_settings_controller );
	Rbdb_Environment*					Rbdb_FileSettingsController_parentEnvironment(							Rbdb_FileSettingsController*		file_settings_controller );
																																	
	char*										Rbdb_FileSettingsController_intermediateDirectoryMode(								Rbdb_FileSettingsController*		file_settings_controller );
	void										Rbdb_FileSettingsController_setIntermediateDirectoryMode(							Rbdb_FileSettingsController*		file_settings_controller, 
																																	const char*							mode );
																																	
	char*										Rbdb_FileSettingsController_tempDirectory(											Rbdb_FileSettingsController*		file_settings_controller );
	void										Rbdb_FileSettingsController_setTempDirectory(										Rbdb_FileSettingsController*		file_settings_controller, 
																																	const char*							temp_directory );
																																	
	int										Rbdb_FileSettingsController_permitEnvironmentBasedFileNaming(						Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOn(				Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOff(				Rbdb_FileSettingsController*		file_settings_controller );

	int	 	   								Rbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming(			Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOn(		Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOff(		Rbdb_FileSettingsController*		file_settings_controller );
																														
	int	 	   								Rbdb_FileSettingsController_createIfNecessary(										Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnCreateIfNecessaryOn(								Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnCreateIfNecessaryOff(								Rbdb_FileSettingsController*		file_settings_controller );
																																	
	int	 	   								Rbdb_FileSettingsController_isErrorIfDBExistsBeforeCreate(							Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOn(					Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOff(					Rbdb_FileSettingsController*		file_settings_controller );
																																	
	int	 	   								Rbdb_FileSettingsController_openReadOnly(											Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnOpenReadOnlyOn(									Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnOpenReadOnlyOff(									Rbdb_FileSettingsController*		file_settings_controller );
																																	
	int										Rbdb_FileSettingsController_forceRemoval(											Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnForceRemovalOn(									Rbdb_FileSettingsController*		file_settings_controller );
	void 										Rbdb_FileSettingsController_turnForceRemovalOff(									Rbdb_FileSettingsController*		file_settings_controller );
																																	
	int											Rbdb_FileSettingsController_fileCreationMode(										Rbdb_FileSettingsController*		file_settings_controller );
	void										Rbdb_FileSettingsController_setFileCreationMode(									Rbdb_FileSettingsController*		file_settings_controller,
	 											   																					int									mode	);
												   																														
	Rbdb_FileVerbositySettingsController*		Rbdb_FileSettingsController_verbositySettingsController(							Rbdb_FileSettingsController*		file_settings_controller );

#endif

