/*
 *		RPbdb::SettingsController::MutexSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "MutexSettingsController.h" 

#include "Environment.h"

#include "MutexSettingsController_internal.h" 
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_MutexSettingsController* RPbdb_MutexSettingsController_new( RPbdb_SettingsController* settings_controller )	{
	
	RPbdb_MutexSettingsController*		mutex_settings_controller = calloc( 1, sizeof( RPbdb_MutexSettingsController ) );

	mutex_settings_controller->parent_settings_controller = settings_controller;

	return mutex_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_MutexSettingsController_free(	RPbdb_MutexSettingsController** mutex_settings_controller )	{

	free( *mutex_settings_controller );
	*mutex_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_MutexSettingsController_parentEnvironment(	RPbdb_MutexSettingsController* mutex_settings_controller )	{
	return mutex_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************************
*  spinTimesBeforeBlockingForTestAndSpinMutexes  *
*****************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_tas_spins.html
uint32_t RPbdb_MutexSettingsController_spinTimesBeforeBlockingForTestAndSpinMutexes( RPbdb_MutexSettingsController* mutex_settings_controller )	{
	
	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_get_tas_spins(	environment->wrapped_bdb_environment, 
																	&( mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes ) );
	}
	
	return mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes;
}

/*********************************************************
*  setSpinTimesBeforeBlockingForTestAndSpinMutexes  *
*********************************************************/

void RPbdb_MutexSettingsController_setSpinTimesBeforeBlockingForTestAndSpinMutexes(	RPbdb_MutexSettingsController*	mutex_settings_controller, 
																					uint32_t						spin_times_before_blocking_for_test_and_spin_mutexes )	{

	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t RPbdb_MutexSettingsController_maxAllowableMutexes( RPbdb_MutexSettingsController* mutex_settings_controller )	{
	
	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
void RPbdb_MutexSettingsController_setMaxAllowableMutexes(	RPbdb_MutexSettingsController*		mutex_settings_controller, 
															uint32_t							max_allowable_mutexes )	{

	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
uint32_t RPbdb_MutexSettingsController_incrementForAddingMutexes( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
void RPbdb_MutexSettingsController_setIncrementForAddingMutexes(	RPbdb_MutexSettingsController*	mutex_settings_controller, 
																	uint32_t						increment_for_adding_mutexes )	{

	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t RPbdb_MutexSettingsController_mutexAlignment( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
void RPbdb_MutexSettingsController_setMutexAlignment(	RPbdb_MutexSettingsController*		mutex_settings_controller, 
																											uint32_t												mutex_alignment )	{

	RPbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_set_align(	environment->wrapped_bdb_environment, 
																														mutex_alignment );
	}
	
	mutex_settings_controller->mutex_alignment = mutex_alignment;	
}

/*************************
*  setMutexAlignment  *
*************************/

BOOL RPbdb_MutexSettingsController_associatedWithSingleProcess( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	if ( mutex_settings_controller->associated_with_single_process == TRUE )	{
	
		return DB_MUTEX_PROCESS_ONLY;		
	}
	
	return FALSE;
}

/*************************
*  setMutexAlignment  *
*************************/

void RPbdb_MutexSettingsController_turnAssociatedWithSingleProcessOn( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->associated_with_single_process = TRUE;
}

/*****************************************
*  turnAssociatedWithSingleProcessOff  *
*****************************************/

void RPbdb_MutexSettingsController_turnAssociatedWithSingleProcessOff( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->associated_with_single_process = FALSE;
}

/*********************
*  selfBlocking  *
*********************/

BOOL RPbdb_MutexSettingsController_selfBlocking( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	if ( mutex_settings_controller->self_blocking == TRUE )	{
	
		return DB_MUTEX_PROCESS_ONLY;		
	}
	
	return FALSE;
}

/*************************
*  turnSelfBlockingOn  *
*************************/

void RPbdb_MutexSettingsController_turnSelfBlockingOn( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->self_blocking = TRUE;
}

/*****************************
*  turnSelfBlockingOff  *
*****************************/

void RPbdb_MutexSettingsController_turnSelfBlockingOff( RPbdb_MutexSettingsController* mutex_settings_controller )	{

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
BOOL RPbdb_MutexSettingsController_internal_openFlags( RPbdb_MutexSettingsController* mutex_settings_controller )	{

	if ( RPbdb_MutexSettingsController_associatedWithSingleProcess( mutex_settings_controller ) )	{
		return RPbdb_MutexSettingsController_associatedWithSingleProcess( mutex_settings_controller );
	}
	else	{
		return RPbdb_MutexSettingsController_selfBlocking( mutex_settings_controller );
	}
}	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_MutexSettingsController* RPbdb_MutexSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_MutexSettingsController* mutex_settings_controller )	{

	RPbdb_MutexSettingsController* mutex_settings_controller_copy	=	RPbdb_MutexSettingsController_new( mutex_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	mutex_settings_controller_copy->associated_with_single_process	=	mutex_settings_controller->associated_with_single_process;
	mutex_settings_controller_copy->mutex_alignment	=	mutex_settings_controller->mutex_alignment;
	mutex_settings_controller_copy->increment_for_adding_mutexes	=	mutex_settings_controller->increment_for_adding_mutexes;
	mutex_settings_controller_copy->max_allowable_mutexes	=	mutex_settings_controller->max_allowable_mutexes;
	mutex_settings_controller_copy->spin_times_before_blocking_for_test_and_spin_mutexes	=	mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes;
	mutex_settings_controller_copy->self_blocking	=	mutex_settings_controller->self_blocking;

	return mutex_settings_controller_copy;
}

