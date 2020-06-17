#include <stdlib.h>
#include "AVLtree.h"

void changeChild(BSTree parent,BSTree cur){
	if( LT(parent->data,cur->data) ){
		parent->rchild = cur;
	}else{
		parent->lchild = cur;
	}
}

void R_Rotate(BSTree *p){
	BSTree lc = (*p)->lchild;
	(*p)->lchild = lc->rchild;
	lc->rchild = *p;
	*p = lc;
}

void L_Rotate(BSTree *p){
	BSTree rc = (*p)->rchild;
	(*p)->rchild = rc->lchild;
	rc->lchild = *p;
	*p = rc;
}

void LeftBalance(BSTree *p){
	BSTree lc = (*p)->lchild,
		   rd = NULL;

	switch( lc->bf ){
		case LH:
			(*p)->bf = lc->bf = EH;
			R_Rotate(p);
			break;
		case RH:
			rd = lc->rchild;
			switch( rd->bf ){
				case LH:
					(*p)->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					(*p)->bf = EH;
					lc->bf = EH;
					break;
				case RH:
					(*p)->bf = EH;
					lc->bf = LH;
					break;
			}
			rd->bf = EH;
			L_Rotate(&lc);
			(*p)->lchild = lc;
			R_Rotate(p);
			break;
	}
}

void RightBalance(BSTree *p){
	BSTree rc = (*p)->rchild,
		   ld = NULL;

	switch( rc->bf ){
		case LH:
			ld = rc->lchild;
			switch( ld->bf ){
				case LH:
					(*p)->bf = EH;
					rc->bf = RH;
					break;
				case EH:
					(*p)->bf = EH;
					rc->bf = EH;
					break;
				case RH:
					(*p)->bf = LH;
					rc->bf = EH;
					break;
			}
			ld->bf = EH;
			R_Rotate(&rc);
			(*p)->rchild = rc;
			L_Rotate(p);
			break;
		case RH:
			(*p)->bf = rc->bf = EH;
			L_Rotate(p);
			break;
	}
}

int InsertAVL(BSTree *t,BSTree parent,int e,int *taller){
	int tall = 0,
		result = 0;

	if( !(*t) ){
		*t = (BSTree)malloc(sizeof(BSTNode));
		if( *t ){
			(*t)->data = e;
			(*t)->bf = EH;
			(*t)->lchild = (*t)->rchild = NULL;
			*taller = 1;
			result = 1;
		}
	}else{
		if( EQ(e,(*t)->data) ){
			*taller = 0;
			result = 0;
		}else if( LT(e,(*t)->data) ){
			if( !InsertAVL(&((*t)->lchild),*t,e,&tall) ){
				*taller = 0;
				result = 0;
			}else{
				if( tall ){
					switch( (*t)->bf ){
						case LH:
							LeftBalance(t);
							if( parent ){
								changeChild(parent,*t);
							}
							*taller = 0;
							break;
						case EH:
							*taller = 1;
							(*t)->bf = LH;
							break;
						case RH:
							*taller = 0;
							(*t)->bf = EH;
							break;
					}	
				}
				result = 1;
			}
		}else{
			if( !InsertAVL(&((*t)->rchild),*t,e,&tall) ){
				*taller = 0;
				result = 0;
			}else{
				if( tall ){
					switch( (*t)->bf ){
						case LH:
							*taller = 0;
							(*t)->bf = EH;
							break;
						case EH:
							*taller = 1;
							(*t)->bf = RH;
							break;
						case RH:
							RightBalance(t);
							if( parent ){
								changeChild(parent,*t);
							}
							*taller = 0;
							break;
					}
				}
				result = 1;
			}
		}
	}

	return result;
}
