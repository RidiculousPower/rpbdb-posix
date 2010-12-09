/*
 *		Rbdb::SettingsController::SettingsVerbosityController::SettingsVerbosityReplicationController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "Rbdb_ReplicationVerbositySettingsController.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

Rbdb_ReplicationVerbositySettingsController* Rbdb_ReplicationVerbositySettingsController_new( Rbdb_ReplicationSettingsController* replication_settings_controller )	{

	Rbdb_ReplicationVerbositySettingsController*		replication_verbosity_settings_controller = calloc( 1, sizeof( Rbdb_ReplicationVerbositySettingsController ) );

	replication_verbosity_settings_controller->parent_replication_settings_controller = replication_settings_controller;

	return replication_verbosity_settings_controller;
}

/***************************
*  free  *
***************************/
void Rbdb_ReplicationVerbositySettingsController_free(	Rbdb_ReplicationVerbositySettingsController** replication_verbosity_settings_controller )	{

	free( replication_verbosity_settings_controller );
}

/***************************************
*  parentEnvironment  *
***************************************/
Rbdb_Environment* Rbdb_ReplicationVerbositySettingsController_parentEnvironment(	Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
	return replication_verbosity_settings_controller->parent_replication_settings_controller->parent_settings_controller->parent_environment;
}

/*****************************************
*  displayAllReplicationInformation  *
*****************************************/

//	DB_VERB_REPLICATION     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayAllReplicationInformation( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_all_replication_information )	{
		return DB_VERB_REPLICATION;
	}
	
	return FALSE;
}

	/*********************************************
	*  turnDisplayAllReplicationInformationOn  *
	*********************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
		
		replication_verbosity_settings_controller->display_all_replication_information = TRUE;
	}

	/*************************************************
	*  turnDisplayAllReplicationInformationOff  *
	*************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayAllReplicationInformationOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{
		
		replication_verbosity_settings_controller->display_all_replication_information = FALSE;
	}

/*********************************
*  displayElectionInformation  *
*********************************/

//	DB_VERB_REP_ELECT    		http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayElectionInformation( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_election_information )	{
		return DB_VERB_REP_ELECT;
	}
	return FALSE;
}

	/*****************************************
	*  turnDisplayElectionInformationOn  *
	*****************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_election_information = TRUE;
	}

	/*****************************************
	*  turnDisplayElectionInformationOff  *
	*****************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayElectionInformationOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_election_information = FALSE;
	}

/*************************************************
*  displayReplicationMasterLeaseInformation  *
*************************************************/

//	DB_VERB_REP_LEASE       	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayReplicationMasterLeaseInformation( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_replication_master_lease_information )	{
		return DB_VERB_REP_LEASE;
	}
	return FALSE;	
}

	/*****************************************************
	*  turnDisplayReplicationMasterLeaseInformationOn  *
	*****************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_replication_master_lease_information = TRUE;
	}

	/*********************************************************
	*  turnDisplayReplicationMasterLeaseInformationOff  *
	*********************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayReplicationMasterLeaseInformationOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_replication_master_lease_information = FALSE;
	}

/*****************************************
*  displayMiscProcessingInformation  *
*****************************************/

//	DB_VERB_REP_MISC        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayMiscProcessingInformation( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_misc_processing_information )	{
		return DB_VERB_REP_MISC;
	}
	return FALSE;

}

	/*********************************************
	*  turnDisplayMiscProcessingInformationOn  *
	*********************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_misc_processing_information = TRUE;
	}

	/*************************************************
	*  turnDisplayMiscProcessingInformationOff  *
	*************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayMiscProcessingInformationOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_misc_processing_information = FALSE;
	}

/*********************************************
*  displayMessageProcessingInformation  *
*********************************************/

//	DB_VERB_REP_MSGS        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayMessageProcessingInformation( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_message_processing_information )	{
		return DB_VERB_REP_MSGS;
	}
	return FALSE;

}

	/*************************************************
	*  turnDisplayMessageProcessingInformationOn  *
	*************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_message_processing_information = TRUE;
	}

	/*************************************************
	*  turnDisplayMessageProcessingInformationOff  *
	*************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayMessageProcessingInformationOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_message_processing_information = FALSE;
	}

/*************************************************
*  displayClientSynchronizationInformation  *
*************************************************/

//	DB_VERB_REP_SYNC        	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayClientSynchronizationInformation( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_client_synchronization_information )	{
		return DB_VERB_REP_SYNC;
	}
	return FALSE;

}

	/*****************************************************
	*  turnDisplayClientSynchronizationInformationOn  *
	*****************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_client_synchronization_information = TRUE;
	}

	/*****************************************************
	*  turnDisplayClientSynchronizationInformationOff  *
	*****************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayClientSynchronizationInformationOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_client_synchronization_information = FALSE;
	}

/*************************************************
*  displayManagerConnectionFailureInformation  *
*************************************************/

//	DB_VERB_REPMGR_CONNFAIL 	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayManagerConnectionFailureInformation( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_manager_connection_failure_information )	{
		return DB_VERB_REPMGR_CONNFAIL;
	}
	return FALSE;
}

	/*********************************************************
	*  turnDisplayManagerConnectionFailureInformationOn  *
	*********************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_connection_failure_information = TRUE;
	}

	/*********************************************************
	*  turnDisplayManagerConnectionFailureInformationOff  *
	*********************************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerConnectionFailureInformationOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_connection_failure_information = FALSE;
	}

/*************************************
*  displayManagerMiscProcessing  *
*************************************/

//	DB_VERB_REPMGR_MISC     	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/env_set_verbose.html
BOOL Rbdb_ReplicationVerbositySettingsController_displayManagerMiscProcessing( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	if ( replication_verbosity_settings_controller->display_manager_misc_processing )	{
		return DB_VERB_REPMGR_MISC;
	}
	return FALSE;	
}

	/*****************************************
	*  turnDisplayManagerMiscProcessingOn  *
	*****************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOn( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

		replication_verbosity_settings_controller->display_manager_misc_processing = TRUE;
	}

	/*********************************************
	*  turnDisplayManagerMiscProcessingOff  *
	*********************************************/

	void Rbdb_ReplicationVerbositySettingsController_turnDisplayManagerMiscProcessingOff( Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

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
Rbdb_ReplicationVerbositySettingsController* Rbdb_ReplicationVerbositySettingsController_internal_copyOfSettingsControllerForInstance(	Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller )	{

	Rbdb_ReplicationVerbositySettingsController* replication_verbosity_settings_controller_copy	=	Rbdb_ReplicationVerbositySettingsController_new( replication_verbosity_settings_controller->parent_replication_settings_controller );

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

