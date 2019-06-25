#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define forn(i,a,n) for(int i=a;i<n;i++)
#define N 10000
#define inf 1000000
#define parent(n)   (n-1)/2
FILE *fp;
FILE *fo;

int dist[N];
int vis[N];
int parent[N];

struct pair
{
  int w;
  int second;
};

typedef struct pair pair;

pair mp(int a,int b)
{
    pair x={a,b};
    return x;
}

struct priority_queue
{
  pair a[N];
  int size;
};

typedef struct priority_queue priority_queue;

priority_queue* new_pq()
{
    priority_queue* pq=(priority_queue*)malloc(sizeof(priority_queue));
    pq->size=0;

    return pq;
}

priority_queue* min_heapify(priority_queue *pq,int n,int i)
{
	int smallest=i;  //index of smallest among i,2*i+1,2*i+2
	int left=2*i+1;
 	int right=2*i+2;
    pair temp;
    
	if(left<n && pq->a[smallest].w >pq->a[left].w) smallest=left;
	if(right<n&& pq->a[smallest].w >pq->a[right].w) smallest=right;
	
	if(smallest!=i)
	{
	  temp=pq->a[i];
	  pq->a[i]=pq->a[smallest];
	  pq->a[smallest]=temp;	
	  pq=min_heapify(pq,n,smallest);	   
    }

    return pq;
}

priority_queue* extract_min(priority_queue* pq)
{
  pq->size--;
  pq->a[0]=pq->a[pq->size];

  pq=min_heapify(pq,pq->size,0);
  return pq;
}

priority_queue* push(priority_queue* pq,pair x)
{
    pq->a[pq->size]=x;
    pq->size++;

    int i=pq->size-1;

    while(i>=0 && pq->a[i].w < pq->a[parent(i)].w)
    {
      pair temp=pq->a[i];
	  pq->a[i]=pq->a[parent(i)];
	  pq->a[parent(i)]=temp;

      i=parent(i);
    }
    
    return pq;
}

struct vector
{
  int size;
  int capacity;
  pair *arr;
};

typedef struct vector vector;

vector* new_vector()
{
    vector* v=(vector*)malloc(sizeof(vector));
    v->size=0;
    v->capacity=1;
    v->arr=(pair*)malloc(sizeof(pair));

    return v;
}

vector* push_back(vector* v,pair x)
{
   if(v->size==v->capacity)
  {
    pair *new_arr=(pair*)malloc(sizeof(pair)*(2*(v->capacity)));

    forn(i,0,v->size)
	new_arr[i]=v->arr[i];

    v->arr=new_arr;
    v->capacity=2*v->capacity;
 }

  v->arr[v->size]=x;
  v->size++;

  return v;
}

int  path[N];

void Dijkstra(int src,int n,vector* adj[])
{
   priority_queue* pq=new_pq(); 
   forn(i,0,n+1) dist[i]=inf;
   pq=push(pq,mp(0,src));
   dist[src]=0;

   while(pq->size)
   {
   pair x=pq->a[0];
   int  v=x.second;
   pq=extract_min(pq);

   vis[v]=1;
   
   int i=0;
   for(i=0;i<adj[v]->size;i++)
   {
     if(!vis[adj[v]->arr[i].second])
     {
       if(dist[adj[v]->arr[i].second]>dist[v]+adj[v]->arr[i].w)
       {
        dist[adj[v]->arr[i].second]=dist[v]+adj[v]->arr[i].w; 
        pq=push(pq,mp(dist[adj[v]->arr[i].second],adj[v]->arr[i].second)); 
        parent[adj[v]->arr[i].second]=v;
       }
     }
   }
   }
}

int main()
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    int n=0,m=0,a=0,b,i=0,w;
    char ch;
    
    fscanf(fp,"%d",&n);
    fscanf(fp,"%d",&m);

    //printf("%d %d",n,m);
    vector* adj[n];
    forn(i,0,n)
    adj[i]=new_vector();

    forn(i,0,m)
    {
      fscanf(fp,"%d%d%d",&a,&b,&w);
      adj[a]=push_back(adj[a],mp(w,b));
    } 

    int src;
    fscanf(fp,"%d",&src);

    Dijkstra(src,n,adj);
    forn(i,0,n)
    {
      fprintf(fo,"%d ",i);
      if(dist[i]==inf)
      fprintf(fo,"inf\n");
      else fprintf(fo,"%d\n",dist[i]);
    }

    
    return 0;
}
