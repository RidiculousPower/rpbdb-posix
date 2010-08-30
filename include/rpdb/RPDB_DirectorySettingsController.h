/*
 *		RPDB::SettingsDirectoryController
 *
 *
 */

#ifndef RPDB_DIRECTORY_SETTINGS_CONTROLLER
	#define RPDB_DIRECTORY_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DirectorySettingsController*		RPDB_DirectorySettingsController_new(					RPDB_SettingsController* 				settings_controller );

	void									RPDB_DirectorySettingsController_free(								RPDB_DirectorySettingsController**	directory_settings_controller );
	RPDB_Environment*				RPDB_DirectorySettingsController_parentEnvironment(	RPDB_DirectorySettingsController*	directory_settings_controller );
											
	const char*								RPDB_DirectorySettingsController_homeDirectory(		RPDB_DirectorySettingsController* 		directory_settings_controller );
	const char**							RPDB_DirectorySettingsController_dataDirectories(		RPDB_DirectorySettingsController* 		directory_settings_controller );
	void									RPDB_DirectorySettingsController_addDataDirectory(		RPDB_DirectorySettingsController*		directory_settings_controller, 
																									char*									directory  );
	void RPDB_DirectorySettingsController_setCreateDirectory(	RPDB_DirectorySettingsController*		directory_settings_controller, 
																char*									directory  );
	char* RPDB_DirectorySettingsController_getCreateDirectory(	RPDB_DirectorySettingsController*		directory_settings_controller  );

#endif

