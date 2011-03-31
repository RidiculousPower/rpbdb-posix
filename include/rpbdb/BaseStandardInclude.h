
//	RPbdb Universal Standard Include: included by every RPbdb base type.

#ifndef RPBDB_BASE_STANDARD_INCLUDE
	#define RPBDB_BASE_STANDARD_INCLUDE
	
	//	calloc and malloc
	#include <stdlib.h>

	//	BDB Types
	#include <db.h>

	//	RPbdb Types
	#include "Types.h"

	//	RPbdb Constants
	#include "Constants.h"
	
	//	Error handling
	#include "ErrorController.h"
	#include "ErrorController_internal.h"
	#include "Error.h"
	#include "Error_internal.h"

#endif