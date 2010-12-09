/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */
 
#ifndef Rbdb_FILE_VERBOSITY_SETTINGS_CONTROLLER
	#define Rbdb_FILE_VERBOSITY_SETTINGS_CONTROLLER
	 
	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_FileVerbositySettingsController*		Rbdb_FileVerbositySettingsController_new(																		Rbdb_FileSettingsController*			file_settings_controller );

	void										Rbdb_FileVerbositySettingsController_free(																Rbdb_FileVerbositySettingsController** file_verbosity_settings_controller );
	Rbdb_Environment*					Rbdb_FileVerbositySettingsController_parentEnvironment(									Rbdb_FileVerbositySettingsController* file_verbosity_settings_controller );

	BOOL										Rbdb_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations(			Rbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn(	Rbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff(	Rbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );

	BOOL										Rbdb_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations(						Rbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOn(				Rbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										Rbdb_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOff(				Rbdb_FileVerbositySettingsController*		file_verbosity_settings_controller );

#endif

