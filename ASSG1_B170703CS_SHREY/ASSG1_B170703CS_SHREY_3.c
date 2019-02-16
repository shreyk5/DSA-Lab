#include<stdio.h>
#include<stdlib.h>
#define inf 1e9

FILE *fo;
struct stack
{
  int *a;
  int size;
  int top;
};

struct stack* new_stack()
{
	struct stack *s;

	s=(struct stack*)malloc(sizeof(struct stack));
	s->a=(int *)malloc(sizeof(int)*100000);
	s->top=-1;
	s->size=0;

    return s;
}

void push(struct stack *s,int data)
{
	s->a[s->size]=data;
	s->size=(s->size)+1;
	s->top++;
}

void pop(struct stack *s)
{
	 if(s->size==0) printf("EMPTY\n");
	 else
     {
		 //printf("%d ",s->top);
		 s->a[(s->size)-1]='a';
		 s->size=(s->size)-1;
	     s->top--;
     }
}

void evaluatePostfix(char *ch)
{
    int ans=0;
    int num=0;
    int i=0;
    //printf("%s\n",ch);
    struct stack* s=new_stack();
    //printf("%d\n",strlen(ch));
    while(i<strlen(ch))
    {
     num=0;
      while(ch[i]<=57&&ch[i]>=48)
      {
        num=num*10+(ch[i]-48);
        i++;
      }
      //printf("%d\n",num);
     if(ch[i]==' '&&ch[i-1]>=48&&ch[i-1]<=57) push(s,num);
     else if(ch[i]=='*')
     {
       ans=((s->a[s->top-1])*(s->a[s->top]));
       pop(s);
       pop(s);
       push(s,ans);
     }
    else if(ch[i]=='+')
    {
       ans=((s->a[s->top-1])+(s->a[s->top]));
       pop(s);
       pop(s);
       push(s,ans);
    }
    else if(ch[i]=='-')
    {
       ans=((s->a[s->top-1])-(s->a[s->top]));
       pop(s);
       pop(s);
       push(s,ans);
    }
    else if(ch[i]=='/')
    {
       if(s->a[s->top]!=0)
       ans=((s->a[s->top-1])/(s->a[s->top]));
       else
       {
           ans=inf;
           break;
       }
       pop(s);
       pop(s);
       push(s,ans);
    }
    else if(ch[i]=='^')
    {
       ans=((s->a[s->top-1])^(s->a[s->top]));
       pop(s);
       pop(s);
       push(s,ans);
    }
    i++;
  }
  print(ans);
}

void print(int ans)
{
    if(ans!=inf)
    fprintf(fo,"%d\n",ans);

    else fprintf(fo,"Invalid input\n");
}

int main()
{
    FILE *fp=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    char *ch=(char *)malloc(sizeof(char)*100000);

    while(fscanf(fp," %[^\n]s",ch)!=EOF)
    {
      evaluatePostfix(ch);
      ch=(char *)malloc(sizeof(char)*100000);
    }

}
