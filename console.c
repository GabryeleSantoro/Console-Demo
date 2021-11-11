#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define maxDim 6

char *getString()
{
	char str[100];
	char *str2;

	fgets(str,100,stdin);
	if(fgets == NULL)
		return NULL;
	str[strlen(str)-1] = '\0';

	str2 = malloc(sizeof(char)*strlen(str));

	strcpy(str2,str);

	return str2;
}

void cutString(char *in, char *arr[maxDim])
{
	int i = 0;

	char *app = strtok(in," ");

	while(app != NULL)
	{
		arr[i] = app;
		i++;
		app = strtok(NULL," ");
	}

	arr[i] = NULL;
}

int main()
{
	int child1, status;
	char *in;

	char *arr[maxDim];

	do
	{

		memset(arr,0,maxDim);
		printf("%%");
		in = getString();

		if(in == NULL)
			exit(1);

		cutString(in,arr);

		child1 = fork();

		if(child1 < 0)
			printf("Error fork");

		else if (child1 == 0)
		{
			if(execvp(arr[0],arr) < 0)
				if(strcmp(arr[0],"exit") !=0)
					printf("Error I can't execute\n");

		}
		else
		{
			waitpid(child1,&status,0);
		}
	}while(strcmp(arr[0],"exit") != 0);
}
