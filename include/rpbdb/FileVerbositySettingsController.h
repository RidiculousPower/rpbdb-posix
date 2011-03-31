/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */
 
#ifndef RPBDB_FILE_VERBOSITY_SETTINGS_CONTROLLER
	#define RPBDB_FILE_VERBOSITY_SETTINGS_CONTROLLER
	 
	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_FileVerbositySettingsController*		RPbdb_FileVerbositySettingsController_new(																		RPbdb_FileSettingsController*			file_settings_controller );

	void										RPbdb_FileVerbositySettingsController_free(																RPbdb_FileVerbositySettingsController** file_verbosity_settings_controller );
	RPbdb_Environment*					RPbdb_FileVerbositySettingsController_parentEnvironment(									RPbdb_FileVerbositySettingsController* file_verbosity_settings_controller );

	BOOL										RPbdb_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations(			RPbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn(	RPbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff(	RPbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );

	BOOL										RPbdb_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations(						RPbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOn(				RPbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOff(				RPbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );

#endif

