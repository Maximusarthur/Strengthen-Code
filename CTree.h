#include "Public.h"
#define MAX_TREE_SIZE 100

//树的带双亲的孩子链表存储表示
typedef struct CTNode{
	int child;
	struct CTNode* next;
}*ChildPtr;


//定义一个节点项
typedef struct{
	int parent;
	TElemType data;
	ChildPtr firstchild;     //指向第一个孩子
}CTBox;

typedef struct{
	CTBox nodes[MAX_TREE_SIZE];
	int n,r;                 //节点数和根的位置
}CTree;


//初始化一棵树T
Status InitCTree(CTree* T);

//创建一棵树T
Status CreatCTree(CTree* T);

//打印树T
Status pr(CTree* T);


//InitCTree操作的实现
Status InitCTree(CTree* T){
	T->n = 0;
	T->r = 0;
	for(int i=0;i<=MAX_TREE_SIZE-1;i++)    //将所有节点的孩子指针初始化为空
		T->nodes[i].firstchild=NULL;
	return OK;
}


//CreatCTree操作的实现
Status CreatCTree(CTree* T){
	char ch=0;               //用来存放用户输入的字符
	int i=0;
	int j=0;                 //i，j为次数变量
	char p;                 //存放双亲
	printf("请按任意次序输入所有节点的值,输入空格代表结束\n");
	printf("若您想进行二叉树的转换，请按从树根到树底，从最左孩子到最右孩子的次序输入\n");
	scanf("%c",&ch);
	fflush(stdin);         //清除缓冲区
	while(ch != ' '){      //让用户输入节点的值直到用户输入空格
		T->nodes[i].data=ch;
		i++;
		scanf("%c",&ch);
		fflush(stdin);
	}
	printf("\n");
	T->n=i;
	for(i=0;i<=T->n-1;i++){        //让用户输入每个节点的双亲
		printf("请输入%c节点的双亲,若是根节点则输入空格\n",T->nodes[i].data);
		scanf("%c",&p);
		if(' '==p){    //如果是根
			T->nodes[i].parent=-1;//根节点双亲的位置置为-1
			T->r=i;
			fflush(stdin);
			continue;
		}
		fflush(stdin);
		for(j=0;j<=T->n-1;j++){
			if(p != T->nodes[j].data)         //寻找双亲的位置j
				continue;
			T->nodes[i].parent=j;             //将节点的双亲置为j
			ChildPtr q=(ChildPtr)malloc(sizeof(CTNode));   //创建双亲的孩子节点
			q->child=i;
			q->next=NULL;
			ChildPtr r=T->nodes[j].firstchild;
			if(NULL == r)
				T->nodes[j].firstchild=q;
			else{                      
			while(NULL !=r->next)
				r=r->next;
			r->next=q;
			}
			
		}
	}
	return OK;
}


//打印操作的实现
Status pr(CTree* T){
	int i=0;
	int j=0;
	ChildPtr p;
	for(;i<=T->n-1;i++){
		if(T->nodes[i].parent!=-1)
 	        printf("节点值：%c   双亲：%c  ",T->nodes[i].data,T->nodes[T->nodes[i].parent].data);
		else
			printf("节点值：%c   根节点无双亲  ",T->nodes[i].data);
		p=T->nodes[i].firstchild;
		while(NULL != p){
			printf("  孩子：%c   ",T->nodes[p->child].data);
			p=p->next;
		}
		printf("\n");
	}
	return OK;
}




	


