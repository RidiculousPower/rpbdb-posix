#ifndef RPBDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_TYPE_RECNO_SETTINGS_CONTROLLER_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

int RPbdb_DatabaseTypeRecnoSettingsController_internal_appendCallbackMethod(	DB*				bdb_database, 
																				DBT*			bdb_data, 
																				db_recno_t		record_number );

RPbdb_DatabaseTypeRecnoSettingsController* RPbdb_DatabaseTypeRecnoSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseTypeRecnoSettingsController* database_type_recno_settings_controller );
void RPbdb_DatabaseTypeRecnoSettingsController_internal_setFlags(	RPbdb_DatabaseTypeRecnoSettingsController*		database_type_recno_settings_controller );

#endif

