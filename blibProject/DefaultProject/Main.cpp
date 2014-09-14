#include "blib.h"
#include "BaseProject.h"

using namespace blib;

int32_t main(int32_t argc, char* argv[]){	
	int32_t result=FAIL;											

	BaseProject project;											//subclass Project, overload at least the Run function
	
	if(project.Init(argc,argv)==SUCCESS)			//project initialize with program arguments
		result=project.Run();										//project main, return value returned to program.
	
	return result;														
}
