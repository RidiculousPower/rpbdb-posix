/*
- (true_or_false) open                                          		
- (true_or_false) closed                                        		
- (statistics) statistics												//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_stat.html
- (true_or_false) hasError                                      		
- (error) error                                                 		
*/

	#include "RPBDB_TransactionStatistics.h"
	#include "RPBDB_Error.h"
	#include "RPBDB_StatusTransactionController.h"
	#include "RPBDB_Transaction.h"

RPBDB_TransactionStatusController* RPBDB_TransactionStatusController_new()	{
	
	RPBDB_TransactionStatusController*		transaction_status_controller = calloc( 1, sizeof( RPBDB_TransactionStatusController ) );

	//	Not much that we have to do here - controllers will be lazy-loaded
	return transaction_status_controller;
}

int RPBDB_TransactionStatusController_open( RPBDB_TransactionStatusController* transaction_status_controller )	{
	
}

int RPBDB_TransactionStatusController_closed( RPBDB_TransactionStatusController* transaction_status_controller )	{
	
}

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/txn_stat.html
RPBDB_TransactionStatistics* RPBDB_TransactionStatusController_statistics( RPBDB_TransactionStatusController* transaction_status_controller )	{
	
}

BOOL RPBDB_TransactionStatusController_hasError( RPBDB_TransactionStatusController* transaction_status_controller )	{
	
}

RPBDB_Error* RPBDB_TransactionStatusController_error( RPBDB_TransactionStatusController* transaction_status_controller )	{
	
}


/*
* (transactions_array) all (implied)
- (transactions_array) active
- (transactions_array) inactive
*/

RPBDB_StatusTransactionController* RPBDB_StatusTransactionController_new()	{
	
	RPBDB_StatusTransactionController*		status_transaction_controller = calloc( 1, sizeof( RPBDB_StatusTransactionController ) );

	//	Not much that we have to do here - controllers will be lazy-loaded
	return status_transaction_controller;
}

RPBDB_Transaction* RPBDB_StatusTransactionController_all( RPBDB *self )	{
	
}

RPBDB_Transaction* RPBDB_StatusTransactionController_active( RPBDB *self )	{
	
}

RPBDB_Transaction* RPBDB_StatusTransactionController_inactive( RPBDB *self )	{
	
}	


	#include "RPBDB_StatusTransactionController.h"
	#include "RPBDB_TransactionStatistics.h"
	#include "RPBDB_Error.h"
	#include "RPBDB_Transaction.h"


/***************************
*			free			*
***************************/
void RPBDB_TransactionStatusController_free(	RPBDB_TransactionStatusController* transaction_status_controller )	{

/***************************
*	settingsController	*
***************************/
RPBDB_TransactionStatusSettingsController* RPBDB_TransactionStatusController_settingsController(	RPBDB_TransactionStatusController* transaction_status_controller )	{
	return transaction_status_controller->settings_controller;
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_TransactionStatusController_parentEnvironment(	RPBDB_TransactionStatusController* transaction_status_controller )	{
	return transaction_status_controller->environment_settings_controller;
}

