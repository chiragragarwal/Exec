typedef struct arrA{
	char cmd[10];
	char path[50];
	char options[20];
} myArray;

myArray *arrA, *arrB;
int n,i;
char com1[10], com2[10], path[50], options[20];
int countA = 0, countB = 0, temp, check, flag;
pid_t varA, varB, childA, childB;
char *new_path, *p, *new, *arg_exec[10];
int arg_count, j;

int search(myArray *a, int N, char *key)
{
	int i;
	for(i=0;i<N;i++)
	{
		if( strcmp(a[i].cmd,key) == 0)
			return i;		//return index of element
	}
	return -1;				//not found
}

extern void function(char **);
