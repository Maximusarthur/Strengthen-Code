#include "Public.h"
#include "CTree.h"
char ch;

//二叉树的链式存储结构
typedef struct BiTNode{
	TElemType data;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
}BiTNode,*BiTree;

//按先序次序输入二叉树的结点的值，空格表示空树
Status CreatBiTree(BiTree* T);

//先序遍历二叉树T，对每个结点调用Visit函数一次，若Visit失败则操作失败返回ERROR，否则返回OK
Status PreOrderTraverse(BiTree T,Status (*Visit)(TElemType e));

//中序遍历二叉树T，对每个结点调用Visit函数一次，若Visit失败则操作失败返回ERROR，否则返回OK
Status InOrderTraverse(BiTree T,Status (*Visit)(TElemType e));

//后序遍历二叉树T，对每个结点调用Visit函数一次，若Visit失败则操作失败返回ERROR，否则返回OK
Status PostOrderTraverse(BiTree T,Status (*Visit)(TElemType e));

//将带双亲的孩子链表存储表示的树C，转换成二叉链表表示的二叉树T，now代表根节点所在位置C.r
Status CTreeToBiTree(int now,CTree* C,BiTree* T);




//CreatBiTree操作的实现
Status CreatBiTree(BiTree* T)
{
	scanf("%c",&ch);
	fflush(stdin);
	if(ch == ' ')
		*T = NULL;
	else{
		if(NULL == (*T = (BiTree)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		(*T)->data = ch;                //创建树或子树的根节点
		CreatBiTree(&((*T)->lchild));   //创建坐子树
		CreatBiTree(&((*T)->rchild));   //创建右子树
	}
	return OK;
}
	

//PreOrderTraverse操作的实现
Status PreOrderTraverse(BiTree T,Status (*Visit)(TElemType e)){
	if(T != NULL){
		if(OK == (*Visit)(T->data))                          //访问节点
			if(OK == PreOrderTraverse(T->lchild,Visit))      //遍历左子树
				if(OK == PreOrderTraverse(T->rchild,Visit))  //遍历右子树
					return OK;
		return ERROR;
	}
	else
		return OK;
}

//InOrderTraverse操作的实现
Status InOrderTraverse(BiTree T,Status (*Visit)(TElemType e)){
	if(T != NULL){
		if(OK == InOrderTraverse(T->lchild,Visit))
		    if(OK == (*Visit)(T->data))
				if(OK == InOrderTraverse(T->rchild,Visit))
					return OK;
		return ERROR;
	}
	else
		return OK;
}

//PostOrderTraverse操作的实现
Status PostOrderTraverse(BiTree T,Status (*Visit)(TElemType e)){
	if(T != NULL){
		if(OK == PostOrderTraverse(T->lchild,Visit))
			if(OK == PostOrderTraverse(T->rchild,Visit))
				 if(OK == (*Visit)(T->data))
					return OK;
		return ERROR;
	}
	else
		return OK;
}

//CTreeToBiTree操作的实现
Status CTreeToBiTree(int now,CTree* C,BiTree* T){
	(*T)=(BiTree)malloc(sizeof(BiTNode));      //创建二叉树根（子树的根）节点
	(*T)->data=C->nodes[now].data;
	(*T)->rchild=NULL;                       //首先将节点的rchild置为空，保证转换成的二叉树根节点的右子树为空
	ChildPtr p;                              //p用来暂时存放孩子指针 
	p=C->nodes[now].firstchild;              //将二叉树根（子树的根）节点的第一个孩子指针赋予p
	if(p!=NULL){                             //若二叉树根（子树的根）节点有孩子
		 CTreeToBiTree(p->child,C,&((*T)->lchild));    //创建二叉树根（子树的根）节点的左孩子为该第一个孩子
	 BiTree q = (*T)->lchild;                          //q用来暂时存放兄弟节点的指针
	 p=p->next;            //下一个孩子
	 while(NULL != p){    //所有孩子
		CTreeToBiTree(p->child,C,&(q->rchild));     //创建二叉树根（子树的根）节点的左孩子的右孩子为第一个孩子的兄弟节点
		p=p->next;
		q=q->rchild;
	 }
	}
	else{            //若是叶子节点则置左右孩子为空
		(*T)->lchild=NULL;
		(*T)->rchild=NULL;
	}

	return OK;
}

		



	 