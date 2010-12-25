/*
*		Rbdb::SettingsController::DatabaseSettingsController::DatabaseReadWriteSettingsController
*		Rbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseReadWriteSettingsController
*
*/

#ifndef RBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER
	#define RBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_DatabaseRecordReadWriteSettingsController*	Rbdb_DatabaseRecordReadWriteSettingsController_new(									Rbdb_DatabaseRecordSettingsController*						database_record_settings_controller );

	void										Rbdb_DatabaseRecordReadWriteSettingsController_free(									Rbdb_DatabaseRecordReadWriteSettingsController** database_record_read_write_settings_controller );
	Rbdb_Environment*					Rbdb_DatabaseRecordReadWriteSettingsController_parentEnvironment(	Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	Rbdb_Database* Rbdb_DatabaseRecordReadWriteSettingsController_parentDatabase(	Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );

	char*										Rbdb_DatabaseRecordReadWriteSettingsController_filename(								Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_setFilename(							Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller,
																																char*													filename	);
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_prohibitSyncOnClose(					Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOn(			Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOff(			Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_ignoreLease(							Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOn(							Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOff(							Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_returnMultiple(						Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOn(					Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOff(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_writeDataOnlyIfNonDuplicate(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOn(			Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff(			Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL 										Rbdb_DatabaseRecordReadWriteSettingsController_prohibitOverwrite(					Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOn(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_prohibitPageCompaction(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOn(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOff(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_returnPagesToFilesystem(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOn(		Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOff(		Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_partialAccess(						Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn(						Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff(						Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											Rbdb_DatabaseRecordReadWriteSettingsController_truncateFileOnOpen(					Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOn(				Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOff(			Rbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL										Rbdb_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks(			Rbdb_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn(		Rbdb_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										Rbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff(		Rbdb_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	BOOL Rbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( Rbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	BOOL Rbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( Rbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	BOOL Rbdb_DatabaseRecordReadWriteSettingsController_duplicates( Rbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller );

BOOL Rbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_partialAccess( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
uint32_t Rbdb_DatabaseRecordReadWriteSettingsController_dataBufferSize( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void Rbdb_DatabaseRecordReadWriteSettingsController_setDataBufferSize(	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
													uint32_t							buffer_size );
uint32_t Rbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteSize( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void Rbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteSize(	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
																																		uint32_t							partial_read_write_size );
uint32_t Rbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteOffset( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void Rbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteOffset(	Rbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
															uint32_t							partial_read_write_offset );

BOOL Rbdb_DatabaseRecordReadWriteSettingsController_storeTyping( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnStoreTypingOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnStoreTypingOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_recordTyping( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnRecordTypingOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnRecordTypingOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_creationStamp( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnCreationStampOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnCreationStampOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL Rbdb_DatabaseRecordReadWriteSettingsController_modificationStamp( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnModificationStampOn( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void Rbdb_DatabaseRecordReadWriteSettingsController_turnModificationStampOff( Rbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
			
	
#endif

