/*
 *		RPDB::TransactionController::Transaction
 *
 *
 */

#ifndef RPDB_TRANSACTION_HEADER
	#define RPDB_TRANSACTION_HEADER

	#include "RPDB_BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPDB_Transaction*							RPDB_Transaction_new(								RPDB_TransactionController*			parent_transaction_controller );
	void										RPDB_Transaction_free(								RPDB_Transaction**						transaction );
	RPDB_TransactionSettingsController*		RPDB_Transaction_settingsController(				RPDB_Transaction*						transaction );
	RPDB_Environment*					RPDB_Transaction_parentEnvironment(	RPDB_Transaction*			transaction );
	void										RPDB_Transaction_free(								RPDB_Transaction**						transaction );
	BOOL RPDB_Transaction_isOpen( RPDB_Transaction* transaction );
	void RPDB_Transaction_closeAllDatabasesOpenedDuringTransaction( RPDB_Transaction* transaction );
	char*										RPDB_Transaction_name(					RPDB_Transaction*						transaction );
	void										RPDB_Transaction_setName(				RPDB_Transaction*						transaction,
	 																								char*									transaction_name );
	RPDB_Transaction* RPDB_Transaction_begin( RPDB_Transaction*		transaction );
	RPDB_Transaction* RPDB_Transaction_beginConcurrentDataStoreGroup( RPDB_Transaction* transaction );
	RPDB_Transaction*							RPDB_Transaction_prepare(				RPDB_Transaction*						transaction,
																									//	global_transaction_id is a DB_XIDDATASIZE (currently 128) length array of 8 bit ints
																									//	The array is used to identify distributed transactions, which may be relayed 
																									//	through multiple centralizing environment nodes to distributed environments.
	 																								u_int8_t								global_transaction_id[]	);
	void										RPDB_Transaction_rollback(				RPDB_Transaction*						transaction );
	void										RPDB_Transaction_commit(				RPDB_Transaction*						transaction );
	RPDB_Transaction* RPDB_Transaction_discardRecoveredResources( RPDB_Transaction* transaction );
	RPDB_TransactionSettingsController*		RPDB_Transaction_settingsController(				RPDB_Transaction*						transaction );

#endif

