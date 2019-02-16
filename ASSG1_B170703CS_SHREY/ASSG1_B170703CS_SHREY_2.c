#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fo;
struct stack
{
  char *a;
  int size;
  int top;
};

struct stack* new_stack()
{
	struct stack *s;

	s=(struct stack*)malloc(sizeof(struct stack));
	s->a=(char *)malloc(sizeof(char)*10000);
	s->top=-1;
	s->size=0;

    return s;
}

void push(struct stack *s,char data)
{
	s->a[s->size]=data;
	s->size=(s->size)+1;
	s->top++;
}

void pop(struct stack *s)
{


		 //printf("%d ",s->top);
	 s->a[(s->size)-1]='a';
	 s->size=(s->size)-1;
	 s->top--;
     

}

int precedence(char ch)
{
    switch (ch)
    {
    case '+': return 1;
    case '-': return 1;

    case '*': return 2;
    case '/': return 2;

    case '^': return 0;
    }

    return -1;
}

int isChar(char ch)
{
    if(ch<=122&&ch>=97) return 1;
    return 0;
}

void infix_to_postfix(char *c)
{
    struct stack *s=new_stack();

    int idx=0,i;

    for(i=0;i<strlen(c);i++)
    {
        if(isChar(c[i])) c[idx++]=c[i];

        else if(c[i]=='(') push(s,c[i]);

        else if(c[i]==')')
        {
            while(s->a[s->size -1]!='(')
            {
                c[idx++]=s->a[s->top];
                pop(s);
            }
            pop(s);
        }
     	else if(c[i]==' ') continue;

        else
        {
            while(s->size!=0 && precedence(c[i])<=precedence(s->a[s->top]))
            {
                c[idx++]=s->a[s->top];
                pop(s);
            }
            push(s,c[i]);
        }
    }
        while(s->size!=0)
        {
            c[idx++]=s->a[s->top];
            pop(s);
        }
        c[idx++]='\0';

    fprintf(fo,"%s\n",c);

}

int main()
{

    char *c;
    c=(char *)malloc(sizeof(char)*10000);

    FILE *fp=fopen("input.txt","r");
          fo=fopen("output.txt","w");
	  
    while(fscanf(fp," %[^\n]s",c)!=EOF)
    {
      infix_to_postfix(c);
      c=(char *)malloc(sizeof(char)*10000);
    }

}
