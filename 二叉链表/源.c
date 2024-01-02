#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0

typedef char BitreeElemType;
typedef struct BiNode {
	BitreeElemType data;
	struct BiNode* lchild, * rchild;
}BiNode;
typedef struct BiNode* BiTree;


#define MAXSIZE 100
typedef BiTree SElemType;
typedef struct {
	SElemType* top;  //顺序栈顶指针
	SElemType* base; //顺序栈底指针
	int stacksize;   //顺序栈最大容量
}SqStack;
int InitStack(SqStack*);
int IsEmpty(SqStack);
int Push(SqStack*, SElemType);
int Pop(SqStack*, SElemType*);


typedef BiTree QElemType;
typedef struct {
	QElemType* base;  //动态分配存储空间
	int front;     //头指针
	int rear;      //尾指针
}SqQueue;
int InitQueue(SqQueue*);
int EnQueue(SqQueue*, QElemType);
int DeQueue(SqQueue*, QElemType*);


void CreateBiTree(BiTree* T); //前序遍历创建

//遍历----------------------------------------

void PreOrderTraverse(BiTree);  //前序遍历
void InOrderTraverse(BiTree);  //中序遍历
void PostOrderTraverse(BiTree);  //后序遍历

void InOrderTraverse_Stack(BiTree); //中序遍历的非递归算法
void LevelOder(BiTree);  //层次遍历
//--------------------------------------------

void Copy(BiTree, BiTree*);  //复制二叉树
int Depth(BiTree);     //计算深度
int Nodes(BiTree);    //计算总结点数
int LeafNodes(BiTree);    //计算叶子结点数
void Destroy(BiTree*);  //后序销毁二叉树


int main(void)
{
	BiTree T = NULL;
	CreateBiTree(&T);



//	PreOrderTraverse(T);
//	InOrderTraverse(T);
//	PostOrderTraverse(T);
//	InOrderTraverse_Stack(T);
	LevelOder(T);

	BiTree NewT;
	Copy(T, &NewT);
	printf("Depth %d\n", Depth(T));
	printf("Nodes %d\n", Nodes(T));
	printf("LeafNodes %d\n", LeafNodes(T));
	Destroy(&T);
	return 0;
}

/* 初始化顺序栈 */
int InitStack(SqStack* S)
{
	S->base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	if (!S->base) exit(-1);  //失败

	S->top = S->base;  //栈顶指针 = 栈底指针
	S->stacksize = MAXSIZE;

	return OK;
}
/* 判断空栈*/
int IsEmpty(SqStack S)
{
	if (S.base == S.top)
		return OK;
	else
		return ERROR;
}
/* 顺序栈的入栈 */
int Push(SqStack* S, BiTree Tree)
{
	if (S->top - S->base == S->stacksize)  //栈满了
		return ERROR;
	*++S->top = Tree;  // S->top++; *S->top = Tree;
	return OK;
}
/* 顺序栈的出栈 */
int Pop(SqStack* S,BiTree *Tree)
{
	if (S->top == S->base)   //空栈
		return ERROR;

	*Tree = *S->top--;  // *Tree = *S->top; S->top--; 
	return OK;
}



/* 初始化循环队列 */
int InitQueue(SqQueue* Q)
{
	Q->base = (QElemType*)malloc(MAXSIZE * sizeof(QElemType));
	if (!Q->base) exit(-1);
	Q->front = Q->rear = 0; //头指针与尾指针都为0
		return OK;
}
/* 循环队列入队 */
int EnQueue(SqQueue* Q, QElemType Tree)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)  //队满
		return ERROR;
	Q->base[Q->rear] = Tree;
	Q->rear = (Q->rear + 1) % MAXSIZE;  //队尾指针 + 1
	return OK;
}
/* 循环队列出队 */
int DeQueue(SqQueue* Q, QElemType* Tree)
{
	if (Q->front == Q->rear) return ERROR;
	*Tree = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;  //队头指针 + 1
	return OK;
}





/* 前序遍历创建 */
void CreateBiTree(BiTree* T)
{
	BitreeElemType ch;
	scanf(" %c", &ch);
	if (ch == '#') //我们用'#'表示空树
		*T = NULL;
	else 
	{
		*T = (BiTree)malloc(sizeof(BiNode));
		(*T)->data = ch;       //生成根结点
		CreateBiTree(&(*T)->lchild); //构造左子树
		CreateBiTree(&(*T)->rchild); //构造右子树
	}
}

/* 前序遍历 */
void PreOrderTraverse(BiTree T)
{
	if (!T) return;
	printf("%c\n", T->data);
	PreOrderTraverse(T->lchild); //先序遍历左子树
	PreOrderTraverse(T->rchild); //先序遍历右子树
}

/* 中序遍历 */
void InOrderTraverse(BiTree T)
{
	if (!T) return;
	InOrderTraverse(T->lchild); //先序遍历左子树
	printf("%c\n", T->data);
	InOrderTraverse(T->rchild); //先序遍历右子树
}

/* 后序遍历 */
void PostOrderTraverse(BiTree T)
{
	if (!T) return;
	PostOrderTraverse(T->lchild); //先序遍历左子树
	PostOrderTraverse(T->rchild); //先序遍历右子树
	printf("%c\n", T->data);

}
/* 中序遍历的非递归算法 */
// 1.建立栈
// 2.根结点入栈 ，遍历左左子树
// 3.根结点出栈，输出根结点,遍历右子树
void InOrderTraverse_Stack(BiTree T)
{
	SqStack S;
	InitStack(&S);
	BiTree p = T;
	while (p || !IsEmpty(S))
	{
		if (p)
		{
			Push(&S, p);//根结点入栈(顺序入栈一定要同类型呀，注意SElemType为Bitree)
			p = p->lchild;
		}
		else
		{
			Pop(&S,&p);//原栈顶元素给p(顺序处栈也要同类型，注意SElemType为Bitree)

			//输出根结点,遍历右子树
			printf("%c\n", p->data);
			p = p->rchild;
		}
	}
}

/* 层次遍历 */
void LevelOder(BiTree T)
{
	BiTree p = NULL;
	SqQueue Q;
	InitQueue(&Q);
	EnQueue(&Q, T);   //根结点入队
	while (Q.front != Q.rear)  //队不为空
	{
		DeQueue(&Q, &p);   //出队结点p
		printf("%c\n", p->data);
		if (p->lchild)    //有左孩子,入队
			EnQueue(&Q, p->lchild);
		if (p->rchild)    //有右孩子,入队
			EnQueue(&Q, p->rchild);
	}
}

/* 复制二叉树 */
void Copy(BiTree T, BiTree* NewT)
{
	if (!T)
	{
		*NewT = NULL;
		return;
	}
	else
	{
		*NewT = (BiTree)malloc(sizeof(BiTree));
		(*NewT)->data = T->data;
		Copy(T->lchild, &(*NewT)->lchild);
		Copy(T->rchild, &(*NewT)->rchild);
	}
}

/* 计算深度 */
int Depth(BiTree T)
{
	if (!T) return 0;

	return Depth(T->lchild) > Depth(T->rchild) ? Depth(T->lchild) + 1 : Depth(T->rchild) + 1;

}

/* 计算总结点数 */
int Nodes(BiTree T)
{
	if (!T) return 0; //空树
	else
	return Nodes(T->lchild) + Nodes(T->rchild) + 1;
}

/* 计算叶子结点数 */
int LeafNodes(BiTree T)
{
	if (!T)    //空树
		return 0;
	if (!T->lchild && !T->rchild) //叶子结点
		return 1;
	else
		return LeafNodes(T->lchild) + LeafNodes(T->rchild);
}
/* 后序销毁二叉树 */
void Destroy(BiTree* T)
{
	if (!(*T)) return;
	else
	{
		Destroy(&(*T)->lchild);
		Destroy(&(*T)->rchild);
		free(*T);
		*T = NULL;
	}

}
