typedef void (*FuncPtr)(int);
typedef int (*chain_func)(const char * ,const char *);

struct handler
{
	const char *str;
	chain_func action_func;
	chain_func cmp_func;
};

enum RetrunType {SUCCESS, FAILURE};
enum RetrunType status;

void Print (int a)
{
	printf("The int value is: %d \n", a);
}

int CmpFunc(const char *input_str, const char *str)
{
	assert(NULL != input_str);
	assert(NULL != str);
	
	status = FAILURE;

	while('\0' != *input_str && *input_str == *str)
	{
		++input_str;
		++str;
	}
	
	if (0 == *input_str - *str)
	{
		status = SUCCESS;
	}
	
	else
	{
		status = FAILURE;
	}
	
	return status;
}

int CmpFuncDef(const char *input_str, const char *str) /* should be func name AlwaysMatch  */
{	
	status = SUCCESS;	
	return status;
}

int AddToStartCmp(const char *input_str, const char *str)
{
	assert(input_str != NULL);
	assert(str != NULL);
	
	if ('<' == *input_str)
	{
		status = SUCCESS;	
	}
	
	else
	{
		status = FAILURE;
	}
	
	return status;
}

int Default(const char *file_name, const char *input_str) /* should say what the func does AppenedToFile */
{
	FILE *fp;
	status = SUCCESS;
	
	assert(NULL != file_name);
	assert(NULL != input_str);
	
	fp = fopen(file_name, "a");
	
	if (NULL == fp)
    {
        printf("Could not open file %s", file_name);
        status = FAILURE;
    }
  
    fputs(input_str, fp);
		
	if (ferror(fp)) 
	{
    printf("Error1 in reading from "
           "file: %s\n", file_name);
    }
    	
	fputs("\n", fp);
		
	if (ferror(fp)) 
	{
    printf("Error2 in reading from "
           "file: %s\n", file_name);
    }
   
    fclose(fp);

    return status;	
}

int AddToHeadOfFile(const char *file_name, const char *input_str) /* can do optimize sol: w input on new file get from original remove the original and change name of new to original */ /* also should cut in to smaller functions like MakeNewFile CpyToFile RemoveFile  */
{
	FILE *fp;
	FILE *tmp_file;
	char ch;
	++input_str;
	status = SUCCESS;
	
	printf("entered to < func\n");
	assert(NULL != file_name);
	assert(NULL != input_str);
	
	fp = fopen(file_name, "r");
	tmp_file = fopen("tmp.txt", "w");
	
	if (NULL == fp || NULL == tmp_file)
    {
        printf("\nUnable to open file.\n");	/* should close the fp and put perror() and OPEN_FILE_ERR */
        exit(-1);
    }
    
    fputs(input_str, tmp_file);
    fputs("\n", tmp_file);
    
    ch = fgetc(fp);
    
    while (EOF != ch)
    {
    	fputc(ch, tmp_file);
    	ch = fgetc(fp);
    }
    
	fclose(fp);
	fclose(tmp_file);
    
    fp = fopen(file_name, "w");
    tmp_file = fopen("tmp.txt", "r");
    
    if (NULL == fp || NULL == tmp_file)
    {
        printf("\nUnable to open file.\n");
        status = FAILURE;
    }
    
    ch = fgetc(tmp_file);
    
    while (EOF != ch)
    {
    	fputc(ch, fp);
    	ch = fgetc(tmp_file);
    }
	
    fclose(fp);
    fclose(tmp_file);
   
    printf("Finish copy string and appending files\n");
  
    remove("tmp.txt");

	return status;
}

int CountLines(const char *file_name, const char *str)
{
	FILE *fp;
	size_t count = 0;
	char c = '\0';
	status = SUCCESS;
	
	assert(NULL != file_name);
	assert(NULL != str);
	
	fp = fopen(file_name, "r");
	
		
	if (NULL == fp)
    {
        printf("Could not open file %s", file_name);  /* perror*/ 
        status = FAILURE; /* OPEN_FILE_ERR */
    }
    
    for (c = getc(fp); EOF != c; c = getc(fp))  /* can do while (EOF != c) */
    {	
    	if ('\n' == c)
    	{
    		++count;
    	}
    }
    
    fclose(fp);
    
    printf("The file %s has %li lines\n", file_name, count); /* need if failed to close status = CLOSE_FILE_ERR */

    return status;	
}

int RemoveFile(const char *file_name, const char *str)
{	

	assert(NULL != file_name);
	assert(NULL != str);
	
	if (remove(file_name) == 0)
	{
    	printf("Deleted SUCCESSfully\n"); 
		status = SUCCESS;
    }
    
   	else
   	{
    	printf("Unable to delete the file\n"); /* perror("fail to remove"); */
    	status = FAILURE; /* should make more statuses like REMOVE_ERROR */
    }
   	return status;
}

int ExitFile(const char *input_str, const char *str)
{
	status = SUCCESS
	exit(0);
}

int Master(const char *file) /* should be *file_name for better understanding */
{
	char input_str[100]; /* MAX_INPUT_SIZE and define it on top */
	size_t i = 0;
	/* should be outside or be initialize with malloc */
	struct handler hand_arr[5] = 
	{ 
		{"-exit", &ExitFile, &CmpFunc},
		{"-count", &CountLines, &CmpFunc},
		{"-remove", &RemoveFile, &CmpFunc},
		{"<", &AddToHeadOfFile, &AddToStartCmp},
		{"default", &Default, &CmpFuncDef}
	};
	
	assert(NULL != file);
	
	while(1)
	{
		printf("Please enter a string, write \"-exit\" for exit\n");
		scanf("%s", input_str); /* fgets(input, MAX_INPUT_SIZE, stdin); */
		
		for (i = 0; i < 5; ++i)
		{
			
			if(0 == ((*(hand_arr[i].cmp_func))(input_str, (char *) hand_arr[i].str))) /* no need deref(*) and it's const, no need to cast */
			{
				(*hand_arr[i].action_func)(file, input_str);
				i = 5;      /* To break the loop can put break or add && in the for () loop line */
			}
	
		}
	}
	return status;
}




