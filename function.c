void function(char **argv)
{
	FILE *f;
		
	f = fopen(argv[1],"r");
	
	fscanf(f,"%d",&n);
	
	arrA = (myArray *)malloc(n*sizeof(myArray));
	arrB = (myArray *)malloc(n*sizeof(myArray));	
	
	for(i=0;i<n;i++)
	{
		flag = 0;
		
		fscanf(f,"%s\t",com1);
		fscanf(f,"%s\t",com2);
		fscanf(f,"%s\t",path);
		fscanf(f,"%[^\n]s",options);

		temp = strcmp(com2,"-");
		if(temp!=0)		//Dependency exists
		{
			check = search(arrA,countA,com2);
			if(check == -1)
			{
				check = search(arrB, countB, com2);
				
				if(check == -1)
					flag = 99;	//not found in both
				else
					flag =	1;	//found in B
			}
			
			if(flag == 0 || flag == 1)
			{
				if(flag==0)	// arrA
				{
					strcpy(arrA[countA].cmd,com1);
					strcpy(arrA[countA].path,path);
					strcpy(arrA[countA].options,options);
					countA++;	
					continue;
				}
				else	//arrB
				{
					strcpy(arrB[countB].cmd,com1);
					strcpy(arrB[countB].path,path);
					strcpy(arrB[countB].options,options);
					countB++;
					continue;
				}
			}
		}
		
		if(temp == 0 || flag == 99)
		{
			flag = 0;
			
			if(countA <= countB)
			{
				strcpy(arrA[countA].cmd,com1);
				strcpy(arrA[countA].path,path);
				strcpy(arrA[countA].options,options);
				countA++;
				continue;
			}
			else
			{
				strcpy(arrB[countB].cmd,com1);
				strcpy(arrB[countB].path,path);
				strcpy(arrB[countB].options,options);
				countB++;
				continue;
			}
		}
	
	}	//end of FOR loop
	
	fclose(f);
	
	varA = fork();
	if(varA==0)
	{
		for(i=0;i<countA;i++)
		{
			arg_count = 1;
			childA = fork();
			if(childA == 0)
			{
				new_path = arrA[i].path;
				
				p = arrA[i].options;
				arg_exec[0] = arrA[i].cmd;
				
				if(strcmp(arrA[i].options,"NULL") != 0)
				{
					while(*p != '\0')	//tokenization of options string
					{
						new = strtok(p," ");
						arg_exec[arg_count] = new;
						arg_count++;
						for(j=0;j<=strlen(new);j++)
							p++;
					}
				}
				
				arg_exec[arg_count]='\0';
					
				if(strcmp(new_path,"-") != 0)
				{
					strcat(new_path,"/");
					strcat(new_path,arrA[i].cmd);
				
					printf("\n----- i = %d ; CHILD PROCESS for arrA ; ' %s '------\n",i,arrA[i].cmd);
					execv(new_path,arg_exec);
					printf("i = %d ; Exec Failed !! ; arrA \n",i);
					exit(2);
				}
				else
				{
					strcpy(new_path,"/bin/");
					strcat(new_path,arrA[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/sbin/");
					strcat(new_path,arrA[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/etc/");
					strcat(new_path,arrA[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/home/usr/");
					strcat(new_path,arrA[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/usr/bin/");	//for the WHO command
					strcat(new_path,arrA[i].cmd);
					execv(new_path,arg_exec);
					printf("i = %d ; Exec Failed !! ; arrA \n",i);
					
					exit(2);
				}
			}	//end of child
			
			wait(NULL);	//parent
			
		}	//for loop
		exit(1);
	}
	
	varB = fork();
	if(varB==0)
	{
		for(i=0;i<countB;i++)
		{
			arg_count = 1;
			childB = fork();
			if(childB == 0)
			{
				new_path = arrB[i].path;
				
				p = arrB[i].options;
				arg_exec[0] = arrB[i].cmd;
				
				if(strcmp(arrB[i].options,"NULL") != 0)
				{
					while(*p != '\0')	//tokenization of options string
					{
						new = strtok(p," ");
						arg_exec[arg_count] = new;
						arg_count++;
						for(j=0;j<=strlen(new);j++)
							p++;
					}
				}
				
				arg_exec[arg_count]='\0';
					
				if(strcmp(new_path,"-") != 0)
				{
					strcat(new_path,"/");
					strcat(new_path,arrB[i].cmd);
					
					printf("\n----- i = %d ; CHILD PROCESS for arrB ; ' %s '------\n",i,arrB[i].cmd);
					execv(new_path,arg_exec);
					printf("i = %d ; Exec Failed !! ; arrB\n",i);
					exit(2);
				}
				else
				{
					strcpy(new_path,"/bin/");
					strcat(new_path,arrB[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/sbin/");
					strcat(new_path,arrB[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/etc/");
					strcat(new_path,arrB[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/home/chirag/");
					strcat(new_path,arrB[i].cmd);
					execv(new_path,arg_exec);
					
					strcpy(new_path,"/usr/bin/");
					strcat(new_path,arrB[i].cmd);
					execv(new_path,arg_exec);
					printf("i = %d ; Exec Failed !! ; arrB \n",i);
					
					exit(2);
				}
			}	//end of child
			
			wait(NULL);	//parent
			
		}	//for loop
		exit(2);
	}
	
	while(wait(NULL) != -1);

return;
}
