#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define print(a)       printf("%d ",a)
#define newline        printf("\n")
#define scan(a)        scanf("%d",&a)
#define fscanch(fp,ch) fscanf(fp,"%c",&ch)
#define fscans(fp,str) fscanf(fp," %[^\n]s",str)
#define fscan(fp,a)    fscanf(fp,"%d",&a)
FILE *fp;
FILE *fo;
typedef long long ll;
const ll mod=1e9+9;
const ll d=256;
const int N=1e5;

int *idx;
char *t;
char *p;
int count;

void initialise()
{

    idx=(int *)malloc(sizeof(int)*10000);
}

void text()
{
    t=(char *)malloc(sizeof(char)*10000);
    fscanf(fp," %[^\n]s",t);
}

void pattern()
{
    p=(char *)malloc(sizeof(char)*10000);
    fscanf(fp," %[^\n]s",p);
}

void Rabin_karp()
{
    ll p_hash=0,t_hash=0;
    ll n=strlen(t);
    ll m=strlen(p);
    ll isOk=1;

    ll x=1,i,j;              // x=d^m-1
    for(i=1;i<m-2;i++)
       x=((x%mod)*(d%mod))%mod;


    for(i=1;i<m-1;i++)
    {
        p_hash=(((p_hash)*d)%mod+p[i])%mod;
        t_hash=(((t_hash)*d)%mod+t[i])%mod;
    }
    for(i=m-1;i<=n-1;i++)
    {
        isOk=1;
        if(p_hash==t_hash)
        {
            //printf("hi");
            for(j=1;j<m-1;j++)
            {
                if(p[j]!=t[i-(m-1)+j])
                    isOk=0;
            }

            if(isOk)
            {
                idx[count]=i-m+1;
                count++;
            }
        }
       t_hash=((d*(t_hash-(x*t[i+2-m])%mod))%mod+t[i]+mod)%mod;
    }

}


int main()
{
   fp=fopen("input.txt","r");
   fo=fopen("output.txt","w");
   char *ch=(char *)malloc(sizeof(char)*100);
   int i;

    while(fscanf(fp,"%s",ch)!=EOF)
   {
    //printf("%s\n",ch);
    if(ch[0]=='t'){
            initialise();
             text();
    }
    if(strlen(ch)==1&&ch[0]=='p')
    {
        pattern();
        Rabin_karp();
    }
    if(strlen(ch)==2&&ch[1]=='r')
     {
        //print(count);
        for(i=0;i<count;i++)
          fprintf(fo,"%d ",idx[i]);
        fprintf(fo,"\n");
        count=0;
     }
    if(ch[0]=='e') break;

    ch=(char *)malloc(sizeof(char)*100);
   }
    return 0;
}
