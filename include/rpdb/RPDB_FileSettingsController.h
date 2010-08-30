/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */
 
#ifndef RPDB_FILE_SETTINGS_CONTROLLER
	#define RPDB_FILE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_FileSettingsController*				RPDB_FileSettingsController_new(													RPDB_SettingsController*			settings_controller );

	void										RPDB_FileSettingsController_free(													RPDB_FileSettingsController**		file_settings_controller );
	RPDB_Environment*					RPDB_FileSettingsController_parentEnvironment(							RPDB_FileSettingsController*		file_settings_controller );
																																	
	char*										RPDB_FileSettingsController_intermediateDirectoryMode(								RPDB_FileSettingsController*		file_settings_controller );
	void										RPDB_FileSettingsController_setIntermediateDirectoryMode(							RPDB_FileSettingsController*		file_settings_controller, 
																																	const char*							mode );
																																	
	char*										RPDB_FileSettingsController_tempDirectory(											RPDB_FileSettingsController*		file_settings_controller );
	void										RPDB_FileSettingsController_setTempDirectory(										RPDB_FileSettingsController*		file_settings_controller, 
																																	const char*							temp_directory );
																																	
	int										RPDB_FileSettingsController_permitEnvironmentBasedFileNaming(						RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnPermitEnvironmentBasedFileNamingOn(				RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnPermitEnvironmentBasedFileNamingOff(				RPDB_FileSettingsController*		file_settings_controller );

	int	 	   								RPDB_FileSettingsController_useEnvironmentHomePermissionsForFileNaming(			RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOn(		RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOff(		RPDB_FileSettingsController*		file_settings_controller );
																														
	int	 	   								RPDB_FileSettingsController_createIfNecessary(										RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnCreateIfNecessaryOn(								RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnCreateIfNecessaryOff(								RPDB_FileSettingsController*		file_settings_controller );
																																	
	int	 	   								RPDB_FileSettingsController_isErrorIfDBExistsBeforeCreate(							RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOn(					RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOff(					RPDB_FileSettingsController*		file_settings_controller );
																																	
	int	 	   								RPDB_FileSettingsController_openReadOnly(											RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnOpenReadOnlyOn(									RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnOpenReadOnlyOff(									RPDB_FileSettingsController*		file_settings_controller );
																																	
	int										RPDB_FileSettingsController_forceRemoval(											RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnForceRemovalOn(									RPDB_FileSettingsController*		file_settings_controller );
	void 										RPDB_FileSettingsController_turnForceRemovalOff(									RPDB_FileSettingsController*		file_settings_controller );
																																	
	int											RPDB_FileSettingsController_fileCreationMode(										RPDB_FileSettingsController*		file_settings_controller );
	void										RPDB_FileSettingsController_setFileCreationMode(									RPDB_FileSettingsController*		file_settings_controller,
	 											   																					int									mode	);
												   																														
	RPDB_FileVerbositySettingsController*		RPDB_FileSettingsController_verbositySettingsController(							RPDB_FileSettingsController*		file_settings_controller );

#endif

