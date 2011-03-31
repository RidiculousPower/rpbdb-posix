#ifndef RPBDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER_INTERNAL
	#define RPBDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void	RPbdb_DatabaseSequenceSettingsController_internal_getFlags(				RPbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		RPbdb_DatabaseSequenceSettingsController_internal_closeFlags(			RPbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		RPbdb_DatabaseSequenceSettingsController_internal_stepByFlags(			RPbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		RPbdb_DatabaseSequenceSettingsController_internal_deleteFlags(			RPbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int RPbdb_DatabaseSequenceSettingsController_internal_createSequenceFlags( RPbdb_DatabaseSequenceSettingsController* sequence_settings_controller __attribute__((unused)) );
int		RPbdb_DatabaseSequenceSettingsController_internal_openSequenceFlags(	RPbdb_DatabaseSequenceController*				database_sequence_controller );
RPbdb_DatabaseSequenceSettingsController* RPbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller );

#endif

