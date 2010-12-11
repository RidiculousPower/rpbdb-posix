#ifndef RBDB_TRANSACTION_INTERNAL
	#define RBDB_TRANSACTION_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

Rbdb_Transaction* Rbdb_Transaction_internal_newWithoutBDBTransaction( Rbdb_TransactionController*						parent_transaction_controller );
DB_TXN*				Rbdb_Transaction_internal_transactionID(					Rbdb_Transaction*				transaction );
void				Rbdb_Transaction_internal_initDefaultInstanceSettings(		Rbdb_Transaction*				transaction );
void Rbdb_Transaction_internal_addDatabaseToListOpenedDuringTransaction(	Rbdb_Transaction*	transaction,
																		 Rbdb_Database*		database	);

void Rbdb_Transaction_internal_freeFromRuntimeStorage( Rbdb_Transaction** transaction );

#endif