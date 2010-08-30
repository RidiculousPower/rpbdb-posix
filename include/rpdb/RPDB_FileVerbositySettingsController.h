/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */
 
#ifndef RPDB_FILE_VERBOSITY_SETTINGS_CONTROLLER
	#define RPDB_FILE_VERBOSITY_SETTINGS_CONTROLLER
	 
	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_FileVerbositySettingsController*		RPDB_FileVerbositySettingsController_new(																		RPDB_FileSettingsController*			file_settings_controller );

	void										RPDB_FileVerbositySettingsController_free(																RPDB_FileVerbositySettingsController** file_verbosity_settings_controller );
	RPDB_Environment*					RPDB_FileVerbositySettingsController_parentEnvironment(									RPDB_FileVerbositySettingsController* file_verbosity_settings_controller );

	BOOL										RPDB_FileVerbositySettingsController_displayAdditionalInformationDuringOpenCloseRenameFileOperations(			RPDB_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOn(	RPDB_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringOpenCloseRenameFileOperationsOff(	RPDB_FileVerbositySettingsController*		file_verbosity_settings_controller );

	BOOL										RPDB_FileVerbositySettingsController_displayAdditionalInformationDuringAllFileOperations(						RPDB_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOn(				RPDB_FileVerbositySettingsController*		file_verbosity_settings_controller );
	void										RPDB_FileVerbositySettingsController_turnDisplayAdditionalInformationDuringAllFileOperationsOff(				RPDB_FileVerbositySettingsController*		file_verbosity_settings_controller );

#endif

