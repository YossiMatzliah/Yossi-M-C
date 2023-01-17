typedef void (*FuncPtr)(int);
typedef int (*chain_func)(const char * ,const char *);

struct handler
{
	const char *str;
	chain_func action_func;
	chain_func cmp_func;
};

enum RetrunType {success, failure};
enum RetrunType status;

void Print (int a)
{
	printf("The int value is: %d \n", a);
}

int CmpFunc(const char *input_str, const char *str)
{
	assert(NULL != input_str);
	assert(NULL != str);
	
	status = failure;

	while('\0' != *input_str && *input_str == *str)
	{
		++input_str;
		++str;
	}
	
	if (0 == *input_str - *str)
	{
		status = success;
	}
	
	else
	{
		status = failure;
	}
	
	return status;
}

int CmpFuncDef(const char *input_str, const char *str)
{	
	status = success;	
	return status;
}

int AddToStartCmp(const char *input_str, const char *str)
{
	assert(input_str != NULL);
	assert(str != NULL);
	
	if ('<' == *input_str)
	{
		status = success;	
	}
	
	else
	{
		status = failure;
	}
	
	return status;
}

int Default(const char *file_name, const char *input_str)
{
	FILE *fp;
	status = success;
	
	assert(NULL != file_name);
	assert(NULL != input_str);
	
	fp = fopen(file_name, "a");
	
	if (NULL == fp)
    {
        printf("Could not open file %s", file_name);
        status = failure;
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

int AddToHeadOfFile(const char *file_name, const char *input_str)
{
	FILE *fp;
	FILE *tmp_file;
	char ch;
	++input_str;
	status = success;
	
	printf("entered to < func\n");
	assert(NULL != file_name);
	assert(NULL != input_str);
	
	fp = fopen(file_name, "r");
	tmp_file = fopen("tmp.txt", "w");
	
	if (NULL == fp || NULL == tmp_file)
    {
        printf("\nUnable to open file.\n");
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
        status = failure;
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
	char c = 0;
	status = success;
	
	assert(NULL != file_name);
	assert(NULL != str);
	
	fp = fopen(file_name, "r");
	
		
	if (NULL == fp)
    {
        printf("Could not open file %s", file_name);
        status = failure;
    }
    
    for (c = getc(fp); EOF != c; c = getc(fp))
    {	
    	if ('\n' == c)
    	{
    		++count;
    	}
    }
    
    fclose(fp);
    
    printf("The file %s has %li lines\n", file_name, count);

    return status;	
}

int RemoveFile(const char *file_name, const char *str)
{	

	assert(NULL != file_name);
	assert(NULL != str);
	
	if (remove(file_name) == 0)
	{
    	printf("Deleted successfully\n");
		status = success;
    }
    
   	else
   	{
    	printf("Unable to delete the file\n");
    	status = failure;
    }
   	return status;
}

int ExitFile(const char *input_str, const char *str)
{
	exit(0);
}

void Master(const char *file)
{
	char input_str[100];
	size_t i = 0;
	
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
		scanf("%s", input_str);
		
		for (i = 0; i < 5; ++i)
		{
			
			if(0 == ((*(hand_arr[i].cmp_func))(input_str, (char *) hand_arr[i].str)))
			{
				(*hand_arr[i].action_func)(file, input_str);
				i = 5;      /* To break the loop */
			}
	
		}
	}
}




