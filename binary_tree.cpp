#include "stdafx.h"
#include "binary_tree.h"
#include <malloc.h>

//Common data
typedef struct   {
	int data;
} TElemType;
typedef int Status;
enum { ERR, OK };

//Binary Three define
typedef struct BiTNode {
	TElemType data;
	struct BiTnode *lchild;
	struct BiTnode *rchild;
} BinTNode;


//Threading three define
typedef enum PointerTag{Link, Thread};
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;


BiThrTree pre;

/*Function area*/

Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e))
{
	BiThrNode * p;
	p = T->lchild;
	while (p != T) {
		while (p->LTag == Link)
			p = p->lchild;
		if (!Visit(p->data))
			return ERR;
		while (p->RTag == Thread && p->rchild != T) {
			p = p->rchild;
			Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}//InOrderTraverse_Thr


void InorderThreading_one(BiThrTree p)
{
	if (p) {
		InorderThreading_one(p->lchild);
		p->LTag = (p->lchild) ? Link : Thread;
		p->RTag = (p->rchild) ? Link : Thread;
		if (pre) {
			if (pre->RTag == Thread) {
				pre->rchild = p;
			}
			if (p->LTag == Thread) {
				p->lchild = pre;
			}
		}
		pre = p;
		InorderThreading_one(p);
	}
} //InorderThreading_one

/*InorderSuccessor*/
BiThrNode *InorderSuccessor(BiThrNode *p)
{
	BiThrNode *q;

	if (p->RTag == Thread)
		return p->rchild;
	else {
		q = p->lchild;
		while (q->LTag == Link)
			q = q->lchild;
		return q;
	}

}

void InThreading(BiThrTree p)
{
	if (p) {
		InThreading(p->lchild);				//左子树线索化
		if (!p->lchild) {					//前驱线索
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild) {					
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}//InThreading

Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	if (!(Thrt = (BiThrNode*)malloc(sizeof(BiThrNode))))
		return ERR;

	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T) {
		Thrt->lchild = Thrt;
	}
	else {
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	//i
}//InOrderThreading