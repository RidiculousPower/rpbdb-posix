/*
 *		Rbdb::Database::DatabaseSettingsController::DatabaseAssociationSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_DatabaseAssociationSettingsController.h"

	#include "Rbdb_DatabaseCursorSettingsController.h"
	#include "Rbdb_DatabaseSettingsController.h"
	
	#include "Rbdb_DatabaseCursorSettingsController_internal.h"
	#include "Rbdb_DatabaseAssociationSettingsController_internal.h"
 
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_DatabaseAssociationSettingsController* Rbdb_DatabaseAssociationSettingsController_new( Rbdb_DatabaseSettingsController* database_settings_controller )	{

	Rbdb_DatabaseAssociationSettingsController*		database_association_settings_controller = calloc( 1, sizeof( Rbdb_DatabaseAssociationSettingsController ) );

	database_association_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_association_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_DatabaseAssociationSettingsController_free(	Rbdb_DatabaseAssociationSettingsController** database_association_settings_controller )	{
	
	free( *database_association_settings_controller );
	*database_association_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_DatabaseAssociationSettingsController_parentEnvironment(	Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
	return database_association_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
Rbdb_Database* Rbdb_DatabaseAssociationSettingsController_parentDatabase(	Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
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
BOOL Rbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex( Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	if ( database_association_settings_controller->index_primary_database == TRUE )	{
		return DB_CREATE;
	}
	return FALSE;
}

	/*********************
	*  indexPrimaryOn  *
	*********************/

	void Rbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOn( Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
		database_association_settings_controller->index_primary_database = TRUE;
	}

	/************************
	*  indexPrimaryOff  *
	************************/

	void Rbdb_DatabaseAssociationSettingsController_turnSecondaryAssociationCreatesIndexOff( Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
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
BOOL Rbdb_DatabaseAssociationSettingsController_immutableSecondaryKey( Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	if ( database_association_settings_controller->secondary_key_is_immutable == TRUE )	{
		return DB_IMMUTABLE_KEY;
	}
	return FALSE;
}

	/********************************
	*  immutableSecondaryKeyOn  *
	********************************/

	void Rbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOn( Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
		database_association_settings_controller->secondary_key_is_immutable = TRUE;
	}

	/********************************
	*  immutableSecondaryKeyOff  *
	********************************/

	void Rbdb_DatabaseAssociationSettingsController_turnImmutableSecondaryKeyOff( Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{
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

int Rbdb_DatabaseCursorSettingsController_internal_associateFlags( Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	return	Rbdb_DatabaseAssociationSettingsController_secondaryAssociationCreatesIndex( database_association_settings_controller )
			|	Rbdb_DatabaseAssociationSettingsController_immutableSecondaryKey( database_association_settings_controller );

}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_DatabaseAssociationSettingsController* Rbdb_DatabaseAssociationSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller )	{

	Rbdb_DatabaseAssociationSettingsController* database_association_settings_controller_copy	=	Rbdb_DatabaseAssociationSettingsController_new( database_association_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_association_settings_controller_copy->secondary_key_is_immutable	=	database_association_settings_controller->secondary_key_is_immutable;
	database_association_settings_controller_copy->index_primary_database	=	database_association_settings_controller->index_primary_database;

	return database_association_settings_controller_copy;
}

