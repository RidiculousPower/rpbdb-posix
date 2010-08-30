/*
 *		RPDB::SettingsController::JoinSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DatabaseJoinSettingsController.h"

#include "RPDB_DatabaseJoinSettingsController.h"
#include "RPDB_DatabaseJoinController.h"

#include "RPDB_DatabaseJoinSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
RPDB_DatabaseJoinSettingsController* RPDB_DatabaseJoinSettingsController_new( RPDB_DatabaseSettingsController* parent_database_settings_controller )	{
	
	RPDB_DatabaseJoinSettingsController*		join_settings_controller = calloc( 1, sizeof( RPDB_DatabaseJoinSettingsController ) );

	join_settings_controller->parent_database_settings_controller = parent_database_settings_controller; 
	
	return join_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DatabaseJoinSettingsController_free(	RPDB_DatabaseJoinSettingsController** join_settings_controller )	{
	
	free( *join_settings_controller );
}

/***************************************
*  parentDatabase  *
***************************************/
RPDB_Database* RPDB_DatabaseJoinSettingsController_parentDatabase(	RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
	return join_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DatabaseJoinSettingsController_parentEnvironment(	RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
	return join_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/*****************************
*  degreeOneIsolation  *
*****************************/

//	DB_READ_UNCOMMITTED				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPDB_DatabaseJoinController_degreeOneIsolation( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
	
	if ( join_settings_controller->degree_one_isolation == TRUE )	{
		return DB_READ_UNCOMMITTED;
	}
	return FALSE;
}

	/********************************
	*  turnDegreeOneIsolationOn  *
	********************************/

	void RPDB_DatabaseJoinController_turnDegreeOneIsolationOn( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->degree_one_isolation = TRUE;
	}

	/********************************
	*  turnDegreeOneIsolationOff  *
	********************************/

	void RPDB_DatabaseJoinController_turnDegreeOneIsolationOff( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->degree_one_isolation = FALSE;
	}

/******************************************
*  writeLocksInsteadOfReadLocks  *
******************************************/

//	DB_RMW						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPDB_DatabaseJoinController_writeLocksInsteadOfReadLocks( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
	
	if ( join_settings_controller->use_write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	********************************************/

	void RPDB_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOn( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->use_write_locks_instead_of_read_locks = TRUE;
	}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	********************************************/

	void RPDB_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOff( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->use_write_locks_instead_of_read_locks = FALSE;
	}

/******************************************
*  writeLocksInsteadOfReadLocks  *
******************************************/

//	DB_JOIN_NOSORT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPDB_DatabaseJoinController_noSortBeforeJoin( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{

	if ( join_settings_controller->sort_before_join == TRUE )	{
		return DB_JOIN_NOSORT;
	}
	return FALSE;
}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	********************************************/

	void RPDB_DatabaseJoinController_turnNoSortBeforeJoinOn( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->sort_before_join = TRUE;
	}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	********************************************/

	void RPDB_DatabaseJoinController_turnNoSortBeforeJoinOff( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
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

BOOL RPDB_DatabaseJoinSettingsController_internal_retrieveFlags( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
	
	return	RPDB_DatabaseJoinController_degreeOneIsolation( join_settings_controller )
			|	RPDB_DatabaseJoinController_writeLocksInsteadOfReadLocks( join_settings_controller );
	
}

/****************
*  joinFlags  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL RPDB_DatabaseJoinSettingsController_internal_joinFlags( RPDB_DatabaseJoinSettingsController* join_settings_controller )	{
	return RPDB_DatabaseJoinController_noSortBeforeJoin( join_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DatabaseJoinSettingsController* RPDB_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseJoinSettingsController* join_settings_controller )	{

	RPDB_DatabaseJoinSettingsController* join_settings_controller_copy	=	RPDB_DatabaseJoinSettingsController_new( join_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	join_settings_controller_copy->degree_one_isolation	=	join_settings_controller->degree_one_isolation;
	join_settings_controller_copy->use_write_locks_instead_of_read_locks	=	join_settings_controller->use_write_locks_instead_of_read_locks;
	join_settings_controller_copy->sort_before_join	=	join_settings_controller->sort_before_join;

	return join_settings_controller_copy;
}

