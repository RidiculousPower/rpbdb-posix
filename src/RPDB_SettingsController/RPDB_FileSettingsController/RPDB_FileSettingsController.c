/*
 *		RPDB::SettingsController::FileSettingsController
 *
 *
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_FileSettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_FileVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_FileSettingsController* RPDB_FileSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_FileSettingsController*		file_settings_controller = calloc( 1, sizeof( RPDB_FileSettingsController ) );

	file_settings_controller->parent_settings_controller = settings_controller;

	return file_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_FileSettingsController_free(	RPDB_FileSettingsController** file_settings_controller )	{

	if ( ( *file_settings_controller )->verbosity_settings_controller != NULL )	{
		RPDB_FileVerbositySettingsController_free( & ( ( *file_settings_controller )->verbosity_settings_controller ) );
	}
	
	free( *file_settings_controller );
	*file_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_FileSettingsController_parentEnvironment(	RPDB_FileSettingsController* file_settings_controller )	{
	return file_settings_controller->parent_settings_controller->parent_environment;
}

/*********************************
*  intermediateDirectoryMode  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_intermediate_dir_mode.html
char* RPDB_FileSettingsController_intermediateDirectoryMode( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->intermediate_directory_mode == NULL )	{

		RPDB_Environment*	environment = file_settings_controller->parent_settings_controller->parent_environment;

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

void RPDB_FileSettingsController_setIntermediateDirectoryMode( RPDB_FileSettingsController* file_settings_controller, const char* mode )	{

	RPDB_Environment*			environment;

	environment = file_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_intermediate_dir_mode(	environment->wrapped_bdb_environment, 
																			mode );
	}
}

/*********************
*  tempDirectory  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_tmp_dir.html
char* RPDB_FileSettingsController_tempDirectory( RPDB_FileSettingsController* file_settings_controller )	{

	RPDB_Environment*			environment;

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

void RPDB_FileSettingsController_setTempDirectory( RPDB_FileSettingsController* file_settings_controller, const char* temp_directory )	{

	RPDB_Environment*			environment;

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
int RPDB_FileSettingsController_permitEnvironmentBasedFileNaming( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->permit_environment_based_file_naming == TRUE )	{
		return DB_USE_ENVIRON;
	}
	return FALSE;
}

	/*************************************
	*  turnPermitEnvironmentNamingOn  *
	*************************************/

	void RPDB_FileSettingsController_turnPermitEnvironmentBasedFileNamingOn( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->permit_environment_based_file_naming = TRUE;
	}

	/*************************************
	*  turnPermitEnvironmentNamingOff  *
	*************************************/

	void RPDB_FileSettingsController_turnPermitEnvironmentBasedFileNamingOff( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->permit_environment_based_file_naming = FALSE;
	}

/****************************
*  useEnvironmentHome  *
****************************/

//	DB_USE_ENVIRON_ROOT     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->use_environment_home_permissions_for_file_naming == TRUE )	{
		return DB_USE_ENVIRON_ROOT;	
	}
	return FALSE;
}

	/*********************************
	*  turnUseEnvironmentHomeOn  *
	*********************************/

	void RPDB_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOn( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->use_environment_home_permissions_for_file_naming = TRUE;
	}

	/*********************************
	*  turnUseEnvironmentHomeOff  *
	*********************************/

	void RPDB_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOff( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->use_environment_home_permissions_for_file_naming = FALSE;
	}

/*********************************
*  createIfNecessary  *
*********************************/

//	DB_CREATE               http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int RPDB_FileSettingsController_createIfNecessary( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->create_if_necessary == TRUE )	{
		return DB_CREATE;
	}
	return FALSE;
}

	/*************************************
	*  turnCreateIfNecessaryOn  *
	*************************************/

	void RPDB_FileSettingsController_turnCreateIfNecessaryOn( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->create_if_necessary = TRUE;
	}

	/**************************************
	*  turnCreateIfNecessaryOff  *
	**************************************/

	void RPDB_FileSettingsController_turnCreateIfNecessaryOff( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->create_if_necessary = FALSE;
	}

/**************************************
*  isErrorIfDBExistsBeforeCreate  *
**************************************/

//	DB_EXCL					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int RPDB_FileSettingsController_isErrorIfDBExistsBeforeCreate( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->error_if_exists_on_create == TRUE )	{
		return DB_EXCL;
	}
	return FALSE;
}

	/********************************************
	*  turnIsErrorIfDBExistsBeforeCreateOn  *
	********************************************/

	void RPDB_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOn( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->error_if_exists_on_create = TRUE;
	}

	/*********************************************
	*  turnIsErrorIfDBExistsBeforeCreateOff  *
	*********************************************/

	void RPDB_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOff( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->error_if_exists_on_create = FALSE;
	}

/*************************
*  openReadOnly  *
*************************/

//	DB_RDONLY					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int RPDB_FileSettingsController_openReadOnly( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->open_read_only == TRUE )	{
		return DB_RDONLY;
	}
	return FALSE;
}

	/********************************
	*  turnOpenReadOnlyOn  *
	********************************/

	void RPDB_FileSettingsController_turnOpenReadOnlyOn( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->open_read_only = TRUE;
	}

	/********************************
	*  turnOpenReadOnlyOff  *
	********************************/

	void RPDB_FileSettingsController_turnOpenReadOnlyOff( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->open_read_only = FALSE;
	}

/*************************
*  forceRemoval  *
*************************/

//	DB_FORCE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_remove.html
int RPDB_FileSettingsController_forceRemoval( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->force_removal == TRUE )	{
		return DB_FORCE;
	}
	return FALSE;
}

	/*********************************
	*  turnForceRemovalOn  *
	*********************************/

	void RPDB_FileSettingsController_turnForceRemovalOn( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->force_removal = TRUE;
	}

	/*********************************
	*  turnForceRemovalOff  *
	*********************************/

	void RPDB_FileSettingsController_turnForceRemovalOff( RPDB_FileSettingsController* file_settings_controller )	{
		file_settings_controller->force_removal = FALSE;
	}

/*************************
*  fileCreationMode  *
*************************/

int RPDB_FileSettingsController_fileCreationMode( RPDB_FileSettingsController* file_settings_controller )	{

	return file_settings_controller->file_creation_mode;
}

/****************************
*  setFileCreationMode  *
****************************/

void RPDB_FileSettingsController_setFileCreationMode(	RPDB_FileSettingsController*	file_settings_controller,
 														int								mode	)	{
	file_settings_controller->file_creation_mode = mode;
}

/*************************************
*  verbositySettingsController  *
*************************************/

RPDB_FileVerbositySettingsController* RPDB_FileSettingsController_verbositySettingsController( RPDB_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->verbosity_settings_controller == NULL )	{
	
		file_settings_controller->verbosity_settings_controller = RPDB_FileVerbositySettingsController_new( file_settings_controller );
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
RPDB_FileSettingsController* RPDB_FileSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_FileSettingsController* file_settings_controller )	{

	RPDB_FileSettingsController* file_settings_controller_copy	=	RPDB_FileSettingsController_new( file_settings_controller->parent_settings_controller );

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

