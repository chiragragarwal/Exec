#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#include "HEADER.h"
#include "function.c"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("\nIMPROPER NUMBER OF ARGUMENTS ! EXITING NOW\n");
		exit(0);
	}
	
	function(argv);
	printf("\n\n-----------ENDING THE MAIN PROCESS. BYE ---------------------\n\n");
	return 0;

}
