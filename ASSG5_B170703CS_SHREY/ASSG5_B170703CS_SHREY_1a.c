#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define print(x)     printf("%d ",x)
#define sprint(s)    printf("%s ",s);
#define forn(i,a,n)  for(int i=a;i<n;i++)
const int N =1000;
int ans;

FILE *fp;
FILE *fo;

int parent[1001];
int Rank[1001];
int Size[1001];

void make_set(int x)
{
  parent[x]=x;
  Rank[x]=0;
  Size[x]=1;
}

int find_set(int x)
{
   if(parent[x]==x)
     return x;

   parent[x]=find_set(parent[x]);
   return parent[x];
}

void union_set(int x,int y)
{
   int px=find_set(x);
   int py=find_set(y);

   if(px!=py)
   {
      if(Rank[px]==Rank[py])
      {
         parent[py]=px;
         Rank[x]++;
         Size[px]+=Size[py];
      }  
      else if(Rank[px]>Rank[py])
      {
        parent[py]=px;
        Size[px]+=Size[py];
      }

      else
      {
       parent[px]=py;
       Size[py]+=Size[px];
      }
   } 
}

struct edge
{
  int src,dest;
  int w;
};

typedef struct edge edge;

struct graph
{
  int n,m;
  edge* e;
};

typedef struct graph graph;

graph* init_graph()
{ 
    graph* g=(graph*)malloc(sizeof(graph));
    g->e=(edge*)malloc(sizeof(edge)*1001);
    return g;
}

int cmp(const void* a,const void* b)
{
     edge* a1=(edge*)a;
     edge* a2=(edge*)b;

     return a1->w > a2->w;
}

edge push_edge(int a,int b,int c)
{
    edge ed={a,b,c};
    return ed;
}

void kruskal(graph* g)
{
   forn(i,0,g->n)
   make_set(i);

   qsort(g->e,g->m,sizeof(g->e[0]),cmp);
   
   forn(i,0,g->m)
   {
       if(find_set(g->e[i].src)!=find_set(g->e[i].dest))
       {
           ans+=g->e[i].w;
           //printf("%d--%d\n",g->e[i].src,g->e[i].dest);
           union_set(g->e[i].src,g->e[i].dest);
       }
   }
}

int main()
{
    int a,b,c;
    graph* g=init_graph();
    
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    int num=0,m1=0,a1=0,b1,i=0;
    char ch;

    while(1)
    {
      fscanf(fp,"%c",&ch);
      if(ch=='\n') break;
      num=num*10+(ch-48);
    }
     g->n=num;
     
      i=0;
      a1=0;
      while(1)
      {
      int num=0;
      while(fscanf(fp,"%c",&ch)!=EOF)
      { 
        if(ch=='\n')
        { 
           if(num!=0)
            {
              
                g->e[m1++]=push_edge(i,a1,1);
               // g->e[m1++]=push_edge(i,a,1);
          
              //adj[a]=push_back(adj[a],mp(-1,i));
            }
           a1=0;
           num=0;
           break;
        }
        if(ch!=' ')
        {
          a1=a1*10+ch-48;
        }
        else if(ch==' ')
        {
          //adj[i]=push_back(adj[i],mp(-1,a));
                g->e[m1++]=push_edge(i,a1,1);
            

          a1=0;
        }
        num++;
      }
      
      i++;
      if(i==g->n)break;
    }

      int j=0; 
      i=0;
      a1=0;
      m1=0;
      while(1)
      {
      int num=0;
      while(fscanf(fp,"%c",&ch)!=EOF)
      { 
        if(ch=='\n')
        { 
           if(num!=0)
            {
              g->e[m1++].w=a1;
            }
           a1=0;
           num=0;
           j=0;
           break;
        }
        if(ch!=' ')
        {
          a1=a1*10+ch-48;
        }
        else if(ch==' ')
        {
          g->e[m1++].w=a1;
          //adj[i]->arr[j].w=a;
          j++;
          a1=0;
        }
        num++;
      }
      
      i++;
      if(i==g->n)break;
    }
    g->m=m1;
    kruskal(g);
    fprintf(fo,"%d",ans);
 
    return 0;
}