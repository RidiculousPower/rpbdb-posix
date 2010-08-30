#ifndef RPDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_TYPE_HASH_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

uint32_t		RPDB_DatabaseTypeHashSettingsController_internal_hashMethod(				DB*				bdb_database, 
   																							const void*		bytes, 
   																							uint32_t		length );
   		
int				RPDB_DatabaseTypeHashSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
   																							const DBT*		data_one, 
   																							const DBT*		data_two);
   				
int				RPDB_DatabaseTypeHashSettingsController_internal_compareMethod(			DB*				bdb_database, 
   																							const DBT*		data_one, 
   																							const DBT*		data_two);

RPDB_DatabaseTypeHashSettingsController* RPDB_DatabaseTypeHashSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeHashSettingsController* database_type_hash_settings_controller );

void RPDB_DatabaseTypeHashSettingsController_internal_setFlags(	RPDB_DatabaseTypeHashSettingsController*		database_type_hash_settings_controller );

#endif

