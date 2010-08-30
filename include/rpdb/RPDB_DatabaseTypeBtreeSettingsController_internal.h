#ifndef RPDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_TYPE_BTREE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

size_t	RPDB_DatabaseTypeBtreeSettingsController_internal_prefixCompareMethod(		DB*				bdb_database, 
	  	 																			const DBT*		data_one, 
	  	 																			const DBT*		data_two );
	  	 																	
int		RPDB_DatabaseTypeBtreeSettingsController_internal_duplicateCompareMethod(	DB*				bdb_database, 
   																					const DBT*		data_one, 
   																					const DBT*		data_two);
   		
int		RPDB_DatabaseTypeBtreeSettingsController_internal_compareMethod(			DB*				bdb_database, 
   																					const DBT*		data_one, 
   																					const DBT*		data_two);

RPDB_DatabaseTypeBtreeSettingsController* RPDB_DatabaseTypeBtreeSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeBtreeSettingsController* database_type_btree_settings_controller );
void RPDB_DatabaseTypeBtreeSettingsController_internal_setFlags(	RPDB_DatabaseTypeBtreeSettingsController*		database_type_btree_settings_controller );

#endif

