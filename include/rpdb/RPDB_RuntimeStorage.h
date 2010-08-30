/*
 *		RPDB::RuntimeStorageController::RuntimeStorage
 *
 *
 */

#ifndef RPDB_RUNTIMESTORAGE
	#define RPDB_RUNTIMESTORAGE

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_RuntimeStorage*						RPDB_RuntimeStorage_new(	RPDB_RuntimeStorageController*		parent_runtime_storage_controller,
																			char*								runtime_storage_name );
	void										RPDB_RuntimeStorage_free(								RPDB_RuntimeStorage**						runtime_storage );
	RPDB_RuntimeStorageSettingsController*		RPDB_RuntimeStorage_settingsController(				RPDB_RuntimeStorage*						runtime_storage );
	RPDB_Environment*					RPDB_RuntimeStorage_parentEnvironment(		RPDB_RuntimeStorage*				runtime_storage );
	RPDB_RuntimeStorage*						RPDB_RuntimeStorage_internal_initStorageHashForName(			RPDB_RuntimeStorage*				runtime_storage,
																										char*								name );
	uint32_t									RPDB_RuntimeStorage_countRecords(						RPDB_RuntimeStorage*				runtime_storage );
	BOOL										RPDB_RuntimeStorage_keyExists(							RPDB_RuntimeStorage*				runtime_storage, 
																										RPDB_Key*							key );
BOOL RPDB_RuntimeStorage_rawKeyExists(	RPDB_RuntimeStorage*		runtime_storage, 
									   void*						raw_key,
									   uint32_t					key_size );
	RPDB_Record*								RPDB_RuntimeStorage_retrieveKey(				RPDB_RuntimeStorage*				runtime_storage, 
																										RPDB_Key*							key );
RPDB_Record* RPDB_RuntimeStorage_retrieveRawKey(	RPDB_RuntimeStorage*		runtime_storage, 
														   void*						key,
														   uint32_t					key_size );
	void										RPDB_RuntimeStorage_insertRecord(						RPDB_RuntimeStorage*				runtime_storage, 
																										RPDB_Record* 						record );
	void										RPDB_RuntimeStorage_insertKeyDataPair(					RPDB_RuntimeStorage*				runtime_storage, 
																										RPDB_Key*	 						key,
																										RPDB_Data*							data );
void RPDB_RuntimeStorage_insertRawKeyDataPair(	RPDB_RuntimeStorage*		runtime_storage, 
											   void* 						key,
											   uint32_t					key_size,
											   void* 						data,
											   uint32_t					data_size );
	void										RPDB_RuntimeStorage_deleteRecord(						RPDB_RuntimeStorage*				runtime_storage,
																										RPDB_Record*						record );
	void										RPDB_RuntimeStorage_deleteRecordForKey(				RPDB_RuntimeStorage*				runtime_storage,
																										RPDB_Key*							key );
	void RPDB_RuntimeStorage_deleteRecordForRawKey(	RPDB_RuntimeStorage*	runtime_storage,
													void*					key,
													uint32_t				key_size	);
	void										RPDB_RuntimeStorage_iterate(							RPDB_RuntimeStorage*				runtime_storage );
	RPDB_Record*								RPDB_RuntimeStorage_currentRecord(						RPDB_RuntimeStorage*				runtime_storage );
	RPDB_Record*								RPDB_RuntimeStorage_nextRecord(						RPDB_RuntimeStorage*				runtime_storage );
	RPDB_Record*								RPDB_RuntimeStorage_popCurrentData(					RPDB_RuntimeStorage*				runtime_storage );
	RPDB_RuntimeStorageSettingsController*		RPDB_RuntimeStorage_settingsController(				RPDB_RuntimeStorage*				runtime_storage );


#endif

