#include<stdio.h>
#include<stdlib.h>

const int inf = 1e9;
FILE *fp;
FILE *fo;

int min(int a,int b)
{
    if(a<=b) return a;
    return b;
}

int max(int a,int b)
{
    if(a>=b) return a;
    return b;
}

struct BST_node
{
   int data;
   struct BST_node *left;
   struct BST_node *right;
   struct BST_node *p;  // parent node
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

struct BST_node* Search(struct BST* b,struct BST_node* bnode,int val)
{
    if(bnode==NULL) return 0;
    else if(bnode->data==val) return bnode;
    else if(val<bnode->data)  return Search(b,bnode->left,val);
    else if(val>bnode->data)  return Search(b,bnode->right,val);
    else return 0;
}

struct BST* insert(struct BST* b,int val)
{
        struct BST_node* bnode=(struct BST_node*)malloc(sizeof(struct BST_node));
        bnode->data=val;

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
               if(val<=x->data) x=x->left;
               else             x=x->right;
           }

            if(val<=y->data)
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
        return b;
}

void preorder(struct BST_node* root)
{
    if(root!=NULL)
    {
     printf("%d",root->data);
     printf("(");
     preorder(root->left);
     printf(")");
     printf("(");
     preorder(root->right);
     printf(")");
    }

}

int main()
{
    struct BST* bst=new_BST();
    int n,i;
    scanf("%d",&n);
    int pre[n];

    for(i=0;i<n;i++)
    {
        scanf("%d",&pre[i]);
        insert(bst,pre[i]);
    }

    printf("(");
    preorder(bst->root);
    printf(")");
    return 0;
}
