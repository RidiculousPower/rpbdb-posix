/*
 *		RPDB_settingsController:RPDB_DebugSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_DebugSettingsController.h"

#include "RPDB_DebugVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_DebugSettingsController* RPDB_DebugSettingsController_new( RPDB_SettingsController* settings_controller )	{

	RPDB_DebugSettingsController*		debug_settings_controller = calloc( 1, sizeof( RPDB_DebugSettingsController ) );

	debug_settings_controller->parent_settings_controller = settings_controller;

	return debug_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_DebugSettingsController_free(	RPDB_DebugSettingsController** debug_settings_controller )	{

	if ( ( *debug_settings_controller )->verbosity_settings_controller != NULL )	{
		RPDB_DebugVerbositySettingsController_free( & ( ( *debug_settings_controller )->verbosity_settings_controller ) );
	}
	
	free( *debug_settings_controller );
	*debug_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_DebugSettingsController_parentEnvironment(	RPDB_DebugSettingsController* debug_settings_controller )	{
	return debug_settings_controller->parent_settings_controller->parent_environment;
}

/*********************************************************
*  runNormalRecoveryBeforeOpeningEnvironment  *
*********************************************************/

//	DB_FAILCHK
int RPDB_DebugSettingsController_checkForEnvironmentFailureDuringOpen( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->check_for_environment_failure_during_open == TRUE )	{
		return DB_FAILCHK;
	}
	return FALSE;
}

	/*************************************************************
	 *  turnRunNormalRecoveryBeforeOpeningEnvironmentOn  *
	 *************************************************************/

	void RPDB_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOn( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->check_for_environment_failure_during_open = TRUE;
	}

	/**************************************************************
	 *  turnRunNormalRecoveryBeforeOpeningEnvironmentOff  *
	 **************************************************************/

	void RPDB_DebugSettingsController_turnCheckForEnvironmentFailureDuringOpenOff( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->check_for_environment_failure_during_open = FALSE;
	}

/*********************************************************
*  runNormalRecoveryBeforeOpeningEnvironment  *
*********************************************************/

//	DB_RECOVER              http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	Run normal recovery on this environment before opening it for normal use. 
//	If this flag is set, the DB_CREATE and DB_INIT_TXN flags must also be set, because the regions will be removed and re-created, 
//	and transactions are required for application recovery.
int RPDB_DebugSettingsController_runNormalRecoveryBeforeOpeningEnvironment( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->run_normal_recovery_before_opening_environment == TRUE )	{
		return DB_RECOVER;
	}
	return FALSE;
}

	/*************************************************************
	*  turnRunNormalRecoveryBeforeOpeningEnvironmentOn  *
	*************************************************************/

	void RPDB_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOn( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->run_normal_recovery_before_opening_environment = TRUE;
	}

	/**************************************************************
	*  turnRunNormalRecoveryBeforeOpeningEnvironmentOff  *
	**************************************************************/

	void RPDB_DebugSettingsController_turnRunNormalRecoveryBeforeOpeningEnvironmentOff( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->run_normal_recovery_before_opening_environment = FALSE;
	}

/**************************************************************
*  runCatastrophicRecoveryBeforeOpeningEnvironment  *
**************************************************************/

//	DB_RECOVER_FATAL        http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	Run catastrophic recovery on this environment before opening it for normal use. 
//	If this flag is set, the DB_CREATE and DB_INIT_TXN flags must also be set, because the regions will be removed and re-created, 
//	and transactions are required for application recovery.
int RPDB_DebugSettingsController_runCatastrophicRecoveryBeforeOpeningEnvironment( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->run_catastrophic_recovery_before_opening_environment == TRUE )	{
		return DB_RECOVER_FATAL;
	}
	return FALSE;
}

	/********************************************************************
	*  turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOn  *
	********************************************************************/

	//	DB_RECOVER_FATAL        http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOn( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->run_catastrophic_recovery_before_opening_environment = TRUE;
	}

	/********************************************************************
	*  turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOff  *
	********************************************************************/

	//	DB_RECOVER_FATAL        http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	void RPDB_DebugSettingsController_turnRunCatastrophicRecoveryBeforeOpeningEnvironmentOff( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->run_catastrophic_recovery_before_opening_environment = FALSE;
	}

/******************************
*  openInLockdown  *
******************************/

//	DB_LOCKDOWN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	Lock shared Berkeley DB environment files and memory-mapped databases into memory.
int RPDB_DebugSettingsController_openInLockdown( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->open_in_lockdown == TRUE )	{
		return DB_LOCKDOWN;
	}
	return FALSE;
}

	/**********************************
	*  turnOpenInLockdownOn  *
	**********************************/

	//	DB_LOCKDOWN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	//	Lock shared Berkeley DB environment files and memory-mapped databases into memory.
	void RPDB_DebugSettingsController_turnOpenInLockdownOn( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->open_in_lockdown = TRUE;	
	}

	/**************************************
	*  turnOpenInLockdownOff  *
	***************************************/

	//	DB_LOCKDOWN             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
	//	Lock shared Berkeley DB environment files and memory-mapped databases into memory.
	void RPDB_DebugSettingsController_turnOpenInLockdownOff( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->open_in_lockdown = FALSE;	
	}

/******************************************************
*  checkForRecoveryBeforeOpeningEnvironment  *
******************************************************/

//	DB_REGISTER             http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_open.html
//	Check to see if recovery needs to be performed before opening the database environment. 
//	(For this check to be accurate, all processes using the environment must specify DB_REGISTER when opening the environment.) 
//	If recovery needs to be performed for any reason (including the initial use of the DB_REGISTER flag), and DB_RECOVER is also specified, 
//	recovery will be performed and the open will proceed normally. If recovery needs to be performed and DB_RECOVER is not specified, 
//	DB_RUNRECOVERY will be returned. If recovery does not need to be performed, the DB_RECOVER flag will be ignored. 
//	See Architecting Transactional Data Store applications for more information.
int RPDB_DebugSettingsController_registerForRecovery( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->check_for_recovery_on_load == TRUE )	{
		return DB_REGISTER;
	}
	return FALSE;
}

	/**************************************************************
	*  turnCheckForRecoveryBeforeOpeningEnvironmentOn  *
	**************************************************************/

	void RPDB_DebugSettingsController_turnRegisterForRecoveryOn( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->check_for_recovery_on_load = TRUE;
	}

	/**************************************************************
	*  turnCheckForRecoveryBeforeOpeningEnvironmentOff  *
	**************************************************************/

	void RPDB_DebugSettingsController_turnRegisterForRecoveryOff( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->check_for_recovery_on_load = FALSE;
	}

/**********************
*  prohibitPanic  *
**********************/

//	DB_NOPANIC				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//
//	If set, Berkeley DB will ignore any panic state in the database environment. 
//
//	Database environments in a panic state normally refuse all attempts to call Berkeley DB functions, returning DB_RUNRECOVERY.
//	This functionality should never be used for purposes other than debugging.
//	Calling DB_ENV->set_flags with the DB_NOPANIC flag only affects the specified DB_ENV name 
//	(and any other Berkeley DB names opened within the scope of that name).
//
//	The DB_NOPANIC flag may be used to configure Berkeley DB at any time during the life of the application.
//
int RPDB_DebugSettingsController_prohibitPanic( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->prohibit_panic )	{
		return DB_NOPANIC;
	}
	return FALSE;
}

/******************************
*  turnProhibitPanicOn  *
******************************/

void RPDB_DebugSettingsController_turnProhibitPanicOn( RPDB_DebugSettingsController* debug_settings_controller )	{
	debug_settings_controller->prohibit_panic = TRUE;
}

/******************************
*  turnProhibitPanicOff  *
******************************/

void RPDB_DebugSettingsController_turnProhibitPanicOff( RPDB_DebugSettingsController* debug_settings_controller )	{
	debug_settings_controller->prohibit_panic = FALSE;
}

/**************
*  panic  *
**************/

//	DB_PANIC_ENVIRONMENT    http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//
//	If set, Berkeley DB will set the panic state for the database environment. 
//
//	Database environments in a panic state normally refuse all attempts to call Berkeley DB functions, returning DB_RUNRECOVERY.
//
//	This flag may not be specified using the environment's DB_CONFIG file.
//
//	Calling DB_ENV->set_flags with the DB_PANIC_ENVIRONMENT flag affects the database environment, including all threads of control accessing the database environment.
//
//	The DB_PANIC_ENVIRONMENT flag may be used to configure Berkeley DB only after the DB_ENV->open method is called.
int RPDB_DebugSettingsController_panic( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->panic == TRUE )	{
		return DB_PANIC_ENVIRONMENT;
	}
	return FALSE;
}

	/**********************
	*  turnPanicOn  *
	**********************/

	//	DB_PANIC_ENVIRONMENT    http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_DebugSettingsController_turnPanicOn( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->panic = TRUE;
	}

	/**********************
	*  turnPanicOff  *
	**********************/

	//	DB_PANIC_ENVIRONMENT    http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
	void RPDB_DebugSettingsController_turnPanicOff( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->panic = FALSE;
	}

/******************************
*  yieldCPUForStressTest  *
******************************/

//	DB_YIELDCPU				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_flags.html
//
//	If set, Berkeley DB will yield the processor immediately after each page or mutex acquisition. 
//
//	This functionality should never be used for purposes other than stress testing.
//
//	Calling DB_ENV->set_flags with the DB_YIELDCPU flag only affects the specified DB_ENV name 
//	(and any other Berkeley DB names opened within the scope of that name). 
//
//	For consistent behavior across the environment, all DB_ENV names opened in the environment must either set the 
//	DB_YIELDCPU flag or the flag should be specified in the DB_CONFIG configuration file.
//
//	The DB_YIELDCPU flag may be used to configure Berkeley DB at any time during the life of the application.
int RPDB_DebugSettingsController_yieldCPUForStressTest( RPDB_DebugSettingsController* debug_settings_controller )	{
	if ( debug_settings_controller->yield_cpu_for_stress_test == TRUE )	{
		return DB_YIELDCPU;
	}
	return FALSE;
}

	/**************************************
	*  turnYieldCPUForStressTestOn  *
	**************************************/

	void RPDB_DebugSettingsController_turnYieldCPUForStressTestOn( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->yield_cpu_for_stress_test = TRUE;
	}

	/**************************************
	*  turnYieldCPUForStressTestOff  *
	**************************************/

	void RPDB_DebugSettingsController_turnYieldCPUForStressTestOff( RPDB_DebugSettingsController* debug_settings_controller )	{
		debug_settings_controller->yield_cpu_for_stress_test = FALSE;
	}

/*************************************
*  verbositySettingsController  *
*************************************/

RPDB_DebugVerbositySettingsController* RPDB_DebugSettingsController_verbositySettingsController( RPDB_DebugSettingsController* debug_settings_controller )	{

	if ( debug_settings_controller->verbosity_settings_controller == NULL )	{
	
		debug_settings_controller->verbosity_settings_controller = RPDB_DebugVerbositySettingsController_new( debug_settings_controller );
	}
	
	return debug_settings_controller->verbosity_settings_controller;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_DebugSettingsController* RPDB_DebugSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_DebugSettingsController* debug_settings_controller )	{

	RPDB_DebugSettingsController* debug_settings_controller_copy	=	RPDB_DebugSettingsController_new( debug_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	debug_settings_controller_copy->check_for_recovery_on_load	=	debug_settings_controller->check_for_recovery_on_load;
	debug_settings_controller_copy->run_normal_recovery_before_opening_environment	=	debug_settings_controller->run_normal_recovery_before_opening_environment;
	debug_settings_controller_copy->panic	=	debug_settings_controller->panic;
	debug_settings_controller_copy->prohibit_panic	=	debug_settings_controller->prohibit_panic;
	debug_settings_controller_copy->run_catastrophic_recovery_before_opening_environment	=	debug_settings_controller->run_catastrophic_recovery_before_opening_environment;
	debug_settings_controller_copy->open_in_lockdown	=	debug_settings_controller->open_in_lockdown;
	debug_settings_controller_copy->yield_cpu_for_stress_test	=	debug_settings_controller->yield_cpu_for_stress_test;

	return debug_settings_controller_copy;
}

