/*
 *		RPDB::RPDB_DatabaseController::RPDB_Database::(RPDB_DatabaseCursorController::RPDB_DatabaseCursor::)RPDB_Record::RPDB_DBT => RPDB_SecondaryKeys
 *
 *
 */

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Headers
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

#include "RPDB_SecondaryKeys.h"

#include "RPDB_Key.h"
#include "RPDB_Key_internal.h"
#include "RPDB_Data.h"
#include "RPDB_Data_internal.h"

/*******************************************************************************************************************************************************************************************
********************************************************************************************************************************************************************************************
																		Public Methods
********************************************************************************************************************************************************************************************
*******************************************************************************************************************************************************************************************/

/*************
*  new  *
*************/

RPDB_SecondaryKeys* RPDB_SecondaryKeys_new( RPDB_Record* parent_record )	{

	RPDB_SecondaryKeys*	secondary_keys	=	calloc( 1, sizeof( RPDB_SecondaryKeys ) );
	
	secondary_keys->parent_record	=	parent_record;
	
	//	Alloc the DBT
	secondary_keys->wrapped_bdb_dbt	=	calloc( 1, sizeof( DBT ) );

	return secondary_keys;
}

/***************************
*  free  *
***************************/
void RPDB_SecondaryKeys_free(	RPDB_SecondaryKeys** keys )	{

	free( *keys );
	*keys	=	NULL;
}

/***************************************
*  parentRecord  *
***************************************/
RPDB_Record* RPDB_SecondaryKeys_parentRecord(	RPDB_DatabaseRecordSettingsController* key )	{
	return key->parent_record;
}

/*****************
*  keyData  *
*****************/

void RPDB_SecondaryKeys_addSecondaryKey(	RPDB_SecondaryKeys*	keys,
 											RPDB_Key*				key )	{

	//	allocate a new pointer of count *  wrapped_bdb_dbt  * size (DBT**)
	RPDB_Key**	key_pointers_array	=	calloc( keys->key_count + 1, sizeof( RPDB_Key* ) );

	//	if we already have keys
	if ( keys->key_count > 0 )	{
	
		//	copy existing data over
		memcpy( key_pointers_array,
				keys->key_pointers_array,
				keys->key_count * sizeof( RPDB_Key* ) );

//			free memory space pointed to by the existing pointer
		free( keys->key_pointers_array );
	}
	
	//	store our new pointer
	keys->key_pointers_array	=	key_pointers_array;

	//	store address of existing dbt
	keys->key_pointers_array[ keys->key_count ]	=	key;

	//	increment key count for added key
	keys->key_count++;
}

/******************
*  setKeyData  *
******************/

RPDB_Key* RPDB_SecondaryKeys_secondaryKeyForIndex(	RPDB_SecondaryKeys*	keys,
														int						index )	{

	return (RPDB_Key*) RPDB_Data_internal_newrb_RPDB_DatabaseObject_internal_retrieveMultipleFromParameterDataArrayT( NULL, & ( (DBT*) keys->wrapped_bdb_dbt->data )[ index ] );
}


/*****************
*  keyData  *
*****************/

void RPDB_SecondaryKeys_addRawSecondaryKey(	RPDB_SecondaryKeys*	keys,
 												void*					raw_key,
 												uint32_t				key_size )	{

	//	allocate a new pointer of count *  wrapped_bdb_dbt  * size (DBT**)
	RPDB_Key**	key_pointers_array	=	calloc( keys->key_count + 1, sizeof( RPDB_Key* ) );

	//	if we already have keys
	if ( keys->key_count > 0 )	{
	
		//	copy existing data over
		memcpy( key_pointers_array,
				keys->key_pointers_array,
				keys->key_count * sizeof( RPDB_Key* ) );

//			free memory space pointed to by the existing pointer
		free( keys->key_pointers_array );
	}
	
	//	store our new pointer
	keys->key_pointers_array	=	key_pointers_array;

	//	allocate space for DBT at pointer location
	keys->key_pointers_array[ keys->key_count ]	=	RPDB_Key_new( NULL );

	//	store data in new DBT
	keys->key_pointers_array[ keys->key_count ]->wrapped_bdb_dbt->data = raw_key;
	keys->key_pointers_array[ keys->key_count ]->wrapped_bdb_dbt->size = key_size;

	//	increment key count for added key
	keys->key_count++;
}

/******************
*  setKeyData  *
******************/

void* RPDB_SecondaryKeys_rawSecondaryKeyForIndex(	RPDB_SecondaryKeys*	keys,
													int						index )	{

	return ( (DBT*)( keys->wrapped_bdb_dbt->data ) )[ index ].data;
}




