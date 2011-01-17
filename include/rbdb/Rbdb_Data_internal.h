/*
 *		Rbdb::Rbdb_DatabaseController::Rbdb_Database::(Rbdb_DatabaseCursorController::Rbdb_DatabaseCursor::)Rbdb_Record::RBDB_DBT => Rbdb_Data
 *
 *
 */

#ifndef RBDB_DATA_INTERNAL
	#define RBDB_DATA_INTERNAL

Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Data_internal_footer( Rbdb_Data* data );
void Rbdb_Data_internal_createFooter( Rbdb_Data* data );
void Rbdb_Data_internal_updateFooter( Rbdb_Data* data );
Rbdb_DataFooterTypeForVersion( Rbdb_DataFooterCurrentVersion )* Rbdb_Data_internal_upgradeFooter( Rbdb_Data*		data );
void Rbdb_Data_internal_addDataFooterToExistingRecord( Rbdb_Data* data __attribute__ ((unused)) );


#endif

