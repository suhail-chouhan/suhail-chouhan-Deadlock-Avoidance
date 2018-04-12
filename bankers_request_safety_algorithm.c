#include<stdio.h>
#include<conio.h>

int main() {
	int process;//for taking the number of process
	int resource;//for taking the number of resources
	int i,j;//iteration variables
	int instance;//variable to take input from user
	int ch;//switch case variable
	int total=0;//for resources adding purpose
	int k=0;//for checking the number of resources
	int c1=0,c2=0;//while loop variable
	int c;//to start the again the program


	printf("ENTER THE NUMBER OF PROCESS :");
	scanf("%d",&process); //Entering No. of Processes
	printf("\nPROCESS CREATED ARE\n");
	for(i=0;i<process;i++)
	{
		printf("%d) P%d\n",i+1,i);
	}


	printf("\nENTER THE NUMBER OF RESOURCES :");
	scanf("%d",&resource); //Entering No. of Resources
	for(i=0;i<resource;i++)
	{
		printf("%d) R%d\n",i+1,i);
	}

	int instance_resource[resource];//1D array containing instance of all variable
	int available_resource[resource];//1D array containing available number of instance of all the resources
	int max_need_resource[process][resource];//2D array containing maximum need of resources by all the process
	int allocated_resource[process][resource];//2D array containing allocated number of resources by all the process
	int need_resource[process][resource];//2D array containing need of resources by all the process
	int completed[process]; //containing the status of all the process
	int copy_available_resource[resource];//containing the out put of the available_resource

	for(i=0;i<process;i++)
		{completed[i]=0;} //Setting Flag for uncompleted Processes



	printf("\nENTER THE NUMBER OF INSTANCE PER RESOURCE\n");//entering the instance allocated with every resource
		for(i=0;i<resource;i++) {
			printf("R%d : ",i);
		    scanf("%d",&instance);
		    instance_resource[i]=instance; //storing the instance value in the instance_resource array
		}
	printf("\nINSTANCE ARE\n");//display the instance of resources
	for(i=0;i<resource;i++)
	{
		printf("R%d : %d\n",i,instance_resource[i]);
	}


	printf("\nENTER THE MAXIMUM RESOUECES REQUIRED BY EACH PROCESS TO EXECUTE\n");//entering maximum how much resources required to execute completely every porcess
		for(i=0;i<process;i++) {
			printf("\nFor P%d: \n",i);
			for(j=0;j<resource;j++) {
				printf("R%d: ",j);
		        scanf("%d",&instance);
		        max_need_resource[i][j]=instance;
		    }
		}
		printf("\nTHE MAXIMUM RESOURCES REQUIRED ARE\n");
	for(i=0;i<process;i++)
	{
		printf("FOR P%d :\n",i);
		for(j=0;j<resource;j++)
		{
			printf("R%d : %d\n",j,max_need_resource[i][j]);
		}
		printf("\n");
	}


	printf("\nENTER THE NUMBER OF RESOURCES ALLOCATED TO THE PROCESS\n"); //entering the initially allocated resources for the every process
			for(i=0;i<process;i++) {
			printf("\nFor P%d: \n",i);
			for(j=0;j<resource;j++) {
				printf("R%d: ",j);
		    	scanf("%d",&instance);
		        a:
		    	if(instance<=max_need_resource[i][j])//checking condition as the resource we input is always lesser then the maximum resource needed
		    	{
		        	allocated_resource[i][j]=instance;
		        }
		        else
		        {
		        	printf("RE-ENTER THE VALUE\n");
		        	printf("R%d: ",j);
		    		scanf("%d",&instance);
		        	goto a;
				}
		        need_resource[i][j]=max_need_resource[i][j]-allocated_resource[i][j]; //Calculating the need of each process
		    }
		}


		printf("\nTHE ALLOCATED RESOURCES ARE\n");
	for(i=0;i<process;i++)
	{
		printf("FOR P%d :\n",i);
		for(j=0;j<resource;j++)
		{
			printf("R%d : %d\n",j,allocated_resource[i][j]);
		}
		printf("\n");
	}



	printf("\nAVAILABLE RESOURCE ARE\n");//cheking the available resources
		for(j=0;j<resource;j++) {
		total=0;
			for(i=0;i<process;i++) {
				total+= allocated_resource[i][j];
		    }
			available_resource[j]=instance_resource[j]-total;
			printf("R%d : %d\n",j,available_resource[j]);
		}
		for(j=0;j<resource;j++)
        {
            copy_available_resource[j]=available_resource[j];
        }
printf("\nCHECKING THE SYSTEM IS IN SAFE OR UNSAFE STATE\n\n< ");//checking the system is in safe or in unsafe state
            while(c1!=process) {
	    	c2 = c1;
	    	for(i=0;i<process;i++) {
	       		for(j=0;j<resource;j++) {
	            	if(need_resource[i][j]<=available_resource[j]) // Checking if Need can be fulfilled
	                	k++;
	        	}
	        	if(k==resource && completed[i]==0 ) {
	           		printf("P%d ",i);
	           		completed[i]=1; // Setting flag for completed Process

	           		for(j=0;j<resource;j++) {
	            		available_resource[j]=available_resource[j]+allocated_resource[i][j]; //Updating instancesable Resources
	            	}
	            	c1++;
	         	}
	        	k=0;
	       	}
	        if(c1==c2) {
	        	printf("STOP ... Deadlock likely to happen!\n");
	        	break;
	       	}

	 	}
	 	printf(" >\n");
	 	printf("\nDO YOU WANT TO USE BANKER'S REQUEST ALGORITHM PRESS 1 OTHERWISE 0 : ");
	 	scanf("%d",&ch);
	 	if(ch == 1)
        {
            for(i=0;i<process;i++)
                {

                    completed[i]=0;
                }
               printf("\nENTER THE REQUEST\n");
				for(i=0;i<process;i++)
				{
					int y_n;
					printf("DO YOU WANT TO REQUEST FOR P%d PRESS 1 FOR YES 0 FOR NO :",i);
					scanf("%d",&y_n);
					if(y_n==1)
					{
						printf("ENTER THE REQUEST FOR P%d :\n\n",i);
						for(j=0;j<resource;j++)
						{
						    b:
						    printf("R%d :",j);
							scanf("%d",&instance);
							if(instance <= need_resource[i][j] && instance <=available_resource[j])
							{
								allocated_resource[i][j]+=instance;
								need_resource[i][j]-=instance;
								copy_available_resource[j]-=instance;
							}
							else
							{
								printf("\nRE-ENTER THE VALUE\n");
								goto b;
							}

						}
						for(j=0;j<resource;j++)
                    {
                        available_resource[j]=copy_available_resource[j];
                    }
            printf("\nCHECKING THE SYSTEM IS IN SAFE OR UNSAFE STATE\n\n< ");//checking the system is in safe or in unsafe state
            c1=0;
            while(c1!=process) {
	    	c2 = c1;
	    	for(i=0;i<process;i++) {
	       		for(j=0;j<resource;j++) {
	            	if(need_resource[i][j]<=available_resource[j]) // Checking if Need can be fulfilled
	                	k++;
	        	}
	        	if(k==resource && completed[i]==0 ) {
	           		printf("P%d ",i);
	           		completed[i]=1; // Setting flag for completed Process

	           		for(j=0;j<resource;j++) {
	            		available_resource[j]=available_resource[j]+allocated_resource[i][j]; //Updating instancesable Resources
	            	}
	            	c1++;
	         	}
	        	k=0;
	       	}
	       	for(i=0;i<process;i++)
            {
                if(completed[i] == 0)
                {

                    for(j=0;j<resource;j++)
                {
                    if(need_resource[i][j]<=available_resource[j]) // Checking if Need can be fulfilled
	                	k++;
	        	}
	        	if(k==resource && completed[i]==0 ) {
	           		printf("P%d ",i);
	           		completed[i]=1; // Setting flag for completed Process

	           		for(j=0;j<resource;j++) {
	            		available_resource[j]=available_resource[j]+allocated_resource[i][j]; //Updating instancesable Resources
	            	}
	            	c1++;
	         	}
	        	k=0;
                }
            }
	       	printf(" >\n");
	       	if(c1==process)
						{
							printf("ALL PROCESS EXECUTED.. SYSTEM IS IN SAFE STATE\n");
							break;
						}
						else if(c1<process && c1 != c2)
						{
							printf("SOME PROCESS IS EXECUTE AND SOME ARE NOT EXECUTE SO IT IS IN UNSAFE STATE\n");
							break;
						}
						else
						{
							printf("NONE OF THE PROCESS IS EXICUTE IN THE SYSTEM HENCE DEADLOCK OCCURE\n");
							break;
						}

	       	}


		}


					}

				}
getch();
	return 0;
}

