#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define forn(i,a,n) for(int i=a;i<n;i++)
#define N 10000
FILE *fp;
FILE *fo;

struct queue
{
  int a[N];
  int size;
  int front;
  int rear;		
};

typedef struct queue queue;

int max_size;
struct queue* new_queue()
{
	struct queue *q;
	q=(struct queue*)malloc(sizeof(struct queue));
	q->front=0;
	q->rear=0;
    q->size=0;

    return q;
}

queue* enqueue(struct queue *q,int data)
{
	q->a[q->rear]=data;
	q->size=(q->size)+1;
	q->rear=q->rear+1;

    return q;	
}

queue* dequeue(struct queue *q)
{
	
		q->front=q->front+1;
		q->size=(q->size)-1;

     return q;  
}

int top(queue* q)
{
    return q->a[q->front];
}

struct vector
{
  int size;
  int capacity;
  int *arr;
};

typedef struct vector vector;

vector* new_vector()
{
    vector* v=(vector*)malloc(sizeof(vector));
    v->size=0;
    v->capacity=1;
    v->arr=(int*)malloc(sizeof(int));

    return v;
}

vector* push_back(vector* v,int x)
{
   if(v->size==v->capacity)
  {
    int *new_arr=(int*)malloc(sizeof(int)*(2*(v->capacity)));

    forn(i,0,v->size)
	new_arr[i]=v->arr[i];

    v->arr=new_arr;
    v->capacity=2*v->capacity;
 }

  v->arr[v->size]=x;
  v->size++;

  return v;
}

vector* adj[N];
int vis[N];

void dfs(int v,int key)
{
  fprintf(fo,"%d ",v);  
  vis[v]=1;
  if(v==key) return;
  forn(i,0,adj[v]->size)
  {
      if(!vis[adj[v]->arr[i]])
       dfs(adj[v]->arr[i],key);

      if(adj[v]->arr[i]==key)
       break; 
  }
}

void bfs(int v,int key)
{
    queue* q=new_queue();
    q=enqueue(q,v);
    vis[v]=1;

    while(q->size)
    {
        int u=top(q);
        q=dequeue(q);

        fprintf(fo,"%d ",u);
        if(u==key) break;

        forn(i,0,adj[u]->size)
        {
            if(!vis[adj[u]->arr[i]])
            {
             q=enqueue(q,adj[u]->arr[i]);
             vis[adj[u]->arr[i]]=1;
            }
        } 
    }
}

int main()
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    int n=0,a=0,b,i=0;
        
    char ch;

    while(1)
    {
      fscanf(fp,"%c",&ch);
      //printf("%c",ch);
      if(ch=='\n') break;
      n=n*10+(ch-48);
    }
  
     forn(i,0,n)
     adj[i]=new_vector();
      
      i=0;
      a=0;
      while(1)
      {
      //printf("hi%c",ch);
      int num=0;
      while(fscanf(fp,"%c",&ch)!=EOF)
      { 
       // if(num==0) printf("%c :",ch)
        if(ch=='\n')
        { 
           if(num!=0)adj[i]=push_back(adj[i],a);
           a=0;
           num=0;
           break;
        }
        if(ch!=' ')
        {
          a=a*10+ch-48;
        }
        else if(ch==' ')
        {
          adj[i]=push_back(adj[i],a);
          a=0;
        }
        num++;
      }
      
      i++;
      if(i==n)break;
    }

    while(fscanf(fp,"%c",&ch)!=EOF)
    {
      if(ch=='s')
      break;

      else if(ch=='d')
      {
        forn(i,0,n) vis[i]=0;
        forn(i,0,3)
        fscanf(fp,"%c",&ch);
        
        a=0,b=0;
        while(1)
        {
          fscanf(fp,"%c",&ch);
          if(ch==' ') break;
          
          a=a*10+ch-48;
        }

        while(1)
        {
          fscanf(fp,"%c",&ch);
          if(ch=='\n') break;
          
          b=b*10+ch-48;
        }
        
        dfs(a,b);
        fprintf(fo,"\n");
      }

      else if(ch=='b')
      {
        forn(i,0,n) vis[i]=0;
        forn(i,0,3)
        fscanf(fp,"%c",&ch);
        
        a=0,b=0;
        while(1)
        {
          fscanf(fp,"%c",&ch);
          if(ch==' ') break;
          
          a=a*10+ch-48;
        }

        while(1)
        {
          fscanf(fp,"%c",&ch);
          if(ch=='\n') break;
          
          b=b*10+ch-48;
        }
        
        bfs(a,b);
        fprintf(fo,"\n");
      }
    }

    return 0;
}