#include<stdio.h>
#include<conio.h>


int main()
{
	int process,res,x,y,k,instance,total_resource,c1=0,c2=1;
	int instance_resource[res],available_resource[res],max_need[process][res],allocated_resource[process][res],need_resource[process][res],completed[process];
	printf("ENTER THE NUMBER OF PROCESS :");
	scanf("%d",&process);//entering the total number of process
	printf("\nPROCESS CREATED ARE\n");
	for(x=0;x<process;x++)
	{
		printf("%d) P%d\n",x+1,x);
	}
	printf("\nENTER THE NUMBER OF RESOURCES :");
	scanf("%d",&res);//enter the total number of resources
	printf("\nRESOURCES ARE\n");
	for(x=0;x<res;x++)
	{
		printf("%d) R%d\n",x+1,x);
	}
	for(x=0;x<process;x++)
	{
		completed[x]=0;//not the single process is executed completely
	}
	printf("\nENTER THE NUMBER OF INSTANCE PER RESOURCE\n");
	for(x=0;x<res;x++)
	{
		printf("R%d : ",x);
		scanf("%d",&instance);
		instance_resource[x]=instance;
	}
	printf("\nENTER THE MAXIMUM RESOUECES REQUIRED BY EACH PROCESS TO EXECUTE\n");
		for(x=0;x<process;x++)
		{
			printf("\nFor P%d: \n",x);
			for(y=0;y<res;y++)
			{
				printf("R%d: ",y);
		        scanf("%d",&instance);
		        max_need[x][y]=instance;
		    }
		}
	printf("\nENTER THE NUMBER OF RESOURCES ALLOCATED TO THE PROCESS\n");
		for(x=0;x<process;x++) {
			printf("\nFor P%d: \n",x);
			for(y=0;y<res;y++)
		   {
				printf("R%d: ",y);
		    	scanf("%d",&instance);
		    	a:
		    	if(instance<=max_need)
		    	{
		        	allocated_resource[x][y]=instance;
		        }
		        else
		        {
		        	printf("RE-ENTER THE VALUE\n");
		        	printf("R%d: ",y);
		    		scanf("%d",&instance);
		        	goto a;
				}
                          need_resource[x][y]=max_need[x][y]-allocated_resource[x][y];//Calculating the Need of each process
		    }
		}
		printf("\nAVAILABLE RESOURCE ARE\n");
	for(y=0;y<res;y++) {
		total_resource=0;
			for(x=0;x<process;x++) {
				total_resource+= allocated_resource[x][y];
		    }
available_resource[y]=instance_resource[y]-total_resource;
			printf("R%d : %d\n",y,available_resource[y]);
		}
		printf("\nCHECKING THE SYSTEM IS IN SAFE OR UNSAFE STATE\n <");
	while(c2!=0)
	{
		c2=c1;
		for(x=0;x<process;x++)
		{
		    k=0;
			for(y=0;y<res;y++)
			{
				if(need_resource <= available_resource)
				{
					k++;
				}
			}
			if(k==res && completed[x]==0)
				{
					printf(" P%d ",x);
					completed[x]=1;
				}
			for(y=0;y<res;y++)
			{

				available_resource[y]=available_resource[y] + allocated_resource[x][y];
			}
			c1++;
		}
		printf(" >\n");
		if(c1=process)
			{
				printf("\nALL PROCESS EXECUTED.. SYSTEM IS IN SAFE STATE\n");
				break;
			}
			else if(c1<process && c1 !=c2)
			{
				printf("\nSOME PROCESS IS EXECUTE AND SOME ARE NOT EXECUTE SO IT IS IN UNSAFE STATE\n");
				break;
			}
			else
			{
				printf("\nNONE OF THE PROCESS IS EXICUTE IN THE SYSTEM HENCE DEADLOCK OCCURE\n");
				break;
			}
	}
	getch();
	return 0;
}
