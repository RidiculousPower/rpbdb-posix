/*
 *		RPDB::SettingsDirectoryController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DirectorySettingsController.h"

#include "RPDB_Environment.h"
#include "RPDB_Directory.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DirectorySettingsController* RPDB_DirectorySettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_DirectorySettingsController*		directory_settings_controller = calloc( 1, sizeof( RPDB_DirectorySettingsController ) );

	directory_settings_controller->parent_settings_controller = settings_controller;

	return directory_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DirectorySettingsController_free(	RPDB_DirectorySettingsController** directory_settings_controller )	{

	free( *directory_settings_controller );
	*directory_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DirectorySettingsController_parentEnvironment(	RPDB_DirectorySettingsController* directory_settings_controller )	{
	return directory_settings_controller->parent_settings_controller->parent_environment;
}

/*********************
*  homeDirectory  *
*********************/

//	Get home directory
//	Environment's home directory	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
const char* RPDB_DirectorySettingsController_homeDirectory( RPDB_DirectorySettingsController* directory_settings_controller )	{

	RPDB_Environment*				environment = directory_settings_controller->parent_settings_controller->parent_environment;
	
	if (	directory_settings_controller->home_directory_path == NULL
		&&	environment->wrapped_bdb_environment	)	{

		environment->wrapped_bdb_environment->get_home(	environment->wrapped_bdb_environment, 
														(const char**) &( directory_settings_controller->home_directory_path ) );
	}
	
	return directory_settings_controller->home_directory_path;
}

/************************
*  dataDirectories  *
************************/

//	Get data directories
//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_data_dir.html
//
//	Set the path of a directory to be used as the location of the access method database files. Paths specified to the DB->open function will be searched relative to this path. 
//	
//	Paths set using this method are additive, and specifying more than one will result in each specified directory being searched for database files. 
//	If any directories are specified, created database files will always be created in the first path specified.
//
//	If no database directories are specified, database files must be named either by absolute paths or relative to the environment home directory. 
//
//	The DB_ENV->set_data_dir method may not be called after the DB_ENV->open method is called. 
//
//	We can let BDB manage this for us
const char** RPDB_DirectorySettingsController_dataDirectories( RPDB_DirectorySettingsController* directory_settings_controller )	{

	RPDB_Environment*					environment	= directory_settings_controller->parent_settings_controller->parent_environment;

	const char**	data_directories	=	NULL;
	if ( directory_settings_controller->directories == NULL )	{
		environment->wrapped_bdb_environment->get_data_dirs(	environment->wrapped_bdb_environment, 
																& data_directories );
	}
	
	return data_directories;
}

/************************
*  dataDirectories  *
************************/

//	Add a data directory
void RPDB_DirectorySettingsController_addDataDirectory(	RPDB_DirectorySettingsController*		directory_settings_controller, 
															char*									directory_path  )	{

	//	store directory in settings controller so we can deal with it separate from bdb instances
	if ( directory_settings_controller->directories == NULL )	{

		//	begin linked list of directories
		directory_settings_controller->directories			=	RPDB_Directory_new( directory_path );
	}
	else {
	
		//	add this directory to the end of linked list of directories
		RPDB_Directory**	this_directory	=	& ( directory_settings_controller->directories );
		while ( ( *this_directory )->next != NULL )	{
			this_directory	=	& ( ( *this_directory )->next );
		}
		( *this_directory )->next	=	RPDB_Directory_new( directory_path );
	}

}

 /************************
*  setCreateDirectory  *
************************/

//	Sets one of the data directories to be where dbs are created
void RPDB_DirectorySettingsController_setCreateDirectory(	RPDB_DirectorySettingsController*		directory_settings_controller, 
															char*									directory  )	{
	
	RPDB_Environment*				environment	= directory_settings_controller->parent_settings_controller->parent_environment;
	
	environment->create_directory	=	directory;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->set_create_dir(	environment->wrapped_bdb_environment, 
																directory );
	}
}

/************************
*  getCreateDirectory  *
************************/

//	Sets one of the data directories to be where dbs are created
char* RPDB_DirectorySettingsController_getCreateDirectory(	RPDB_DirectorySettingsController*		directory_settings_controller  )	{
	
	RPDB_Environment*				environment	= directory_settings_controller->parent_settings_controller->parent_environment;
	
	if (	environment->create_directory == NULL
		&&	environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->get_create_dir(	environment->wrapped_bdb_environment, 
																(const char**) & environment->create_directory );
	}
	
	return environment->create_directory;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DirectorySettingsController* RPDB_DirectorySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DirectorySettingsController* directory_settings_controller )	{

	RPDB_DirectorySettingsController* directory_settings_controller_copy	=	RPDB_DirectorySettingsController_new( directory_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	directory_settings_controller_copy->home_directory_path	=	directory_settings_controller->home_directory_path;

	return directory_settings_controller_copy;
}

