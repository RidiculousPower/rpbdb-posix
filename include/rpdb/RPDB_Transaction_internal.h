#ifndef RPDB_TRANSACTION_INTERNAL
	#define RPDB_TRANSACTION_INTERNAL

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

RPDB_Transaction* RPDB_Transaction_internal_newWithoutBDBTransaction( RPDB_TransactionController*						parent_transaction_controller );
DB_TXN*				RPDB_Transaction_internal_transactionID(					RPDB_Transaction*				transaction );
void				RPDB_Transaction_internal_initDefaultInstanceSettings(		RPDB_Transaction*				transaction );
void RPDB_Transaction_internal_addDatabaseToListOpenedDuringTransaction(	RPDB_Transaction*	transaction,
																		 RPDB_Database*		database	);
	
#endif