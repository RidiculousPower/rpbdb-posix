/*
 *		Rbdb::SettingsController::MutexSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_MutexSettingsController.h" 

#include "Rbdb_Environment.h"

#include "Rbdb_MutexSettingsController_internal.h" 
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_MutexSettingsController* Rbdb_MutexSettingsController_new( Rbdb_SettingsController* settings_controller )	{
	
	Rbdb_MutexSettingsController*		mutex_settings_controller = calloc( 1, sizeof( Rbdb_MutexSettingsController ) );

	mutex_settings_controller->parent_settings_controller = settings_controller;

	return mutex_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_MutexSettingsController_free(	Rbdb_MutexSettingsController** mutex_settings_controller )	{

	free( *mutex_settings_controller );
	*mutex_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_MutexSettingsController_parentEnvironment(	Rbdb_MutexSettingsController* mutex_settings_controller )	{
	return mutex_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************************
*  spinTimesBeforeBlockingForTestAndSpinMutexes  *
*****************************************************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/mutex_set_tas_spins.html
uint32_t Rbdb_MutexSettingsController_spinTimesBeforeBlockingForTestAndSpinMutexes( Rbdb_MutexSettingsController* mutex_settings_controller )	{
	
	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_get_tas_spins(	environment->wrapped_bdb_environment, 
																	&( mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes ) );
	}
	
	return mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes;
}

/*********************************************************
*  setSpinTimesBeforeBlockingForTestAndSpinMutexes  *
*********************************************************/

void Rbdb_MutexSettingsController_setSpinTimesBeforeBlockingForTestAndSpinMutexes(	Rbdb_MutexSettingsController*	mutex_settings_controller, 
																					uint32_t						spin_times_before_blocking_for_test_and_spin_mutexes )	{

	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_MutexSettingsController_maxAllowableMutexes( Rbdb_MutexSettingsController* mutex_settings_controller )	{
	
	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
void Rbdb_MutexSettingsController_setMaxAllowableMutexes(	Rbdb_MutexSettingsController*		mutex_settings_controller, 
															uint32_t							max_allowable_mutexes )	{

	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
uint32_t Rbdb_MutexSettingsController_incrementForAddingMutexes( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
void Rbdb_MutexSettingsController_setIncrementForAddingMutexes(	Rbdb_MutexSettingsController*	mutex_settings_controller, 
																	uint32_t						increment_for_adding_mutexes )	{

	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

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
uint32_t Rbdb_MutexSettingsController_mutexAlignment( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;
	
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
void Rbdb_MutexSettingsController_setMutexAlignment(	Rbdb_MutexSettingsController*		mutex_settings_controller, 
																											uint32_t												mutex_alignment )	{

	Rbdb_Environment*		environment	= mutex_settings_controller->parent_settings_controller->parent_environment;

	if ( environment->wrapped_bdb_environment != NULL )	{

		environment->wrapped_bdb_environment->mutex_set_align(	environment->wrapped_bdb_environment, 
																														mutex_alignment );
	}
	
	mutex_settings_controller->mutex_alignment = mutex_alignment;	
}

/*************************
*  setMutexAlignment  *
*************************/

BOOL Rbdb_MutexSettingsController_associatedWithSingleProcess( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	if ( mutex_settings_controller->associated_with_single_process == TRUE )	{
	
		return DB_MUTEX_PROCESS_ONLY;		
	}
	
	return FALSE;
}

/*************************
*  setMutexAlignment  *
*************************/

void Rbdb_MutexSettingsController_turnAssociatedWithSingleProcessOn( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->associated_with_single_process = TRUE;
}

/*****************************************
*  turnAssociatedWithSingleProcessOff  *
*****************************************/

void Rbdb_MutexSettingsController_turnAssociatedWithSingleProcessOff( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->associated_with_single_process = FALSE;
}

/*********************
*  selfBlocking  *
*********************/

BOOL Rbdb_MutexSettingsController_selfBlocking( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	if ( mutex_settings_controller->self_blocking == TRUE )	{
	
		return DB_MUTEX_PROCESS_ONLY;		
	}
	
	return FALSE;
}

/*************************
*  turnSelfBlockingOn  *
*************************/

void Rbdb_MutexSettingsController_turnSelfBlockingOn( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	mutex_settings_controller->self_blocking = TRUE;
}

/*****************************
*  turnSelfBlockingOff  *
*****************************/

void Rbdb_MutexSettingsController_turnSelfBlockingOff( Rbdb_MutexSettingsController* mutex_settings_controller )	{

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
BOOL Rbdb_MutexSettingsController_internal_openFlags( Rbdb_MutexSettingsController* mutex_settings_controller )	{

	if ( Rbdb_MutexSettingsController_associatedWithSingleProcess( mutex_settings_controller ) )	{
		return Rbdb_MutexSettingsController_associatedWithSingleProcess( mutex_settings_controller );
	}
	else	{
		return Rbdb_MutexSettingsController_selfBlocking( mutex_settings_controller );
	}
}	

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
Rbdb_MutexSettingsController* Rbdb_MutexSettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_MutexSettingsController* mutex_settings_controller )	{

	Rbdb_MutexSettingsController* mutex_settings_controller_copy	=	Rbdb_MutexSettingsController_new( mutex_settings_controller->parent_settings_controller );

	//	Instances and Pointers
	mutex_settings_controller_copy->associated_with_single_process	=	mutex_settings_controller->associated_with_single_process;
	mutex_settings_controller_copy->mutex_alignment	=	mutex_settings_controller->mutex_alignment;
	mutex_settings_controller_copy->increment_for_adding_mutexes	=	mutex_settings_controller->increment_for_adding_mutexes;
	mutex_settings_controller_copy->max_allowable_mutexes	=	mutex_settings_controller->max_allowable_mutexes;
	mutex_settings_controller_copy->spin_times_before_blocking_for_test_and_spin_mutexes	=	mutex_settings_controller->spin_times_before_blocking_for_test_and_spin_mutexes;
	mutex_settings_controller_copy->self_blocking	=	mutex_settings_controller->self_blocking;

	return mutex_settings_controller_copy;
}

