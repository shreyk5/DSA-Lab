#include<stdio.h>
#include<stdlib.h>

#define inf 1e9
#define MAX 1001
int mini;

FILE *fp;
FILE *fo;

int min(int a,int b)
{
  if(a<b)
    return a;
  return b;
}

int max(int a,int b)
{
  if(a>b)
    return a;
  return b;
}

struct node
{
  int key;
  int degree;
  struct node* child;
  struct node* parent;
  struct node* sibling;
};

typedef struct node node;

node* hash[MAX];
node* negHash;

struct queue
{
  struct node* a[MAX];
  int size;
  int front;
  int rear;
};

typedef struct queue queue;

queue* new_queue()
{
	queue *q;
	q=(struct queue*)malloc(sizeof(struct queue));
	q->front=0;
	q->rear=0;
	q->size=0;

    return q;
}

queue* enqueue(struct queue *q,node* data)
{
	q->a[q->rear]=data;
	q->size=(q->size)+1;
	q->rear=q->rear+1;

	return q;
}

queue* dequeue(struct queue *q)
{

	 if(q->size==0) printf("EMPTY\n");

	 else
	   {
	     //	printf("%d ",q->a[q->front]);
		q->front=q->front+1;
		q->size=(q->size)-1;
	   }
	 return q;
}


struct binomial_heap
{
  node* head;
};

typedef struct binomial_heap binomial_heap;

node* create_node(int val)
{
  node* tmp=(node*)malloc(sizeof(node));
  tmp->key=val;
  tmp->degree=0;
  tmp->child=tmp->sibling=tmp->parent=NULL;

  return tmp;
}

binomial_heap* create_heap()
{
   binomial_heap* myheap=(binomial_heap*)malloc(sizeof(binomial_heap));

   myheap->head=NULL;
   
  return myheap;	   
}

node* reverse(node* head)
{
   struct node *temp=head;           //just keeps the head safe
   struct node *currentNode=head;
   struct node *previousNode=NULL;
   struct node *nextNode;

   while(currentNode->sibling!=NULL)
   {
      currentNode=currentNode->sibling;
   }

   head=currentNode;
   currentNode=temp;

   while(currentNode!=NULL)
   {
      nextNode=currentNode->sibling;
      currentNode->sibling=previousNode;

      //previousNode=previousNode->next;
      previousNode=currentNode;
      currentNode=nextNode;
   }

   temp->sibling=NULL;

   return head;
}


node* minimum(binomial_heap* myheap)
{
   int mini=inf;

   node* curr=myheap->head;
   node* y=(node*)malloc(sizeof(node));

   while(curr)
   {
     if(curr->key < mini)
     {
       mini=curr->key;
       y=curr;
     }

     curr=curr->sibling;
   }
   
  return y;
}

node* binomial_link(binomial_heap* myheap,node* y,node* z)
{
   if((z->key<y->key))
   {
    y->parent=z;
    y->sibling=z->child;
    z->child=y;
    z->degree++;

    return z;
   }

   else
   {
     z->parent=y;
     z->sibling=y->child;
     y->child=z;
     y->degree++;

     return y;
   }

}

binomial_heap* merge(binomial_heap* h1,binomial_heap* h2)
{
    binomial_heap* h=create_heap();

    node* curr1=h1->head;
    node* curr2=h2->head;
    node* curr=(node*)malloc(sizeof(node));
    
    if(curr1==NULL)        return h2;
    else if(curr2==NULL)   return h1;

    if(curr1->degree<=curr2->degree)  
    {
      h->head=curr1;
      curr1=curr1->sibling;
    }

    else
    {
       h->head=curr2;
       curr2=curr2->sibling;
    }

    curr=h->head;

    while(1)
    {
       if(curr1==NULL && curr2==NULL)
        break;

       else if(curr1 && curr2)
       {
         if(curr1->degree<=curr2->degree)
         {
            curr->sibling=curr1;
	    curr1=curr1->sibling;
	    curr=curr->sibling;
	 }

	 else
	 {
	   curr->sibling=curr2;
	   curr2=curr2->sibling;
           curr=curr->sibling;
	 }
       }

       else if(curr1)
       {
         curr->sibling=curr1;
	 curr=curr->sibling;
         curr1=curr1->sibling;
       }

       else if(curr2)
       {
         curr->sibling=curr2;
	 curr=curr->sibling;
	 curr2=curr2->sibling;
       }
    
    }

   return h;
}

binomial_heap* heap_union(binomial_heap* h1,binomial_heap* h2)
{
   binomial_heap* h=create_heap();
   h=merge(h1,h2);

   if(h->head==NULL) return h;
   
   node* x=NULL;
   node* y=h->head;
   node* z=y->sibling;

   while(z!=NULL)
   {
     if(y->degree!=z->degree || (z->sibling!=NULL && z->sibling->degree==y->degree))
     {
       x=y;
       y=z;
       z=z->sibling;
     }

     else
     {
        if(y->key<=z->key)
	{
	   y->sibling=z->sibling;
           binomial_link(h,y,z);
	}

	else if(y->key>z->key)   // h->head has to be changed in this case if x==NULL
	{
	  if(x==NULL)
	   h->head=z;

	  else
	    x->sibling=z;
	  
	  binomial_link(h,y,z);
	  y=z;
	}
     }
      
     z=y->sibling;
   }
  
   return h;
}

binomial_heap* insert(binomial_heap* h,int x)
{
   binomial_heap* h1=create_heap();
   node* tmp=create_node(x);
   hash[x]=tmp;
  
   h1->head=tmp;

   h=heap_union(h,h1);
	 
   return h;
}

binomial_heap* extract_min(binomial_heap* h)
{

  mini=inf;

  node* curr=h->head;
  node* prev=NULL;
  node* tmp=(node*)malloc(sizeof(node));
  while(curr)
  {
     if(mini>curr->key)
     {
	 mini=curr->key;
	 tmp=curr;
     }
   curr=curr->sibling;
  }

  curr=h->head;

  if(tmp==(h->head))
  {
    h->head=NULL;
  }	  
  
  while(curr->sibling)
  {
    if(curr->sibling->key==mini)
    {
      tmp=curr->sibling;
      curr->sibling=curr->sibling->sibling;
      break;
    } 
    curr=curr->sibling;
  }

  // tmp is the root to be removed
  
  node* head1=tmp->child;
  node* tmp1=head1;

  while(tmp1)
  {
    tmp1->parent=NULL;
    tmp1=tmp1->sibling;   
  }

  head1=reverse(head1); // we get the reversed list

  binomial_heap* h1=create_heap();
  h1->head=head1;
  
  h=heap_union(h,h1);
  
  //printf("%d\n",mini);
  return h;
}

void print(binomial_heap* h)
{
   queue* q=new_queue();

   node* curr=h->head;   
   q=enqueue(q,curr);
   
   node* tmp;

   while((q->size)!=0)
   {
     tmp=q->a[q->front];
     q=dequeue(q);
     while(tmp)
     {
       fprintf(fo,"%d ",tmp->key);
       q=enqueue(q,tmp->child);
       tmp=tmp->sibling;
     }
   }

   fprintf(fo,"\n");

}

void swap(binomial_heap* h,node *a,node *b)
{
  node* tmp;
  
  if(a->key<0)
  {	  
   tmp=negHash;
  // tmp=hash[a->key];
  // hash[a->key]=hash[b->key];
   hash[b->key]=tmp;
  }

  else
  {
    tmp=hash[a->key];
    hash[a->key]=hash[b->key];
    hash[b->key]=tmp;
  }

  int t=a->key;
  a->key=b->key;
  b->key=t;
}

binomial_heap* decrease_key(binomial_heap* h,node* x,int k)
{
   if(k>(x->key))
   {
     fprintf(fo,"ERROR\n");
     return h;
   }
   
   if(k>=0)
      hash[k]=hash[x->key];
   else negHash=hash[x->key];

   x->key=k;
   node* y=x;
   node* z=y->parent;

   while(z && y->key<z->key)
   {
     swap(h,y,z);
     y=z;
     z=y->parent;
   }	   
  
  return h;
}

binomial_heap* delete(binomial_heap* h,node* x)
{
  h=decrease_key(h,x,-inf);
  h=extract_min(h);

  return h;
}


int main()
{
  binomial_heap* h=create_heap();
  fp=fopen("input.txt","r");
  fo=fopen("output.txt","w");
  int n;
  char ch;
/*
  h=insert(h,2);
  h=insert(h,3);
  h=insert(h,1);
  h=insert(h,6);
  h=insert(h,7);
  h=insert(h,10);

 //printf("%d\n",hash[1]->key);
 print(h);
 // printf("%d %d\n",h->head->degree,h->head->sibling->degree);
  
  h=extract_min(h);
 // printf("%d %d\n",h->head->degree,h->head->sibling->degree);
  
  print(h);
 // printf("%d ",hash[3]->key);
  h=decrease_key(h,hash[3],1);
  print(h);
  
  h=delete(h,hash[2]);

  print(h);
*/
  
  while(fscanf(fp,"%c",&ch)!=EOF)
  {
    if(ch=='s') break;

    else if(ch=='i')
    {
      fscanf(fp,"%d",&n);
      h=insert(h,n);
    }

    else if(ch=='d')
    {
      fscanf(fp,"%d",&n);
      h=delete(h,hash[n]);
    }

    else if(ch=='m')
    {
      node* tmp=minimum(h);
      fprintf(fo,"%d\n",tmp->key);
    }

    else if(ch=='p')
     print(h);

    else if(ch=='x')
     h=extract_min(h);
  
  }
  
  /*
  h=insert(h,10);
  h=insert(h,20);
  h=insert(h,30);
  h=insert(h,40);
  h=insert(h,50);

  print(h);
  h=extract_min(h);
  print(h);
 */

  return 0;
}



