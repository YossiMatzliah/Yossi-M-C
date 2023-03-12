#include <stdio.h>	/* printf */
#include <dlfcn.h>	/* dl open, dl close, dlsym */
#include <stddef.h>	/* NULL */

#include "include.h"

int x = 7;

int main()
{
	void *handler_lib = NULL;
	void (*func_ptr)();
	

	
	handler_lib = dlopen("libsrc.so", RTLD_LAZY);
	
	if(NULL == handler_lib)
	{
		printf("failed to open library\n");
		
		return 0;
	}  
	
	*(void **)(&func_ptr) = dlsym(handler_lib, "Foo3");
	
	func_ptr();
	
	printf("The address of x after dlopen : %p\n", &x);

	dlclose(handler_lib);
	
	return 0;
}
