/*
 *		RPbdb::Database::DatabaseSettingsController::DatabaseAssociationSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseAssociationSettingsController.h"

	#include "DatabaseCursorSettingsController.h"
	#include "DatabaseSettingsController.h"
	
	#include "DatabaseCursorSettingsController_internal.h"
	#include "DatabaseAssociationSettingsController_internal.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseAssociationSettingsController* RPbdb_DatabaseAssociationSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseAssociationSettingsController*		database_association_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseAssociationSettingsController ) );

	database_association_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_association_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseAssociationSettingsController_free(	RPbdb_DatabaseAssociationSettingsController** database_association_settings_controller )	{
	
	free( *database_association_settings_controller );
	*database_association_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseAssociationSettingsController_parentEnvironment(	RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
	return database_association_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseAssociationSettingsController_parentDatabase(	RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
	return database_association_settings_controller->parent_database_settings_controller->parent_database;
}

/*********************
*  indexPrimary  *
*********************/

//	DB_CREATE	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_associate.html
//	If the secondary database is empty, walk through the primary and create an index to it in the empty secondary. This operation is potentially very expensive.
//	Care should be taken not to use a newly-populated secondary database in another thread of control until the DB->associate call has returned successfully in the first thread.
//	If transactions are not being used, care should be taken not to modify a primary database being used to populate a secondary database in another thread of control, 
//	until the DB->associate call has returned successfully in the first thread. 
//	If transactions are being used, Berkeley DB will perform appropriate locking and the application need not do any special operation ordering.
BOOL RPbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex( RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	if ( database_association_settings_controller->index_primary_database == TRUE )	{
		return DB_CREATE;
	}
	return FALSE;
}

	/*********************
	*  indexPrimaryOn  *
	*********************/

	void RPbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOn( RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
		database_association_settings_controller->index_primary_database = TRUE;
	}

	/************************
	*  indexPrimaryOff  *
	************************/

	void RPbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOff( RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
		database_association_settings_controller->index_primary_database = FALSE;
	}

/*****************************
*  immutableSecondaryKey  *
*****************************/

//	DB_IMMUTABLE_KEY		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_associate.html
//	This flag can be used to optimize updates when the secondary key in a primary record will never be changed after the primary record is inserted. 
//	For immutable secondary keys, a best effort is made to avoid calling the secondary callback function when primary records are updated. 
//	This optimization may reduce the overhead of update operations significantly if the callback function is expensive.
//	Be sure to specify this flag only if the secondary key in the primary record is never changed. 
//	If this rule is violated, the secondary index will become corrupted, that is, it will become out of sync with the primary.
BOOL RPbdb_DatabaseAssociationSettingsController_immutableSecondaryKey( RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	if ( database_association_settings_controller->secondary_key_is_immutable == TRUE )	{
		return DB_IMMUTABLE_KEY;
	}
	return FALSE;
}

	/********************************
	*  immutableSecondaryKeyOn  *
	********************************/

	void RPbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOn( RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
		database_association_settings_controller->secondary_key_is_immutable = TRUE;
	}

	/********************************
	*  immutableSecondaryKeyOff  *
	********************************/

	void RPbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOff( RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
		database_association_settings_controller->secondary_key_is_immutable = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/**************************
*  associateFlags  *
**************************/

int RPbdb_DatabaseCursorSettingsController_internal_associateFlags( RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	return	RPbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex( database_association_settings_controller )
			|	RPbdb_DatabaseAssociationSettingsController_immutableSecondaryKey( database_association_settings_controller );

}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseAssociationSettingsController* RPbdb_DatabaseAssociationSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	RPbdb_DatabaseAssociationSettingsController* database_association_settings_controller_copy	=	RPbdb_DatabaseAssociationSettingsController_new( database_association_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_association_settings_controller_copy->secondary_key_is_immutable	=	database_association_settings_controller->secondary_key_is_immutable;
	database_association_settings_controller_copy->index_primary_database	=	database_association_settings_controller->index_primary_database;

	return database_association_settings_controller_copy;
}

