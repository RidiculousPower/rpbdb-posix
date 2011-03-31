/*
 *		RPbdb::SettingsController::SettingsVerbosityController::SettingsVerbosityReplicationController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "ReplicationVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_ReplicationVerbositySettingsController* RPbdb_ReplicationVerbositySettingsController_new( RPbdb_ReplicationSettingsController* replication_settings_controller )	{

	RPbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller = calloc( 1, sizeof( RPbdb_ReplicationVerbositySettingsController ) );

	replication_verbosity_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_ReplicationVerbositySettingsController_free(	RPbdb_ReplicationVerbositySettingsController** replication_verbosity_settings_controller )	{

	free( replication_verbosity_settings_controller );
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_ReplicationVerbositySettingsController_parentEnvironment(	RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
	return replication_verbosity_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************
*  displayAllReplicationInformation  *
*****************************************/

//	DB_VERB_REPLICATION     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayAllReplicationInformation( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_all_replication_information )	{
		return DB_VERB_REPLICATION;
	}
	
	return FALSE;
}

	/*********************************************
	*  turnDisplayAllReplicationInformationOn  *
	*********************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
		
		replication_verbosity_settings_controller->display_all_replication_information = TRUE;
	}

	/*************************************************
	*  turnDisplayAllReplicationInformationOff  *
	*************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
		
		replication_verbosity_settings_controller->display_all_replication_information = FALSE;
	}

/*********************************
*  displayElectionInformation  *
*********************************/

//	DB_VERB_REP_ELECT    		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayElectionInformation( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_election_information )	{
		return DB_VERB_REP_ELECT;
	}
	return FALSE;
}

	/*****************************************
	*  turnDisplayElectionInformationOn  *
	*****************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_election_information = TRUE;
	}

	/*****************************************
	*  turnDisplayElectionInformationOff  *
	*****************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_election_information = FALSE;
	}

/*************************************************
*  displayReplicationMasterLeaseInformation  *
*************************************************/

//	DB_VERB_REP_LEASE       	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_replication_master_lease_information )	{
		return DB_VERB_REP_LEASE;
	}
	return FALSE;	
}

	/*****************************************************
	*  turnDisplayReplicationMasterLeaseInformationOn  *
	*****************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_replication_master_lease_information = TRUE;
	}

	/*********************************************************
	*  turnDisplayReplicationMasterLeaseInformationOff  *
	*********************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_replication_master_lease_information = FALSE;
	}

/*****************************************
*  displayMiscProcessingInformation  *
*****************************************/

//	DB_VERB_REP_MISC        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayMiscProcessingInformation( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_misc_processing_information )	{
		return DB_VERB_REP_MISC;
	}
	return FALSE;

}

	/*********************************************
	*  turnDisplayMiscProcessingInformationOn  *
	*********************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_misc_processing_information = TRUE;
	}

	/*************************************************
	*  turnDisplayMiscProcessingInformationOff  *
	*************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_misc_processing_information = FALSE;
	}

/*********************************************
*  displayMessageProcessingInformation  *
*********************************************/

//	DB_VERB_REP_MSGS        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayMessageProcessingInformation( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_message_processing_information )	{
		return DB_VERB_REP_MSGS;
	}
	return FALSE;

}

	/*************************************************
	*  turnDisplayMessageProcessingInformationOn  *
	*************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_message_processing_information = TRUE;
	}

	/*************************************************
	*  turnDisplayMessageProcessingInformationOff  *
	*************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_message_processing_information = FALSE;
	}

/*************************************************
*  displayClientSynchronizationInformation  *
*************************************************/

//	DB_VERB_REP_SYNC        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayClientSynchronizationInformation( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_client_synchronization_information )	{
		return DB_VERB_REP_SYNC;
	}
	return FALSE;

}

	/*****************************************************
	*  turnDisplayClientSynchronizationInformationOn  *
	*****************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_client_synchronization_information = TRUE;
	}

	/*****************************************************
	*  turnDisplayClientSynchronizationInformationOff  *
	*****************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_client_synchronization_information = FALSE;
	}

/*************************************************
*  displayManagerConnectionFailureInformation  *
*************************************************/

//	DB_VERB_REPMGR_CONNFAIL 	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_manager_connection_failure_information )	{
		return DB_VERB_REPMGR_CONNFAIL;
	}
	return FALSE;
}

	/*********************************************************
	*  turnDisplayManagerConnectionFailureInformationOn  *
	*********************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_connection_failure_information = TRUE;
	}

	/*********************************************************
	*  turnDisplayManagerConnectionFailureInformationOff  *
	*********************************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_connection_failure_information = FALSE;
	}

/*************************************
*  displayManagerMiscProcessing  *
*************************************/

//	DB_VERB_REPMGR_MISC     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL RPbdb_ReplicationVerbositySettingsController_displayManagerMiscProcessing( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_manager_misc_processing )	{
		return DB_VERB_REPMGR_MISC;
	}
	return FALSE;	
}

	/*****************************************
	*  turnDisplayManagerMiscProcessingOn  *
	*****************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOn( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_misc_processing = TRUE;
	}

	/*********************************************
	*  turnDisplayManagerMiscProcessingOff  *
	*********************************************/

	void RPbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOff( RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

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
RPbdb_ReplicationVerbositySettingsController* RPbdb_ReplicationVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	RPbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller_copy	=	RPbdb_ReplicationVerbositySettingsController_new( replication_verbosity_settings_controller->parent_replication_settings_controller );

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

