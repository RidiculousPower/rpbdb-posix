#ifndef RPDB_TRANSACTION_SETTINGS_CONTROLLER_INTERNAL
	#define RPDB_TRANSACTION_SETTINGS_CONTROLLER_INTERNAL
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Method Prototypes
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/
/*
int														RPDB_TransactionSettingsController_internal_transactionRecoveryCallbackMethod(		DB_ENV*										bdb_environment, 
   																																			DBT*										transaction_log_record, 
   																																			DB_LSN*										lsn, 
   																																			db_recops									recovery_operation );
*/
RPDB_TransactionSettingsController*		RPDB_TransactionSettingsController_internal_copyOfDefaultSettingsForInstance(		RPDB_TransactionSettingsController*		transaction_settings_controller );
int													RPDB_TransactionSettingsController_internal_beginFlags(				RPDB_TransactionSettingsController*		transaction_settings_controller );
int													RPDB_TransactionSettingsController_internal_discardFlags(				RPDB_TransactionSettingsController*		transaction_settings_controller );
int													RPDB_TransactionSettingsController_internal_commitFlags(				RPDB_TransactionSettingsController*		transaction_settings_controller );
int													RPDB_TransactionSettingsController_internal_commitCheckpointFlags(		RPDB_TransactionSettingsController*		transaction_settings_controller );
int													RPDB_TransactionSettingsController_internal_recoverFlags(				RPDB_TransactionSettingsController*		transaction_settings_controller );	

RPDB_TransactionSettingsController* RPDB_TransactionSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_TransactionSettingsController* transaction_settings_controller );
	
#endif

