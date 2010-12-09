/*
 *		Rbdb::TransactionController
 *
 *
 */

#ifndef Rbdb_TRANSACTION_CONTROLLER
	#define Rbdb_TRANSACTION_CONTROLLER

	#include "Rbdb_BaseStandardInclude.h"
	
	/****************
	*  Prototypes  *
	****************/

Rbdb_TransactionController*			Rbdb_TransactionController_new(													Rbdb_Environment*				environment );
void									Rbdb_TransactionController_free(													Rbdb_TransactionController**		transaction_controller );
Rbdb_TransactionSettingsController*	Rbdb_TransactionController_settingsController(										Rbdb_TransactionController*		transaction_controller );
Rbdb_Environment*				Rbdb_TransactionController_parentEnvironment(						Rbdb_TransactionController*	transaction_controller );
Rbdb_Transaction*						Rbdb_TransactionController_beginTransaction(													Rbdb_TransactionController*	transaction_controller );
Rbdb_Transaction*						Rbdb_TransactionController_beginConcurrentDataStoreGroup(								Rbdb_TransactionController*	transaction_controller );
void Rbdb_TransactionController_commitTransaction( Rbdb_TransactionController* transaction_controller );
void Rbdb_TransactionController_commitAllTransactions( Rbdb_TransactionController* transaction_controller );
void Rbdb_TransactionController_rollbackTransaction( Rbdb_TransactionController* transaction_controller );
	Rbdb_Transaction*						Rbdb_TransactionController_currentTransaction(										Rbdb_TransactionController*	transaction_controller );
Rbdb_Transaction**						Rbdb_TransactionController_recoverTransactions(									Rbdb_TransactionController*	transaction_controller );
void Rbdb_TransactionController_commitCheckpoint( Rbdb_TransactionController*	transaction_controller );
void Rbdb_TransactionController_commitCheckpointIfSufficientWrittenData(	Rbdb_TransactionController*	transaction_controller,
																		 uint32_t						minimum_written_data_for_checkpoint_in_k );
void Rbdb_TransactionController_commitCheckpointIfSufficientTimeElapsed(	Rbdb_TransactionController*	transaction_controller,
																		 uint32_t						minimum_time_for_checkpoint_in_minutes );
void Rbdb_TransactionController_commitCheckpointIfSufficientWrittenDataOrTimeElapsed(	Rbdb_TransactionController*	transaction_controller,
																					  uint32_t						minimum_written_data_for_checkpoint_in_k,
																					  uint32_t						minimum_time_for_checkpoint_in_minutes );
	
void Rbdb_TransactionController_closeAllTransactions( Rbdb_TransactionController* transaction_controller );
void Rbdb_TransactionController_freeAllTransactions( Rbdb_TransactionController* transaction_controller );
	

#endif

