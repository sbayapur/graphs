#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "seqpair.h"
void free_list(Node* head);

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Arguments do not match. Use input_file output_file"); 
		return EXIT_FAILURE;
	}
	double io_time;
	clock_t inputio,outputio;
 //	printf("%s",argv[1]);
    inputio = clock();
	Node* head = Load_Into_Tree(argv[1]);
	FILE* output =  fopen(argv[2], "wb");
	if(output == NULL)
	{
		printf("Error opening output file");
	}
    //print_list(head);
	save_coordinates(head, output);
	outputio= clock();
	io_time = (double)(outputio - inputio)/CLOCKS_PER_SEC;	
//	printf("\nI/O time:  %12.9e", io_time);
	fclose(output);
	free_list(head);
	return EXIT_SUCCESS;
}

void free_list(Node* head)
{
	if(head == NULL)
	{
		return;
	}

	while (head != NULL)
	{
	   Node* current = head;
	   head = head->next;
	   free(current);
	}

} 

