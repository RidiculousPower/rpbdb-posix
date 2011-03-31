/*
 *		RPbdb::SettingsDirectoryController
 *
 *
 */

#ifndef RPBDB_DIRECTORY_SETTINGS_CONTROLLER
	#define RPBDB_DIRECTORY_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DirectorySettingsController*		RPbdb_DirectorySettingsController_new(					RPbdb_SettingsController* 				settings_controller );

	void									RPbdb_DirectorySettingsController_free(								RPbdb_DirectorySettingsController**	directory_settings_controller );
	RPbdb_Environment*				RPbdb_DirectorySettingsController_parentEnvironment(	RPbdb_DirectorySettingsController*	directory_settings_controller );
											
	const char*								RPbdb_DirectorySettingsController_homeDirectory(		RPbdb_DirectorySettingsController* 		directory_settings_controller );
	const char**							RPbdb_DirectorySettingsController_dataDirectories(		RPbdb_DirectorySettingsController* 		directory_settings_controller );
	void									RPbdb_DirectorySettingsController_addDataDirectory(		RPbdb_DirectorySettingsController*		directory_settings_controller, 
																									char*									directory  );
	void RPbdb_DirectorySettingsController_setCreateDirectory(	RPbdb_DirectorySettingsController*		directory_settings_controller, 
																char*									directory  );
	char* RPbdb_DirectorySettingsController_getCreateDirectory(	RPbdb_DirectorySettingsController*		directory_settings_controller  );

#endif

