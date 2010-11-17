/*
 *		RPDB::SettingsController::MutexSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_MutexSettingsController.h" 

#include "RPDB_Environment.h"

#include "RPDB_MutexSettingsController_internal.h" 
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_MutexSettingsController* RPDB_MutexSettingsController_new( RPDB_SettingsController* settings_controller )	{
	
	RPDB_MutexSettingsController*		mutex_settings_controller = calloc( 1, sizeof( RPDB_MutexSettingsController ) );

	mutex_settings_controller->parent_settings_controller = settings_controller;

	return mutex_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_MutexSettingsController_free(	RPDB_MutexSettingsController** mutex_settings_controller )	{

	free( *mutex_settings_controller );
	*mutex_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_MutexSettingsController_parentEnvironment(	RPDB_MutexSettingsController* mutex_settings_controller )	{
	return mutex_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************************
*  spinTimesBeforeBlockingForTestAndSpinMutexes  *
*****************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_tas_spins.html
uint32_t RPDB_MutexSettingsController_spinTimesBeforeBlockingForTestAndSpinMutexes( RPDB_MutexSettingsController* mutex_settings_controller )	{
	
	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_get_tas_spins(	environment->wrapped_bdb_environment, 
																	&( mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes ) );
	}
	
	return mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes;
}

/*********************************************************
*  setSpinTimesBeforeBlockingForTestAndSpinMutexes  *
*********************************************************/

void RPDB_MutexSettingsController_setSpinTimesBeforeBlockingForTestAndSpinMutexes(	RPDB_MutexSettingsController*	mutex_settings_controller, 
																					uint32_t						spin_times_before_blocking_for_test_and_spin_mutexes )	{

	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_set_tas_spins(	environment->wrapped_bdb_environment, 
																	spin_times_before_blocking_for_test_and_spin_mutexes );
	}
	
	mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes = spin_times_before_blocking_for_test_and_spin_mutexes;
}

/*****************************
*  maxAllowableMutexes  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_max.html
uint32_t RPDB_MutexSettingsController_maxAllowableMutexes( RPDB_MutexSettingsController* mutex_settings_controller )	{
	
	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{
		environment->wrapped_bdb_environment->mutex_get_max(	environment->wrapped_bdb_environment, 
																&( mutex_settings_controller->max_allowable_mutexes ) );
	}
	
	return mutex_settings_controller->max_allowable_mutexes;
}

/*****************************
*  setMaxAllowableMutexes  *
*****************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_max.html
void RPDB_MutexSettingsController_setMaxAllowableMutexes(	RPDB_MutexSettingsController*		mutex_settings_controller, 
															uint32_t							max_allowable_mutexes )	{

	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_set_max(	environment->wrapped_bdb_environment, 
									max_allowable_mutexes );
	}
	
	mutex_settings_controller->max_allowable_mutexes = max_allowable_mutexes;
}

/*********************************
*  incrementForAddingMutexes  *
*********************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_max.html
uint32_t RPDB_MutexSettingsController_incrementForAddingMutexes( RPDB_MutexSettingsController* mutex_settings_controller )	{

	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_get_increment(	environment->wrapped_bdb_environment, 
																	&( mutex_settings_controller->increment_for_adding_mutexes ) );
	}
	
	return mutex_settings_controller->increment_for_adding_mutexes;
}

/*************************************
*  setIncrementForAddingMutexes  *
*************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_max.html
void RPDB_MutexSettingsController_setIncrementForAddingMutexes(	RPDB_MutexSettingsController*	mutex_settings_controller, 
																	uint32_t						increment_for_adding_mutexes )	{

	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_set_increment(	environment->wrapped_bdb_environment, 
											increment_for_adding_mutexes );
	}
	
	mutex_settings_controller->increment_for_adding_mutexes = increment_for_adding_mutexes;	
}

/*********************
*  mutexAlignment  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_max.html
uint32_t RPDB_MutexSettingsController_mutexAlignment( RPDB_MutexSettingsController* mutex_settings_controller )	{

	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_get_align(	environment->wrapped_bdb_environment, 
																														&( mutex_settings_controller->mutex_alignment ) );
	}
	
	return mutex_settings_controller->mutex_alignment;
}

/*************************
*  setMutexAlignment  *
*************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_max.html
void RPDB_MutexSettingsController_setMutexAlignment(	RPDB_MutexSettingsController*		mutex_settings_controller, 
																											uint32_t												mutex_alignment )	{

	RPDB_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_set_align(	environment->wrapped_bdb_environment, 
																														mutex_alignment );
	}
	
	mutex_settings_controller->mutex_alignment = mutex_alignment;	
}

/*************************
*  setMutexAlignment  *
*************************/

BOOL RPDB_MutexSettingsController_associatedWithSingleProcess( RPDB_MutexSettingsController* mutex_settings_controller )	{

	if ( mutex_settings_controller->associated_with_single_process == TRUE )	{
	
		return DB_MUTEX_PROCESS_ONLY;		
	}
	
	return FALSE;
}

/*************************
*  setMutexAlignment  *
*************************/

void RPDB_MutexSettingsController_turnAssociatedWithSingleProcessOn( RPDB_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->associated_with_single_process = TRUE;
}

/*****************************************
*  turnAssociatedWithSingleProcessOff  *
*****************************************/

void RPDB_MutexSettingsController_turnAssociatedWithSingleProcessOff( RPDB_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->associated_with_single_process = FALSE;
}

/*********************
*  selfBlocking  *
*********************/

BOOL RPDB_MutexSettingsController_selfBlocking( RPDB_MutexSettingsController* mutex_settings_controller )	{

	if ( mutex_settings_controller->self_blocking == TRUE )	{
	
		return DB_MUTEX_PROCESS_ONLY;		
	}
	
	return FALSE;
}

/*************************
*  turnSelfBlockingOn  *
*************************/

void RPDB_MutexSettingsController_turnSelfBlockingOn( RPDB_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->self_blocking = TRUE;
}

/*****************************
*  turnSelfBlockingOff  *
*****************************/

void RPDB_MutexSettingsController_turnSelfBlockingOff( RPDB_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->self_blocking = FALSE;
}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*****************
*  openFlags  *
*****************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_alloc.html
BOOL RPDB_MutexSettingsController_internal_openFlags( RPDB_MutexSettingsController* mutex_settings_controller )	{

	if ( RPDB_MutexSettingsController_associatedWithSingleProcess( mutex_settings_controller ) )	{
		return RPDB_MutexSettingsController_associatedWithSingleProcess( mutex_settings_controller );
	}
	else	{
		return RPDB_MutexSettingsController_selfBlocking( mutex_settings_controller );
	}
}	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_MutexSettingsController* RPDB_MutexSettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_MutexSettingsController* mutex_settings_controller )	{

	RPDB_MutexSettingsController* mutex_settings_controller_copy	=	RPDB_MutexSettingsController_new( mutex_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	mutex_settings_controller_copy->associated_with_single_process	=	mutex_settings_controller->associated_with_single_process;
	mutex_settings_controller_copy->mutex_alignment	=	mutex_settings_controller->mutex_alignment;
	mutex_settings_controller_copy->increment_for_adding_mutexes	=	mutex_settings_controller->increment_for_adding_mutexes;
	mutex_settings_controller_copy->max_allowable_mutexes	=	mutex_settings_controller->max_allowable_mutexes;
	mutex_settings_controller_copy->spin_times_before_blocking_for_test_and_spin_mutexes	=	mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes;
	mutex_settings_controller_copy->self_blocking	=	mutex_settings_controller->self_blocking;

	return mutex_settings_controller_copy;
}

