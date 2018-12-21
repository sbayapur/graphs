#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seqpair.h"
Node *BuildPacking(FILE* inFile, long size);
void print_list(Node *ptr);
void print_array(int arr[], int n);
double getWeight(int label, Node* head, char type);
int CommonValues(int arr1[], int arr2[], int m, int n, int cArray[]);
void Quick_Sort(int *Array, int Size);
void quickSortHelper(int* Array, int left,int right);


Node *Load_Into_Tree(char *Filename) 

{
	FILE *inFile;
	long size;
	Node *head = NULL;
 
	inFile = fopen(Filename, "rb");
    
	if(inFile == NULL)
	{
		printf("Error opening input file.");
		return NULL;
	}

	fseek(inFile, 0, SEEK_END);
	size = ftell(inFile);
	//printf("size:= %d\n", size);
	fseek(inFile, 0, SEEK_SET);
	rewind(inFile);
	head = BuildPacking(inFile, size);
   
	fclose(inFile);
	return head;

} 


Node *BuildPacking(FILE* inFile, long size)
{
	char *buffer = malloc(size * sizeof(char) + 1);
	char *buffer2 = malloc(size * sizeof(char) + 1);
	int label;
	double width = 0;
	double height = 0;
	int num_rectangles;
	getline(&buffer, &size, inFile);
	sscanf(buffer, "%d",&num_rectangles);
	//printf("num_rectangles:= %d\n", num_rectangles);
	int i;
	Node* head = NULL;
	Node* current = NULL;
	for(i=0; i < num_rectangles; i++)
    {
		getline(&buffer, &size, inFile);
     	sscanf(buffer, "%d(%le,%le)",&label, &width, &height);
		// printf("\nlabel:%d", label);
		//printf("\n%le", height);
		//printf("\n%le", width);
		Node* temp = malloc(sizeof(*temp)); 
		temp->label = label;
		temp->width = width;
		temp->height = height;
		temp->xcoor = 0;
		temp->ycoor = 0;
		temp->next = NULL;
		if(head == NULL)
		{
			head = temp;
			current = head;
        } 
	    else 
		{
			current->next = temp;
			current = current->next ;
        }	
		
	}
	//printf("\nHeadlabel:%d", head->label);
	
	getline(&buffer, &size, inFile);
	
	int seqpair1[num_rectangles];
	i = 0;
	const char s[2] = " ";
    char *token;
    token = strtok(buffer, s);
  
    while( token != NULL ) 
    {
		seqpair1[i]=atoi(token);
		i++;
		//printf( "%s\n", token );
		token = strtok(NULL, s);
    }
	
	

	int seqpair2[num_rectangles];
	getline(&buffer2, &size, inFile);
	
	i = 0;
    token = strtok(buffer2, s);
  

    while( token != NULL ) 
    {
		seqpair2[i]=atoi(token);
		i++;
		// printf( "%s\n", token );
		token = strtok(NULL, s);
    
    }

	int j;
	//print_list(head);
	for(i=0; i<num_rectangles; i++)
	{
		int leftArray[num_rectangles];
        int label = seqpair1[i];
		//printf("\nlabel %d", label);
		int intLeft[num_rectangles];
		int intLeft2[num_rectangles];
		int m =0;
		int k = 0;
		for(j=0; j<num_rectangles; j++)
		{ 
		    int label2 = seqpair1[j];
			//printf("\nlabel2 %d", label2);
     	    if(label != label2)
			{
				intLeft[m] = seqpair1[j];
				m++;
			}
			else
			{
			    break;
			}
		}
		int intLeftSize = m;

		for(j=0; j<num_rectangles; j++)
		{ 
		    int label3 = seqpair2[j];
			//printf("\nlabel3 %d", label3);
     	    if(label != label3)
			{
				intLeft2[k] = seqpair2[j];
				k++;
			}
			else
			{
			   break;
			}
		}
        int intLeft2Size = k;
		
	/*	printf("\nLeft1");
		print_array(intLeft, intLeftSize);
		printf("\nLeft2");
		print_array(intLeft2, intLeft2Size); */
		
		current = head;
		while(current != NULL)
		{
			int label1 = current->label;  
			double weight = 0;
			double currWeight = 0;
			// printf("\nlabel1: %d", label1);

			if (label1 == label)
			{
				int cSize = CommonValues(intLeft, intLeft2, intLeftSize, intLeft2Size, leftArray);
				//printf("\nsize: %d",  cSize);
				//print_array(leftArray, cSize); 
				if(cSize == 0) 
				{
					current->xcoor = 0;
				}
				else 
				{ 
					for(j =0; j < cSize; j++)
					{
						weight = getWeight(leftArray[j], head, 'w');
						//printf("\nweight: %le", weight);
						if(weight > currWeight)
						{
							current->xcoor = weight;
							currWeight = weight;
						}
					 
					 
					}
				}
				// printf("\nxcoor:%le",  current->xcoor);
				break;
			}
			current = current->next;
		}
		
	}
	
	
	for(i=0; i<num_rectangles; i++)
	{
		int label = seqpair2[i];
		//printf("\nlabel %d", label);
		int intRight[num_rectangles];
		int intLeft2[num_rectangles];
		
		int m =0;
		int bfound = 0;
		for(j=0; j<num_rectangles; j++)
		{ 
			int label2 = seqpair1[j];
			//printf("\nlabel2 %d", label2);
    		if(label == label2)
			{
				bfound = 1;
			}
			if(bfound == 1)
			{
				if(j+1 < num_rectangles)
				{
					intRight[m] = seqpair1[j+1];
					m++;
				}
			}
			/*else  // not needed
			{
				 intLeft[k] = seqpair1[j];
				 k++;
			} */
			
		}
		int intRightSize = m;

		int k = 0;
		for(j=0; j<num_rectangles; j++)
		{ 
		    int label3 = seqpair2[j];
			//printf("\nlabel3 %d", label3);
     	    if(label != label3)
			{
				intLeft2[k] = seqpair2[j];
				k++;
			}
			else
			{
			   break;
			}
		}
        int intLeft2Size = k;
		
		//printf("\nRight");
		//print_array(intRight, intRightSize);
		//printf("\nLeft2");
		//print_array(intLeft2, intLeft2Size); 
		
		
		current = head;
		while(current != NULL)
		{
			int label1 = current->label;
			double weight = 0;
			double currWeight = 0;
			//printf("\nlabel1: %c", label1);
			// printf("\nlabel %c", label);
			if (label1 == label)
			{
				int belowArray[num_rectangles];
				int cSize = CommonValues(intRight, intLeft2, intRightSize, intLeft2Size, belowArray);
				//printf("\nsizebelow: %d", cSize);
				//print_array(belowArray, cSize);
		
				if(cSize == 0) 
				{
					current->ycoor = 0;
				}
				else 
				{ 
					for(j =0; j < cSize; j++)
					{
						weight = getWeight(belowArray[j], head, 'h');
						//printf("\n weight: %le", weight);
						//printf("\n cweight: %le", currWeight);
						if(weight > currWeight)
						{
							// printf("\n setting weight");
							current->ycoor = weight; 
							currWeight = weight;
						}
					
					}
				}
				//printf("\nycoor:%le",  current->ycoor);
				break;
			}
			current = current->next;
		}
		
	}

    free(buffer);
	free(buffer2);
    return head;
}


int CommonValues(int array1[], int array2[], int m, int n, int cArray[])
{
	int i = 0, j = 0, size =0;
	Quick_Sort(array1, m);
	Quick_Sort(array2, n);
  
	while ((i < m) && (j < n))
    {
        if (array1[i] < array2[j])
        {
            i++;
        }
        else if (array1[i] > array2[j])
        {
            j++;
        }
        else
        {
            cArray[size] = array1[i];
            i++;
            j++;
            size++;
        }
    }
	return size;
}
	
	
double getWeight(int label, Node* head, char type)
{
	double wt = 0;
	while(head != NULL)
	{
	  
		int label1 = head->label;
		// printf("\nlabel1: %d", label1);
		// printf("\nlabel %d", label);
		if(label1 == label)
		{
			if(type == 'w')
			{
				wt = head->xcoor + head->width;
			}
			else
			{  
				// printf("\nlabelxxxx %c", label1);
				//printf("\n yco1: %le", head->ycoor);
				//printf("\n ht1: %le", head->height);
				wt = head->ycoor + head->height;
			}
			return wt;
		}
		head = head->next;
	  
	}
	return wt;
}	
	


void save_coordinates(Node* head, FILE* output)
{
    
	if (head == NULL)
		return;
		
	while(head != NULL)
	{
		//printf("%d(%le,%le)\n", head->label, head->xcoor, head->ycoor);
		fprintf(output, "%d(%le,%le)\n",head->label, head->xcoor, head->ycoor);
		head = head->next;
	}

} 

void print_list(Node *head)
{
    while(head != NULL)
    {
        printf("\n%d", head->label);
        head = head->next;
    }
}


void print_array(int arr[], int n)
{
	int i;
    for (i=0; i<n; i++)
	{
		printf("\n%d", arr[i]);
	}
}
	

void Quick_Sort(int *Array, int Size)
{	
	if(Size <=0)
	{
		//printf("\nQuicksort return. \n");
		return;
	}
    quickSortHelper(Array, 0, Size - 1);
	
}

void quickSortHelper(int* Array, int left,int right) 
{
	
	if (left >= right) 
	{
        return;
    }
    int i = left;
    int j = right;
    int pivotIndex = right;
    int pivot = Array[pivotIndex];

    //  arr[pivotIndex] = save;

    while (i < j) 
	{
        while (Array[i] < pivot) 
		{
            i++;
        }
        while (Array[j] > pivot) 
		{
            j--;
        }
        if (i <= j) 
		{
            long save1 = Array[i];
            Array[i] = Array[j];
            Array[j] = save1;
            i++;
            j--;
        }
    }
    if (left < j) 
	{
        quickSortHelper(Array, left, j);
    }
    if (i < right) {
        quickSortHelper(Array, i, right);
    }
	
}

