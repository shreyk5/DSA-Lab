#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define scan(a) scanf("%d",&a)
#define print(a) printf("%d",a)
#define endl     printf("\n")
const int N=1e4;
int m;


struct pairs
{
    int x;
    int y;
};

struct node
{
   struct pairs p;
   struct node *previous;
   struct node *next;
};


struct node* create_node(struct pairs n)
{
     struct node *curr=(struct node*)malloc(sizeof(struct node));
     curr->p=n;
     curr->next=NULL;
     curr->previous=NULL;
     return curr;
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


struct linked_list* push_front(struct linked_list *list,int k,int val)
{
   struct pairs pr;
   pr.x=k;
   pr.y=val;
   struct node* tmp=(struct node*)malloc(sizeof(struct node));
   tmp=list->head;
   struct node* new_node=create_node(pr);

   list->head=new_node;
   list->head->next=tmp;
   if(tmp) tmp->previous=new_node;
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

int search(struct hash_table* tab,int k,int val)
{
    struct node *current=tab->arr[k%m]->head;
    while(current)
    {
      if(current->p.y==val)
        return 1;
      current=current->next;
    }

    return -1;
}

struct pair* search_node(struct hash_table* tab,int k,int val)
{
    struct pair* pr=(struct pair*)malloc(sizeof(struct pair));
    pr->curr=0;
    pr->list=0;
       struct node* current=tab->arr[k%m]->head;
       while(current)
       {
           if(current->p.y==val)
            {
                pr->curr=current;
                pr->list=tab->arr[k%m];
                return pr;
            }
           current=current->next;
       }
    return pr;
}

struct hash_table* insert(struct hash_table *tab,int k,int val)
{
  if(search(tab,k,val)==-1)
     tab->arr[k%m]=push_front(tab->arr[k%m],k,val);
    return tab;
}

struct hash_table* del(struct hash_table* tab,int k,int val)
{

     struct pair* tmp=search_node(tab,k,val);
     //printf("HI\n");
     //printf("%d\n",tmp->curr->p.x);
     tmp->list=erase(tmp->list,tmp->curr);
        return tab;
}


void print_ll(struct linked_list* list)
{
    struct node *curr=list->head;
    while(curr)
    {
        //printf("%d %d\n",curr->p.x,curr->p.y);
        curr=curr->next;
    }
}

void print_table(struct hash_table* tab)
{
    int i;
    for(i=0;i<m;i++)
    {
        printf("%d :",i);
        struct node* curr=tab->arr[i]->head;
        while(curr)
        {
            printf("(%d, %d) ",curr->p.x,curr->p.y);
            curr=curr->next;
        }

        endl;
    }
}

int main()
{
    FILE *fp=fopen("input.txt","r");
    FILE *fo=fopen("output.txt","w");
    m=1;
    struct hash_table *tab=create_table(1);

    struct pairs ans[N];
    char ch;
    char *str;
    int n1,n2,i,j=0;
    int count=0;
    int key,value;
    while(fscanf(fp,"%c",&ch)!=EOF)
    {
        str=(char *)malloc(sizeof(char)*10);
        if(ch=='s')
        {
            fscanf(fp," %[^\n]s",str);
            n1=0;
            n2=0;

            i=1;
            while(str[i]!=',')
            {
                n1=n1*10 + str[i]-48;
                i++;
            }
            i+=2;
            while(str[i]!=')')
            {
                n2=n2*10 + str[i]-48;
                i++;
            }
            //printf("%d %d\n",n1,n2);
            tab=insert(tab,n1,n2);
        }

        if(ch=='p')
        {
            //print_ll(tab->arr[0]);
            for(i=0;i<m;i++)
            {
              struct node* curr=tab->arr[i]->head;

              while(curr)
              {
                  //print_table(tab);
                  key=curr->p.x;
                  value=curr->p.y;
                  
                  //printf("%d %d\n",key,value);
                  if(search(tab,value,key)==1)
                  {

                      ans[count].x=key;
                      ans[count].y=value;

                      tab=del(tab,value,key);
                      count++;
                     // printf("%d %d\n",key,value);
                  }
                  tab=del(tab,key,value);
                   //printf("%d %d\n",key,value);
                  curr=tab->arr[i]->head;
                  //printf("%d %d\n",key,value);
              }
            }
            //print_table(tab);
            for(i=0;i<count;i++)
                fprintf(fo,"(%d, %d)\n",ans[i].x,ans[i].y);
        }
    }
    return 0;
}
