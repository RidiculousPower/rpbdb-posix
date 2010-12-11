#ifndef RBDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER_INTERNAL
	#define RBDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int Rbdb_DatabaseTypeRecnoSettingsController_internal_appendCallbackMethod(	DB*				bdb_database, 
																				DBT*			bdb_data, 
																				db_recno_t		record_number );

Rbdb_DatabaseTypeRecnoSettingsController* Rbdb_DatabaseTypeRecnoSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
void Rbdb_DatabaseTypeRecnoSettingsController_internal_setFlags(	Rbdb_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller );

#endif

