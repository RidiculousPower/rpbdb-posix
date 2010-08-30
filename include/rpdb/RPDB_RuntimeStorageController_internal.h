#ifndef RPDB_RUNTIME_STORAGE_CONTROLLER_INTERNAL
	#define RPDB_RUNTIME_STORAGE_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPDB_RuntimeStorageController_internal_associateCallback_RuntimeStorage__name(	DB*				bdb_secondary_database, 
																						const DBT*		bdb_key, 
																						const DBT*		bdb_data, 
																						DBT*			bdb_return_data	);	

int RPDB_RuntimeStorageController_internal_associateCallback_RuntimeStorage__address(	DB*				bdb_secondary_database, 
																						const DBT*		bdb_key, 
																						const DBT*		bdb_data, 
																						DBT*			bdb_return_data	);

int RPDB_RuntimeStorageController_internal_associateCallback_RuntimeStorage__environment_name(	DB*				bdb_secondary_database, 
			 																						const DBT*		bdb_key, 
																									const DBT*		bdb_data, 
																									DBT*			bdb_return_data	);

void RPDB_RuntimeStorageController_internal_storeEnvironmentForBDBEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																			   RPDB_Environment*					environment	);

void RPDB_RuntimeStorageController_internal_removeStoredEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																		RPDB_Environment*					environment	);

void RPDB_RuntimeStorageController_internal_storeDatabaseForBDBDatabase(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																		 RPDB_Database*						database	);
void RPDB_RuntimeStorageController_internal_removeDatabaseStoredForBDBDatabase(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																				RPDB_Database*						database	);
RPDB_Environment* RPDB_RuntimeStorageController_internal_environmentForBDBEnvironment(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																						DB_ENV*								bdb_environment	);
RPDB_Database* RPDB_RuntimeStorageController_internal_databaseForBDBDatabase(	RPDB_RuntimeStorageController*		runtime_storage_controller,
																			   DB*									bdb_database	);
	
int RPDB_RuntimeStorageController_environmentNextAutoNumber( RPDB_RuntimeStorageController*		runtime_storage_controller );
	
#endif