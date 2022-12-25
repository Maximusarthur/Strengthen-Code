#include "Public.h"

typedef struct{
	int weight;
	int parent,lchild,rchild;
}HTNode,*HuffmanTree;  //动态分配数组存储赫夫曼树

typedef char **HuffmanCode;  //动态分配数组存储赫夫曼编码表



//求赫夫曼编码,w存放n个字符的权值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
void HuffmanCoding(HuffmanTree* HT,HuffmanCode* HC,int* w,int n){
	int i=1;
	int j=1;
	int firstsmall,secondsmall;
	HuffmanTree p;
	if(n <= 1)
		return;
	int m = 2 * n - 1;
	(*HT) = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));
	(*HT)[0].weight=9999;
	for(p = (*HT) + 1;i <= n;++i,++p,++w){
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for(;i <= m;++i,++p){
		p->weight=0;
	    p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
}
	for(i = n + 1;i <= m;i++){
		//在HT[1...i-1]选择parent为0且weight最小的两个节点，其序号分别为firstsmall和secondsmall
		firstsmall = 0;
	    secondsmall = 0;
		for(j = 1;j <= i-1;j++){
			if((*HT)[j].parent != 0)
				continue;
			if((*HT)[j].weight <= (*HT)[firstsmall].weight || (*HT)[j].weight <= (*HT)[secondsmall].weight){
				if((*HT)[firstsmall].weight <= (*HT)[secondsmall].weight)
					secondsmall = j;
				else
					firstsmall = j;
			}
		}		
		//select(HT,i-1, &firstsmall,&secondsmall);
		(*HT)[firstsmall].parent = i;
		(*HT)[secondsmall].parent = i;
		(*HT)[i].lchild = firstsmall;
		(*HT)[i].rchild=secondsmall;
		(*HT)[i].weight=(*HT)[firstsmall].weight + (*HT)[secondsmall].weight;
	}
	
	//从叶子到根逆向求每个字符的赫夫曼编码
	(*HC) = (HuffmanCode)malloc((n + 1)*sizeof(char*));  //分配n个字符编码的头指针向量
	char* cd = (char*)malloc(n*sizeof(char));  //分配求编码的工作空间
	cd[n-1]='\0';    //编码结束符
	int start;
	int c; //存放当前节点位置
	int f; //存放父节点位置
	for(i=1;i <= n;i++){   //逐个字符求赫夫曼编码
		start = n-1;     //编码结束符位置
		for(c = i,f = (*HT)[i].parent;f != 0;c = f,f = (*HT)[f].parent){ //从叶子到根逆向求编码
			if( (*HT)[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		(*HC)[i] = (char*)malloc((n-start)*sizeof(char)); //为第i个字符编码分配空间
		int k;
		strcpy((*HC)[i],&cd[start]);
	}
	free(cd); //释放cd

}//HuffanCoding
			

























