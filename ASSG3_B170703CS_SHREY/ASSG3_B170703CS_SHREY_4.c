#include<stdio.h>
#include<stdlib.h>

#define print(x)    printf("%d ",x)
#define nwl         printf("\n")
#define N           10001
#define forn(i,a,n) for(int i=a;i<n;i++)

FILE *fp;
FILE *fo;

struct node
{
  int data;
  struct node* prev;
  struct node* next;
  struct node* parent;
};

typedef struct node node;

struct dll
{
  struct node* head;
  struct node* tail;
  int size;
};

typedef struct dll dll;

struct disjoint_set
{
  struct node* hash[N];
  struct dll*  set[N];
  int type;

};

typedef struct disjoint_set disjoint_set;

node* create_node(int val)
{
  node* tmp=(node*)malloc(sizeof(node));
  tmp->data=val;
  
  tmp->parent=tmp;
  tmp->prev=tmp->next=NULL;

  return tmp;
}

dll* create_list()
{
   dll *tmp=(dll*)malloc(sizeof(dll));
   tmp->size=0;
   tmp->head=NULL;
   tmp->tail=NULL;

   return tmp;	
}

dll* pb(dll *list,node* tmp)
{
   if(!list->head)
   {
    // node *tmp=create_node(val);
     list->head=tmp;
     list->tail=tmp;
     tmp->parent=list->head;    //SETS THE PARENT
   }	   
  
   else
   {
    // node *tmp=create_node(val);	   
     node *curr=list->head;
     while(curr->next)
       curr=curr->next;

     tmp->prev=curr;
     curr->next=tmp;
     list->tail=tmp;
     tmp->parent=list->head;   // SETS THE PARENT
   }
   list->size++;

   return list;
}

dll* append(dll *a,dll*b)
{
  a->tail->next=b->head;
  b->head->prev=a->tail;

  node* curr=b->head;
  while(curr)
  {
    curr->parent=a->head;
    curr=curr->next;
  }

  a->tail=b->tail;
  a->size+=b->size;

  b->size=0;
  b->head=NULL;
  
  return a;
}

disjoint_set* init()
{
  disjoint_set* dsu=(disjoint_set*)malloc(sizeof(disjoint_set));
  forn(i,0,N) dsu->set[i]=create_list();
  
  forn(i,0,N) dsu->hash[i]=0;

  return dsu;
} 

disjoint_set* make_set(disjoint_set* dsu,int i)
{
    node* tmp=create_node(i);
    dsu->hash[i]=tmp;
    dsu->set[i]=pb(dsu->set[i],tmp);
   
   return dsu;
}

int find_set(disjoint_set* dsu,int x)
{
   return dsu->hash[x]->parent->data;

}

disjoint_set* union_set(disjoint_set* dsu,int a,int b)
{
  node *tmp1=dsu->hash[a];
  node *tmp2=dsu->hash[b];

  tmp1=tmp1->parent;
  tmp2=tmp2->parent;

  int x=tmp1->data;
  int y=tmp2->data;
  
  if(dsu->type==0)
  {
    dsu->set[x]=append(dsu->set[x],dsu->set[y]);
    fprintf(fo,"%d ",dsu->set[x]->head->data);
  } 	  
  
  else
 {	  

  if(dsu->set[x]->size==dsu->set[y]->size)
  {
     if(x<y)
     {
      fprintf(fo,"%d ",dsu->set[x]->head->data);
      dsu->set[x]=append(dsu->set[x],dsu->set[y]);
     }
     else
     {
	     fprintf(fo,"%d ",dsu->set[y]->head->data);
	     dsu->set[y]=append(dsu->set[y],dsu->set[x]);     
  
     }
  }     

  else if(dsu->set[x]->size>dsu->set[y]->size)
  { 
     fprintf(fo,"%d ",dsu->set[x]->head->data);
  
     dsu->set[x]=append(dsu->set[x],dsu->set[y]);
  }
  else
  {
     dsu->set[y]=append(dsu->set[y],dsu->set[x]);
     fprintf(fo,"%d ",dsu->set[y]->head->data);
  }     
 } 	

  return dsu;
}

int main()
{
    char ch;
    int a,b,n;
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");

    disjoint_set* dsu=init();
    disjoint_set* dsu1=init();
    
    dsu->type=0;
    dsu1->type=1;
    
    while(1)
    { 
       fscanf(fp,"%c",&ch);

       if(ch=='m')
       {
           fscanf(fp,"%d",&n);

	   if(dsu->hash[n]!=0)
	    fprintf(fo,"PRESENT\n");
	   else
            fprintf(fo,"%d\n",n);

	   dsu=make_set(dsu,n);
	   dsu1=make_set(dsu1,n);
       }

       else if(ch=='f')
       {
         fscanf(fp,"%d",&n);
         if(dsu->hash[n]==0)
	   fprintf(fo,"NOT FOUND\n");

	 else 
         {
           fprintf(fo,"%d ",find_set(dsu,n));
	   fprintf(fo,"%d\n",find_set(dsu1,n));
         }
       }

       else if(ch=='u')
       {
         fscanf(fp,"%d",&a);
	 fscanf(fp,"%d",&b);

	 if(dsu->hash[a]==0 || dsu->hash[b]==0)
		 fprintf(fo,"ERROR\n");
	 else
	 {
	   dsu=union_set(dsu,a,b);
	   dsu1=union_set(dsu1,a,b);
	   fprintf(fo,"\n");
	 }
       }

       else if(ch=='s')
	   break;
    }


   return 0;
}


