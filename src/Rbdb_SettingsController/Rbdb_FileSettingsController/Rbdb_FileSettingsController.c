/*
 *		Rbdb::SettingsController::FileSettingsController
 *
 *
 */
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_FileSettingsController.h"

#include "Rbdb_Environment.h"
#include "Rbdb_FileVerbositySettingsController.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_FileSettingsController* Rbdb_FileSettingsController_new( Rbdb_SettingsController* settings_controller )	{

	Rbdb_FileSettingsController*		file_settings_controller = calloc( 1, sizeof( Rbdb_FileSettingsController ) );

	file_settings_controller->parent_settings_controller = settings_controller;

	return file_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_FileSettingsController_free(	Rbdb_FileSettingsController** file_settings_controller )	{

	if ( ( *file_settings_controller )->verbosity_settings_controller != NULL )	{
		Rbdb_FileVerbositySettingsController_free( & ( ( *file_settings_controller )->verbosity_settings_controller ) );
	}
	
	free( *file_settings_controller );
	*file_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_FileSettingsController_parentEnvironment(	Rbdb_FileSettingsController* file_settings_controller )	{
	return file_settings_controller->parent_settings_controller->parent_environment;
}

/*********************************
*  intermediateDirectoryMode  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_intermediate_dir_mode.html
char* Rbdb_FileSettingsController_intermediateDirectoryMode( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->intermediate_directory_mode == NULL )	{

		Rbdb_Environment*	environment = file_settings_controller->parent_settings_controller->parent_environment;

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
void Rbdb_FileSettingsController_setIntermediateDirectoryMode( Rbdb_FileSettingsController* file_settings_controller, const char* mode )	{

	Rbdb_Environment*			environment	= file_settings_controller->parent_settings_controller->parent_environment;

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
char* Rbdb_FileSettingsController_tempDirectory( Rbdb_FileSettingsController* file_settings_controller )	{

	Rbdb_Environment*			environment;

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

void Rbdb_FileSettingsController_setTempDirectory( Rbdb_FileSettingsController* file_settings_controller, const char* temp_directory )	{

	Rbdb_Environment*			environment;

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
int Rbdb_FileSettingsController_permitEnvironmentBasedFileNaming( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->permit_environment_based_file_naming == TRUE )	{
		return DB_USE_ENVIRON;
	}
	return FALSE;
}

	/*************************************
	*  turnPermitEnvironmentNamingOn  *
	*************************************/

	void Rbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOn( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->permit_environment_based_file_naming = TRUE;
	}

	/*************************************
	*  turnPermitEnvironmentNamingOff  *
	*************************************/

	void Rbdb_FileSettingsController_turnPermitEnvironmentBasedFileNamingOff( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->permit_environment_based_file_naming = FALSE;
	}

/****************************
*  useEnvironmentHome  *
****************************/

//	DB_USE_ENVIRON_ROOT     http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_FileSettingsController_useEnvironmentHomePermissionsForFileNaming( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->use_environment_home_permissions_for_file_naming == TRUE )	{
		return DB_USE_ENVIRON_ROOT;	
	}
	return FALSE;
}

	/*********************************
	*  turnUseEnvironmentHomeOn  *
	*********************************/

	void Rbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOn( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->use_environment_home_permissions_for_file_naming = TRUE;
	}

	/*********************************
	*  turnUseEnvironmentHomeOff  *
	*********************************/

	void Rbdb_FileSettingsController_turnUseEnvironmentHomePermissionsForFileNamingOff( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->use_environment_home_permissions_for_file_naming = FALSE;
	}

/*********************************
*  createIfNecessary  *
*********************************/

//	DB_CREATE               http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
int Rbdb_FileSettingsController_createIfNecessary( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->create_if_necessary == TRUE )	{
		return DB_CREATE;
	}
	return FALSE;
}

	/*************************************
	*  turnCreateIfNecessaryOn  *
	*************************************/

	void Rbdb_FileSettingsController_turnCreateIfNecessaryOn( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->create_if_necessary = TRUE;
	}

	/**************************************
	*  turnCreateIfNecessaryOff  *
	**************************************/

	void Rbdb_FileSettingsController_turnCreateIfNecessaryOff( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->create_if_necessary = FALSE;
	}

/**************************************
*  isErrorIfDBExistsBeforeCreate  *
**************************************/

//	DB_EXCL					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int Rbdb_FileSettingsController_isErrorIfDBExistsBeforeCreate( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->error_if_exists_on_create == TRUE )	{
		return DB_EXCL;
	}
	return FALSE;
}

	/********************************************
	*  turnIsErrorIfDBExistsBeforeCreateOn  *
	********************************************/

	void Rbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOn( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->error_if_exists_on_create = TRUE;
	}

	/*********************************************
	*  turnIsErrorIfDBExistsBeforeCreateOff  *
	*********************************************/

	void Rbdb_FileSettingsController_turnIsErrorIfDBExistsBeforeCreateOff( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->error_if_exists_on_create = FALSE;
	}

/*************************
*  openReadOnly  *
*************************/

//	DB_RDONLY					http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_open.html
int Rbdb_FileSettingsController_openReadOnly( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->open_read_only == TRUE )	{
		return DB_RDONLY;
	}
	return FALSE;
}

	/********************************
	*  turnOpenReadOnlyOn  *
	********************************/

	void Rbdb_FileSettingsController_turnOpenReadOnlyOn( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->open_read_only = TRUE;
	}

	/********************************
	*  turnOpenReadOnlyOff  *
	********************************/

	void Rbdb_FileSettingsController_turnOpenReadOnlyOff( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->open_read_only = FALSE;
	}

/*************************
*  forceRemoval  *
*************************/

//	DB_FORCE				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_remove.html
int Rbdb_FileSettingsController_forceRemoval( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->force_removal == TRUE )	{
		return DB_FORCE;
	}
	return FALSE;
}

	/*********************************
	*  turnForceRemovalOn  *
	*********************************/

	void Rbdb_FileSettingsController_turnForceRemovalOn( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->force_removal = TRUE;
	}

	/*********************************
	*  turnForceRemovalOff  *
	*********************************/

	void Rbdb_FileSettingsController_turnForceRemovalOff( Rbdb_FileSettingsController* file_settings_controller )	{
		file_settings_controller->force_removal = FALSE;
	}

/*************************
*  fileCreationMode  *
*************************/

int Rbdb_FileSettingsController_fileCreationMode( Rbdb_FileSettingsController* file_settings_controller )	{

	return file_settings_controller->file_creation_mode;
}

/****************************
*  setFileCreationMode  *
****************************/

void Rbdb_FileSettingsController_setFileCreationMode(	Rbdb_FileSettingsController*	file_settings_controller,
 														int								mode	)	{
	file_settings_controller->file_creation_mode = mode;
}

/*************************************
*  verbositySettingsController  *
*************************************/

Rbdb_FileVerbositySettingsController* Rbdb_FileSettingsController_verbositySettingsController( Rbdb_FileSettingsController* file_settings_controller )	{

	if ( file_settings_controller->verbosity_settings_controller == NULL )	{
	
		file_settings_controller->verbosity_settings_controller = Rbdb_FileVerbositySettingsController_new( file_settings_controller );
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
Rbdb_FileSettingsController* Rbdb_FileSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_FileSettingsController* file_settings_controller )	{

	Rbdb_FileSettingsController* file_settings_controller_copy	=	Rbdb_FileSettingsController_new( file_settings_controller->parent_settings_controller );

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

