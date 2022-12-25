#include "BiTree.h"
#include "HuffmanCode.h"
#define MAXSIZE 100
#define MAXSIZE_msg 200
#define MAXSIZE_Code 50

//定义Visit函数
Status print(TElemType e){
	printf("%c",e);
	return OK;
}

//A难度模块
int Apro(void){
	BiTree T; //定义二叉树T（二叉链表表示法）
	printf("按先序次序输入二叉树的结点的值，空格表示空树\n");
	CreatBiTree(&T);//建立二叉树
	Status (*Visit)(TElemType e)=print; //函数指针Visit指向print
	printf("生成二叉树的前序输出：\n");
	PreOrderTraverse(T,Visit);   //前序遍历
	printf("\n");
	printf("生成二叉树的中序输出：\n");
	InOrderTraverse(T,Visit);   //中序遍历
	printf("\n");
	printf("生成二叉树的后序输出：\n");
	PostOrderTraverse(T,Visit);  //后序遍历
	printf("\n");
	printf("按下Y返回上一级，按其他任意键退出程序");
	char ch=getch();
	if(ch==121||ch==89)
		return 1;  //返回上一级
	else
	    exit(0);   //退出程序
}


//B难度模块
int Bpro(void){
	CTree C;    //定义树C（孩子链表表示法）
	BiTree T;   //定义二叉树T（二叉链表表示法）
	InitCTree(&C); //初始化树C
	CreatCTree(&C); //建立树C
	printf("请确认您输入的树的信息:\n");
	pr(&C);
	printf("按任意键开始将树转换为二叉树:\n");
	fflush(stdin);
	getch();
	CTreeToBiTree(C.r,&C,&T); //将树C转换成二叉树T
	Status (*Visit)(TElemType e)=print; ////函数指针Visit指向print
	printf("转换中...完成\n");
	printf("转换成的二叉树的前序输出：\n");
	PreOrderTraverse(T,Visit); //前序输出转换后的树T
	printf("\n");
	printf("转换成的二叉树的中序输出：\n");
	InOrderTraverse(T,Visit);  //中序输出转换后的树T
	printf("\n");
	printf("转换成的二叉树的后序输出：\n");
	PostOrderTraverse(T,Visit);  //后序输出转换后的树T
	printf("\n");
	printf("按下Y返回上一级，按其他任意键退出程序");
	char ch=getch();
	if(ch==121||ch==89)
		return 1;  //返回上一级
	else
	    exit(0);   //退出程序
}

int Cpro1(void){
	HuffmanTree HT;//定义赫夫曼树
	HuffmanCode HC;//定义赫夫曼编码
	int n;//字符个数
	char select;
	char* ch;//存放字符
	char houzhui1[]="HuffmanCode.txt";
	char houzhui2[]="KeyToCode.Key";
	int* w;//存放权重
	int i,j=0;//循环变量
	FILE* fp;//文件流结构体 
	char e; //存放加密编码时从文件中读出的字符
	char* file = (char*)malloc(sizeof(char) * MAXSIZE);//定义存放文件路径的一维数组
	printf("请输入您想加密的字符个数：\n");
	scanf("%d",&n);
	ch = (char*)malloc(n * sizeof(char)); //存放用户加密的字符
	w = (int*)malloc(n * sizeof(int));    //存放对应字符的权重
	fflush(stdin); 
	printf("请输入您想加密的字符及其权重（空格分开），按回车完成一项的输入：\n");
	for(i = 0;i <= n-1;i++){              //让用户依次输入加密的字符和权值
		scanf("%c %d",&ch[i],&w[i]);
		fflush(stdin);
	}
	printf("生成编码中...完成\n");
	printf("生成的各字符的赫夫曼编码如下:\n");
	HuffmanCoding(&HT,&HC,w,n);  //生成赫夫曼编码
    for(i=1;i<=n;i++){    //打印生成的赫夫曼编码
	  printf("%c:",ch[i-1]);
      printf("%s",HC[i]);
	  printf("\n");
    }
	printf("是否导出编码信息？ Y\\N\n");
	select=getch();
	fflush(stdin);
	if(select == 121 || select == 89){
		printf("请输入编码信息的保存路径\n");
		gets(file); 
		 strcat(file,houzhui1);
		while(!(fp=fopen(file,"w+"))){   //若打开文件失败则提示用户重新输入文件路径
		  printf("请输入正确路径：\n");
		  gets(file); 
		  strcat(file,houzhui1);
	    }    
		for(i = 0;i <= n-1;i++){   //导出编码到指定文件
		fputc(ch[i],fp);
		fputc(':',fp);
		while( HC[i+1][j] != '\0'){
			fputc(HC[i+1][j],fp);
			j++;
		}
		j = 0;
		fputc('\n',fp);
	}
	fclose(fp);
	printf("编码信息文件已生成\n");
	}
	j=0; //循环变量重新赋值
	printf("请输入生成的密匙路径\n");  
	gets(file);   //得到输入的文件路径
	strcat(file,houzhui2);
	while(!(fp=fopen(file,"w+"))){   //若打开文件失败则提示用户重新输入文件路径
		printf("建立密匙失败，请确认密匙路径是否正确\n");
		gets(file); 
		strcat(file,houzhui2);
	}    
	for(i = 0;i <= n-1;i++){  //将ASCII码进行处理后导入密匙，形成加密文件
		fputc(ch[i]+168,fp);
		while( HC[i+1][j] != '\0'){
			fputc(HC[i+1][j]+168,fp);
			j++;
		}
		j = 0;
		fputc('#'+168,fp);
	}
	fclose(fp);
	printf("密匙创建成功，它将是解码的唯一凭证\n");
	printf("按下Y返回上一级，按其他任意键退出程序");
	char chh=getch();
	if(chh==121||chh==89)
		return 1;  //返回上一级
	else
	    exit(0);   //退出程序
}


int Cpro2(void){
	int i,j=0;//循环变量
	char* msg = (char*)malloc(sizeof(char) * MAXSIZE_msg);//存放要解码的信息
	printf("请输入您想解码的信息\n");
	gets(msg);
	HuffmanCode HCC; //存放从密匙中读入的信息
	HCC = (char**)malloc(MAXSIZE_Code * sizeof(char*));
	HCC[0] = (char*)malloc((MAXSIZE_Code*MAXSIZE_Code) * sizeof(char)); //为赫夫曼编码表生成空间
	for(i = 1;i <= MAXSIZE_Code - 1;i++)
		HCC[i]=HCC[i-1] + MAXSIZE_Code;
	printf("请输入要载入的密匙路径：\n");
	char* file2 = (char*)malloc(sizeof(char) * MAXSIZE);//定义存放文件路径的一维数组
	FILE* fp2;
	gets(file2);   //得到输入的文件路径
	while(!(fp2=fopen(file2,"r"))){   //若打开文件失败则提示用户重新输入文件路径
		printf("打开密匙失败，请确认密匙路径:\n");
		gets(file2); 
	}    
	char e;
	e=fgetc(fp2) - 168; //e存放从密匙中读取的一个字符
    i=1; //循环变量重新赋值
    while(e != EOF){     //导入密匙信息
		if(e != '#'){
			HCC[i][j] = e;
			j++;
		}
		else{
			HCC[i][j] = '\0';
			i++;
			j = 0;
		}
		e=fgetc(fp2);
		if( e != EOF)
			e = e-168;
	
	}
	int z = i-1;//z代表字符个数
	i=0;// 循环变量重新赋值
	int b = 1;//指示当前匹配到第几个字符
	int d = 1;//指示当前匹配到字串的第d个字符
	int n; //指示当前从第几个msg开始比的
	printf("解码中...完成\n");
	printf("代表信息如下：\n");
	while(msg[i] != '\0'){
		n = i;
		while(b <= z){
			while((msg[n] == HCC[b][d])&&(!((msg[n] == '\0')&&(HCC[b][d] == '\0')))){ //当前字符匹配则指针前移
				n++;
				d++;
			}
			if(HCC[b][d] == '\0'){ // 判断是否匹配
				printf("%c",HCC[b][0]); //输出编码
				i = n; //变量重新赋值
				b = 1;
				d = 1;
				break;
			}
			else if(n == z){ //如果是最后一个字符完成匹配查询，则主串指针前移一个字符继续匹配
				i++;
				b = 1;
				d = 1;
				break;
			}
			else{ // 匹配下一个字符的赫夫曼编码
				n=i;
				b++;
				d=1;
			}
		}
	}
	printf("\n按下Y返回上一级，按其他任意键退出程序");
	char chh=getch();
	if(chh==121||chh==89)
		return 1;  //返回上一级
	else
	    exit(0);   //退出程序
}



int main(){
 begin:system("cls");
	int select; //存放用户选择的难度
	printf("输入1转入难度A对应程序（建立二叉树并实现二叉树的先根、中根、后根遍历）\n");
	printf("输入2转入难度B对应程序（树的建立、树与二叉树的相互转换）\n");
	printf("输入3转入难度C对应程序（赫夫曼编码/译码器）\n");
	scanf("%d",&select);
	fflush(stdin); //清空缓存区
	switch(select){
	case 1:{
		if(Apro() == 1)        //执行A难度程序
			goto begin;}break;
	case 2:{
		if(Bpro() == 1)        //执行B难度程序
			goto begin;}break;
	case 3:{
		printf("输入1进入编码加密器，输入2进入编码解密器\n");
		int select2;
		scanf("%d",&select2);
		fflush(stdin);
		switch(select2){
		case 1:{
		    if(Cpro1() == 1)      //执行编码程序
			    goto begin;}
		case 2:{
			if(Cpro2() == 1)      //执行解码程序
				goto begin;}
		}break;
    }
  }
	return 0;
}

