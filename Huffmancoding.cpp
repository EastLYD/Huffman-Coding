#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define codemax 300
#define charmax 50
using namespace std;

typedef struct
{
    char ch;
	int weight;
    int parent,lchild,rchild;

}HTNode,*HuffmanTree;
typedef char * *HuffmanCode;



int Select(HuffmanTree HT,int n,int &s1,int &s2)
{
 	int j,k,w1,w2,w3;

	for(j=1,k=1;j<=n;j++)
	{
	 if(HT[j].parent==0)   //选择parent为0的结点
	 {

	    k++;
		if(k>3)
		{
		  w3=HT[j].weight;
		  w1=HT[s1].weight;
		  w2=HT[s2].weight;
		  if((w3<w2)&&(w3<w1))   //比较第三个结点与之前暂存的结点权值大小
            //如果第三个结点小于前两个，则将较大者替换
		  {
		     if(w2<=w1) s1=j;
			 else s2=j;
		  }
		  if((w3<w2)&&(w3>w1)) s2=j;
		  if((w3<w1)&&(w3>w2)) s1=j;
		}
		if(k==3)  s2=j;   //将前两个结点为零的结点暂存
		if (k==2)  s1=j;
	 }
	}
	 return 1;
}

void HuffmanTreeCreate(HuffmanTree &HT,int n)               //建立hfm树
{//w存放n个字符的权值，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC

    FILE *fp;
	int m,i,s1,s2;
	int q=1;
	HuffmanTree p;
	int count_n=n;
	if(n<=1) return;
	m=2*n-1;
	//HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)) ;//0号单元未用
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)) ;
    while(count_n!=0)
    {
        cin >> HT[q].ch;
        cin >> HT[q].weight;
        count_n--;
        q++;
    }
	for(p=HT+1,i=1;i<=m;++i,++p)
    {
        p->lchild=0;
        p->parent=0;
        p->rchild=0;
    }
	for(i=n+1;i<=m;++i)
	{
	  //在HT[1...i-1] 选择parent为0且weight最小的两个结点，其序号分别为s1和s2
	  Select(HT,i-1,s1,s2);
	  HT[s1].parent=i;
	  HT[s2].parent=i;
	  HT[i].lchild=s1;
	  HT[i].rchild=s2;
	  HT[i].weight=HT[s1].weight+HT[s2].weight;
	  HT[i].ch='#';

	} //建立赫夫曼树
	if((fp=fopen("E:\\hfmTree.txt","ab"))==NULL)
  {
      printf("can not open the file\n");
      exit(0);
  }
  //判断文件是否能打开
	for(i=1;i<=m;i++)
    {
        fwrite(&HT[i],sizeof(HTNode),1,fp);
    }//输入数据建立文件
    fclose(fp);
}

void HuffmanCoding(HuffmanTree HT,int n)       //求hfm编码
{
    HuffmanCode HC;
    FILE *rfp1;
    FILE *wfp;
    FILE *tofp;
    char tobetran[charmax];
     char * cd;
     int i,f,c;
     int start;
     int k=0;
	 //从叶子到根逆向求编码
	 HC=(HuffmanCode)malloc((n+1)*sizeof(char *)); //分配存放n个字符编码的头指针向量

	 cd=(char *)malloc(n*sizeof(char));  //分配求编码的工作空间
	 cd[n-1]='\0';
	 for(i=1;i<=n;++i)  //求编码
	 {
	   start=n-1;
	   for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
	   {
	      if(HT[f].lchild==c)  cd[--start]='0';
		  else cd[--start]='1';

	   }
	   HC[i]=(char *)malloc((n-start)*sizeof(char)); //为第i个字符编码分配空间
	   strcpy(HC[i],&cd[start]);

	 }
	  free(cd);

    tofp=fopen("E:\\tobetran.txt","r");
    fgets(tobetran,charmax,tofp);
        printf("%s",tobetran);
      if((wfp=fopen("E:\\CodeFile.txt","a"))==NULL)
  {
      printf("can not open the file\n");
      exit(0);
  }

    while(tobetran[k]!='\0')
    {

        for(i=1;i<=n;i++)
        {
            if(tobetran[k]==HT[i].ch)
                fputs(HC[i],wfp);
        }
        k++;
    }
    fclose(wfp);
    fclose(tofp);

  //判断文件是否能打开

}

void decode(HuffmanTree HT,int n)//译码
{
    int k,j=0,i=0;
    k=2*n-1;
    FILE *codefile,*textfp;
    char b[codemax];
    codefile=fopen("E:\\CodeFile.txt","r");
    textfp=fopen("E:\\TextFile.txt","a");
    fgets(b,codemax,codefile);

    while(b[j]!='\0')
    {
        //printf("%c ",b[j]);
        if(b[j]=='0')
            k=HT[k].lchild;
        else
            k=HT[k].rchild;
        if(HT[k].lchild==0)
        {
            printf("%c",HT[k].ch);
            fputc(HT[k].ch,textfp);
            k=2*n-1;   //每次译码从头开始
        }
        j++;
    }
    fclose(codefile);
    fclose(textfp);
}

void printtree(HuffmanTree Ht,int n)//打印哈夫曼树
{
    FILE *rfp;
    rfp=fopen("E:\hfmTree.txt","r");
    int i;
    	for(i=1;i<=2*n-1;++i)
    {
       // printf("%c %d %d %d %d\n",HT[i].ch,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
       fread(&Ht[i],sizeof(HTNode),1,rfp);
       printf("%c %d %d %d %d\n",Ht[i].ch,Ht[i].weight,Ht[i].parent,Ht[i].lchild,Ht[i].rchild);
   }
   fclose(rfp);
}

void printcode()//打印哈夫曼编码
{
   char code[codemax];
   FILE *codefile;
   codefile=fopen("E:\\CodeFile.txt","r");
   fgets(code,codemax,codefile);
   fclose(codefile);
   printf("%s",code);
}

void menu()
{
    printf(" 菜单\nI.初始化编码系统\nE.编码\nD.译码\nP.显示哈夫曼编码\nT.显示哈夫曼树\nQ.退出系统\n") ;
    printf("\n请输入选项: ");
}
HuffmanTree Ht,HT;
char option;
int n;
int m;
int main(){
    menu();

	while(1){
        scanf("%c",&option);
		switch(option){
            case 'I': {
                system("CLS");
                remove("E:\\CodeFile.txt");
                remove("E:\\TextFile.txt");
                remove("E:\hfmTree.txt");       //删除上次生成的文件
                printf("请输入编码的字符数：");
                scanf("%d",&n);
                m=2*n-1;
                HuffmanTreeCreate(HT,n);
                printf("\n\n\n          编码系统初始化成功！\n\n");
                menu();
                break;
            }
		case 'E':{
		    system("CLS");
		    HuffmanCoding(HT,n);
		    printf("\n编码成功\n\n");
		    menu();
		    break;
            }
		case 'D':{
		    system("CLS");
		    printf("\n译码的结果为：");
		    decode(HT,n);
		    printf("\n\n");
		    menu();
		    break;
            }
        case 'P':{
            system("CLS");
		    printf("\n哈夫曼编码为");
		    printcode();
		    printf("\n\n");
		    menu();
		    break;
            }
		case 'T':{
		    system("CLS");
		    printf("\n显示哈夫曼树\n");
		    Ht=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
		    printtree(Ht,n);
		    printf("\n\n");
		    menu();
		    break;
            }
		case 'Q':{
		    system("CLS");
		    printf("\n退出系统");
		    exit(0);
		    return 0;
            }
        }
	}
    return 0;
}


