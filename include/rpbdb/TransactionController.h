/*
 *		RPbdb::TransactionController
 *
 *
 */

#ifndef RPBDB_TRANSACTION_CONTROLLER
	#define RPBDB_TRANSACTION_CONTROLLER

	#include "BaseStandardInclude.h"
	
	/****************
	*  Prototypes  *
	****************/

RPbdb_TransactionController*			RPbdb_TransactionController_new(													RPbdb_Environment*				environment );
void									RPbdb_TransactionController_free(													RPbdb_TransactionController**		transaction_controller );
RPbdb_TransactionSettingsController*	RPbdb_TransactionController_settingsController(										RPbdb_TransactionController*		transaction_controller );
RPbdb_Environment*				RPbdb_TransactionController_parentEnvironment(						RPbdb_TransactionController*	transaction_controller );
RPbdb_Transaction*						RPbdb_TransactionController_beginTransaction(													RPbdb_TransactionController*	transaction_controller );
RPbdb_Transaction*						RPbdb_TransactionController_beginConcurrentDataStoreGroup(								RPbdb_TransactionController*	transaction_controller );
void RPbdb_TransactionController_commitTransaction( RPbdb_TransactionController* transaction_controller );
void RPbdb_TransactionController_commitAllTransactions( RPbdb_TransactionController* transaction_controller );
void RPbdb_TransactionController_rollbackTransaction( RPbdb_TransactionController* transaction_controller );
	RPbdb_Transaction*						RPbdb_TransactionController_currentTransaction(										RPbdb_TransactionController*	transaction_controller );
RPbdb_Transaction**						RPbdb_TransactionController_recoverTransactions(									RPbdb_TransactionController*	transaction_controller );
void RPbdb_TransactionController_commitCheckpoint( RPbdb_TransactionController*	transaction_controller );
void RPbdb_TransactionController_commitCheckpointIfSufficientWrittenData(	RPbdb_TransactionController*	transaction_controller,
																		 uint32_t						minimum_written_data_for_checkpoint_in_k );
void RPbdb_TransactionController_commitCheckpointIfSufficientTimeElapsed(	RPbdb_TransactionController*	transaction_controller,
																		 uint32_t						minimum_time_for_checkpoint_in_minutes );
void RPbdb_TransactionController_commitCheckpointIfSufficientWrittenDataOrTimeElapsed(	RPbdb_TransactionController*	transaction_controller,
																					  uint32_t						minimum_written_data_for_checkpoint_in_k,
																					  uint32_t						minimum_time_for_checkpoint_in_minutes );
	
void RPbdb_TransactionController_closeAllTransactions( RPbdb_TransactionController* transaction_controller );
void RPbdb_TransactionController_freeAllTransactions( RPbdb_TransactionController* transaction_controller );
	

#endif

