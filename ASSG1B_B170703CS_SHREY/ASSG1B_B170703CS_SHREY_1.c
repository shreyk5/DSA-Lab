#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

FILE *fp;
FILE *fo;
const int MAX=1e4;
const int N=1e3;
int time=0;
int code[26][1000];
int arr[10000];

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

int ischar(char ch)
{
    if(ch<=122 && ch>=97) return 1;
    return 0;
}
struct node
{
    char data;
    int t;
    int frequency;
    struct node* left;
    struct node* right;
    struct node* p;
};

int cmp(struct node *x,struct node *y)
{
  if (x->frequency < y->frequency)
    return 1;
  else if (!ischar(x->data) && !ischar(y->data) && (x->frequency == y->frequency))
  {      if(x->t<y->t)
          return 1;
       else if(x->t>y->t)
          return 0;
  }

  else if (!ischar(y->data) && (x->frequency == y->frequency))
    return 1;
  else if (!ischar(x->data) && (x->frequency == y->frequency))
    return 0;
  else if (x->data!= '!' && y->data != '!' && (x->frequency == y->frequency) && (x->data < y->data))
    return 1;
  else
    return 0;
}

struct node* newNode(char ch,int f,int time)
{
  struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->left = temp->right = NULL;
    temp->data = ch;
    temp->frequency = f;
    temp->t=time;

    return temp;
}


struct priority_queue
{
    int size;
    struct node** hash;
};

struct tree
{
    struct node* root;
};

struct priority_queue* newQueue(int n)
{
   struct priority_queue* q=(struct priority_queue*)malloc(sizeof(struct priority_queue));
   q->size=0;
   q->hash=(struct node **)malloc(n*sizeof(struct node*));

   return q;
}

void swap(struct node **a,struct node **b)
{
   struct node* t=*a;
   *a=*b;
   *b=t;
}


void min_heapify(struct priority_queue* q,int idx)
{
    int smallest=idx;

    if((2*idx+1<q->size)&& cmp(q->hash[2*idx+1],q->hash[smallest]))
        smallest=2*idx+1;
    if((2*idx+2<q->size)&& cmp(q->hash[2*idx+2],q->hash[smallest]))
        smallest=2*idx+2;

    if(smallest!=idx)
    {
      swap(&(q->hash[smallest]),&(q->hash[idx]));
      min_heapify(q,smallest);
    }
}

struct node* extract_min(struct priority_queue* q)
{
    struct node* temp=q->hash[0];
    q->size--;
    //printf("MIN:%d\n",q->hash[0]->ch);
    //printf("%c %d\n",q->hash[0]->data,q->hash[0]->frequency);
    q->hash[0]=q->hash[q->size];
    min_heapify(q,0);

    return temp;
}


struct priority_queue* insert(struct priority_queue* q,struct node* temp)
{
   q->size++;
   int i=q->size-1;
   q->hash[i]=temp;
   while(i>0 && cmp(q->hash[i],q->hash[(i-1)/2]))
   {
       swap(&(q->hash[i]),&(q->hash[(i-1)/2]));
       i=(i-1)/2;
   }

   return q;
}

struct priority_queue* buildQueue(char ch[],int freq[],int size)
{
  struct priority_queue* q=newQueue(size);
  int i;
  int n=strlen(ch);
  int flag[26]={0};

  for(i=0;i<n;i++)
  {
    if(!flag[ch[i]-'a'])
    {
     //printf("%c\n",ch[i]);
    flag[ch[i]-'a']=1;
    struct node* temp=newNode(ch[i],freq[ch[i]-'a'],0);
    q=insert(q,temp);
    }
  }

  return q;
}

struct node* huffman(struct priority_queue* q)
{
    int n=q->size;
    int i;
    for(i=0;i<n-1;i++)
    {
        struct node* z=(struct node*)malloc(sizeof(struct node));

        z->left=extract_min(q);
        z->right=extract_min(q);

        z->frequency=z->left->frequency + z->right->frequency;
        z->data='!';
        z->t=time++;
        //printf("%d\n",z->frequency);
        q=insert(q,z);
    }

   return extract_min(q);
}

void store(int n,char ch)
{
    int i;
    int j=0;
    for(i=0;i<n;i++)
    {
     code[ch-'a'][j++]=arr[i];
    }
}

int isLeaf(struct node* curr)
{
    if(curr->left==0&&curr->right==0)
        return 1;
    return 0;
}

void fill_codes(struct node* root,int idx)
{
    if(root->left)
    {
        arr[idx]=0;
        fill_codes(root->left,idx+1);
    }
    if(root->right)
    {
        arr[idx]=1;
        fill_codes(root->right,idx+1);
    }
    if((!(root->left)&&!(root->right)))
    {
        //printf("%c ",root->data);
         store(idx,root->data);
    }
}

void print_codes(char *ch)
{
    int i,j;
    for(i=0;i<strlen(ch);i++)
    {
        for(j=0;j<1000;j++)
        {
            if(code[ch[i]-97][j]!=-1)
            fprintf(fo,"%d",code[ch[i]-97][j]);
            else break;
        }
       fprintf(fo," ");
    }
    fprintf(fo,"\n");
}

void inorder(struct node* root)
{
    if(root)
    {
        inorder(root->left);
        printf("%c->%d\n",root->data,root->frequency);
        inorder(root->right);
    }
}

int main()
{
    fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    int n=0,b,i;
    int j=0;
    char *ch=(char *)malloc(sizeof(char)*100);
    while(fscanf(fp," %[^\n]s",ch)!=EOF)
    {
     int f[26]={0};
    
     for(i=0;i<strlen(ch);i++)
       f[ch[i]-'a']++;

    struct priority_queue* q=buildQueue(ch,f,100);

    struct node* root=huffman(q);
    //inorder(root);

    for(i=0;i<26;i++)
        for(j=0;j<1000;j++)
         code[i][j]=-1;
    
    fill_codes(root,0);
    print_codes(ch);
    ch=(char *)malloc(sizeof(char)*100);
  }
    return 0;
}


