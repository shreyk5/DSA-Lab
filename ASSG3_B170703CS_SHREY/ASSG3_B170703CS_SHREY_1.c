#include<stdio.h>
#include<stdlib.h>

#define N 10001
#define print(x) printf("%d ",x)
#define nwl      printf("\n")

FILE *fp;
FILE *fo;
int c[4];

struct disjoint_set
{
  int parent[N];
  int rank[N];
  int type;       // type 0 --> simple 
                  // type 1 -->ranked union--- type 2 -->path
};

struct disjoint_set* init(int t)
{
  struct disjoint_set *ds=(struct disjoint_set*)malloc(sizeof(struct disjoint_set));

  int i=0;
  for(int i=0;i<N;i++) ds->parent[i]=-1;
  ds->type=t;

  return ds; 
}

struct disjoint_set* make_set(struct disjoint_set *ds,int i)
{
    if(ds->parent[i]!=-1)
    {
	    if(ds->type==0)
	    fprintf(fo,"PRESENT\n");
    }
    
    else
    {
     if(ds->type==0) fprintf(fo,"%d\n",i);	    
     ds->parent[i]=i;
     ds->rank[i]=0;
    }
    return ds;
}

int find(struct disjoint_set *ds,int i)
{
   c[ds->type]++;	
   if(ds->parent[i]==-1) return -1;	
   else if(ds->type==0 || ds->type==1)
   {	   	   
     if(i==ds->parent[i]) return i;
     else             return find(ds,ds->parent[i]);
   }

   else if(ds->type==2 || ds->type==3)
   {
     if(i==(ds->parent[i])) return i;
     else             return ds->parent[i]=find(ds,ds->parent[i]);
   }	   
}

struct disjoint_set* uni(struct disjoint_set *ds,int x,int y)
{
   if((ds->parent[x]==-1 ||ds-> parent[y]==-1))
   {
     if(ds->type==3)	    
     fprintf(fo,"ERROR ");

     else fprintf(fo,"ERROR ");
   }

   else
   {
     if(ds->type==0 || ds->type==2) // Without rank heuristic
     {
       int px=find(ds,x);
       int py=find(ds,y);

       if(px==py)
       {
	       fprintf(fo,"%d ",px);
	       return ds;
       }
       else
       {
          ds->parent[py]=px;
          fprintf(fo,"%d ",px);
       }
     }

     else                     // With rank heuristic
     {
       int px=find(ds,x);
       int py=find(ds,y);

       if(px==py)
       {
	       fprintf(fo,"%d ",px);
	       return ds;
       }
       else 
       {
         if(ds->rank[px]<ds->rank[py])
	 {
		 ds->parent[px]=py;
		 fprintf(fo,"%d ",py);
	 }

	 else if(ds->rank[px]>ds->rank[py])
	 {
		ds->parent[py]=px;
		 fprintf(fo,"%d ",px);
	 }
         
	 else
	 {
          fprintf(fo,"%d ",px);		 
	  ds->parent[py]=px;
	  ds->rank[px]++;
	 }
       }
     }
  }   
   
   return ds;
}

int main()
{
   fp=fopen("input.txt","r");
   fo=fopen("output.txt","w");

   int i,n,x,y;	
   char ch;
   struct disjoint_set *ds[4];
   for(i=0;i<4;i++) ds[i]=init(i);

   while(1)
   {
     fscanf(fp,"%c",&ch);
     if(ch=='s')break;
     
     else if(ch=='m')
     {
	fscanf(fp,"%d",&n);     
       for(i=0;i<4;i++)
	    ds[i]=make_set(ds[i],n);
       //fprintf(fo,"\n");
     }    

     else if(ch=='u')
     {
       fscanf(fp,"%d%d",&x,&y);
       for(i=0;i<4;i++)
       {
	       ds[i]=uni(ds[i],x,y);
       }
       fprintf(fo,"\n");
     }
     else if(ch=='f')
     {
       fscanf(fp,"%d",&n);
     //  int k=find(ds[0],n);

       if(ds[0]->parent[n]==-1) printf("NOT FOUND\n");
       else 
       {
	for(i=0;i<4;i++)       
         fprintf(fo,"%d ",find(ds[i],n));

 	fprintf(fo,"\n");
       }
     }

   }
   fprintf(fo,"%d ",c[0]);
   fprintf(fo,"%d ",c[1]);
   fprintf(fo,"%d ",c[2]);
   fprintf(fo,"%d ",c[3]);
   return 0;
}
