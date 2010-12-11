/*
 *		Rbdb::SettingsDirectoryController
 *
 *
 */

#ifndef RBDB_DIRECTORY_SETTINGS_CONTROLLER
	#define RBDB_DIRECTORY_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DirectorySettingsController*		Rbdb_DirectorySettingsController_new(					Rbdb_SettingsController* 				settings_controller );

	void									Rbdb_DirectorySettingsController_free(								Rbdb_DirectorySettingsController**	directory_settings_controller );
	Rbdb_Environment*				Rbdb_DirectorySettingsController_parentEnvironment(	Rbdb_DirectorySettingsController*	directory_settings_controller );
											
	const char*								Rbdb_DirectorySettingsController_homeDirectory(		Rbdb_DirectorySettingsController* 		directory_settings_controller );
	const char**							Rbdb_DirectorySettingsController_dataDirectories(		Rbdb_DirectorySettingsController* 		directory_settings_controller );
	void									Rbdb_DirectorySettingsController_addDataDirectory(		Rbdb_DirectorySettingsController*		directory_settings_controller, 
																									char*									directory  );
	void Rbdb_DirectorySettingsController_setCreateDirectory(	Rbdb_DirectorySettingsController*		directory_settings_controller, 
																char*									directory  );
	char* Rbdb_DirectorySettingsController_getCreateDirectory(	Rbdb_DirectorySettingsController*		directory_settings_controller  );

#endif

