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
	SElemType* top;  //˳��ջ��ָ��
	SElemType* base; //˳��ջ��ָ��
	int stacksize;   //˳��ջ�������
}SqStack;
int InitStack(SqStack*);
int IsEmpty(SqStack);
int Push(SqStack*, SElemType);
int Pop(SqStack*, SElemType*);


typedef BiTree QElemType;
typedef struct {
	QElemType* base;  //��̬����洢�ռ�
	int front;     //ͷָ��
	int rear;      //βָ��
}SqQueue;
int InitQueue(SqQueue*);
int EnQueue(SqQueue*, QElemType);
int DeQueue(SqQueue*, QElemType*);


void CreateBiTree(BiTree* T); //ǰ���������

//����----------------------------------------

void PreOrderTraverse(BiTree);  //ǰ�����
void InOrderTraverse(BiTree);  //�������
void PostOrderTraverse(BiTree);  //�������

void InOrderTraverse_Stack(BiTree); //��������ķǵݹ��㷨
void LevelOder(BiTree);  //��α���
//--------------------------------------------

void Copy(BiTree, BiTree*);  //���ƶ�����
int Depth(BiTree);     //�������
int Nodes(BiTree);    //�����ܽ����
int LeafNodes(BiTree);    //����Ҷ�ӽ����
void Destroy(BiTree*);  //�������ٶ�����


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

/* ��ʼ��˳��ջ */
int InitStack(SqStack* S)
{
	S->base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	if (!S->base) exit(-1);  //ʧ��

	S->top = S->base;  //ջ��ָ�� = ջ��ָ��
	S->stacksize = MAXSIZE;

	return OK;
}
/* �жϿ�ջ*/
int IsEmpty(SqStack S)
{
	if (S.base == S.top)
		return OK;
	else
		return ERROR;
}
/* ˳��ջ����ջ */
int Push(SqStack* S, BiTree Tree)
{
	if (S->top - S->base == S->stacksize)  //ջ����
		return ERROR;
	*++S->top = Tree;  // S->top++; *S->top = Tree;
	return OK;
}
/* ˳��ջ�ĳ�ջ */
int Pop(SqStack* S,BiTree *Tree)
{
	if (S->top == S->base)   //��ջ
		return ERROR;

	*Tree = *S->top--;  // *Tree = *S->top; S->top--; 
	return OK;
}



/* ��ʼ��ѭ������ */
int InitQueue(SqQueue* Q)
{
	Q->base = (QElemType*)malloc(MAXSIZE * sizeof(QElemType));
	if (!Q->base) exit(-1);
	Q->front = Q->rear = 0; //ͷָ����βָ�붼Ϊ0
		return OK;
}
/* ѭ��������� */
int EnQueue(SqQueue* Q, QElemType Tree)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)  //����
		return ERROR;
	Q->base[Q->rear] = Tree;
	Q->rear = (Q->rear + 1) % MAXSIZE;  //��βָ�� + 1
	return OK;
}
/* ѭ�����г��� */
int DeQueue(SqQueue* Q, QElemType* Tree)
{
	if (Q->front == Q->rear) return ERROR;
	*Tree = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;  //��ͷָ�� + 1
	return OK;
}





/* ǰ��������� */
void CreateBiTree(BiTree* T)
{
	BitreeElemType ch;
	scanf(" %c", &ch);
	if (ch == '#') //������'#'��ʾ����
		*T = NULL;
	else 
	{
		*T = (BiTree)malloc(sizeof(BiNode));
		(*T)->data = ch;       //���ɸ����
		CreateBiTree(&(*T)->lchild); //����������
		CreateBiTree(&(*T)->rchild); //����������
	}
}

/* ǰ����� */
void PreOrderTraverse(BiTree T)
{
	if (!T) return;
	printf("%c\n", T->data);
	PreOrderTraverse(T->lchild); //�������������
	PreOrderTraverse(T->rchild); //�������������
}

/* ������� */
void InOrderTraverse(BiTree T)
{
	if (!T) return;
	InOrderTraverse(T->lchild); //�������������
	printf("%c\n", T->data);
	InOrderTraverse(T->rchild); //�������������
}

/* ������� */
void PostOrderTraverse(BiTree T)
{
	if (!T) return;
	PostOrderTraverse(T->lchild); //�������������
	PostOrderTraverse(T->rchild); //�������������
	printf("%c\n", T->data);

}
/* ��������ķǵݹ��㷨 */
// 1.����ջ
// 2.�������ջ ��������������
// 3.������ջ����������,����������
void InOrderTraverse_Stack(BiTree T)
{
	SqStack S;
	InitStack(&S);
	BiTree p = T;
	while (p || !IsEmpty(S))
	{
		if (p)
		{
			Push(&S, p);//�������ջ(˳����ջһ��Ҫͬ����ѽ��ע��SElemTypeΪBitree)
			p = p->lchild;
		}
		else
		{
			Pop(&S,&p);//ԭջ��Ԫ�ظ�p(˳��ջҲҪͬ���ͣ�ע��SElemTypeΪBitree)

			//��������,����������
			printf("%c\n", p->data);
			p = p->rchild;
		}
	}
}

/* ��α��� */
void LevelOder(BiTree T)
{
	BiTree p = NULL;
	SqQueue Q;
	InitQueue(&Q);
	EnQueue(&Q, T);   //��������
	while (Q.front != Q.rear)  //�Ӳ�Ϊ��
	{
		DeQueue(&Q, &p);   //���ӽ��p
		printf("%c\n", p->data);
		if (p->lchild)    //������,���
			EnQueue(&Q, p->lchild);
		if (p->rchild)    //���Һ���,���
			EnQueue(&Q, p->rchild);
	}
}

/* ���ƶ����� */
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

/* ������� */
int Depth(BiTree T)
{
	if (!T) return 0;

	return Depth(T->lchild) > Depth(T->rchild) ? Depth(T->lchild) + 1 : Depth(T->rchild) + 1;

}

/* �����ܽ���� */
int Nodes(BiTree T)
{
	if (!T) return 0; //����
	else
	return Nodes(T->lchild) + Nodes(T->rchild) + 1;
}

/* ����Ҷ�ӽ���� */
int LeafNodes(BiTree T)
{
	if (!T)    //����
		return 0;
	if (!T->lchild && !T->rchild) //Ҷ�ӽ��
		return 1;
	else
		return LeafNodes(T->lchild) + LeafNodes(T->rchild);
}
/* �������ٶ����� */
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
