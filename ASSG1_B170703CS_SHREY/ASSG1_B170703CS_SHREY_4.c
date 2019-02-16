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

void findMin(struct BST* b)
{
    int ans=-1;
    struct BST_node* bnode=b->root;
    while(bnode!=NULL)
    {
        ans=bnode->data;
        bnode=bnode->left;
    }
    if(b->root==NULL) fprintf(fo,"NIL\n");
    else              fprintf(fo,"%d\n",ans);
}

void findMax(struct BST* b)
{
    int ans=-1;
    struct BST_node* bnode=b->root;
    while(bnode!=NULL)
    {
        ans=bnode->data;
        bnode=bnode->right;
    }
    if(b->root==NULL) fprintf(fo,"NIL\n");
    else              fprintf(fo,"%d\n",ans);
}

int succesor(struct BST* b,int val)
{
    int ans=0,flag=0;
    struct BST_node* bnode=Search(b,b->root,val);

    if(bnode==NULL)
    {
        fprintf(fo,"NOT FOUND\n");
        return -1;
    }

    else
    {
      if(bnode->right!=NULL)
      {
        bnode=bnode->right;
        while(bnode!=NULL)
        {
            flag=1;
            ans=bnode->data;
            bnode=bnode->left;
        }
      }

      else
      {
         ans=inf;
         bnode=b->root;
         while(bnode->data!=val)
         {
           if(bnode->data>val && ans>val )
           {
             flag=1;
             ans=min(ans,bnode->data);
           }
           if(bnode->data>val) bnode=bnode->left;
           else if(bnode->data<val) bnode=bnode->right;
         }
      }
    }

    if(!flag) fprintf(fo,"NIL\n");
    return ans;
}

int predeccesor(struct BST* b,int val)
{
    int ans=0;
    int flag=0;
    struct BST_node* bnode=Search(b,b->root,val);
    if(bnode==NULL)
    {
        fprintf(fo,"NOT FOUND\n");
        return -1;
    }

    else
    {
      if(bnode->left!=NULL)
      {
        bnode=bnode->left;
        while(bnode!=NULL)
        {
            flag=1;
            ans=bnode->data;
            bnode=bnode->right;
        }
      }

      else
      {
         ans=-1;
         bnode=b->root;

         while(bnode->data!=val)
         {

           if(bnode->data<val)
           {
            flag = 1;
            ans=max(ans,bnode->data);
             //printf("%d\n",ans);
           }
           if(bnode->data>val) bnode=bnode->left;
           else if(bnode->data<val) bnode=bnode->right;
         }
      }
    }
    //printf("%d\n",flag);
    if(!flag) fprintf(fo,"NIL\n");
    return ans;
}

void del(struct BST* bst,int val)
{
    int a;
    struct BST_node* z=Search(bst,bst->root,val);
    //printf("%d ",z->data);
    struct BST_node* y; //y has to be deleted
    struct BST_node* x;
    if(z->left==NULL||z->right==NULL)
           y=z;
    else
    {
        a=succesor(bst,val);
        //printf("%d ",a);
        y=Search(bst,bst->root,a);
    }
    if(y->left)  x=y->left;
    else         x=y->right;

    if(x!=NULL) x->p=y->p;

    if(y->p==NULL) bst->root=x;
    else if(y->p->left==y)   y->p->left=x;
    else if(y->p->right==y)  y->p->right=x;

    if(y!=z) z->data=y->data;

}


void inorder(struct BST_node* root)
{
    if(root!=NULL)
    {
    inorder(root->left);
    fprintf(fo,"%d ",root->data);
    inorder(root->right);
    }
}

void preorder(struct BST_node* root)
{
    if(root!=NULL)
    {
        fprintf(fo,"%d ",root->data);
    preorder(root->left);

    preorder(root->right);
    }
}

void postorder(struct BST_node* root)
{
    if(root!=NULL)
    {
     postorder(root->left);
     postorder(root->right);
     fprintf(fo,"%d ",root->data);
    }
}


int main()
{
   fp=fopen("input.txt","r");
   fo=fopen("output.txt","w");
   struct BST* bst=new_BST();
   int n,i;

   char c[4];

   while(fscanf(fp,"%s",c)!=EOF)
   {
       if(strcmp(c,"maxm")==0)
         findMax(bst);

       else if(strcmp(c,"minm")==0)
         findMin(bst);

       else if(strcmp(c,"srch")==0)
       {
         fscanf(fp,"%d",&n);
         if(Search(bst,bst->root,n)==NULL) fprintf(fo,"NOT FOUND\n");
         else                              fprintf(fo,"FOUND\n");

       }
       else if(strcmp(c,"insr")==0)
       {
            fscanf(fp,"%d",&n);
            insert(bst,n);
       }
       else if(strcmp(c,"delt")==0)
       {
            fscanf(fp,"%d",&n);
            del(bst,n);
       }
       else if(strcmp(c,"pred")==0)
       {
           fscanf(fp,"%d",&n);
           n=predeccesor(bst,n);
       }
       else if(strcmp(c,"succ")==0)
       {
           fscanf(fp,"%d",&n);
           n=succesor(bst,n);
       }

       else if(strcmp(c,"inor")==0)
        {
            inorder(bst->root);
            fprintf(fo,"\n");
        }

       else if(strcmp(c,"prer")==0)
          {
              preorder(bst->root);
              fprintf(fo,"\n");
          }

       else if(strcmp(c,"post")==0)
          {
              postorder(bst->root);
              fprintf(fo,"\n");
          }
   }

   return 0;
}
