/*
 *		Rbdb_settingsController:Rbdb_DatabaseRecordSettingsController
 *
 *
 */

#ifndef Rbdb_RECORDSETTINGS_CONTROLLER
	#define Rbdb_RECORDSETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseRecordSettingsController*	Rbdb_DatabaseRecordSettingsController_new(										Rbdb_DatabaseSettingsController* database_settings_controller );
	void							Rbdb_DatabaseRecordSettingsController_free(									Rbdb_DatabaseRecordSettingsController** record_settings_controller );
	Rbdb_Environment*		Rbdb_DatabaseRecordSettingsController_parentEnvironment(			Rbdb_DatabaseRecordSettingsController* record_settings_controller );
	Rbdb_Database* Rbdb_DatabaseRecordSettingsController_parentDatabase(	Rbdb_DatabaseRecordSettingsController* record_settings_controller );

	BOOL		Rbdb_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingMalloc(			Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn(	Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff(	Rbdb_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		Rbdb_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingRealloc(		Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn(		Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn(	Rbdb_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		Rbdb_DatabaseRecordSettingsController_applicationAllocatesMemory(					Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOn(			Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOff(			Rbdb_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		Rbdb_DatabaseRecordSettingsController_databaseFreesMemory(						Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOn(					Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		Rbdb_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOff(					Rbdb_DatabaseRecordSettingsController*		record_settings_controller );


	Rbdb_DatabaseRecordFixedLengthSettingsController* Rbdb_DatabaseRecordSettingsController_fixedLengthSettingsController( Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	Rbdb_DatabaseRecordVariableLengthSettingsController* Rbdb_DatabaseRecordSettingsController_variableLengthSettingsController( Rbdb_DatabaseRecordSettingsController*		record_settings_controller );
	Rbdb_DatabaseRecordReadWriteSettingsController*		Rbdb_DatabaseRecordSettingsController_readWriteSettingsController( Rbdb_DatabaseRecordSettingsController*		record_settings_controller );

#endif

