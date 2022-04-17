//  BT20CSE087  Naman Jain
/* simulation */

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define size 8		//in our diagram total 8 nodes

struct node	
{
       
    struct node *link1;	
    struct node *link2;
    struct node *link3;		//atmost 3 links in our given diagram
    
     int data;		//value
    int refCount;	//refrence count
    bool mark;		//extra mark bit

    
};

struct node *ptr[size];		//array pointer for each node

void display_node(int i)
{
	printf("value=%d\t refrence-count=%d freed-size=%d\n",ptr[i]->data,ptr[i]->refCount,sizeof(struct node));
}

void set(int so,int dest1,int dest2,int dest3)	//set edges  within vertices
{
	if(dest1!=-1)
	{
		ptr[so]->link1=ptr[dest1];
		ptr[dest1]->refCount+=1;
	}
	if(dest2!=-1)
	{
		ptr[so]->link2=ptr[dest2];
		ptr[dest2]->refCount+=1;
	}
	if(dest3!=-1)
	{
		ptr[so]->link3=ptr[dest3];
		ptr[dest3]->refCount+=1;
	}
	
}

void display_all(struct node* root)		//display all nodes which are connected through root
{
	if(root!=NULL)
	{
		printf("val=%d, refrence-count=%d\n",root->data,root->refCount);
	}
	if(root==NULL)
	{
		return;
	}
	display_all(root->link1);
	display_all(root->link2);
	display_all(root->link3);
}

void adj_list()		//adjacency list for each node
{
	int i=0;
	for(i=0;i<size;i++)
	{
		
	if(ptr[i]!=NULL)
	{
	
	printf("val=%d, ->: ",ptr[i]->data);
	if(ptr[i]->link1!=NULL)
	{
		printf("%d ->",ptr[i]->link1->data);
	}
	if(ptr[i]->link2!=NULL)
	{
		printf("%d ->",ptr[i]->link2->data);
	}
	if(ptr[i]->link3!=NULL)
	{
		printf("%d ->",ptr[i]->link3->data);
	}
	printf("NULL\n");
	
	}
	
	}
	
}

int isroot(struct node* root1, struct node* temp)	//check if a node temp is connected through root
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->data==temp->data)
	{
		return 1;
	}
	
	if(isroot(root1->link1,temp))
	{
		return 1;
	}
	
	if(isroot(root1->link2,temp))
	{
		return 1;
	}
	if(isroot(root1->link3,temp))
	{
		return 1;
	}
 return 0;
}

void gc_refcounting(struct node* root)		//refrence counting
{
	int i=0;
	while(i<size)
	{
		if(isroot(root,ptr[i])==0 )			//if refrence count is 0 delete that node
		{		
			if(ptr[i]->link1!=NULL)
			{
				ptr[i]->link1->refCount-=1;		//remove links connected by it and update refrence count of its child node also
			}
			if(ptr[i]->link2!=NULL)
			{
				ptr[i]->link2->refCount-=1;		//remove links connected by it and update refrence count of its child node also
			}
			if(ptr[i]->link3!=NULL)
			{
				ptr[i]->link3->refCount-=1;		//remove links connected by it and update refrence count of its child node also
			}
			
			printf("garbage:");
			display_node(i);
			free(ptr[i]);					//freeing garbage
			ptr[i]=NULL;
		}
		 i++;		
	}
	 
}

void Matrix()		//Adjacency matrix for nodes
{
	int adm[size][size];
	int i,j,k;
	
	for(i=0;i<size;i++)		//initialising all elements to 0
	{
		for(j=0;j<size;j++)
		{
			adm[i][j]=0;
		}	
	}
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			
		if(ptr[j]!=NULL&&ptr[i]!=NULL)
		{
			
			if(ptr[i]->link1!=NULL)
			{
				if(ptr[i]->link1->data==ptr[j]->data&&i!=j)		//if there is edge set array element to 1
				{
					adm[i][j]=1;
				}
			}
			if(ptr[i]->link2!=NULL)
			{
				if(ptr[i]->link2->data==ptr[j]->data&&i!=j)		//if there is connection set array element to 1
				{
					adm[i][j]=1;
				}
			}
			if(ptr[i]->link3!=NULL)
			{
				if(ptr[i]->link3->data==ptr[j]->data&&i!=j)		//if there is connection set array element to 1
				{
					adm[i][j]=1;
				}
			}
		}
		
		}
	}
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%d ",adm[i][j]);		//printing matrix
		}
		printf("\n");
	}
}

void markNodes(struct node *root)		//mark nodes by morris traversal(based on thread binary tree)
{
    struct node *current, *pre;

    current = root;
        
    while (current != NULL) 
    {
  
        if (current->link1== NULL) 
        {
            current->mark=true;
            current = current->link2;
        }   
        else 
        {
            pre = current->link1;
            while ((pre->link2 != NULL) && (pre->link2 != current))
            {
            	pre = pre->link2;
			}
                
            if (pre->link2 == NULL) 
            {
                pre->link2 = current;
                current = current->link1;
            }
            else 
            {
                pre->link2 = NULL;
                current->mark=true;
                current = current->link2;
            } 
        }
    }   
    
    current = root;
        
    while (current != NULL) 
    {
  
        if (current->link1== NULL) 
        {
            current->mark=true;
            current = current->link3;
        }   
        else 
        {
            pre = current->link1;
            while ((pre->link3 != NULL) && (pre->link3 != current))
            {
            	pre = pre->link3;
			}
                
            if (pre->link3 == NULL) 
            {
                pre->link3 = current;
                current = current->link1;
            }
            else 
            {
                pre->link3 = NULL;
                current->mark=true;
                current = current->link3;
            } 
        }
    }  
    
}

void mark_root_nodes(struct node* root )		// marks via root and using array of pointers
{
	int i;
	while(i<8)
	{
		if(isroot(root,ptr[i])==1 )
		{			
          ptr[i]->mark=true;
		}
		 i++;		
	}	 
}

void marks(struct node* root)		//marking nodes by recursion
{
	
	if(root!=NULL)
	{
		root->mark=true;
	}
	if(root==NULL)
	{
		return;
	}
	marks(root->link1);
	marks(root->link2);
	marks(root->link3);
}

void sweep()		//sweeping unmarked nodes(garbage)
{
	int i;
	for(i=0;i<size;i++)
	{
		if(ptr[i]->mark==false)
		{
			if(ptr[i]->link1!=NULL)
			{
				ptr[i]->link1->refCount-=1;
			}
			if(ptr[i]->link2!=NULL)
			{
				ptr[i]->link2->refCount-=1;
			}
			if(ptr[i]->link3!=NULL)
			{
				ptr[i]->link3->refCount-=1;
			}
			
			printf("garbage:");
			display_node(i);
			free(ptr[i]);		//freeing garbage
			ptr[i]=NULL;
		}
	}
	
	for(i=0;i<size;i++)
	{
		if(ptr[i]!=NULL)
		{
			ptr[i]->mark=false;		//reseting all the marked bits
		}
	}
}

int main()
{
	
	//node number  		   	   0,1,2,3,4,5,6,7	
	/*value*/		int val[]={1,2,3,5,7,8,9,10};
	
	
	int i;
	
	for( i=0;i<8;i++)									//initialising nodes
	{
		struct node* newNode = malloc(sizeof(struct node));		
		newNode->data=val[i];		//setting value in nodes
		newNode->link1=NULL;
		newNode->link2=NULL;
		newNode->link3=NULL;
		newNode->refCount=0;		//initially refrence count is 0
		newNode->mark=false;		//initially all bits are unmarked
		ptr[i]=newNode;
	}
	
	struct node* root1=ptr[3];		//connecting through root
	ptr[3]->refCount+=1;
	struct node* root2=ptr[0];
	ptr[0]->refCount+=1;
	
	set(0,1,6,7);	//1 to 2, 1 to 9, 1 to 10				//setting connections(edges)
	set(2,5,7,-1);	//3 to 8, 3 to 10
	set(3,0,-1,-1);	//5 to 1
	set(4,0,5,-1);	//7 to 1, 7 to 8
	set(5,6,-1,-1);	//8 to 9
	
	printf("\nall nodes through root1:\n");
	display_all(root1);
	
	printf("\n\nadj list:\n");
	adj_list();
	
	printf("\n\nadj matrix:\n");
	Matrix();
	
	/*printf("\n--------------------------------------------------------------------------");
	printf("\ncalling refrence count garbage collector\n");
	printf("-------------------------------------------------------------------------\n\n");
	gc_refcounting(root1);
	
	printf("\nall nodes through root1:\n");
	display_all(root1);
	
	printf("\n\nadj list after removal of garbage:\n");
	adj_list();
	
	printf("\n\nadj matrix after removal of garbage:\n");
	Matrix();*/
	
	printf("\n--------------------------------------------------------------------------------");
	printf("\ncalling mark sweep garbage collector\n");
	printf("-------------------------------------------------------------------------------\n\n");
	
	markNodes(root1);		//by moris traversal
	markNodes(root2);
	//mark_root_nodes(root1);	//by isroot function
	//mark_root_nodes(root2);	
	//marks(root1);			//by recursion
	//marks(root2);
	sweep();
	
	printf("\nall nodes through root1:\n");
	display_all(root1);
	
	printf("\n\nadj list after removal of garbage:\n");
	adj_list();
	
	printf("\n\nadj matrix after removal of garbage:\n");
	Matrix();
	
	return 0;
	
}


	
	
