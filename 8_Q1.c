#include <stdlib.h>
#include <stdio.h>

struct node{
	int data;
	struct node *next;
}*front,*rear,*temp,*front1;

//Queue Operations
int frontelement_queue();
void enq();
int deq();
void create_queue();
void queuesize();


int q_count = 0;


//Graph representations
int number_of_vertices = 0;
struct node *adj_list[100],*ptr,*temp2;
void read_graph();
void bfs();

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
	bfs(1,n);
}


void create()
{
	front = rear = NULL;
}

void enq(int data)
{
	if(rear == NULL)
	{
		rear = (struct node*)malloc(1*sizeof(struct node));
		rear->next = NULL;
		rear->data = data;
		front = rear;
	}
	else
	{
		temp = (struct node*)malloc(1*sizeof(struct node));
		temp->next = NULL;
		temp->data = data;
		rear -> next = temp;
		rear = rear->next;
	}
	q_count++;
}

int deq()
{
	int ans;
	if(front == NULL)
	{
		printf("%s","Queue underflow ERROR");
	}
	else if(front == rear)
	{
		front1 = front;
		ans = front1->data;
		front = front->next;
		free(front1);
		rear = front;
	}
	else
	{
		front1 = front;
		ans = front1->data;
		front = front -> next;
		free(front1);
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

void bfs(int root,int goal)
{
	enq(root);
	while(q_count != 0)
	{
		int v = deq();
		if(v == goal)
			break;
		if(!(is_in_visited(v)))
		{
			add_to_visited(v);
			ptr = adj_list[v];
			while(ptr != NULL)
			{
				enq(ptr->data);
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