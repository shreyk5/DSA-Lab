#include<stdio.h>
#include<stdlib.h>

#define forn(i,a,n) for(int i=a;i<n;i++)
#define inf 1e8
#define N 10000
#define parent(n)   (n-1)/2
FILE *fp;
FILE *fo;

int idx[N];
int dist[N];
int mark[N];
int parent[N];
int key[N];
int wt[100][100];
int ans=0;
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
      idx[pq->a[smallest].second]=smallest;
      idx[pq->a[i].second]=i;
	  pq=min_heapify(pq,n,smallest);	   
    }

    return pq;
}

priority_queue* extract_min(priority_queue* pq)
{
  pq->size--;
  pq->a[0]=pq->a[pq->size];
  idx[pq->a[pq->size].second]=0;

  pq=min_heapify(pq,pq->size,0);
  return pq;
}

priority_queue* push(priority_queue* pq,pair x)
{
    pq->a[pq->size]=x;
    pq->size++;

    int i=pq->size-1;
    idx[x.second]=i; 
    while(i>0 && pq->a[i].w < pq->a[parent(i)].w)
    {
      pair temp=pq->a[i];
	  pq->a[i]=pq->a[parent(i)];
	  pq->a[parent(i)]=temp;

      idx[pq->a[i].second]=i;
      idx[pq->a[parent(i)].second]=parent(i);

      i=parent(i);
    }
    
    return pq;
}

priority_queue* decrease_key(priority_queue* pq,int id,int k)
{
  pq->a[id].w=k;
  int i=id;
  while(i>0 && pq->a[i].w < pq->a[parent(i)].w)
    {
      pair temp=pq->a[i];
	  pq->a[i]=pq->a[parent(i)];
	  pq->a[parent(i)]=temp;

      idx[pq->a[i].second]=i;
      idx[pq->a[parent(i)].second]=parent(i);

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

vector* adj[N];

void prims(int n)
{
  forn(i,0,n)
  {
    parent[i]=-1;
    key[i]=inf;
  }

  key[0]=0;
  priority_queue* Q=new_pq();

  forn(i,0,n)
  Q=push(Q,mp(key[i],i));

  while(Q->size)
  {
      int v=Q->a[0].second;
      Q=extract_min(Q);
      mark[v]=1;

      //printf("Extracted vertex: %d\n",v);
      if(v!=0)
      {
       //printf("%d-%d %d\n",v,parent[v],wt[v][parent[v]]);
       ans+=wt[v][parent[v]];
      }
      forn(i,0,adj[v]->size)
      {
          int u=adj[v]->arr[i].second;
          
          if(!mark[u]&&(wt[v][adj[v]->arr[i].second] < key[u]))
          {
              Q=decrease_key(Q,idx[u],(wt[v][adj[v]->arr[i].second]));
              
              key[u]=wt[v][adj[v]->arr[i].second];
              parent[u]=v;
             // printf("%d->%d\n",u,key[u]);
          }
      }

  }
}

int main()
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    int n=0,m=0,a=0,b,i=0;
    char ch;

    while(1)
    {
      fscanf(fp,"%c",&ch);
      if(ch=='\n') break;
      n=n*10+(ch-48);
    }
  
     forn(i,0,n)
     adj[i]=new_vector();
      
      i=0;
      a=0;
      while(1)
      {
      int num=0;
      while(fscanf(fp,"%c",&ch)!=EOF)
      { 
        if(ch=='\n')
        { 
           if(num!=0)
            {
              adj[i]=push_back(adj[i],mp(-1,a));
              //adj[a]=push_back(adj[a],mp(-1,i));
            }
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
          adj[i]=push_back(adj[i],mp(-1,a));
          //adj[a]=push_back(adj[a],mp(-1,i));
          a=0;
        }
        num++;
      }
      
      i++;
      if(i==n)break;
    }
      /*forn(i,0,n)
      {
      forn(j,0,adj[i]->size) 
      {
       printf("%d ",adj[i]->arr[j].second);
      }
      printf("\n");
      }
*/
      int j=0; 
      i=0;
      a=0;
      while(1)
      {
      int num=0;
      while(fscanf(fp,"%c",&ch)!=EOF)
      { 
        if(ch=='\n')
        { 
           if(num!=0)
            {
              adj[i]->arr[j].w=a;
              wt[i][adj[i]->arr[j].second]=a;
          wt[adj[i]->arr[j].second][i]=a;
            }
           a=0;
           num=0;
           j=0;
           break;
        }
        if(ch!=' ')
        {
          a=a*10+ch-48;
        }
        else if(ch==' ')
        {
          adj[i]->arr[j].w=a;
          wt[i][adj[i]->arr[j].second]=a;
          wt[adj[i]->arr[j].second][i]=a;
          //adj[i]->arr[j].w=a;
          j++;
          a=0;
        }
        num++;
      }
      
      i++;
      if(i==n)break;
    }
    
    prims(n);
    fprintf(fo,"%d\n",ans);
    
    return 0;
}
