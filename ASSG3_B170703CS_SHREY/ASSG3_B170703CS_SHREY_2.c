#include<stdio.h>
#include<stdlib.h>

#define print(x)    printf("%d",x)
#define scan(x)     scanf("%d",&x)
#define inf         1e9

FILE *fp;
FILE *fo;

int max(int a,int b)
{
    if(a>b) return a;
    return b;
}

int min(int a,int b)
{
    if(a<b) return a;
    return b;
}

struct node
{
    int key;
    int height;
    struct node* left;
    struct node* right;
    struct node* parent;
};

typedef struct node node;

int ht(node *tmp)
{
    if(!tmp) return -1;
    else     return tmp->height;
}

int balance_factor(node *tmp)
{
    return (ht(tmp->left)- ht(tmp->right));
}

node* set_height(node* tmp)
{
    if(!tmp)
    {
        return tmp;
    }

    else
    {
      if(tmp->left && tmp->right)
            tmp->height=1+max(tmp->left->height,tmp->right->height);

      else if(tmp->left)
            tmp->height=1+ tmp->left->height;

      else if(tmp->right)
            tmp->height=1+tmp->right->height;

      else tmp->height=0;
    }

    return tmp;
}

struct avl
{
    int size;
    node* root;
};
typedef struct avl avl;

avl* create_tree()
{
    avl* tree=(avl*)malloc(sizeof(avl));
    tree->size=0;
    tree->root=NULL;

    return tree;
}

node* create_node(int val)
{
    node* tmp=(node*)malloc(sizeof(node));
    tmp->height=-1;
    tmp->key=val;
    tmp->parent=tmp->left=tmp->right=NULL;

    return tmp;
}

node* search_node(avl* tree,int val)
{
    node* x=tree->root;

    while(x)
    {
        if(x->key==val) return x;

        if(x->key>val)
            x=x->left;
        else
            x=x->right;
    }

    return NULL;
}

int succesor(avl* b,int val)
{
    int ans=0,flag=0;
    node* bnode=search_node(b,val);

    if(bnode==NULL)
    {
        printf("NOT FOUND\n");
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
            ans=bnode->key;
            bnode=bnode->left;
        }
      }

      else
      {
         ans=inf;
         bnode=b->root;
         while(bnode->key!=val)
         {
           if(bnode->key>val && ans>val )
           {
             flag=1;
             ans=min(ans,bnode->key);
           }
           if(bnode->key>val) bnode=bnode->left;
           else if(bnode->key<val) bnode=bnode->right;
         }
      }
    }

    if(!flag) printf("NIL\n");
    return ans;
}


node* left_rotate(avl* tree,node *x)
{
    node* xp=x->parent;
    node* y=x->right;
    node* tmp=y->left;

    y->left=x;
    x->parent=y;
    x->right=tmp;
    if(tmp) tmp->parent=x;

    if(xp)
    {
       if(xp->key < y->key )
           xp->right=y;
       else xp->left=y;
    }
    else
    {
        tree->root=y;
    }
    y->parent=xp;

    x=set_height(x);
    y=set_height(y);

    return y;
}

node* right_rotate(avl* tree,node *x)
{
    node* xp=x->parent;
    node* y=x->left;
    node* tmp=y->right;

    y->right=x;
    x->parent=y;
    x->left=tmp;
    if(tmp) tmp->parent=x;

    if(xp)
    {
       if(xp->key < y->key )
           xp->right=y;
       else xp->left=y;
    }
    else tree->root=y;

    y->parent=xp;

    x=set_height(x);
    y=set_height(y);

    return y;
}

avl* insert(avl* tree,int val)
{
    node* tmp=create_node(val);
    node* x=tree->root;
    node* y=NULL;

    if(!x)
    {
        tree->root=tmp;
        tree->root=set_height(tree->root);
    }

    else if(search_node(tree,val)!=NULL)
    {
      return tree;
    }
    else
    {
      while(x)
      {
        y=x;

        if(x->key<val)
            x=x->right;

        else x=x->left;
      }

      if(y->key<val)
      {
          y->right=tmp;
          tmp->parent=y;
      }
      else
      {
          y->left=tmp;
          tmp->parent=y;
      }

      //Now update heights
      //print(tmp->key);
      //printf("\n");
      y=tmp;

      while(y)
      {
        y=set_height(y);
        y=y->parent;
      }
      //print(tmp->parent->height);

      y=tmp->parent->parent;
      node* z;

      while(y)
      {
          if(balance_factor(y)>1)
          {
            if(val < y->left->key)
            {
              y->parent=right_rotate(tree,y);
              z=y->parent;
              while(z)
              {
                  z=set_height(z);
                  z=z->parent;
              }
            }

            else
            {
               y=y->left;
               y->parent=left_rotate(tree,y);

               z=right_rotate(tree,y->parent->parent);

               while(z)
              {
                  z=set_height(z);
                  z=z->parent;
              }
            }
          }

          else if(balance_factor(y)<-1)
          {
             //printf("hi");
             if(val > y->right->key)
            {
               //printf("hi");
              // print(y->key);
              y->parent=left_rotate(tree,y);
              z=y->parent;
              //printf("%d\n",z->key);
              while(z)
              {
                  z=set_height(z);
                 // print(z->height);
                  z=z->parent;
              }
            }

            else
            {
               y=y->right;
               y->parent=right_rotate(tree,y);

               z=left_rotate(tree,y->parent->parent);
               while(z)
              {
                  z=set_height(z);
                  z=z->parent;
              }
            }
          }
          y=y->parent;
      }

    }
    return tree;
}

avl* del(avl* tree,int val)
{
    int a;
    node* z=search_node(tree,val);
    //printf("%d ",z->data);
    
    if(z)
    {
    node* y; //y has to be deleted
    node* x;
    if(z->left==NULL||z->right==NULL)
           y=z;

    else
    {
        a=succesor(tree,val);
        y=search_node(tree,a);
    }
    if(y->left)  x=y->left;
    else         x=y->right;

    if(x!=NULL) x->parent=y->parent;

    if(y->parent==NULL) tree->root=x;
    else if(y->parent->left==y)   y->parent->left=x;
    else if(y->parent->right==y)  y->parent->right=x;

    if(y!=z) z->key=y->key;
    
    node* curr=y->parent;
    
    while(curr)
    {
	   node *tmp1 = curr->parent;
            curr=set_height(curr);

         if(balance_factor(curr)>1 && balance_factor(curr->left)>=0 )
        { 		
            curr->parent=right_rotate(tree,curr);
            
	    curr=tmp1;
        }
        else if(curr->parent && balance_factor(curr)>1 && balance_factor(curr->left)<0)
        {	
            node* tmp=curr->parent;

            curr=curr->left;
            curr->parent=left_rotate(tree,curr);
            z=right_rotate(tree,curr->parent->parent);

            curr=tmp;
        }

        else if(curr->parent && balance_factor(curr)<-1 && balance_factor(curr->right)<=0)
       {
	    curr->parent=left_rotate(tree,curr);
            curr=tmp1;
        }
        else if(balance_factor(curr)<-1 && balance_factor(curr->right)>0)
        {
	    node* tmp=curr->parent;
            curr=curr->right;
            curr->parent=right_rotate(tree,curr);
            z=left_rotate(tree,curr->parent->parent);

            curr=tmp;
        }

        else 
	{
		curr=curr->parent;
        }
    }
   }  
   return tree;
}


void preorder(node* root)
{
    if(root && (root->left||root->right))
    {
       fprintf(fo,"%d",root->key);

       fprintf(fo,"(");
       preorder(root->left);
       fprintf(fo,")");
       //print(root->height);
       fprintf(fo,"(");
       preorder(root->right);
       fprintf(fo,")");
    }
    else if(root)
    {
        //printf("(");
        fprintf(fo,"%d",root->key);
        //printf(")");

    }
}

void printTree(avl* tree)
{
    fprintf(fo,"(");
    preorder(tree->root);
    fprintf(fo,")");
    fprintf(fo,"\n");
}

int isAVL(node* root)
{
    if(root)
    {
        if(balance_factor(root)<=1 && balance_factor(root)>=-1)
        {
            int a=isAVL(root->left);
            int b=isAVL(root->right);
            return a&b;
        }
        else return 0;
    }

    else return 1;
}



int main()
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    avl* tree=create_tree();
    
    int n,k;
    int i;
    
    while(1)
    {
     
       fscanf(fp,"%d",&k);
      
       if(k==9) break;

       else if(k==1)
       {
         fscanf(fp,"%d",&n);
         tree=insert(tree,n);
        // fprintf(fo,"%d\n",isAVL(tree->root));
       }

       else if(k==2)
       {
         fscanf(fp,"%d",&n);
         tree=del(tree,n);
       }

       else if(k==3)
       {
	    fscanf(fp,"%d",&n);
            node* tmp=search_node(tree,n);
            
	    tmp=left_rotate(tree,tmp);

	    while(tmp)
	    {
	      set_height(tmp);
	      tmp=tmp->parent;
	    }
       }

       else if(k==4)
       {
         fscanf(fp,"%d",&n);
	 node *tmp=search_node(tree,n);
	 tmp=right_rotate(tree,tmp);
         
	 while(tmp)
	 {
	  set_height(tmp);
	  tmp=tmp->parent;
	 }
       }

       else if(k==5)
       {
         fscanf(fp,"%d",&n);
	 node* tmp=search_node(tree,n);

	 fprintf(fo,"%d\n",balance_factor(tmp));
       }

       else if(k==6)
        printTree(tree);

       else if(k==7)
       {
         if(isAVL(tree->root)==1)
		 fprintf(fo,"TRUE\n");
	 else fprintf(fo,"FALSE\n");
       }

       else if(k==8)
       {
          fscanf(fp,"%d",&n);
	  node* tmp=search_node(tree,n);

	  if(tmp)
	     fprintf(fo,"TRUE\n");
	  else fprintf(fo,"FALSE\n");
       
       }
    
    }

    //printf("%d",search_node(tree,53)->key);
  
    /*scan(n);
    int a[n];
    for(i=0;i<n;i++)
    {
        scan(a[i]);
        tree=insert(tree,a[i]);
    }
    printTree(tree);
    tree=del(tree,10);
    printTree(tree);
   */


    return 0;
}

