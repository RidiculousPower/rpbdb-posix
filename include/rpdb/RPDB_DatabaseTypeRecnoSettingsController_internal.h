#ifndef RPDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPDB_DatabaseTypeRecnoSettingsController_internal_appendCallbackMethod(	DB*				bdb_database, 
																				DBT*			bdb_data, 
																				db_recno_t		record_number );

RPDB_DatabaseTypeRecnoSettingsController* RPDB_DatabaseTypeRecnoSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
void RPDB_DatabaseTypeRecnoSettingsController_internal_setFlags(	RPDB_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller );

#endif

