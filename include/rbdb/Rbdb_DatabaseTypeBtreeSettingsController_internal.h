#ifndef RBDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

size_t	Rbdb_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod(		DB*				bdb_database, 
	  	 																			const DBT*		data_one, 
	  	 																			const DBT*		data_two );
	  	 																	
int		Rbdb_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
   																					const DBT*		data_one, 
   																					const DBT*		data_two);
   		
int		Rbdb_DatabaseTypeBtreeSettingsController_internal_compareMethod(			DB*				bdb_database, 
   																					const DBT*		data_one, 
   																					const DBT*		data_two);

Rbdb_DatabaseTypeBtreeSettingsController* Rbdb_DatabaseTypeBtreeSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
void Rbdb_DatabaseTypeBtreeSettingsController_internal_setFlags(	Rbdb_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller );

#endif

