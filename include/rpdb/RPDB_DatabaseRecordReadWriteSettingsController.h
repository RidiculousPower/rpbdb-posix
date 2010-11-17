/*
*		RPDB::SettingsController::DatabaseSettingsController::DatabaseReadWriteSettingsController
*		RPDB::DatabaseController::Database::DatabaseSettingsController::DatabaseReadWriteSettingsController
*
*/

#ifndef RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER
	#define RPDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_DatabaseRecordReadWriteSettingsController*	RPDB_DatabaseRecordReadWriteSettingsController_new(									RPDB_DatabaseRecordSettingsController*						database_record_settings_controller );

	void										RPDB_DatabaseRecordReadWriteSettingsController_free(									RPDB_DatabaseRecordReadWriteSettingsController** database_record_read_write_settings_controller );
	RPDB_Environment*					RPDB_DatabaseRecordReadWriteSettingsController_parentEnvironment(	RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	RPDB_Database* RPDB_DatabaseRecordReadWriteSettingsController_parentDatabase(	RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );

	char*										RPDB_DatabaseRecordReadWriteSettingsController_filename(								RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_setFilename(							RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller,
																																char*													filename	);
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_prohibitSyncOnClose(					RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOn(			RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOff(			RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_ignoreLease(							RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOn(							RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOff(							RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_returnMultiple(						RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOn(					RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOff(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_writeDataOnlyIfNonDuplicate(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOn(			RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff(			RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL 										RPDB_DatabaseRecordReadWriteSettingsController_prohibitOverwrite(					RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOn(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_prohibitPageCompaction(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOn(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOff(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_returnPagesToFilesystem(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOn(		RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOff(		RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_partialAccess(						RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn(						RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff(						RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPDB_DatabaseRecordReadWriteSettingsController_truncateFileOnOpen(					RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOn(				RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOff(			RPDB_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL										RPDB_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks(			RPDB_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn(		RPDB_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										RPDB_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff(		RPDB_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	BOOL RPDB_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( RPDB_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn( RPDB_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff( RPDB_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	BOOL RPDB_DatabaseRecordReadWriteSettingsController_sortedDuplicates( RPDB_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn( RPDB_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff( RPDB_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );

BOOL RPDB_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPDB_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPDB_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPDB_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPDB_DatabaseRecordReadWriteSettingsController_partialAccess( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPDB_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOn( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPDB_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOff( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
uint32_t RPDB_DatabaseRecordReadWriteSettingsController_dataBufferSize( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void RPDB_DatabaseRecordReadWriteSettingsController_setDataBufferSize(	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
													uint32_t							buffer_size );
uint32_t RPDB_DatabaseRecordReadWriteSettingsController_partialReadWriteSize( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void RPDB_DatabaseRecordReadWriteSettingsController_setPartialReadWriteSize(	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
																																		uint32_t							partial_read_write_size );
uint32_t RPDB_DatabaseRecordReadWriteSettingsController_partialReadWriteOffset( RPDB_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void RPDB_DatabaseRecordReadWriteSettingsController_setPartialReadWriteOffset(	RPDB_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
															uint32_t							partial_read_write_offset );
		
	
#endif

