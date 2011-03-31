#ifndef RPBDB_RUNTIME_STORAGE_CONTROLLER_INTERNAL
	#define RPBDB_RUNTIME_STORAGE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPbdb_RuntimeStorageController_internal_associateCallback_RuntimeStorage__name(	DB*				bdb_secondary_database, 
																						const DBT*		bdb_key, 
																						const DBT*		bdb_data, 
																						DBT*			bdb_return_data	);	

int RPbdb_RuntimeStorageController_internal_associateCallback_RuntimeStorage__address(	DB*				bdb_secondary_database, 
																						const DBT*		bdb_key, 
																						const DBT*		bdb_data, 
																						DBT*			bdb_return_data	);

int RPbdb_RuntimeStorageController_internal_associateCallback_RuntimeStorage__environment_name(	DB*				bdb_secondary_database, 
			 																						const DBT*		bdb_key, 
																									const DBT*		bdb_data, 
																									DBT*			bdb_return_data	);

void RPbdb_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																			   RPbdb_Environment*					environment	);

void RPbdb_RuntimeStorageController_internal_removeStoredEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																		RPbdb_Environment*					environment	);

void RPbdb_RuntimeStorageController_internal_storeDatabaseForBDBDatabase(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																		 RPbdb_Database*						database	);
void RPbdb_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																				RPbdb_Database*						database	);
RPbdb_Environment* RPbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																						DB_ENV*								bdb_environment	);
RPbdb_Database* RPbdb_RuntimeStorageController_internal_databaseForBDBDatabase(	RPbdb_RuntimeStorageController*		runtime_storage_controller,
																			   DB*									bdb_database	);
		
#endif