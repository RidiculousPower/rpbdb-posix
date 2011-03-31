#ifndef RPBDB_DATABASE_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPbdb_DatabaseController* RPbdb_DatabaseController_internal_newWithoutRuntimeStorage( RPbdb_Environment* parent_environment );

RPbdb_Database* RPbdb_DatabaseController_internal_databaseForBDBDatabase(	DB*									bdb_database );

int RPbdb_DatabaseController_internal_associateCallback_Database__bdb_db_address(	DB*				bdb_secondary_database, 
																					 const DBT*		bdb_key, 
																					 const DBT*		bdb_data, 
																					 DBT*			bdb_return_data	);
	
#endif
