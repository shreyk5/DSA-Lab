#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define forn(i,a,n) for(int i=a;i<n;i++)
FILE *fp;
FILE *fo;

int flag;

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
    int color;          //color=0 -> red , color=1 -> black
    struct node* left;
    struct node* right;
    struct node* parent;
};

typedef struct node node;

node* new_node(int data)
{
    node* tmp=(node*)malloc(sizeof(node));
    tmp->key=data;
    tmp->height=0;
    tmp->color=0;
    tmp->left=tmp->right=tmp->parent=NULL;

    return tmp;
}

struct RBT
{
  node* root;
};

typedef struct RBT RBT;

RBT* new_tree()
{
    RBT* tree=(RBT*)malloc(sizeof(RBT));
    tree->root=NULL;
    return tree;
}

node* left_rotate(RBT* tree,node *x)
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

    return y;
}

node* right_rotate(RBT* tree,node *x)
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

    return y;
}

void inorder(node* root)
{
    if(root && (root->left||root->right))
    {
       if(root->left)
       { 
       fprintf(fo,"(");
       inorder(root->left);
       fprintf(fo,")");
       }
       //print(root->height);
       
       fprintf(fo,"%d",root->key);
       if(root->color==1) fprintf(fo,"B");
       else               fprintf(fo,"R");
       
       if(root->right)
       {
       fprintf(fo,"(");
       inorder(root->right);
       fprintf(fo,")");
       }
    }
    else if(root)
    {
        fprintf(fo,"%d",root->key);
        if(root->color==1) fprintf(fo,"B");
        else               fprintf(fo,"R");
    }
}

void printTree(RBT* tree)
{
    fprintf(fo,"(");
    inorder(tree->root);
    fprintf(fo,")\n");
}

node* rbinsert(RBT* tree,node* r,node* x)
{
    if(!r) 
         return x;
    
    else
    {
        if(x->key<r->key)
        {
            r->left=rbinsert(tree,r->left,x);
            if(r->left->key==x->key) printTree(tree);
            if(r->left)
            r->left->parent=r;
            if(r->left->color==0)
            {
                if((r->left->left && r->left->left->color==0) ||(r->left->right && r->left->right->color==0))
                {
                    if(r->right && r->right->color==0)
                    {
                        flag=1;
                        r->left->color=1;
                        r->right->color=1;
                        r->color=0;
                    }
                    else
                    {
                        if(r->left->left && r->left->left->color==0)
                        {
                        flag=1;    
                        node* y=r;
                        r=right_rotate(tree,y);
                        r->right->color=0;
                        r->color=1;
                        }
                        else if(r->left->right && r->left->right->color==0)
                        {
                            flag=1;
                            r->left=left_rotate(tree,r->left);
                            node* y=r;
                            r=right_rotate(tree,y);
                            r->color=1;
                            r->right->color=0;
                        }
                    }
                }
            }
        }
        else
        {
            r->right=rbinsert(tree,r->right,x);
            if(r->right->key==x->key) printTree(tree);
            if(r->right)
            r->right->parent=r;
            if(r->right->color==0)
            {
                if((r->right->right&&r->right->right->color==0) ||(r->right->left&& r->right->left->color==0))
                {
                    if(r->left && r->left->color==0)
                    {
                        flag=1;
                        r->right->color=1;
                        r->left->color=1;
                        r->color=0;
                    }
                    else
                    {
                        if(r->right->right && r->right->right->color==0)
                        {
                        flag=1;
                        node* y=r;
                        r=left_rotate(tree,y);
                        r->left->color=0;
                        r->color=1;
                        }
                        else if(r->right->left && r->right->left->color==0)
                        {
                            flag=1;
                            r->right=right_rotate(tree,r->right);
                            node* y=r;
                            r=left_rotate(tree,y);
                            r->color=1;
                            r->left->color=0;
                        }
                        
                    }
                }
            }
        }
        return r;
    }
    return r;
}

RBT* insert(RBT* tree,int data)
{
    flag=0;
    node* tmp=new_node(data);
    if(!(tree->root))
    {
        tree->root=tmp;
        tmp->color=1;
        printTree(tree);
    }
    
    else
    {
        tree->root=rbinsert(tree,tree->root,tmp);
        if(tree->root->color==0) tree->root->color=1;
        if(flag) printTree(tree);
    }
    return tree;    
}
        

int main()
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    RBT* tree=new_tree();
    int i=0,n=0,j;
    
    n=0;
    char *str=(char*)malloc(sizeof(char)*100);
    while(fscanf(fp," %[^\n]s",str)!=EOF)
    {
      n=0;
      //printf("%s",str);
      forn(i,0,strlen(str)-1)
      n=n*10+(str[i]-48);

      tree=insert(tree,n);
      str=(char*)malloc(sizeof(char)*100);
    }
    //printf("%d\n",i);
    //tree=insert(tree,n); 
    //printTree(tree);
    return 0;
}
