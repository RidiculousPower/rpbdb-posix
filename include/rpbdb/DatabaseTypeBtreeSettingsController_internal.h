#ifndef RPBDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

size_t	RPbdb_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod(		DB*				bdb_database, 
	  	 																			const DBT*		data_one, 
	  	 																			const DBT*		data_two );
	  	 																	
int		RPbdb_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
   																					const DBT*		data_one, 
   																					const DBT*		data_two);
   		
int		RPbdb_DatabaseTypeBtreeSettingsController_internal_compareMethod(			DB*				bdb_database, 
   																					const DBT*		data_one, 
   																					const DBT*		data_two);

RPbdb_DatabaseTypeBtreeSettingsController* RPbdb_DatabaseTypeBtreeSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
void RPbdb_DatabaseTypeBtreeSettingsController_internal_setFlags(	RPbdb_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller );

#endif

