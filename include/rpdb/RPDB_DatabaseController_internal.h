#ifndef RPDB_DATABASE_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_DatabaseController* RPDB_DatabaseController_internal_newWithoutRuntimeStorage( RPDB_Environment* parent_environment );

RPDB_Database* RPDB_DatabaseController_internal_databaseForBDBDatabase(	DB*									bdb_database );

int RPDB_DatabaseController_internal_associateCallback_Database__bdb_db_address(	DB*				bdb_secondary_database, 
																					 const DBT*		bdb_key, 
																					 const DBT*		bdb_data, 
																					 DBT*			bdb_return_data	);
char* RPDB_DatabaseController_internal_uniqueIdentifier( RPDB_DatabaseController* database_controller );

char* RPDB_DatabaseController_internal_autonumberName( RPDB_DatabaseController* database_controller );
	
#endif
