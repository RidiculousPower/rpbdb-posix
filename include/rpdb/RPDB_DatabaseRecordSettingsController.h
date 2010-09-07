/*
 *		RPDB_settingsController:RPDB_DatabaseRecordSettingsController
 *
 *
 */

#ifndef RPDB_RECORDSETTINGS_CONTROLLER
	#define RPDB_RECORDSETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseRecordSettingsController*	RPDB_DatabaseRecordSettingsController_new(										RPDB_DatabaseSettingsController* database_settings_controller );
	void							RPDB_DatabaseRecordSettingsController_free(									RPDB_DatabaseRecordSettingsController** record_settings_controller );
	RPDB_Environment*		RPDB_DatabaseRecordSettingsController_parentEnvironment(			RPDB_DatabaseRecordSettingsController* record_settings_controller );
	RPDB_Database* RPDB_DatabaseRecordSettingsController_parentDatabase(	RPDB_DatabaseRecordSettingsController* record_settings_controller );

	BOOL		RPDB_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingMalloc(			RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn(	RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff(	RPDB_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		RPDB_DatabaseRecordSettingsController_databaseAllocatesMemoryUsingRealloc(		RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn(		RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn(	RPDB_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		RPDB_DatabaseRecordSettingsController_applicationAllocatesMemory(					RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOn(			RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnApplicationAllocatesMemoryOff(			RPDB_DatabaseRecordSettingsController*		record_settings_controller );

	BOOL		RPDB_DatabaseRecordSettingsController_databaseFreesMemory(						RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOn(					RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	void		RPDB_DatabaseRecordSettingsController_turnDatabaseFreesMemoryOff(					RPDB_DatabaseRecordSettingsController*		record_settings_controller );


	RPDB_DatabaseRecordFixedLengthSettingsController* RPDB_DatabaseRecordSettingsController_fixedLengthSettingsController( RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	RPDB_DatabaseRecordVariableLengthSettingsController* RPDB_DatabaseRecordSettingsController_variableLengthSettingsController( RPDB_DatabaseRecordSettingsController*		record_settings_controller );
	RPDB_DatabaseRecordReadWriteSettingsController*		RPDB_DatabaseRecordSettingsController_readWriteSettingsController( RPDB_DatabaseRecordSettingsController*		record_settings_controller );

#endif

