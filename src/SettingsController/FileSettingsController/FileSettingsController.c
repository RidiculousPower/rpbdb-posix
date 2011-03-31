/*
 *		RPbdb::SettingsController::FileSettingsController
 *
 *
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "FileSettingsController.h"

#include "Environment.h"
#include "FileVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_FileSettingsController* RPbdb_FileSettingsController_new( RPbdb_SettingsController* settings_controller )	{

	RPbdb_FileSettingsController*		file_settings_controller = calloc( 1, sizeof( RPbdb_FileSettingsController ) );

	file_settings_controller->parent_settings_controller = settings_controller;

	return file_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_FileSettingsController_free(	RPbdb_FileSettingsController** file_settings_controller )	{

	if ( ( *file_settings_controller )->verbosity_settings_controller != NULL )	{
		RPbdb_FileVerbositySettingsController_free( & ( ( *file_settings_controller )->verbosity_settings_controller ) );
	}
	
	free( *file_settings_controller );
	*file_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_FileSettingsController_parentEnvironment(	RPbdb_FileSettingsController* file_settings_controller )	{
	return file_settings_controller->parent_settings_controller->parent_environment;
}

/*********************************
*  intermediateDirectoryMode  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_intermediate_dir_mode.html
char* RPbdb_FileSettingsController_intermediateDirectoryMode( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->intermediate_directory_mode == NULL )	{

		RPbdb_Environment*	environment = file_settings_controller->parent_settings_controller->parent_environment;

		if ( environment->wrapped_bdb_environment != NULL )	{
			environment->wrapped_bdb_environment->get_intermediate_dir_mode(	environment->wrapped_bdb_environment, 
																																				(const char**) &( file_settings_controller->intermediate_directory_mode ) );
		}
	}

	return file_settings_controller->intermediate_directory_mode;
}

/*************************************
*  setIntermediateDirectoryMode  *
*************************************/

//	9 character string for unix-style directory permissions
void RPbdb_FileSettingsController_setIntermediateDirectoryMode( RPbdb_FileSettingsController* file_settings_controller, const char* mode )	{

	RPbdb_Environment*			environment	= file_settings_controller->parent_settings_controller->parent_environment;

	file_settings_controller->intermediate_directory_mode	=	(char*) mode;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_intermediate_dir_mode(	environment->wrapped_bdb_environment, 
																																			mode );
	}
}

/*********************
*  tempDirectory  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tmp_dir.html
char* RPbdb_FileSettingsController_tempDirectory( RPbdb_FileSettingsController* file_settings_controller )	{

	RPbdb_Environment*			environment;

	if ( file_settings_controller->temp_directory == NULL )	{

		environment = file_settings_controller->parent_settings_controller->parent_environment;

		if ( environment->wrapped_bdb_environment != NULL )	{
			environment->wrapped_bdb_environment->get_tmp_dir(	environment->wrapped_bdb_environment, 
																													(const char**) &( file_settings_controller->temp_directory ) );
		}
	}

	return file_settings_controller->temp_directory;
}

/*************************
*  setTempDirectory  *
*************************/

void RPbdb_FileSettingsController_setTempDirectory( RPbdb_FileSettingsController* file_settings_controller, const char* temp_directory )	{

	RPbdb_Environment*			environment;

	environment = file_settings_controller->parent_settings_controller->parent_environment;

	file_settings_controller->temp_directory = (char*) temp_directory;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_tmp_dir( environment->wrapped_bdb_environment, temp_directory );
	}
}

/*********************************
*  permitEnvironmentNaming  *
*********************************/

//	DB_USE_ENVIRON          http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_FileSettingsController_permitEnvironmentBasedFileNaming( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->permit_environment_based_file_naming == TRUE )	{
		return DB_USE_ENVIRON;
	}
	return FALSE;
}

	/*************************************
	*  turnPermitEnvironmentNamingOn  *
	*************************************/

	void RPbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOn( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->permit_environment_based_file_naming = TRUE;
	}

	/*************************************
	*  turnPermitEnvironmentNamingOff  *
	*************************************/

	void RPbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOff( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->permit_environment_based_file_naming = FALSE;
	}

/****************************
*  useEnvironmentHome  *
****************************/

//	DB_USE_ENVIRON_ROOT     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->use_environment_home_permissions_for_file_naming == TRUE )	{
		return DB_USE_ENVIRON_ROOT;	
	}
	return FALSE;
}

	/*********************************
	*  turnUseEnvironmentHomeOn  *
	*********************************/

	void RPbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOn( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->use_environment_home_permissions_for_file_naming = TRUE;
	}

	/*********************************
	*  turnUseEnvironmentHomeOff  *
	*********************************/

	void RPbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOff( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->use_environment_home_permissions_for_file_naming = FALSE;
	}

/*********************************
*  createIfNecessary  *
*********************************/

//	DB_CREATE               http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPbdb_FileSettingsController_createIfNecessary( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->create_if_necessary == TRUE )	{
		return DB_CREATE;
	}
	return FALSE;
}

	/*************************************
	*  turnCreateIfNecessaryOn  *
	*************************************/

	void RPbdb_FileSettingsController_turnCreateIfNecessaryOn( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->create_if_necessary = TRUE;
	}

	/**************************************
	*  turnCreateIfNecessaryOff  *
	**************************************/

	void RPbdb_FileSettingsController_turnCreateIfNecessaryOff( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->create_if_necessary = FALSE;
	}

/**************************************
*  isErrorIfDBExistsBeforeCreate  *
**************************************/

//	DB_EXCL					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int RPbdb_FileSettingsController_isErrorIfDBExistsBeforeCreate( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->error_if_exists_on_create == TRUE )	{
		return DB_EXCL;
	}
	return FALSE;
}

	/********************************************
	*  turnIsErrorIfDBExistsBeforeCreateOn  *
	********************************************/

	void RPbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOn( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->error_if_exists_on_create = TRUE;
	}

	/*********************************************
	*  turnIsErrorIfDBExistsBeforeCreateOff  *
	*********************************************/

	void RPbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOff( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->error_if_exists_on_create = FALSE;
	}

/*************************
*  openReadOnly  *
*************************/

//	DB_RDONLY					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int RPbdb_FileSettingsController_openReadOnly( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->open_read_only == TRUE )	{
		return DB_RDONLY;
	}
	return FALSE;
}

	/********************************
	*  turnOpenReadOnlyOn  *
	********************************/

	void RPbdb_FileSettingsController_turnOpenReadOnlyOn( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->open_read_only = TRUE;
	}

	/********************************
	*  turnOpenReadOnlyOff  *
	********************************/

	void RPbdb_FileSettingsController_turnOpenReadOnlyOff( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->open_read_only = FALSE;
	}

/*************************
*  forceRemoval  *
*************************/

//	DB_FORCE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_remove.html
int RPbdb_FileSettingsController_forceRemoval( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->force_removal == TRUE )	{
		return DB_FORCE;
	}
	return FALSE;
}

	/*********************************
	*  turnForceRemovalOn  *
	*********************************/

	void RPbdb_FileSettingsController_turnForceRemovalOn( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->force_removal = TRUE;
	}

	/*********************************
	*  turnForceRemovalOff  *
	*********************************/

	void RPbdb_FileSettingsController_turnForceRemovalOff( RPbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->force_removal = FALSE;
	}

/*************************
*  fileCreationMode  *
*************************/

int RPbdb_FileSettingsController_fileCreationMode( RPbdb_FileSettingsController* file_settings_controller )	{

	return file_settings_controller->file_creation_mode;
}

/****************************
*  setFileCreationMode  *
****************************/

void RPbdb_FileSettingsController_setFileCreationMode(	RPbdb_FileSettingsController*	file_settings_controller,
 														int								mode	)	{
	file_settings_controller->file_creation_mode = mode;
}

/*************************************
*  verbositySettingsController  *
*************************************/

RPbdb_FileVerbositySettingsController* RPbdb_FileSettingsController_verbositySettingsController( RPbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->verbosity_settings_controller == NULL )	{
	
		file_settings_controller->verbosity_settings_controller = RPbdb_FileVerbositySettingsController_new( file_settings_controller );
	}
	
	return file_settings_controller->verbosity_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_FileSettingsController* RPbdb_FileSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_FileSettingsController* file_settings_controller )	{

	RPbdb_FileSettingsController* file_settings_controller_copy	=	RPbdb_FileSettingsController_new( file_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	file_settings_controller_copy->create_if_necessary	=	file_settings_controller->create_if_necessary;
	file_settings_controller_copy->file_creation_mode	=	file_settings_controller->file_creation_mode;
	file_settings_controller_copy->force_removal	=	file_settings_controller->force_removal;
	file_settings_controller_copy->open_read_only	=	file_settings_controller->open_read_only;
	file_settings_controller_copy->error_if_exists_on_create	=	file_settings_controller->error_if_exists_on_create;
	file_settings_controller_copy->permit_environment_based_file_naming	=	file_settings_controller->permit_environment_based_file_naming;
	file_settings_controller_copy->temp_directory	=	file_settings_controller->temp_directory;
	file_settings_controller_copy->intermediate_directory_mode	=	file_settings_controller->intermediate_directory_mode;
	file_settings_controller_copy->use_environment_home_permissions_for_file_naming	=	file_settings_controller->use_environment_home_permissions_for_file_naming;
	file_settings_controller_copy->xa_compliant	=	file_settings_controller->xa_compliant;

	return file_settings_controller_copy;
}

