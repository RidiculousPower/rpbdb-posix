#ifndef RPBDB_TRANSACTION_INTERNAL
	#define RPBDB_TRANSACTION_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPbdb_Transaction* RPbdb_Transaction_internal_newWithoutBDBTransaction( RPbdb_TransactionController*						parent_transaction_controller );
DB_TXN*				RPbdb_Transaction_internal_transactionID(					RPbdb_Transaction*				transaction );
void				RPbdb_Transaction_internal_initDefaultInstanceSettings(		RPbdb_Transaction*				transaction );
void RPbdb_Transaction_internal_addDatabaseToListOpenedDuringTransaction(	RPbdb_Transaction*	transaction,
																		 RPbdb_Database*		database	);

void RPbdb_Transaction_internal_freeFromRuntimeStorage( RPbdb_Transaction** transaction );

#endif