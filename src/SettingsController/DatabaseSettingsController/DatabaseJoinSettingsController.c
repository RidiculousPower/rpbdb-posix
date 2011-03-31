/*
 *		RPbdb::SettingsController::JoinSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseJoinSettingsController.h"

#include "DatabaseJoinSettingsController.h"
#include "DatabaseJoinController.h"

#include "DatabaseJoinSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPbdb_DatabaseJoinSettingsController* RPbdb_DatabaseJoinSettingsController_new( RPbdb_DatabaseSettingsController* parent_database_settings_controller )	{
	
	RPbdb_DatabaseJoinSettingsController*		join_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseJoinSettingsController ) );

	join_settings_controller->parent_database_settings_controller = parent_database_settings_controller; 
	
	return join_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseJoinSettingsController_free(	RPbdb_DatabaseJoinSettingsController** join_settings_controller )	{
	
	free( *join_settings_controller );
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseJoinSettingsController_parentDatabase(	RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	return join_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseJoinSettingsController_parentEnvironment(	RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	return join_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/*****************************
*  degreeOneIsolation  *
*****************************/

//	DB_READ_UNCOMMITTED				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPbdb_DatabaseJoinController_degreeOneIsolation( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	
	if ( join_settings_controller->degree_one_isolation == TRUE )	{
		return DB_READ_UNCOMMITTED;
	}
	return FALSE;
}

	/********************************
	*  turnDegreeOneIsolationOn  *
	********************************/

	void RPbdb_DatabaseJoinController_turnDegreeOneIsolationOn( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->degree_one_isolation = TRUE;
	}

	/********************************
	*  turnDegreeOneIsolationOff  *
	********************************/

	void RPbdb_DatabaseJoinController_turnDegreeOneIsolationOff( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->degree_one_isolation = FALSE;
	}

/******************************************
*  writeLocksInsteadOfReadLocks  *
******************************************/

//	DB_RMW						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPbdb_DatabaseJoinController_writeLocksInsteadOfReadLocks( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	
	if ( join_settings_controller->use_write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	********************************************/

	void RPbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOn( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->use_write_locks_instead_of_read_locks = TRUE;
	}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	********************************************/

	void RPbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOff( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->use_write_locks_instead_of_read_locks = FALSE;
	}

/******************************************
*  writeLocksInsteadOfReadLocks  *
******************************************/

//	DB_JOIN_NOSORT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPbdb_DatabaseJoinController_noSortBeforeJoin( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{

	if ( join_settings_controller->sort_before_join == TRUE )	{
		return DB_JOIN_NOSORT;
	}
	return FALSE;
}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	********************************************/

	void RPbdb_DatabaseJoinController_turnNoSortBeforeJoinOn( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->sort_before_join = TRUE;
	}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	********************************************/

	void RPbdb_DatabaseJoinController_turnNoSortBeforeJoinOff( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->sort_before_join = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/********************
*  retrieveFlags  *
********************/

BOOL RPbdb_DatabaseJoinSettingsController_internal_retrieveFlags( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	
	return	RPbdb_DatabaseJoinController_degreeOneIsolation( join_settings_controller )
			|	RPbdb_DatabaseJoinController_writeLocksInsteadOfReadLocks( join_settings_controller );
	
}

/****************
*  joinFlags  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPbdb_DatabaseJoinSettingsController_internal_joinFlags( RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	return RPbdb_DatabaseJoinController_noSortBeforeJoin( join_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseJoinSettingsController* RPbdb_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseJoinSettingsController* join_settings_controller )	{

	RPbdb_DatabaseJoinSettingsController* join_settings_controller_copy	=	RPbdb_DatabaseJoinSettingsController_new( join_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	join_settings_controller_copy->degree_one_isolation	=	join_settings_controller->degree_one_isolation;
	join_settings_controller_copy->use_write_locks_instead_of_read_locks	=	join_settings_controller->use_write_locks_instead_of_read_locks;
	join_settings_controller_copy->sort_before_join	=	join_settings_controller->sort_before_join;

	return join_settings_controller_copy;
}

