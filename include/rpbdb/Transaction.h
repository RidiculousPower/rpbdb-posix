/*
 *		RPbdb::TransactionController::Transaction
 *
 *
 */

#ifndef RPBDB_TRANSACTION_HEADER
	#define RPBDB_TRANSACTION_HEADER

	#include "BaseStandardInclude.h"

	/****************
	*  Prototypes  *
	****************/

	RPbdb_Transaction*							RPbdb_Transaction_new(								RPbdb_TransactionController*			parent_transaction_controller );
	void										RPbdb_Transaction_free(								RPbdb_Transaction**						transaction );
	RPbdb_TransactionSettingsController*		RPbdb_Transaction_settingsController(				RPbdb_Transaction*						transaction );
	RPbdb_Environment*					RPbdb_Transaction_parentEnvironment(	RPbdb_Transaction*			transaction );
	void										RPbdb_Transaction_free(								RPbdb_Transaction**						transaction );
	BOOL RPbdb_Transaction_isOpen( RPbdb_Transaction* transaction );
	void RPbdb_Transaction_closeAllDatabasesOpenedDuringTransaction( RPbdb_Transaction* transaction );
	char*										RPbdb_Transaction_name(					RPbdb_Transaction*						transaction );
	void										RPbdb_Transaction_setName(				RPbdb_Transaction*						transaction,
	 																								char*									transaction_name );
	RPbdb_Transaction* RPbdb_Transaction_begin( RPbdb_Transaction*		transaction );
	RPbdb_Transaction* RPbdb_Transaction_beginConcurrentDataStoreGroup( RPbdb_Transaction* transaction );
	RPbdb_Transaction*							RPbdb_Transaction_prepare(				RPbdb_Transaction*						transaction,
																									//	global_transaction_id is a DB_XIDDATASIZE (currently 128) length array of 8 bit ints
																									//	The array is used to identify distributed transactions, which may be relayed 
																									//	through multiple centralizing environment nodes to distributed environments.
	 																								u_int8_t								global_transaction_id[]	);
	void										RPbdb_Transaction_rollback(				RPbdb_Transaction*						transaction );
	void										RPbdb_Transaction_commit(				RPbdb_Transaction*						transaction );
	RPbdb_Transaction* RPbdb_Transaction_discardRecoveredResources( RPbdb_Transaction* transaction );
	RPbdb_TransactionSettingsController*		RPbdb_Transaction_settingsController(				RPbdb_Transaction*						transaction );

#endif

