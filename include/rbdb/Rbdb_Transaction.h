/*
 *		Rbdb::TransactionController::Transaction
 *
 *
 */

#ifndef RBDB_TRANSACTION_HEADER
	#define RBDB_TRANSACTION_HEADER

	#include "Rbdb_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	Rbdb_Transaction*							Rbdb_Transaction_new(								Rbdb_TransactionController*			parent_transaction_controller );
	void										Rbdb_Transaction_free(								Rbdb_Transaction**						transaction );
	Rbdb_TransactionSettingsController*		Rbdb_Transaction_settingsController(				Rbdb_Transaction*						transaction );
	Rbdb_Environment*					Rbdb_Transaction_parentEnvironment(	Rbdb_Transaction*			transaction );
	void										Rbdb_Transaction_free(								Rbdb_Transaction**						transaction );
	BOOL Rbdb_Transaction_isOpen( Rbdb_Transaction* transaction );
	void Rbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( Rbdb_Transaction* transaction );
	char*										Rbdb_Transaction_name(					Rbdb_Transaction*						transaction );
	void										Rbdb_Transaction_setName(				Rbdb_Transaction*						transaction,
	 																								char*									transaction_name );
	Rbdb_Transaction* Rbdb_Transaction_begin( Rbdb_Transaction*		transaction );
	Rbdb_Transaction* Rbdb_Transaction_beginConcurrentDataStoreGroup( Rbdb_Transaction* transaction );
	Rbdb_Transaction*							Rbdb_Transaction_prepare(				Rbdb_Transaction*						transaction,
																									//	global_transaction_id is a DB_XIDDATASIZE (currently 128) length array of 8 bit ints
																									//	The array is used to identify distributed transactions, which may be relayed 
																									//	through multiple centralizing environment nodes to distributed environments.
	 																								u_int8_t								global_transaction_id[]	);
	void										Rbdb_Transaction_rollback(				Rbdb_Transaction*						transaction );
	void										Rbdb_Transaction_commit(				Rbdb_Transaction*						transaction );
	Rbdb_Transaction* Rbdb_Transaction_discardRecoveredResources( Rbdb_Transaction* transaction );
	Rbdb_TransactionSettingsController*		Rbdb_Transaction_settingsController(				Rbdb_Transaction*						transaction );

#endif

