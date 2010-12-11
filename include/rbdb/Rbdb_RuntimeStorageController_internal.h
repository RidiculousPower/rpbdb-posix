#ifndef RBDB_RUNTIME_STORAGE_CONTROLLER_INTERNAL
	#define RBDB_RUNTIME_STORAGE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int Rbdb_RuntimeStorageController_internal_associateCallback_RuntimeStorage__name(	DB*				bdb_secondary_database, 
																						const DBT*		bdb_key, 
																						const DBT*		bdb_data, 
																						DBT*			bdb_return_data	);	

int Rbdb_RuntimeStorageController_internal_associateCallback_RuntimeStorage__address(	DB*				bdb_secondary_database, 
																						const DBT*		bdb_key, 
																						const DBT*		bdb_data, 
																						DBT*			bdb_return_data	);

int Rbdb_RuntimeStorageController_internal_associateCallback_RuntimeStorage__environment_name(	DB*				bdb_secondary_database, 
			 																						const DBT*		bdb_key, 
																									const DBT*		bdb_data, 
																									DBT*			bdb_return_data	);

void Rbdb_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																			   Rbdb_Environment*					environment	);

void Rbdb_RuntimeStorageController_internal_removeStoredEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																		Rbdb_Environment*					environment	);

void Rbdb_RuntimeStorageController_internal_storeDatabaseForBDBDatabase(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																		 Rbdb_Database*						database	);
void Rbdb_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																				Rbdb_Database*						database	);
Rbdb_Environment* Rbdb_RuntimeStorageController_internal_environmentForBDBEnvironment(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																						DB_ENV*								bdb_environment	);
Rbdb_Database* Rbdb_RuntimeStorageController_internal_databaseForBDBDatabase(	Rbdb_RuntimeStorageController*		runtime_storage_controller,
																			   DB*									bdb_database	);
		
#endif