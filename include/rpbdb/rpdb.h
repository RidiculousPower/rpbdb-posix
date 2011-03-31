#ifndef RPBDB
	#define RPBDB
	
	//	Standard includes for users of RPbdb
	
	#include "BaseStandardInclude.h"
	
	//	Types and Constants
	#include "Types.h"
	#include "Constants.h"

	//	Main - version info, etc.
	#include "main.h"
	
	//	Environment
	#include "Environment.h"
	
	//	Database
	#include "DatabaseController.h"
		#include "Database.h"
			#include "DatabaseCursorController.h"
				#include "DatabaseCursor.h"
	
	//	Error
	#include "ErrorController.h"
		#include "Error.h"
	
	//	Records, Data, Keys
	#include "Record.h"
	#include "Data.h"
	#include "Key.h"
	
	//	Runtime Storage
	#include "RuntimeStorageController.h"
		#include "RuntimeStorage.h"
	
	//	Settings
	#include "SettingsController.h"
		#include "DatabaseSettingsController.h"
			#include "DatabaseAssociationSettingsController.h"
			#include "DatabaseCursorSettingsController.h"
				#include "DatabaseCursorReadWriteSettingsController.h"
			#include "DatabaseErrorSettingsController.h"
			#include "DatabaseRecordReadWriteSettingsController.h"
			#include "DatabaseRecordSettingsController.h"
			#include "DatabaseTypeSettingsController.h"
				#include "DatabaseTypeBtreeSettingsController.h"
		#include "DirectorySettingsController.h"
		#include "ErrorSettingsController.h"
		#include "FileSettingsController.h"
		#include "MemoryPoolSettingsController.h"
		
#endif