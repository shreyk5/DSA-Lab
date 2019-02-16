#include<stdio.h>
#include<stdlib.h>

FILE *fp;
FILE *fo;

const int N=1e5;

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

struct node
{
   int data;
   int height;
   struct node *left;
   struct node *right;
   struct node *p;  // parent node
};

struct binaryTree
{
    struct node* root;

};

struct binaryTree* new_tree()
{
    struct binaryTree* tree=(struct binaryTree*)malloc(sizeof(struct binaryTree));
    tree->root=NULL;
    return tree;
};


int updateHeight(struct binaryTree* tree,struct node* bnode)
{

    if(bnode==NULL)             return  -1;
    else if(bnode->height!=-2)  return bnode->height;
       //  printf("%d ",bnode->height);
    else
        return bnode->height=max(updateHeight(tree,bnode->left)+1,updateHeight(tree,bnode->right)+1);
}

int updateDiameter(struct binaryTree* tree,struct node* bnode)
{
    if(bnode->left==NULL&&bnode->left==NULL) return 0;
    if(bnode->left==NULL)                    return updateDiameter(tree,bnode->right);
    if(bnode->right==NULL)                   return updateDiameter(tree,bnode->left);
    else return max(bnode->left->height+bnode->right->height+2,max(updateDiameter(tree,bnode->left),updateDiameter(tree,bnode->right)));

}


int findIndex(char *a,int i)
{
    int count=0;
    int flag=0;
    int j;

    for(j=i;j<strlen(a);j++)
    {
       if(flag&&count==0)
            break;

       if(a[j]=='(')
       {
           flag=1;
           count++;
       }
        else if(a[j]==')')
         count--;
    }
    return j-1;
}

int number(char *a,int i)
{
    int num=0;
    int j;
    for(j=i;j<strlen(a);j++)
    {
        if(a[j]=='('||a[j]==')')
            break;
        num=num*10+(a[j]-48);
    }
    return num;
}

struct node* construct(int i,char *a,struct node* root)
{
    if(a[i]==')') return NULL;

    else
    {
       struct node* new_node=(struct node*)malloc(sizeof(struct node));
       new_node->data=number(a,i);
       new_node->height=-2;
       new_node->left=NULL;
       new_node->right=NULL;
       root=new_node;

       int idx=findIndex(a,i);

       root->left=construct(i+log10(new_node->data)+2,a,root->left);
       root->right=construct(idx+2,a,root->right);

       if(root->left) root->left->p=root;
       if(root->right) root->right->p=root;

       return root;
    }
}

void inorder(struct node* root)
{
    if(root)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void preorder(struct node* root)
{
    if(root!=NULL)
    {
     printf("%d ",root->data);
     preorder(root->left);
     preorder(root->right);
    }

}

void width(struct node* root,int *level,int l)
{
    if(root)
    {
    level[l]++;
    width(root->left,level,l+1);
    width(root->right,level,l+1);
    }
}

int main()
{
    int i,j=0;
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    char *a=(char*)malloc(sizeof(char)*100000);
    fscanf(fp,"%[^\n]%*c",a);
    //printf("%s",a);
    //printf("%d ",findIndex(a,3));
    char *s=(char*)malloc(sizeof(char)*100000);
    //printf("%s\n",a);

    for( i=0;i<strlen(a);i++)
    {
        if(a[i]!=' ')
        s[j++]=a[i];
    }
    //printf("%s",s);
    struct binaryTree* tree=new_tree();
    tree->root=construct(1,s,tree->root);
    fprintf(fo,"%d ",updateHeight(tree,tree->root));
    fprintf(fo,"%d ",updateDiameter(tree,tree->root));
    //inorder(tree->root);

    int max_width=0;
    int level[N];
    for(i=0;i<N;i++) level[i]=0;
    width(tree->root,level,0);
    for(i=0;i<N;i++)
    {
        //printf("%d ",level[i]);
        max_width=max(max_width,level[i]);
    }
    fprintf(fo,"%d ",max_width);

}
