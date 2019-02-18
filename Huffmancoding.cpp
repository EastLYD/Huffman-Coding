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
	 if(HT[j].parent==0)   //ѡ��parentΪ0�Ľ��
	 {

	    k++;
		if(k>3)
		{
		  w3=HT[j].weight;
		  w1=HT[s1].weight;
		  w2=HT[s2].weight;
		  if((w3<w2)&&(w3<w1))   //�Ƚϵ����������֮ǰ�ݴ�Ľ��Ȩֵ��С
            //������������С��ǰ�������򽫽ϴ����滻
		  {
		     if(w2<=w1) s1=j;
			 else s2=j;
		  }
		  if((w3<w2)&&(w3>w1)) s2=j;
		  if((w3<w1)&&(w3>w2)) s1=j;
		}
		if(k==3)  s2=j;   //��ǰ�������Ϊ��Ľ���ݴ�
		if (k==2)  s1=j;
	 }
	}
	 return 1;
}

void HuffmanTreeCreate(HuffmanTree &HT,int n)               //����hfm��
{//w���n���ַ���Ȩֵ������շ�����HT�������n���ַ��ĺշ�������HC

    FILE *fp;
	int m,i,s1,s2;
	int q=1;
	HuffmanTree p;
	int count_n=n;
	if(n<=1) return;
	m=2*n-1;
	//HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)) ;//0�ŵ�Ԫδ��
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
	  //��HT[1...i-1] ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
	  Select(HT,i-1,s1,s2);
	  HT[s1].parent=i;
	  HT[s2].parent=i;
	  HT[i].lchild=s1;
	  HT[i].rchild=s2;
	  HT[i].weight=HT[s1].weight+HT[s2].weight;
	  HT[i].ch='#';

	} //�����շ�����
	if((fp=fopen("E:\\hfmTree.txt","ab"))==NULL)
  {
      printf("can not open the file\n");
      exit(0);
  }
  //�ж��ļ��Ƿ��ܴ�
	for(i=1;i<=m;i++)
    {
        fwrite(&HT[i],sizeof(HTNode),1,fp);
    }//�������ݽ����ļ�
    fclose(fp);
}

void HuffmanCoding(HuffmanTree HT,int n)       //��hfm����
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
	 //��Ҷ�ӵ������������
	 HC=(HuffmanCode)malloc((n+1)*sizeof(char *)); //������n���ַ������ͷָ������

	 cd=(char *)malloc(n*sizeof(char));  //���������Ĺ����ռ�
	 cd[n-1]='\0';
	 for(i=1;i<=n;++i)  //�����
	 {
	   start=n-1;
	   for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
	   {
	      if(HT[f].lchild==c)  cd[--start]='0';
		  else cd[--start]='1';

	   }
	   HC[i]=(char *)malloc((n-start)*sizeof(char)); //Ϊ��i���ַ��������ռ�
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

  //�ж��ļ��Ƿ��ܴ�

}

void decode(HuffmanTree HT,int n)//����
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
            k=2*n-1;   //ÿ�������ͷ��ʼ
        }
        j++;
    }
    fclose(codefile);
    fclose(textfp);
}

void printtree(HuffmanTree Ht,int n)//��ӡ��������
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

void printcode()//��ӡ����������
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
    printf(" �˵�\nI.��ʼ������ϵͳ\nE.����\nD.����\nP.��ʾ����������\nT.��ʾ��������\nQ.�˳�ϵͳ\n") ;
    printf("\n������ѡ��: ");
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
                remove("E:\hfmTree.txt");       //ɾ���ϴ����ɵ��ļ�
                printf("�����������ַ�����");
                scanf("%d",&n);
                m=2*n-1;
                HuffmanTreeCreate(HT,n);
                printf("\n\n\n          ����ϵͳ��ʼ���ɹ���\n\n");
                menu();
                break;
            }
		case 'E':{
		    system("CLS");
		    HuffmanCoding(HT,n);
		    printf("\n����ɹ�\n\n");
		    menu();
		    break;
            }
		case 'D':{
		    system("CLS");
		    printf("\n����Ľ��Ϊ��");
		    decode(HT,n);
		    printf("\n\n");
		    menu();
		    break;
            }
        case 'P':{
            system("CLS");
		    printf("\n����������Ϊ");
		    printcode();
		    printf("\n\n");
		    menu();
		    break;
            }
		case 'T':{
		    system("CLS");
		    printf("\n��ʾ��������\n");
		    Ht=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
		    printtree(Ht,n);
		    printf("\n\n");
		    menu();
		    break;
            }
		case 'Q':{
		    system("CLS");
		    printf("\n�˳�ϵͳ");
		    exit(0);
		    return 0;
            }
        }
	}
    return 0;
}


