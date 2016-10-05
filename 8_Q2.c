#include <stdlib.h>
#include <stdio.h>

struct node{
	int data;
	struct node *next;
}*front,*rear,*temp,*front1,*top,*top1,*temp1;

//Queue Operations
int frontelement_queue();
void push();
int pop();
void create_queue();
void queuesize();


int q_count = 0;


//Graph representations
int number_of_vertices = 0;
struct node *adj_list[100],*ptr,*temp2;
void read_graph();
void dfs();

//Utility Lists and Operations
int parentMap[100] = {-1};
struct node *visited_list = NULL;
struct node *ptr2;
void add_to_visited(int data);
int is_element_in_visited(int data);

int main()
{
	printf("Enter number of vertices:");
	int n;
	scanf("%d",&n);
	number_of_vertices = n;
	read_graph();
	printf("%s\n","Enter the goal:");
	scanf("%d",&n);
	dfs(1,n);
}


void create()
{
	front = rear = NULL;
}

void push(int data)
{
	if(top == NULL)
	{
		top = (struct node*)malloc(1*sizeof(struct node));
		top->next = NULL;
		top->data = data;
	}
	else
	{
		temp = (struct node*)malloc(1*sizeof(struct node));
		temp->data = data;
		temp->next = top;
		top = temp;
	}
	q_count++;
}

int pop()
{
	int ans;
	if(top == NULL)
	{
		printf("%s","Queue underflow ERROR");
	}
	else
	{
		temp1 = top;
		top = top->next;
		ans = temp1->data;
		free(temp);
	}
	q_count --;
	return ans;
}

void read_graph()
{
	int i,j;
	for( i=1;i<=number_of_vertices;i++)
	{
		for(j = 1; j <= number_of_vertices; j++)
		{
			if(i == j)
				continue;
			printf("Is vertex %d adjacent to vertex %d (1/0)?",i,j);
			int c;
			scanf("%d",&c);
			if(c == 1)
			{
				temp2 = (struct node*)malloc(1*sizeof(struct node));
				temp2->data = j;
				temp2->next = NULL;
				if(adj_list[i] == NULL)
					adj_list[i] = temp2;
				else
				{
					ptr = adj_list[i];
					while(ptr->next != NULL)
						ptr = ptr->next;

					ptr->next = temp2;
				}
			}
		}
	}
}

void add_to_visited(int data)
{
	ptr2 = visited_list;
	if(ptr2 == NULL)
	{
		ptr2 = (struct node*)malloc(1*sizeof(struct node));
		ptr2->data = data;
		ptr2->next = NULL;
	}
	else
	{
		while(ptr != NULL)
			ptr2 = ptr2->next;
		ptr2 = (struct node*)malloc(1*sizeof(struct node));
	}
}

int is_in_visited(int data)
{
	ptr2 = visited_list;
	if(ptr2 == NULL)
		return 0;
	while(ptr2 != NULL)
	{
		if(ptr2->data == data)
			return 1;
		ptr2 = ptr2->next;
	}
	return 0;
}

void dfs(int root,int goal)
{
	push(root);
	while(q_count != 0)
	{
		int v = pop();
		if(v == goal)
			break;
		if(!(is_in_visited(v)))
		{
			add_to_visited(v);
			ptr = adj_list[v];
			while(ptr != NULL)
			{
				push(ptr->data);
				if(!(is_in_visited(ptr->data)))
				{
					parentMap[ptr->data] = v;
					ptr = ptr->next;
				}
				//printf("%s\n","ADD ELEMENT TO QUEUE" );
			}
		}
	}
	int curr = goal;
	if(parentMap[curr] == -1)
	{
		printf("%s","NO PATH");
		return;
	}
	printf("%d-",curr);
	while(!(parentMap[curr] == -1))
	{
		if(curr == root)
			break;
		printf("%d-",parentMap[curr]);
		curr = parentMap[curr];
	}
	return;
}