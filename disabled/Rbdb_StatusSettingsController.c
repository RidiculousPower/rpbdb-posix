/*
 *		RPBDB::SettingsController::SettingsStatusController
 *
 *
 */

#include "RPBDB_StatusSettingsController.h"

	#include "RPBDB_StatusController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*	 new	 *
*************/

RPBDB_StatusController* RPBDB_StatusSettingsController_new( RPBDB_SettingsController* settings_controller )	{

	RPBDB_StatusSettingsController*		status_settings_controller = calloc( 1, sizeof( RPBDB_StatusSettingsController ) );

	status_settings_controller->parent_settings_controller = settings_controller;

	return status_settings_controller;
}

/***************************
*			free			*
***************************/
void RPBDB_StatusSettingsController_free(	RPBDB_StatusSettingsController* status_settings_controller )	{
	if ( status_settings_controller->parent_settings_controller != NULL )	{
		RPBDB_SettingsController_free( status_settings_controller->parent_settings_controller );
	}
	RPBDB_StatusSettingsController_free( status_settings_controller );
}

/***************************************
*	parentEnvironment	*
***************************************/
RPBDB_Environment* RPBDB_StatusSettingsController_parentEnvironment(	RPBDB_StatusSettingsController* status_settings_controller )	{
	return status_settings_controller->environment_settings_controller;
}

/******************************
*	 displayAllInformation	  *
******************************/

//	DB_STAT_ALL				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_stat.html
BOOL RPBDB_StatusSettingsController_displayAllInformation( RPBDB_StatusSettingsController* status_settings_controller )	{

	if ( status_settings_controller->display_all == TRUE )	{
		return DB_STAT_ALL;
	}
	return FALSE;
}

	/*************************************
	*	 turnDisplayAllInformationOn	 *
	*************************************/

	void RPBDB_StatusSettingsController_turnDisplayAllInformationOn( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->display_all = TRUE;
	}

	/*************************************
	*	 turnDisplayAllInformationOff	 *
	*************************************/

	void RPBDB_StatusSettingsController_turnDisplayAllInformationOff( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->display_all = FALSE;
	}

/*************************************
*	 resetStatisticsAfterDisplay	 *
*************************************/

//	DB_STAT_CLEAR			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_stat.html
BOOL RPBDB_StatusSettingsController_resetStatisticsAfterDisplay( RPBDB_StatusSettingsController* status_settings_controller )	{

	if ( status_settings_controller->reset_after_display == TRUE )	{
		return DB_STAT_CLEAR;
	}
	return FALSE;
}

	/*****************************************
	*	 turnResetStatisticsAfterDisplayOn	 *
	*****************************************/

	void RPBDB_StatusSettingsController_turnResetStatisticsAfterDisplayOn( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->reset_after_display = TRUE;
	}

	/*****************************************
	*	 turnResetStatisticsAfterDisplayOff	 *
	*****************************************/

	void RPBDB_StatusSettingsController_turnResetStatisticsAfterDisplayOff( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->reset_after_display = FALSE;
	}

/*************************************
*	 displayAllSubsystemInformation	 *
*************************************/

//	DB_STAT_SUBSYSTEM		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_stat.html
BOOL RPBDB_StatusSettingsController_displayAllSubsystemInformation( RPBDB_StatusSettingsController* status_settings_controller )	{

	if ( status_settings_controller->display_for_all_subsystems == TRUE )	{
		return DB_STAT_SUBSYSTEM;
	}
	return FALSE;		
}

	/*********************************************
	*	 turnDisplayAllSubsystemInformationOn	 *
	*********************************************/

	void RPBDB_StatusSettingsController_turnDisplayAllSubsystemInformationOn( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->display_for_all_subsystems = TRUE;
	}

	/*********************************************
	*	 turnDisplayAllSubsystemInformationOff	 *
	*********************************************/

	void RPBDB_StatusSettingsController_turnDisplayAllSubsystemInformationOff( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->display_for_all_subsystems = FALSE;
	}

/************************************************
*	 retrieveCachedStatistics	*
************************************************/

//	DB_FAST_STAT				http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_stat.html
BOOL RPBDB_StatusSettingsController_retrieveCachedStatistics( RPBDB_StatusSettingsController* status_settings_controller )	{

	if ( status_settings_controller->no_traversal == TRUE )	{
		return DB_FAST_STAT;
	}
	return FALSE;
}

	/*********************************************************
	*	 turnRetrieveCachedStatisticsOn	 *
	*********************************************************/

	void RPBDB_StatusSettingsController_turnRetrieveCachedStatisticsOn( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->no_traversal = TRUE;
	}

	/*********************************************************
	*	 turnRetrieveCachedStatisticsOff	 *
	*********************************************************/

	void RPBDB_StatusSettingsController_turnRetrieveCachedStatisticsOff( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->no_traversal = FALSE;
	}

/****************************
*	 degreeTwoIsolation		*
****************************/

//	DB_READ_COMMITTED			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_stat.html
//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/read.html
BOOL RPBDB_StatusSettingsController_degreeTwoIsolation( RPBDB_StatusSettingsController* status_settings_controller )	{

	if ( status_settings_controller->degree_two_isolation == TRUE )	{
		return DB_READ_COMMITTED;
	}
	return FALSE;
}

	/*********************************
	*	 turnDegreeTwoIsolationOn	 *
	**********************************/

	void RPBDB_StatusSettingsController_turnDegreeTwoIsolationOn( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->degree_two_isolation = TRUE;
	}

	/*********************************
	*	 turnDegreeTwoIsolationOff	 *
	*********************************/

	void RPBDB_StatusSettingsController_turnDegreeTwoIsolationOff( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->degree_two_isolation = FALSE;
	}

/********************************
*	 degreeOneIsolation		*
********************************/

//	DB_READ_UNCOMMITTED			http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_stat.html
//	http://www.oracle.com/technology/documentation/berkeley-db/db/ref/transapp/read.html
BOOL RPBDB_StatusSettingsController_degreeOneIsolation( RPBDB_StatusSettingsController* status_settings_controller )	{

	if ( status_settings_controller->degree_one_isolation == TRUE )	{
		return DB_READ_UNCOMMITTED;
	}
	return FALSE;
}

	/*********************************
	*	 turnDegreeOneIsolationOn	 *
	*********************************/

	void RPBDB_StatusSettingsController_turnDegreeOneIsolationOn( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->degree_one_isolation = TRUE;
	}

	/*********************************
	*	 turnDegreeOneIsolationOff	 *
	*********************************/

	void RPBDB_StatusSettingsController_turnDegreeOneIsolationOff( RPBDB_StatusSettingsController* status_settings_controller )	{
		status_settings_controller->degree_one_isolation = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*	copyOfSettingsControllerForInstance	*
*******************************************/
RPBDB_StatusSettingsController* RPBDB_StatusSettingsController_internal_copyOfSettingsControllerForInstance(	RPBDB_StatusSettingsController* status_settings_controller )	{

	RPBDB_StatusSettingsController* status_settings_controller_copy	=	RPBDB_StatusSettingsController_new( status_settings_controller );

	//	Instances and Pointers
	status_settings_controller_copy->display_for_all_subsystems	=	status_settings_controller->display_for_all_subsystems;
	status_settings_controller_copy->no_traversal	=	status_settings_controller->no_traversal;
	status_settings_controller_copy->degree_one_isolation	=	status_settings_controller->degree_one_isolation;
	status_settings_controller_copy->reset_after_display	=	status_settings_controller->reset_after_display;
	status_settings_controller_copy->display_all	=	status_settings_controller->display_all;
	status_settings_controller_copy->degree_two_isolation	=	status_settings_controller->degree_two_isolation;

	return status_settings_controller_copy;
}

