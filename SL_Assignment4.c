#include<stdio.h>
#include<stdlib.h>
// Structure for free node list
typedef struct free_node
{
    int size;
    struct free_node* next;
}F_list;
F_list *F_head = NULL,*F_prev = NULL;

// Structure for allocated list
typedef struct alloc_node
{
    int size;
	struct alloc_node* next;
}alloc_list;
alloc_list *A_head=NULL,*A_prev =NULL;

// Creating a free list
void create_free_list(int data)
{
	F_list* F = (F_list*)malloc(sizeof(F_list));
	F->size = data;
	F->next = NULL;
	if(F_head == NULL)
	{
		F_head = F;
	}
	else
    {
		F_prev->next = F;
	}
	F_prev = F;
}
// printing free list
void print_free_list()
{
    F_list *F = F_head;
    printf("Free list\n");
    while (F != NULL)
    {
    	printf("%d\n",F->size);
        F = F->next;
    }
}
// creating a allocated list
// first fit algorithm 
void create_allocated_list(int data)
{
    alloc_list *A = (alloc_list *)malloc(sizeof(alloc_list));
    A->size = data;
    A->next = NULL;
    F_list *F = F_head;
    while (F != NULL)
    {
        if (A->size <= F->size)
            break;
        F = F->next;
    }

    if (F != NULL)
    {
        F->size -= A->size;
        if (A_head == NULL)
        {
            A_head = A;
        }
        else
        {
            A_prev = A_head;
            while (A_prev->next != NULL)
            {
                A_prev = A_prev->next;
            }
            A_prev->next = A;
        }
    }
	else
    {
		printf("Block of size %d can't be allocated\n",data);
	}

}
void print_allocated_list()
{
	alloc_list* A = A_head;
	printf("Process Size\n");
	while(A!= NULL)
	{
		printf("%d\n",A->size);
		A = A->next;
	}
}
// Standard delete function
void delete_allocated_list(int data)
{
    alloc_list *A = A_head, *B = NULL;
    F_list *temp = F_head;
    while (A != NULL)
    {
        if(A->size == data)
        {
            break;
        }
        B = A;
        A = A->next;
    }
    if (A == NULL)
    {
         printf(" Block with mentioned Space doesn't exist\n");
    }
    else if (A == A_head)
    {
        A_head = A_head->next;
        temp->size += data;
    }
    else
    {
        B->next = A->next;
        temp->size += data;
    }
}
int main()
{
    int i,b,p;
    printf("enter the number of block sizes of the memory : \n");
    scanf("%d",&b);
    int block_size[b];
    printf("enter the block sizes of the memory : \n");
    for ( i = 0; i < b; i++)
    {
        scanf("%d",&block_size[i]);
    }
    printf("enter the number of process sizes of the memory :\n");
    scanf("%d",&p);
    int process_size[p];
    printf("enter the process sizes of the memory : \n");
    for (i = 0; i < p; i++)
    {
        scanf("%d", &process_size[i]);
    }
    for(i=0;i<b;i++)
    {
		create_free_list(block_size[i]);
	}
    print_free_list();
	for(i=0;i<p;i++)
	{
		create_allocated_list(process_size[i]);
	}
    print_allocated_list();
    printf("Free list after allocation\n");
    print_free_list();
    int n;
    printf("Enter the size to be deleted:\n");
    scanf("%d",&n);
    delete_allocated_list(n);
    printf("List after deleting\n");
    print_allocated_list();
    print_free_list();
    return 0;
}