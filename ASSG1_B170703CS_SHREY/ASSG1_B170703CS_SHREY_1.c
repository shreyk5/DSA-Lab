#include<stdio.h>
#include<stdlib.h>

FILE *fp;
FILE *fo;
int max_count=0;
int ans;

struct BST_node
{
   int data;
   int count;
   struct BST_node *left;
   struct BST_node *right;
   struct BST_node *p;  // parent node
};

struct node
{
    int data;
    struct node* next;
};

struct LinkedList
{
    int size;
    struct node* head;
};

struct BST
{
    struct BST_node* root;
};

struct BST *new_BST()
{
  struct BST* bst=(struct BST*)malloc(sizeof(struct BST));
  bst->root=NULL;

  return bst;
}

struct BST_node* Tree_Search(struct BST* b,struct BST_node* bnode,int val)
{
    //struct BST_node* bnode=b->root;
    if(bnode==NULL) return 0;
    else if(bnode->data==val) return bnode;
    else if(val<bnode->data)  return Tree_Search(b,bnode->left,val);
    else if(val>bnode->data)  return Tree_Search(b,bnode->right,val);
    else return 0;
}

void add_BSTnode(struct BST* b,int val)
{
    struct BST_node *bnode=Tree_Search(b,b->root,val);
    if(bnode==0)
    {
        bnode=(struct BST_node*)malloc(sizeof(struct BST_node));
        bnode->data=val;
        bnode->count=1;
        if(b->root==NULL)
        {
            b->root=bnode;
            bnode->p=NULL;
            bnode->left=NULL;
            bnode->right=NULL;
        }
        else  // insert node in correct position
        {
           struct BST_node *x=b->root;
           struct BST_node *y=NULL;

           while(x!=NULL)
           {
               y=x;
               if(val<x->data) x=x->left;
               else            x=x->right;
           }
            //bnode=(struct BST_node*)malloc(sizeof(struct BST_node));
            if(val<y->data)
            {
                y->left=bnode;
                bnode->p=y;
            }
            else
            {
                y->right=bnode;
                bnode->p=y;
            }

            bnode->left=NULL;
            bnode->right=NULL;
        }
    }

    else
      bnode->count++;
}

struct LinkedList* newlist()
{
    struct LinkedList* h;
    h = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    h->size=0;
    h->head=0;
    return h;
}

void add_node(struct LinkedList *ll,int value)
{
   struct node *newNode=(struct node*)malloc(sizeof(struct node));

   if(ll->head==NULL)
   {
      ll->head=newNode;
      ll->head->data=value;
      ll->head->next=NULL;
   }

    else
   {
     struct node *currentNode;
     currentNode=ll->head;

     while(currentNode->next!=NULL)
       currentNode=currentNode->next;

      currentNode->next=newNode;
      newNode->data=value;
      newNode->next=NULL;
   }
       ll->size++;
}

struct LinkedList* create(int n,struct BST* bst)
{
    struct LinkedList* ll=newlist();
    int a,i;
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%d",&a);
        add_BSTnode(bst,a);
        add_node(ll,a);
    }
    return ll;
}

void print_ll(struct LinkedList* h)
{
    if (h->head==0)
       { printf("Empty list\n");}
    else
    {
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode=h->head;

    while (newnode)
    {
        fprintf(fo,"%d ",newnode->data);
        newnode=newnode->next;
    }
    fprintf(fo,"\n");

    }
}

void inorder(struct BST_node* root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        if(root->count>max_count)
        {
            max_count=root->count;
            ans=root->data;
        }
        inorder(root->right);
    }
}


int main()
{
   fo=fopen("output.txt","w");
   fp=fopen("input.txt","r");
   struct LinkedList* ll;
   struct BST* bst=new_BST();
   char ch;
    while(fscanf(fp,"%c",&ch)!=EOF)
    {
        int n;
        if(ch=='c')
        {
            fscanf(fp,"%d",&n);
            ll=create(n,bst);
        }
        else if(ch=='p')
            print_ll(ll);

        else if(ch=='a')
        {
            fscanf(fp,"%d",&n);
            add_node(ll,n);
            add_BSTnode(bst,n);
        }
        else if(ch=='h')
        {
            inorder(bst->root);
            fprintf(fo,"%d\n",ans);
        }
    }
return 0;
}

