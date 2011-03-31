/*
 *		RPbdb_settingsController:RPbdb_DatabaseRecordSettingsController
 *
 *
 */

#ifndef RPBDB_RECORDSETTINGS_CONTROLLER
	#define RPBDB_RECORDSETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseRecordSettingsController*	RPbdb_DatabaseRecordSettingsController_new(										RPbdb_DatabaseSettingsController* database_settings_controller );
	void							RPbdb_DatabaseRecordSettingsController_free(									RPbdb_DatabaseRecordSettingsController** record_settings_controller );
	RPbdb_Environment*		RPbdb_DatabaseRecordSettingsController_parentEnvironment(			RPbdb_DatabaseRecordSettingsController* record_settings_controller );
	RPbdb_Database* RPbdb_DatabaseRecordSettingsController_parentDatabase(	RPbdb_DatabaseRecordSettingsController* record_settings_controller );

	BOOL		RPbdb_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingMalloc(			RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn(	RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff(	RPbdb_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		RPbdb_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingRealloc(		RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn(		RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn(	RPbdb_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		RPbdb_DatabaseRecordSettingsController_applicationAllocatesMemory(					RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOn(			RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOff(			RPbdb_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		RPbdb_DatabaseRecordSettingsController_databaseFreesMemory(						RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOn(					RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPbdb_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOff(					RPbdb_DatabaseRecordSettingsController*		record_settings_controller );


	RPbdb_DatabaseRecordFixedLengthSettingsController* RPbdb_DatabaseRecordSettingsController_fixedLengthSettingsController( RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	RPbdb_DatabaseRecordVariableLengthSettingsController* RPbdb_DatabaseRecordSettingsController_variableLengthSettingsController( RPbdb_DatabaseRecordSettingsController*		record_settings_controller );
	RPbdb_DatabaseRecordReadWriteSettingsController*		RPbdb_DatabaseRecordSettingsController_readWriteSettingsController( RPbdb_DatabaseRecordSettingsController*		record_settings_controller );

#endif

