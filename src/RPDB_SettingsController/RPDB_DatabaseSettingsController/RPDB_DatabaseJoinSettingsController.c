/*
 *		Rbdb::SettingsController::JoinSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseJoinSettingsController.h"

#include "Rbdb_DatabaseJoinSettingsController.h"
#include "Rbdb_DatabaseJoinController.h"

#include "Rbdb_DatabaseJoinSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/
	
Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseJoinSettingsController_new( Rbdb_DatabaseSettingsController* parent_database_settings_controller )	{
	
	Rbdb_DatabaseJoinSettingsController*		join_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseJoinSettingsController ) );

	join_settings_controller->parent_database_settings_controller = parent_database_settings_controller; 
	
	return join_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseJoinSettingsController_free(	Rbdb_DatabaseJoinSettingsController** join_settings_controller )	{
	
	free( *join_settings_controller );
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseJoinSettingsController_parentDatabase(	Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	return join_settings_controller->parent_database_settings_controller->parent_database;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseJoinSettingsController_parentEnvironment(	Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	return join_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/*****************************
*  degreeOneIsolation  *
*****************************/

//	DB_READ_UNCOMMITTED				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL Rbdb_DatabaseJoinController_degreeOneIsolation( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	
	if ( join_settings_controller->degree_one_isolation == TRUE )	{
		return DB_READ_UNCOMMITTED;
	}
	return FALSE;
}

	/********************************
	*  turnDegreeOneIsolationOn  *
	********************************/

	void Rbdb_DatabaseJoinController_turnDegreeOneIsolationOn( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->degree_one_isolation = TRUE;
	}

	/********************************
	*  turnDegreeOneIsolationOff  *
	********************************/

	void Rbdb_DatabaseJoinController_turnDegreeOneIsolationOff( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->degree_one_isolation = FALSE;
	}

/******************************************
*  writeLocksInsteadOfReadLocks  *
******************************************/

//	DB_RMW						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL Rbdb_DatabaseJoinController_writeLocksInsteadOfReadLocks( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	
	if ( join_settings_controller->use_write_locks_instead_of_read_locks == TRUE )	{
		return DB_RMW;
	}
	return FALSE;
}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	********************************************/

	void Rbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOn( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->use_write_locks_instead_of_read_locks = TRUE;
	}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	********************************************/

	void Rbdb_DatabaseJoinController_turnWriteLocksInsteadOfReadLocksOff( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->use_write_locks_instead_of_read_locks = FALSE;
	}

/******************************************
*  writeLocksInsteadOfReadLocks  *
******************************************/

//	DB_JOIN_NOSORT			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL Rbdb_DatabaseJoinController_noSortBeforeJoin( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{

	if ( join_settings_controller->sort_before_join == TRUE )	{
		return DB_JOIN_NOSORT;
	}
	return FALSE;
}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOn  *
	********************************************/

	void Rbdb_DatabaseJoinController_turnNoSortBeforeJoinOn( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
		join_settings_controller->sort_before_join = TRUE;
	}

	/********************************************
	*  turnWriteLocksInsteadOfReadLocksOff  *
	********************************************/

	void Rbdb_DatabaseJoinController_turnNoSortBeforeJoinOff( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
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

BOOL Rbdb_DatabaseJoinSettingsController_internal_retrieveFlags( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	
	return	Rbdb_DatabaseJoinController_degreeOneIsolation( join_settings_controller )
			|	Rbdb_DatabaseJoinController_writeLocksInsteadOfReadLocks( join_settings_controller );
	
}

/****************
*  joinFlags  *
****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_join.html
BOOL Rbdb_DatabaseJoinSettingsController_internal_joinFlags( Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{
	return Rbdb_DatabaseJoinController_noSortBeforeJoin( join_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseJoinSettingsController* Rbdb_DatabaseJoinSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseJoinSettingsController* join_settings_controller )	{

	Rbdb_DatabaseJoinSettingsController* join_settings_controller_copy	=	Rbdb_DatabaseJoinSettingsController_new( join_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	join_settings_controller_copy->degree_one_isolation	=	join_settings_controller->degree_one_isolation;
	join_settings_controller_copy->use_write_locks_instead_of_read_locks	=	join_settings_controller->use_write_locks_instead_of_read_locks;
	join_settings_controller_copy->sort_before_join	=	join_settings_controller->sort_before_join;

	return join_settings_controller_copy;
}

