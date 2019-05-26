#include <pthread.h>  // header file for threads
#include <stdio.h>   // header file for standard input and output.
#include <stdlib.h> // header file for functions involving memory allocation, process control, conversions and others
#include <unistd.h> //header file that provides access to the POSIX operating system API. (fork, pipe and I/O primitives [read, write, close, etc.] )
#include <errno.h>  //header file for error handling 
#include <math.h> //header file for math fast operations 

//hint 1: use struct to pass large number arrays
//hint 2: any function from math.h isn't required to complete this assignment
struct matrixData
{
    int i;//Row
    int j;//Column
};


void * multiplyer (void *);  //prototype for function multiplyer

int i=0;
int **mat1,**mat2,**result;
int main(int arg, char ** args)
{
	int k,l;
	//int num1;
	  pthread_t thr[3];
	FILE *file1=fopen(args[1],"r");
	FILE *file2=fopen(args[2],"r");
	if ( file1 == NULL ||file2 == NULL) 
            {   
              printf("Error!!!!dash dash Could not open file\n"); 
              exit(1); // must include stdlib.h 
            } 
	
	int x=0,y=0;
	mat1=(int **)malloc(3*sizeof(int *));
	mat2=(int **)malloc(3*sizeof(int *));
	result=(int **)malloc(3*sizeof(int *));
	for(int i=0;i<3;i++)
		mat1[i]=(int*)malloc(3*sizeof(int ));
	for(int i=0;i<3;i++)
		mat2[i]=(int*)malloc(3*sizeof(int ));
	for(int i=0;i<3;i++)
		result[i]=(int*)malloc(3*sizeof(int ));

        fscanf(file1,"%d",&mat1[x][y]);
	while(!feof(file1))
	{
         //printf("%d",mat1[x][y]);
        y++;
	if(y==3)
	{
	y=0;
	x++;
	} 	
	fscanf(file1,"%d",&mat1[x][y]);
	}
        
       printf("\n");
	
        x=0;y=0;
        fscanf(file2,"%d",&mat2[x][y]);
	while(!feof(file2))
	{
        // printf("%d",mat2[x][y]);
        y++;
	if(y==3)
	{
	y=0;
	x++;
	} 	
	fscanf(file2,"%d",&mat2[x][y]);
	} 
       
         printf("\n");


	
	for(l=0;l<3;l++)
	{
	
	
	struct matrixData *entry[3];//1 entry for each row
		for(k=0;k<3;k++)
		{           
       		 entry[k] = (struct matrixData *) malloc(sizeof(struct matrixData));//9 entries

       		 entry[k]->i =l; 
       		 entry[k]->j = k;
		}

         pthread_attr_t at;
         pthread_attr_init(&at);
	pthread_create( &thr[l],&at,multiplyer,(void*)&entry);
	//pthread_join(tid[l], NULL);
	}
	//for(int q=0; q < 3; q++)
         //  pthread_join(thr[q], NULL);

	

   	for (int  p= 0; p < 3; p++)
     	for (int k = 0; k < 3; k++)
       	 printf("%d\t", result[p][k]);

	
	printf("\nmain is ended \n");
   return 0;
}

void * multiplyer (void * arg)
{
	printf("\n executing thread # %d", i++ ); 
	struct matrixData *data = (struct matrixData *)arg;
    int l;
    for(l=0;l<3;l++)
    {
       int i=((struct matrixData)data[l]).i;
        int j=((struct matrixData)data[l]).j;
        int d;
	int sum=0;
        for (d = 0; d < 3; d++)
        {
            sum = sum + mat1[i][d]*mat2[d][j];
        }
        result[i][j] = sum;
        sum = 0;
    }
   
	
	
	 }
