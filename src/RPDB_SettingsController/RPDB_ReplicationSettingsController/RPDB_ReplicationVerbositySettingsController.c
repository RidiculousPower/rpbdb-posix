/*
 *		RPDB::SettingsController::SettingsVerbosityController::SettingsVerbosityReplicationController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_ReplicationVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_ReplicationVerbositySettingsController* RPDB_ReplicationVerbositySettingsController_new( RPDB_ReplicationSettingsController* replication_settings_controller )	{

	RPDB_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller = calloc( 1, sizeof( RPDB_ReplicationVerbositySettingsController ) );

	replication_verbosity_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPDB_ReplicationVerbositySettingsController_free(	RPDB_ReplicationVerbositySettingsController** replication_verbosity_settings_controller )	{

	free( replication_verbosity_settings_controller );
}

/***************************************
*  parentEnvironment  *
***************************************/
RPDB_Environment* RPDB_ReplicationVerbositySettingsController_parentEnvironment(	RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
	return replication_verbosity_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************
*  displayAllReplicationInformation  *
*****************************************/

//	DB_VERB_REPLICATION     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayAllReplicationInformation( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_all_replication_information )	{
		return DB_VERB_REPLICATION;
	}
	
	return FALSE;
}

	/*********************************************
	*  turnDisplayAllReplicationInformationOn  *
	*********************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
		
		replication_verbosity_settings_controller->display_all_replication_information = TRUE;
	}

	/*************************************************
	*  turnDisplayAllReplicationInformationOff  *
	*************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
		
		replication_verbosity_settings_controller->display_all_replication_information = FALSE;
	}

/*********************************
*  displayElectionInformation  *
*********************************/

//	DB_VERB_REP_ELECT    		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayElectionInformation( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_election_information )	{
		return DB_VERB_REP_ELECT;
	}
	return FALSE;
}

	/*****************************************
	*  turnDisplayElectionInformationOn  *
	*****************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayElectionInformationOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_election_information = TRUE;
	}

	/*****************************************
	*  turnDisplayElectionInformationOff  *
	*****************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayElectionInformationOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_election_information = FALSE;
	}

/*************************************************
*  displayReplicationMasterLeaseInformation  *
*************************************************/

//	DB_VERB_REP_LEASE       	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_replication_master_lease_information )	{
		return DB_VERB_REP_LEASE;
	}
	return FALSE;	
}

	/*****************************************************
	*  turnDisplayReplicationMasterLeaseInformationOn  *
	*****************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_replication_master_lease_information = TRUE;
	}

	/*********************************************************
	*  turnDisplayReplicationMasterLeaseInformationOff  *
	*********************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_replication_master_lease_information = FALSE;
	}

/*****************************************
*  displayMiscProcessingInformation  *
*****************************************/

//	DB_VERB_REP_MISC        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayMiscProcessingInformation( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_misc_processing_information )	{
		return DB_VERB_REP_MISC;
	}
	return FALSE;

}

	/*********************************************
	*  turnDisplayMiscProcessingInformationOn  *
	*********************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_misc_processing_information = TRUE;
	}

	/*************************************************
	*  turnDisplayMiscProcessingInformationOff  *
	*************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_misc_processing_information = FALSE;
	}

/*********************************************
*  displayMessageProcessingInformation  *
*********************************************/

//	DB_VERB_REP_MSGS        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayMessageProcessingInformation( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_message_processing_information )	{
		return DB_VERB_REP_MSGS;
	}
	return FALSE;

}

	/*************************************************
	*  turnDisplayMessageProcessingInformationOn  *
	*************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_message_processing_information = TRUE;
	}

	/*************************************************
	*  turnDisplayMessageProcessingInformationOff  *
	*************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_message_processing_information = FALSE;
	}

/*************************************************
*  displayClientSynchronizationInformation  *
*************************************************/

//	DB_VERB_REP_SYNC        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayClientSynchronizationInformation( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_client_synchronization_information )	{
		return DB_VERB_REP_SYNC;
	}
	return FALSE;

}

	/*****************************************************
	*  turnDisplayClientSynchronizationInformationOn  *
	*****************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_client_synchronization_information = TRUE;
	}

	/*****************************************************
	*  turnDisplayClientSynchronizationInformationOff  *
	*****************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_client_synchronization_information = FALSE;
	}

/*************************************************
*  displayManagerConnectionFailureInformation  *
*************************************************/

//	DB_VERB_REPMGR_CONNFAIL 	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_manager_connection_failure_information )	{
		return DB_VERB_REPMGR_CONNFAIL;
	}
	return FALSE;
}

	/*********************************************************
	*  turnDisplayManagerConnectionFailureInformationOn  *
	*********************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_connection_failure_information = TRUE;
	}

	/*********************************************************
	*  turnDisplayManagerConnectionFailureInformationOff  *
	*********************************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_connection_failure_information = FALSE;
	}

/*************************************
*  displayManagerMiscProcessing  *
*************************************/

//	DB_VERB_REPMGR_MISC     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPDB_ReplicationVerbositySettingsController_displayManagerMiscProcessing( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_manager_misc_processing )	{
		return DB_VERB_REPMGR_MISC;
	}
	return FALSE;	
}

	/*****************************************
	*  turnDisplayManagerMiscProcessingOn  *
	*****************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOn( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_misc_processing = TRUE;
	}

	/*********************************************
	*  turnDisplayManagerMiscProcessingOff  *
	*********************************************/

	void RPDB_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOff( RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_misc_processing = FALSE;
	}
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPDB_ReplicationVerbositySettingsController* RPDB_ReplicationVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	RPDB_ReplicationVerbositySettingsController* replication_verbosity_settings_controller_copy	=	RPDB_ReplicationVerbositySettingsController_new( replication_verbosity_settings_controller->parent_replication_settings_controller );

	//	Instances and Pointers
	replication_verbosity_settings_controller_copy->display_manager_misc_processing	=	replication_verbosity_settings_controller->display_manager_misc_processing;
	replication_verbosity_settings_controller_copy->display_message_processing_information	=	replication_verbosity_settings_controller->display_message_processing_information;
	replication_verbosity_settings_controller_copy->display_all_replication_information	=	replication_verbosity_settings_controller->display_all_replication_information;
	replication_verbosity_settings_controller_copy->display_client_synchronization_information	=	replication_verbosity_settings_controller->display_client_synchronization_information;
	replication_verbosity_settings_controller_copy->display_misc_processing_information	=	replication_verbosity_settings_controller->display_misc_processing_information;
	replication_verbosity_settings_controller_copy->display_manager_connection_failure_information	=	replication_verbosity_settings_controller->display_manager_connection_failure_information;
	replication_verbosity_settings_controller_copy->display_election_information	=	replication_verbosity_settings_controller->display_election_information;
	replication_verbosity_settings_controller_copy->display_replication_master_lease_information	=	replication_verbosity_settings_controller->display_replication_master_lease_information;

	return replication_verbosity_settings_controller_copy;
}

