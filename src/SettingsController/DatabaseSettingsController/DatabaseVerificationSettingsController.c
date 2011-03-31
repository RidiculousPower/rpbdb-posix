/*
 *		RPbdb::Database::DatabaseSettingsController::DatabaseVerificationSettingsController
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "DatabaseVerificationSettingsController.h"

#include "ErrorController.h"
#include "Environment.h"

#include "DatabaseVerificationSettingsController_internal.h"
	
/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPbdb_DatabaseVerificationSettingsController* RPbdb_DatabaseVerificationSettingsController_new( RPbdb_DatabaseSettingsController* database_settings_controller )	{

	RPbdb_DatabaseVerificationSettingsController*		database_verification_settings_controller = calloc( 1, sizeof( RPbdb_DatabaseVerificationSettingsController ) );

	database_verification_settings_controller->parent_database_settings_controller = database_settings_controller;

	return database_verification_settings_controller;
}

/***************************
*  free  *
***************************/
void RPbdb_DatabaseVerificationSettingsController_free(	RPbdb_DatabaseVerificationSettingsController** database_verification_settings_controller )	{

	//	Make sure file is open so we don't close a closed file.
	if ( ( *database_verification_settings_controller )->file_is_open )	{

		fclose( ( *database_verification_settings_controller )->file );
		( *database_verification_settings_controller )->file_is_open	=	FALSE;
		( *database_verification_settings_controller )->file			=	NULL;
	}

	free( *database_verification_settings_controller );
	*database_verification_settings_controller	=	NULL;
}

/***************************************
*  parentEnvironment  *
***************************************/
RPbdb_Environment* RPbdb_DatabaseVerificationSettingsController_parentEnvironment(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	return database_verification_settings_controller->parent_database_settings_controller->parent_database->parent_database_controller->parent_environment;
}

/***************************************
*  parentDatabase  *
***************************************/
RPbdb_Database* RPbdb_DatabaseVerificationSettingsController_parentDatabase(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	return database_verification_settings_controller->parent_database_settings_controller->parent_database;
}

/*************
*  file  *
*************/

FILE* RPbdb_DatabaseVerificationSettingsController_file(	RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller )	{
	
	return database_verification_settings_controller->file;
}

/*****************
*  setFile  *
*****************/

void RPbdb_DatabaseVerificationSettingsController_setFile(	RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
															FILE*											data_output_file )	{
	
	database_verification_settings_controller->file = data_output_file;
}

/*****************
*  filePath  *
*****************/

char* RPbdb_DatabaseVerificationSettingsController_filePath(	RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller )	{
	
	return database_verification_settings_controller->file_path;
}

/*********************
*  setFilePath  *
*********************/

void RPbdb_DatabaseVerificationSettingsController_setFilePath(	RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
																char*											data_output_file_path )	{
	
	database_verification_settings_controller->file_path = data_output_file_path;
}

/**********************************
*  aggressiveKeyDataPairDump  *
**********************************/

//	DB_AGGRESSIVE						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPbdb_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->aggressive_key_data_pair_dump )	{
		return DB_AGGRESSIVE;
	}
	return FALSE;
}

	/******************************************
	*  turnAggressiveKeyDataPairDumpOn  *
	******************************************/

	void RPbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOn( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->aggressive_key_data_pair_dump = TRUE;
	}

	/******************************************
	*  turnAggressiveKeyDataPairDumpOff  *
	******************************************/

	void RPbdb_DatabaseVerificationSettingsController_turnAggressiveKeyDataPairDumpOff( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->aggressive_key_data_pair_dump = FALSE;
	}

/******************************
*  printableCharacters  *
******************************/

//	DB_PRINTABLE						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPbdb_DatabaseVerificationSettingsController_printableCharacters( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->printable_characters )	{
		return DB_PRINTABLE;
	}
	return FALSE;
}

	/**********************************
	*  turnPrintableCharactersOn  *
	**********************************/

	void RPbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOn( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->printable_characters = TRUE;
	}

	/**********************************
	*  turnPrintableCharactersOff  *
	**********************************/

	void RPbdb_DatabaseVerificationSettingsController_turnPrintableCharactersOff( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->printable_characters = FALSE;
	}

/**********************
*  skipOrderCheck  *
**********************/

//	DB_NOORDERCHK						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPbdb_DatabaseVerificationSettingsController_skipOrderCheck( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	if ( database_verification_settings_controller->skip_order_checking )	{
		return DB_NOORDERCHK;
	}
	return FALSE;
}

	/******************************
	*  turnSkipOrderCheckOn  *
	******************************/

	void RPbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOn( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->skip_order_checking = TRUE;

		//	If we are skipping order check then we aren't doing only an order check (although next we will)
		RPbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff( database_verification_settings_controller );
	}

	/******************************
	*  turnSkipOrderCheckOff  *
	******************************/

	void RPbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOff( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->skip_order_checking = FALSE;
	}

/**********************
*  onlyOrderCheck  *
**********************/

//	DB_NOORDERCHK						http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
BOOL RPbdb_DatabaseVerificationSettingsController_onlyOrderCheck( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	//	Assumes we have already done a check without order checking
	if ( database_verification_settings_controller->only_order_check )	{
		return DB_ORDERCHKONLY;
	}
	return FALSE;
}

	/******************************
	*  turnOnlyOrderCheckOn  *
	******************************/

	void RPbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOn(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

		database_verification_settings_controller->only_order_check = TRUE;
	
		//	If we haven't already done an unordered check, don't do an order check unless we are explicitly forcing it. 
		if (	! database_verification_settings_controller->force_order_check 
			&&	! database_verification_settings_controller->has_done_unordered_check )	{
		
			RPbdb_ErrorController_throwError(	RPbdb_Environment_errorController(	database_verification_settings_controller->parent_database_settings_controller->parent_settings_controller->parent_environment ),
																				-1,
																				"DatabaseVerificationSettingsController_onlyOrderCheck",
																				"Must first perform check while skipping order or force ordered check explicitly (may cause corruption)." );
		}
	
		//	Skipping order check can't also be true
		RPbdb_DatabaseVerificationSettingsController_turnSkipOrderCheckOff( database_verification_settings_controller );
	}

	/******************************
	*  turnOnlyOrderCheckOff  *
	******************************/

	void RPbdb_DatabaseVerificationSettingsController_turnOnlyOrderCheckOff( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	
		database_verification_settings_controller->only_order_check = FALSE;
	}

/**************************
*  forceOrderCheck  *
**************************/

BOOL RPbdb_DatabaseVerificationSettingsController_forceOrderCheck(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	return database_verification_settings_controller->force_order_check;
}

	/******************************
	*  turnForceOrderCheckOn  *
	******************************/

	void RPbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOn(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
		database_verification_settings_controller->force_order_check = TRUE;
	}

	/******************************
	*  turnForceOrderCheckOff  *
	******************************/

	void RPbdb_DatabaseVerificationSettingsController_turnForceOrderCheckOff(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
		database_verification_settings_controller->force_order_check = FALSE;
	}

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																Internal Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*******************************
*  hasDoneUnorderedCheck  *
*******************************/
	
void RPbdb_DatabaseVerificationSettingsController_internal_hasDoneUnorderedCheck( 	RPbdb_DatabaseVerificationSettingsController*	database_verification_settings_controller, 
																					int												on_or_off )	{
	
	database_verification_settings_controller->has_done_unordered_check = on_or_off;
}

/*********************
*  verifyFlags  *
*********************/

//	http://www.oracle.com/technology/documentation/berkeley-db/db/api_c/db_verify.html
int RPbdb_DatabaseVerificationSettingsController_internal_verifyFlags( RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{
	//	Make sure we return DB_SALVAGE if a file exists
	return	( database_verification_settings_controller->file ? DB_SALVAGE : 0 )
			|	RPbdb_DatabaseVerificationSettingsController_aggressiveKeyDataPairDump(			database_verification_settings_controller )
			|	RPbdb_DatabaseVerificationSettingsController_printableCharacters(	database_verification_settings_controller ) 
			|	RPbdb_DatabaseVerificationSettingsController_skipOrderCheck(		database_verification_settings_controller ) 
			|	RPbdb_DatabaseVerificationSettingsController_onlyOrderCheck(		database_verification_settings_controller );
}

/*******************************************
*  copyOfSettingsControllerForInstance  *
*******************************************/
RPbdb_DatabaseVerificationSettingsController* RPbdb_DatabaseVerificationSettingsController_internal_copyOfSettingsControllerForInstance(	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller )	{

	RPbdb_DatabaseVerificationSettingsController* database_verification_settings_controller_copy	=	RPbdb_DatabaseVerificationSettingsController_new( database_verification_settings_controller->parent_database_settings_controller );

	//	Instances and Pointers
	database_verification_settings_controller_copy->aggressive_key_data_pair_dump	=	database_verification_settings_controller->aggressive_key_data_pair_dump;
	database_verification_settings_controller_copy->file_path	=	database_verification_settings_controller->file_path;
	database_verification_settings_controller_copy->force_order_check	=	database_verification_settings_controller->force_order_check;
	database_verification_settings_controller_copy->only_order_check	=	database_verification_settings_controller->only_order_check;
	database_verification_settings_controller_copy->skip_order_checking	=	database_verification_settings_controller->skip_order_checking;
	database_verification_settings_controller_copy->printable_characters	=	database_verification_settings_controller->printable_characters;
	database_verification_settings_controller_copy->has_done_unordered_check	=	database_verification_settings_controller->has_done_unordered_check;
	database_verification_settings_controller_copy->file_is_open	=	database_verification_settings_controller->file_is_open;
	database_verification_settings_controller_copy->file	=	database_verification_settings_controller->file;

	return database_verification_settings_controller_copy;
}

