/*
 *		Rbdb::RuntimeStorageController::RuntimeStorage
 *
 *
 */

#ifndef Rbdb_RUNTIMESTORAGE
	#define Rbdb_RUNTIMESTORAGE

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_RuntimeStorage*						Rbdb_RuntimeStorage_new(	Rbdb_RuntimeStorageController*		parent_runtime_storage_controller,
																			char*								runtime_storage_name );
	void										Rbdb_RuntimeStorage_free(								Rbdb_RuntimeStorage**						runtime_storage );
	Rbdb_RuntimeStorageSettingsController*		Rbdb_RuntimeStorage_settingsController(				Rbdb_RuntimeStorage*						runtime_storage );
	Rbdb_Environment*					Rbdb_RuntimeStorage_parentEnvironment(		Rbdb_RuntimeStorage*				runtime_storage );
	uint32_t									Rbdb_RuntimeStorage_countRecords(						Rbdb_RuntimeStorage*				runtime_storage );
	BOOL										Rbdb_RuntimeStorage_keyExists(							Rbdb_RuntimeStorage*				runtime_storage, 
																										Rbdb_Key*							key );
BOOL Rbdb_RuntimeStorage_rawKeyExists(	Rbdb_RuntimeStorage*		runtime_storage, 
									   void*						raw_key,
									   uint32_t					key_size );
	Rbdb_Record*								Rbdb_RuntimeStorage_retrieveKey(				Rbdb_RuntimeStorage*				runtime_storage, 
																										Rbdb_Key*							key );
Rbdb_Record* Rbdb_RuntimeStorage_retrieveRawKey(	Rbdb_RuntimeStorage*		runtime_storage, 
														   void*						key,
														   uint32_t					key_size );
	void										Rbdb_RuntimeStorage_insertRecord(						Rbdb_RuntimeStorage*				runtime_storage, 
																										Rbdb_Record* 						record );
	void										Rbdb_RuntimeStorage_insertKeyDataPair(					Rbdb_RuntimeStorage*				runtime_storage, 
																										Rbdb_Key*	 						key,
																										Rbdb_Data*							data );
void Rbdb_RuntimeStorage_insertRawKeyDataPair(	Rbdb_RuntimeStorage*		runtime_storage, 
											   void* 						key,
											   uint32_t					key_size,
											   void* 						data,
											   uint32_t					data_size );
	void										Rbdb_RuntimeStorage_deleteRecord(						Rbdb_RuntimeStorage*				runtime_storage,
																										Rbdb_Record*						record );
	void										Rbdb_RuntimeStorage_deleteRecordForKey(				Rbdb_RuntimeStorage*				runtime_storage,
																										Rbdb_Key*							key );
	void Rbdb_RuntimeStorage_deleteRecordForRawKey(	Rbdb_RuntimeStorage*	runtime_storage,
													void*					key,
													uint32_t				key_size	);
	void										Rbdb_RuntimeStorage_iterate(							Rbdb_RuntimeStorage*				runtime_storage );
	Rbdb_Record*								Rbdb_RuntimeStorage_currentRecord(						Rbdb_RuntimeStorage*				runtime_storage );
	Rbdb_Record*								Rbdb_RuntimeStorage_nextRecord(						Rbdb_RuntimeStorage*				runtime_storage );
	Rbdb_Record*								Rbdb_RuntimeStorage_popCurrentData(					Rbdb_RuntimeStorage*				runtime_storage );
	Rbdb_RuntimeStorageSettingsController*		Rbdb_RuntimeStorage_settingsController(				Rbdb_RuntimeStorage*				runtime_storage );


#endif

