#include<stdio.h>
#include<stdlib.h>
#define forn(i,a,n) for(int i=a;i<n;i++)
#define inf 1e8

#define N 1001
int dist[N];

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

void bellman_ford(vector* adj[],int n)
{
  int isok=1;
  forn(i,0,n)
  dist[i]=inf;

  forn(i,0,n-1)
  {
      forn(v,0,n)
      {
         forn(j,0,adj[v]->size)
         {
            int u=adj[v]->arr[j].second;
            int wt=adj[v]->arr[j].w;
            if(dist[u]>(dist[v]+wt))
            dist[u]=dist[v]+wt;
         }
      }
  }  
  
      forn(v,0,n)
      {
         forn(j,0,adj[v]->size)
         {
            int u=adj[v]->arr[j].second;
            int wt=adj[v]->arr[j].w;
            if(dist[u]>(dist[v]+wt))
            {
                isok=0;
                break;
            }
         }
      }

      if(isok)
      printf("-1");
      else 
      printf("1");
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);

    vector* adj[n];
    forn(i,0,n)
    adj[i]=new_vector();
    
    int x,y,w;
    forn(i,0,m)
    {
       scanf("%d%d%d",&x,&y,&w);
       adj[x]=push_back(adj[x],mp(w,y));
    }
    
    bellman_ford(adj,n);

    return 0;
}