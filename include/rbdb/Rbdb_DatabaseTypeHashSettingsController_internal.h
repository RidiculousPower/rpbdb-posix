#ifndef RBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

uint32_t		Rbdb_DatabaseTypeHashSettingsController_internal_hashMethod(				DB*				bdb_database, 
   																							const void*		bytes, 
   																							uint32_t		length );
   		
int				Rbdb_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
   																							const DBT*		data_one, 
   																							const DBT*		data_two);
   				
int				Rbdb_DatabaseTypeHashSettingsController_internal_compareMethod(			DB*				bdb_database, 
   																							const DBT*		data_one, 
   																							const DBT*		data_two);

Rbdb_DatabaseTypeHashSettingsController* Rbdb_DatabaseTypeHashSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );

void Rbdb_DatabaseTypeHashSettingsController_internal_setFlags(	Rbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller );

#endif

