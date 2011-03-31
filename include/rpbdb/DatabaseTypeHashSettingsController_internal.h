#ifndef RPBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

uint32_t		RPbdb_DatabaseTypeHashSettingsController_internal_hashMethod(				DB*				bdb_database, 
   																							const void*		bytes, 
   																							uint32_t		length );
   		
int				RPbdb_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
   																							const DBT*		data_one, 
   																							const DBT*		data_two);
   				
int				RPbdb_DatabaseTypeHashSettingsController_internal_compareMethod(			DB*				bdb_database, 
   																							const DBT*		data_one, 
   																							const DBT*		data_two);

RPbdb_DatabaseTypeHashSettingsController* RPbdb_DatabaseTypeHashSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );

void RPbdb_DatabaseTypeHashSettingsController_internal_setFlags(	RPbdb_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller );

#endif

