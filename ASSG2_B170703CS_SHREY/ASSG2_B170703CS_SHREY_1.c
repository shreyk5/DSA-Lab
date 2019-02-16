#include<stdio.h>
#include<stdlib.h>

#define and &&
#define or  ||
#define scan(a) scanf("%d",&a)
#define print(a) printf("%d",a)
#define endl     printf("\n")
const int inf=1e8;
const int N=1e5;
int m;
int *deleted;
int c1,c2;
char ch;
FILE *fp;
FILE *fo;

int min(int a,int b)
{
    if(a<b) return a;
    return b;
}
int max(int a,int b)
{
    if(a>b) return a;
    return b;
}

int prime(int m)
{
    int i,j;
    int flag;
    for(i=m-1;i>=1;i--)
    {
        flag=1;
        for(j=2;j*j<=i;j++)
        {
            if(i%j==0)
            {
             flag=0;
             break;
            }
        }
        if(flag==1) return max(1,i);
    }

    return max(1,i);
}

struct node
{
   int data;
   struct node *previous;
   struct node *next;

};

struct node* create_node(int n)
{
     struct node *curr=(struct node*)malloc(sizeof(struct node));
     curr->data=n;
     curr->next=NULL;
     curr->previous=NULL;
}


struct linked_list
{
    struct node* head;
    int size;

};

struct pair
{
    struct node* curr;
    struct linked_list* list;
};

struct linked_list* create_list()
{
    struct linked_list* list=(struct linked_list*)malloc(sizeof(struct linked_list));
    list->head=NULL;
    list->size=0;

    return list;
}


struct linked_list* push_back(struct linked_list *list,int k)
{
   struct node* tmp=list->head;
   struct node* new_node=create_node(k);
   if(!tmp)
   list->head=new_node;

   else
   {
     while(tmp->next)
     {
         tmp=tmp->next;

     }
     tmp->next=new_node;
     new_node->previous=tmp;
     //list->head->next=tmp;
   }
     list->size++;
   return list;
}

struct linked_list* erase(struct linked_list* list,struct node *n)
{
   struct node *curr=n->previous;
   if(!curr)
   {
     list->head=n->next;
     if(n->next) n->next->previous=NULL;
   }

   else
   {
     curr->next=n->next;
     if(n->next) n->next->previous=curr;
   }
    list->size--;
    return list;
}

void print_ll(struct linked_list* list)
{
    struct node *curr=list->head;

    if(ch=='a' || ch=='b' || ch=='c')
    {
        if(curr) fprintf(fo,"%d",curr->data);
    }

    else
     {
       while(curr)
       {
        if(curr!=list->head)fprintf(fo," %d",curr->data);
        else                fprintf(fo,"%d",curr->data);
        curr=curr->next;
       }
       //if(curr) fprintf(fo,"%d",curr->data);
     }
}

struct hash_table
{
    struct linked_list** arr;
    int m;
};


struct hash_table* create_table(int s)
{
   int i;
   struct hash_table* tab=(struct hash_table*)malloc(sizeof(struct hash_table));

   tab->arr=(struct linked_list*)malloc(sizeof(struct linked_list)*s);
   tab->m=s;
   for(i=0;i<s;i++)
   {
     tab->arr[i]=create_list();
   }

   return tab;
}

// Linear probing h(k,i)=(h1(k) + i)%m where h1(k) = k%m
// Quadratic probing h(k,i)=(h1(k)+c1*i+c2 i^2)%m
int hash(int k,int i,char ch)
{
   if(ch=='a') return (k%m +i)%m;
   if(ch=='b') return (k%m + c1*i +c2*i*i)%m;
   if(ch=='c')
   {
       int r=prime(m);
       return (k%m + i*(r - k%r))%m;
   }
}

int search(struct hash_table* tab,int k)
{
    int i=0,slot;
    if(ch=='d')
    {
        struct node *current=tab->arr[k%m]->head;
         while(current)
         {
             if(current->data==k)
                return 1;
             current=current->next;
         }
         return -1;
    }

    else
    for(i=0;i<m;i++)
   {

     slot=hash(k,i,ch);
     if(tab->arr[slot]->size==0 and !deleted[slot])
     {
      return -1;
     }
     else
     {
       struct node* curr=tab->arr[slot]->head;
       while(curr)
       {
           if(curr->data==k)
            return 1;
           curr=curr->next;
       }
     }
    }
    return -1;
}

struct pair* search_node(struct hash_table* tab,int k)
{
    int i=0,slot;
    struct pair* p=(struct pair*)malloc(sizeof(struct pair));
    p->curr=0;
    p->list=0;
    for(i=0;i<m;i++)
   {

     slot=hash(k,i,ch);
     if(tab->arr[slot]->size==0)
     {
      return p;
     }
     else
     {
       struct node* current=tab->arr[slot]->head;
       while(current)
       {
           if(current->data==k)
            {
                p->curr=current;
                p->list=tab->arr[slot];
                deleted[slot]=1;
                return p;
            }
           current=current->next;
       }
     }
    }
    return p;
}


struct hash_table* insert(struct hash_table *table,int k)
{
  int i=0,slot;
  if(ch=='d')
  {
    if(search(table,k)==-1)
     table->arr[k%m]=push_back(table->arr[k%m],k);
    return table;
  }

  else
  {
    if(search(table,k)==-1)
    for(i=0;i<m;i++)
   {

     slot=hash(k,i,ch);
     if(table->arr[slot]->size==0)
     {
      table->arr[slot]=push_back(table->arr[slot],k);
      return table;
     }
    }

  }
}

struct hash_table* del(struct hash_table* tab,int k)
{
     if(ch!='d')
     {
     struct pair* tmp=search_node(tab,k);
     tmp->list=erase(tmp->list,tmp->curr);
     }

     else
     {
         struct node *current=tab->arr[k%m]->head;
         while(current)
         {
             if(current->data==k)
             {
                 tab->arr[k%m]=erase(tab->arr[k%m],current);
                 break;
             }
             current=current->next;
         }
     }

   return tab;
}

int main()
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    fscanf(fp,"%c",&ch);     // Type of probing
    fscanf(fp,"%d",&m);         // Size of hash table
    if(ch=='b')
    {
        fscanf(fp,"%d",&c1);
        fscanf(fp,"%d",&c2);
    }
    int i;

    deleted=(int *)malloc(sizeof(int)*N);
    for(i=0;i<N;i++) deleted[i]=0;

    struct hash_table *tab=create_table(m);
    char c;
    int n;

    while(fscanf(fp,"%c",&c)!=EOF)
    {
       if(c=='i')
       {
         fscanf(fp,"%d",&n);
         tab=insert(tab,n);
       }

       else if(c=='s')
       {
         fscanf(fp,"%d",&n);
         fprintf(fo,"%d\n",search(tab,n));
       }

       else if(c=='p')
       {
         for(i=0;i<m;i++)
         {
          fprintf(fo,"%d ",i);
          fprintf(fo,"(");
          print_ll(tab->arr[i]);
          fprintf(fo,")");
          fprintf(fo,"\n");
         }
       }

       else if(c=='d')
       {
         fscanf(fp,"%d",&n);
         tab=del(tab,n);
       }

       else if(c=='t')
            break;
    }

   return 0;
}
