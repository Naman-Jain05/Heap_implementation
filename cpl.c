//BT20CSE087
#include <stdio.h>
#include <stdlib.h>

struct free //free block
{
	int tag;
	int size;
	struct free* next;
};

struct alloc //alloc block
{
	int id;
	int tag;
	int size;
	struct alloc* next;
};

void print_free(struct free* free_head)
{
	struct free* p = free_head;
	printf("\n");
	printf("free_block_Tag\tfree_block_Size\n");
	
	while (p != NULL)
	{
		printf("  %d\t\t%d\n",p->tag,p->size);
		p = p->next;
	}
	printf("\n");
}

void print_alloc(struct alloc* alloc_head)
{
	struct alloc* p = alloc_head;
	printf("\n");
	printf("process_Tag\tfree_Block_Tag\tprocess_Size\n");
	while (p != NULL)
	{
		printf("  %d\t\t  %d\t\t  %d\n",p->tag,p->id,p->size);
		p = p->next;
	}
	printf("\n");
}

void create_free(int s,struct free** free_hea)
{
	struct free* free_head=*free_hea;
	static int free_counter=0;
	
	struct free* p = (struct free*) malloc(sizeof(struct free));
	p->size = s;
	p->tag = free_counter;
	p->next = NULL;
	
	struct free* temp = free_head;
	if (free_head == NULL)
	{
		free_head = p;	
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = p;
	}
	
	free_counter++;
	*free_hea=free_head;
}

void create_alloc(int s,struct alloc** alloc_hea,struct free* free_head)
{
	struct alloc* alloc_head=*alloc_hea;
	static int alloc_counter=0;
	
	struct alloc* q = (struct alloc*) malloc(sizeof(struct alloc));
	q->size = s;
	q->tag = alloc_counter;
	q->next = NULL;
	
	struct free* p = free_head;
	struct free* r = (struct free*) malloc(sizeof(struct free));
	r->size = 8193;
	
	struct alloc* temp = alloc_head;
	while (p != NULL) 
	{
		if (q->size <= p->size) 
		{
			if (p->size < r->size)
			{
				r = p; //finding min space which fits the required space 
			}
		}
		p = p->next;
	}
	
	if (r->size != 8193) 
	{
		q->id = r->tag; //allocating the process tag the free block id
		r->size -= q->size; //removing allocated space from free block
		if (alloc_head == NULL)
		{
			alloc_head = q;
		}
		else 
		{
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = q; //adding process at end in alloc list
		}
		
		alloc_counter++;
	}
	else
	{
		printf("Block with size %d can't be allocated\n\n",s);
	}
	
	*alloc_hea=alloc_head;
}

void create_allocf(int s,struct alloc** alloc_hea,struct free* free_head)
{
    struct alloc* alloc_head=*alloc_hea;
	static int alloc_counterf=0;
	
    struct alloc* q = (struct alloc*) malloc(sizeof(struct alloc));
    q->size = s;
    q->tag = alloc_counterf;
    q->next = NULL;
    
    struct free* p = free_head;
	struct alloc* temp = alloc_head;
	
    while (p != NULL) 
	{
        if (q->size <= p->size)
        {
        	break;	
		}
        p = p->next;
    }

    if (p != NULL) 
	{
        q->id = p->tag;
        p->size -= q->size;
        if (alloc_head == NULL)
        {
        	alloc_head = q;
		}
        else 
		{
         	while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = q; //adding process at end in alloc list   
        }
        alloc_counterf++;
    }
    else
    {
    	printf("Block with size %d can't be allocated\n\n",s);
	}
        
            
    *alloc_hea=alloc_head;        
}

void delete_alloc(int t,struct alloc** alloc_hea,struct free** free_hea)
{
	struct alloc* alloc_head=*alloc_hea;
	struct free* free_head=*free_hea;
	
	struct alloc *p = alloc_head, *q = NULL;
	while (p != NULL)
	{
		if (p->tag == t)
		{
			break;
		}
		q = p;
		p = p->next;
	}
	
	if (p == NULL)
	{
		printf("Process_tag doesn't exist\n");
	}
	else if (p == alloc_head)
	{
		alloc_head = alloc_head->next;
	}
	else
	{
		q->next = p->next;
	}
		
	struct free* temp = free_head;
	while (temp != NULL) 
	{
		if (temp->tag == p->id) 
		{
			temp->size += p->size; //merging free blocks and restoring the free space
			break;
		}
		temp = temp->next;
	}
	free(p);
	
}

int main()
{
	struct free* free_head=NULL;
	struct alloc* alloc_head=NULL;
	
	int n,i,m=10,choice=0;
	int blockSize[] = { 16,32,64,128,256,512,1024,2048,4096,8192 };
	
	/*assume these are the free space available in heap at different locations
	and in between heap is filled with different other data*/
	
	for (i=0;i<m;i++)
	{
		create_free(blockSize[i],&free_head);
	}
	
	printf("Enter number of processes:");
	scanf("%d",&n);
	int processSize[n];
	printf("\nEnter size of each process:\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&processSize[i]);
	}
	
	printf("\npress 0 to allocate by best fit and 1 to allocate by first fit:\n");
	scanf("%d",&choice);
	if(choice==0)
	{
		for (i=0;i<n;i++)
		{
		create_alloc(processSize[i],&alloc_head,free_head);
		}
	}
	else
	{
		for (i=0;i<n;i++)
		{
		create_allocf(processSize[i],&alloc_head,free_head);
		}
	}
	
	
	printf("\nfree list after allocation:\n");
	print_free(free_head);
	
	printf("\nallocation list:\n");
	print_alloc(alloc_head);
	
	delete_alloc(2,&alloc_head,&free_head);
	printf("\nalloc list after deleting block with process_tag=2:\n");
	print_alloc(alloc_head);
	print_free(free_head);
}
