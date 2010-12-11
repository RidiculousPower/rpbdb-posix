#ifndef RBDB_DATABASE_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_DatabaseController* Rbdb_DatabaseController_internal_newWithoutRuntimeStorage( Rbdb_Environment* parent_environment );

Rbdb_Database* Rbdb_DatabaseController_internal_databaseForBDBDatabase(	DB*									bdb_database );

int Rbdb_DatabaseController_internal_associateCallback_Database__bdb_db_address(	DB*				bdb_secondary_database, 
																					 const DBT*		bdb_key, 
																					 const DBT*		bdb_data, 
																					 DBT*			bdb_return_data	);
	
#endif
