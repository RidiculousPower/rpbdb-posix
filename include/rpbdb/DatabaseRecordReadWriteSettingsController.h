/*
*		RPbdb::SettingsController::DatabaseSettingsController::DatabaseReadWriteSettingsController
*		RPbdb::DatabaseController::Database::DatabaseSettingsController::DatabaseReadWriteSettingsController
*
*/

#ifndef RPBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER
	#define RPBDB_DATABASE_READ_WRITE_SETTINGS_CONTROLLER

	#include "BaseStandardInclude.h"

	#include <cerialize.h>
	
	/****************
	*  Prototypes  *
	****************/

	RPbdb_DatabaseRecordReadWriteSettingsController*	RPbdb_DatabaseRecordReadWriteSettingsController_new(									RPbdb_DatabaseRecordSettingsController*						database_record_settings_controller );

	void										RPbdb_DatabaseRecordReadWriteSettingsController_free(									RPbdb_DatabaseRecordReadWriteSettingsController** database_record_read_write_settings_controller );
	RPbdb_Environment*					RPbdb_DatabaseRecordReadWriteSettingsController_parentEnvironment(	RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	RPbdb_Database* RPbdb_DatabaseRecordReadWriteSettingsController_parentDatabase(	RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );

	char*										RPbdb_DatabaseRecordReadWriteSettingsController_filename(								RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_setFilename(							RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller,
																																char*													filename	);
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_prohibitSyncOnClose(					RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOn(			RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitSyncOnCloseOff(			RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_ignoreLease(							RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOn(							RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnIgnoreLeaseOff(							RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_returnMultiple(						RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOn(					RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnMultipleOff(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_writeDataOnlyIfNonDuplicate(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOn(			RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteDataOnlyIfNonDuplicateOff(			RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL 										RPbdb_DatabaseRecordReadWriteSettingsController_prohibitOverwrite(					RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOn(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitOverwriteOff(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_prohibitPageCompaction(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOn(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnProhibitPageCompactionOff(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_returnPagesToFilesystem(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOn(		RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnReturnPagesToFilesystemOff(		RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_partialAccess(						RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn(						RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff(						RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL											RPbdb_DatabaseRecordReadWriteSettingsController_truncateFileOnOpen(					RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOn(				RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnTruncateFileOnOpenOff(			RPbdb_DatabaseRecordReadWriteSettingsController*				database_record_read_write_settings_controller );
	BOOL										RPbdb_DatabaseRecordReadWriteSettingsController_writeLocksInsteadOfReadLocks(			RPbdb_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOn(		RPbdb_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	void										RPbdb_DatabaseRecordReadWriteSettingsController_turnWriteLocksInsteadOfReadLocksOff(		RPbdb_DatabaseRecordReadWriteSettingsController*				database_write_retrieve_settings_controller );
	BOOL RPbdb_DatabaseRecordReadWriteSettingsController_unsortedDuplicates( RPbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnUnsortedDuplicatesOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	BOOL RPbdb_DatabaseRecordReadWriteSettingsController_sortedDuplicates( RPbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSortedDuplicatesOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_write_retrieve_settings_controller );
	BOOL RPbdb_DatabaseRecordReadWriteSettingsController_duplicates( RPbdb_DatabaseRecordReadWriteSettingsController* database_read_write_settings_controller );

BOOL RPbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingMalloc( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingMallocOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_databaseAllocatesMemoryUsingRealloc( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseAllocatesMemoryUsingReallocOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_applicationAllocatesMemory( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnApplicationAllocatesMemoryOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_databaseFreesMemory( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnDatabaseFreesMemoryOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_partialAccess( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnPartialAccessOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_syncPriorToWriteReturn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnSyncPriorToWriteReturnOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
uint32_t RPbdb_DatabaseRecordReadWriteSettingsController_dataBufferSize( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void RPbdb_DatabaseRecordReadWriteSettingsController_setDataBufferSize(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
													uint32_t							buffer_size );
uint32_t RPbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteSize( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void RPbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteSize(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
																																		uint32_t							partial_read_write_size );
uint32_t RPbdb_DatabaseRecordReadWriteSettingsController_partialReadWriteOffset( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
void RPbdb_DatabaseRecordReadWriteSettingsController_setPartialReadWriteOffset(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller, 
															uint32_t							partial_read_write_offset );

CerializeType RPbdb_DatabaseRecordReadWriteSettingsController_storeKeyTyping( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreKeyTypingOn(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller,
																																						CerializeType										database_record_storage_type	);
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreKeyTypingOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
CerializeType RPbdb_DatabaseRecordReadWriteSettingsController_storeDataTyping( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreDataTypingOn(	RPbdb_DatabaseRecordReadWriteSettingsController*		database_record_read_write_settings_controller,
																																							CerializeType										database_record_storage_type	);
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreDataTypingOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_recordTyping( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnRecordTypingOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnRecordTypingOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_creationStamp( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnCreationStampOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnCreationStampOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_modificationStamp( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnModificationStampOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnModificationStampOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
BOOL RPbdb_DatabaseRecordReadWriteSettingsController_storeFileNotPath( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOn( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
	void RPbdb_DatabaseRecordReadWriteSettingsController_turnStoreFileNotPathOff( RPbdb_DatabaseRecordReadWriteSettingsController* database_record_read_write_settings_controller );
			
	
#endif

