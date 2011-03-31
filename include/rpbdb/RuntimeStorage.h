/*
 *		RPbdb::RuntimeStorageController::RuntimeStorage
 *
 *
 */

#ifndef RPBDB_RUNTIMESTORAGE
	#define RPBDB_RUNTIMESTORAGE

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_RuntimeStorage*						RPbdb_RuntimeStorage_new(	RPbdb_RuntimeStorageController*		parent_runtime_storage_controller,
																			char*								runtime_storage_name );
	void										RPbdb_RuntimeStorage_free(								RPbdb_RuntimeStorage**						runtime_storage );
	RPbdb_RuntimeStorageSettingsController*		RPbdb_RuntimeStorage_settingsController(				RPbdb_RuntimeStorage*						runtime_storage );
	RPbdb_Environment*					RPbdb_RuntimeStorage_parentEnvironment(		RPbdb_RuntimeStorage*				runtime_storage );
	uint32_t									RPbdb_RuntimeStorage_countRecords(						RPbdb_RuntimeStorage*				runtime_storage );
	BOOL										RPbdb_RuntimeStorage_keyExists(							RPbdb_RuntimeStorage*				runtime_storage, 
																										RPbdb_Key*							key );
BOOL RPbdb_RuntimeStorage_rawKeyExists(	RPbdb_RuntimeStorage*		runtime_storage, 
									   void*						raw_key,
									   uint32_t					key_size );
	RPbdb_Record*								RPbdb_RuntimeStorage_retrieveKey(				RPbdb_RuntimeStorage*				runtime_storage, 
																										RPbdb_Key*							key );
RPbdb_Record* RPbdb_RuntimeStorage_retrieveRawKey(	RPbdb_RuntimeStorage*		runtime_storage, 
														   void*						key,
														   uint32_t					key_size );
	void										RPbdb_RuntimeStorage_insertRecord(						RPbdb_RuntimeStorage*				runtime_storage, 
																										RPbdb_Record* 						record );
	void										RPbdb_RuntimeStorage_insertKeyDataPair(					RPbdb_RuntimeStorage*				runtime_storage, 
																										RPbdb_Key*	 						key,
																										RPbdb_Data*							data );
void RPbdb_RuntimeStorage_insertRawKeyDataPair(	RPbdb_RuntimeStorage*		runtime_storage, 
											   void* 						key,
											   uint32_t					key_size,
											   void* 						data,
											   uint32_t					data_size );
	void										RPbdb_RuntimeStorage_deleteRecord(						RPbdb_RuntimeStorage*				runtime_storage,
																										RPbdb_Record*						record );
	void										RPbdb_RuntimeStorage_deleteRecordForKey(				RPbdb_RuntimeStorage*				runtime_storage,
																										RPbdb_Key*							key );
	void RPbdb_RuntimeStorage_deleteRecordForRawKey(	RPbdb_RuntimeStorage*	runtime_storage,
													void*					key,
													uint32_t				key_size	);
	void										RPbdb_RuntimeStorage_iterate(							RPbdb_RuntimeStorage*				runtime_storage );
	RPbdb_Record*								RPbdb_RuntimeStorage_currentRecord(						RPbdb_RuntimeStorage*				runtime_storage );
	RPbdb_Record*								RPbdb_RuntimeStorage_nextRecord(						RPbdb_RuntimeStorage*				runtime_storage );
	RPbdb_Record*								RPbdb_RuntimeStorage_popCurrentData(					RPbdb_RuntimeStorage*				runtime_storage );
	RPbdb_RuntimeStorageSettingsController*		RPbdb_RuntimeStorage_settingsController(				RPbdb_RuntimeStorage*				runtime_storage );


#endif

