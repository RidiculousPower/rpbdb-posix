#ifndef Rbdb_DATABASE_SEQUENCE_SETTINGS_CONTROLLER_INTERNAL
	#define Rbdb_DATABASE_SEQUENCE_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

void	Rbdb_DatabaseSequenceSettingsController_internal_getFlags(				Rbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		Rbdb_DatabaseSequenceSettingsController_internal_closeFlags(			Rbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		Rbdb_DatabaseSequenceSettingsController_internal_stepByFlags(			Rbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		Rbdb_DatabaseSequenceSettingsController_internal_deleteFlags(			Rbdb_DatabaseSequenceSettingsController*		sequence_settings_controller );
int		Rbdb_DatabaseSequenceSettingsController_internal_createSequenceFlags(	Rbdb_DatabaseSequenceController*				database_sequence_controller );
int		Rbdb_DatabaseSequenceSettingsController_internal_openSequenceFlags(	Rbdb_DatabaseSequenceController*				database_sequence_controller );
Rbdb_DatabaseSequenceSettingsController* Rbdb_DatabaseSequenceSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_DatabaseSequenceSettingsController* database_sequence_settings_controller );

#endif

