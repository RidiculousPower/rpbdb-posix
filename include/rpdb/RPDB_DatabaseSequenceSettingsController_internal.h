#ifndef RPDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_DATABASE_SEQUENCE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void	RPDB_DatabaseSequenceSettingsController_internal_getFlags(				RPDB_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		RPDB_DatabaseSequenceSettingsController_internal_closeFlags(			RPDB_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		RPDB_DatabaseSequenceSettingsController_internal_stepByFlags(			RPDB_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		RPDB_DatabaseSequenceSettingsController_internal_deleteFlags(			RPDB_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		RPDB_DatabaseSequenceSettingsController_internal_createSequenceFlags(	RPDB_DatabaseSequenceController*				database_sequence_controller );
int		RPDB_DatabaseSequenceSettingsController_internal_openSequenceFlags(	RPDB_DatabaseSequenceController*				database_sequence_controller );
RPDB_DatabaseSequenceSettingsController* RPDB_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DatabaseSequenceSettingsController* database_sequence_settings_controller );

#endif

