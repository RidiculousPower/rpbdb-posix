/*
 *		RPDB::TransactionController
 *
 *
 */

#ifndef RPDB_TRANSACTION_CONTROLLER
	#define RPDB_TRANSACTION_CONTROLLER

	#include "RPDB_BaseStandardInclude.h"
	
	/****************
	*  Prototypes  *
	****************/

RPDB_TransactionController*			RPDB_TransactionController_new(													RPDB_Environment*				environment );
void									RPDB_TransactionController_free(													RPDB_TransactionController**		transaction_controller );
RPDB_TransactionSettingsController*	RPDB_TransactionController_settingsController(										RPDB_TransactionController*		transaction_controller );
RPDB_Environment*				RPDB_TransactionController_parentEnvironment(						RPDB_TransactionController*	transaction_controller );
RPDB_Transaction*						RPDB_TransactionController_beginTransaction(													RPDB_TransactionController*	transaction_controller );
RPDB_Transaction*						RPDB_TransactionController_beginConcurrentDataStoreGroup(								RPDB_TransactionController*	transaction_controller );
void RPDB_TransactionController_commitTransaction( RPDB_TransactionController* transaction_controller );
void RPDB_TransactionController_commitAllTransactions( RPDB_TransactionController* transaction_controller );
void RPDB_TransactionController_rollbackTransaction( RPDB_TransactionController* transaction_controller );
	RPDB_Transaction*						RPDB_TransactionController_currentTransaction(										RPDB_TransactionController*	transaction_controller );
RPDB_Transaction**						RPDB_TransactionController_recoverTransactions(									RPDB_TransactionController*	transaction_controller );
void RPDB_TransactionController_commitCheckpoint( RPDB_TransactionController*	transaction_controller );
void RPDB_TransactionController_commitCheckpointIfSufficientWrittenData(	RPDB_TransactionController*	transaction_controller,
																		 uint32_t						minimum_written_data_for_checkpoint_in_k );
void RPDB_TransactionController_commitCheckpointIfSufficientTimeElapsed(	RPDB_TransactionController*	transaction_controller,
																		 uint32_t						minimum_time_for_checkpoint_in_minutes );
void RPDB_TransactionController_commitCheckpointIfSufficientWrittenDataOrTimeElapsed(	RPDB_TransactionController*	transaction_controller,
																					  uint32_t						minimum_written_data_for_checkpoint_in_k,
																					  uint32_t						minimum_time_for_checkpoint_in_minutes );
	
void RPDB_TransactionController_closeAllTransactions( RPDB_TransactionController* transaction_controller );
void RPDB_TransactionController_freeAllTransactions( RPDB_TransactionController* transaction_controller );
	

#endif

