//B+树的功能实现

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include "btree.h"

#define log_debug(msg,...)  printf(msg, ##__VA_ARGS__)
#define log_info(msg,...)  printf(msg, ##__VA_ARGS__)
#define new(type, num)		(malloc(sizeof(type)*(num)))
#define del(ptr)			{if(NULL != ptr)free(ptr);}

static inline void equal_divi(int value, int num, int * arry){
    if(NULL == arry)
        return;
    int n = value/num;
    int i = 0;
    for(i=0; i< num; i++){
        arry[i] = n;
    }
    for(i=0; i<value%num; i++){
        arry[i]++;
    }
}


btnode_t * bt_new_node(btype_t type){
	int size = 0;
	btnode_t * pNode = (btnode_t *)new(char, NODE_SIZE);
	if(NULL == pNode){
		log_debug("Malloc new Node for B+Tree failed, please check!\n");
		return NULL;
	}
	memset(pNode, 0, NODE_SIZE);

	pNode->bn_type = type;
	if(TYPE_LEAF == type){
		pNode->bn_leaf.lnode.next = NULL;
		pNode->bn_leaf.lnode.prev = NULL;
	}

	return pNode;
}

void bt_free_node(btp_t ptr){
	del(ptr.bn_ptr);
}


int bt_key_cmp(btk_t key1, btk_t key2){
	if(key1.bn_key > key2.bn_key)
		return 1;
	else if(key1.bn_key == key2.bn_key)
		return 0;
	else
		return -1;
}

static inline btk_t bt_maxkey(btnode_t * pNode){
	if(TYPE_INT == pNode->bn_type){
		return pNode->bn_inter.bn_entry[pNode->bn_inter.bn_num-1].bn_key;
	}
	else{
		return pNode->bn_leaf.bn_data[pNode->bn_leaf.bn_num-1];
	}
}

static inline int bt_keynum(btnode_t * pNode){
	if(TYPE_INT == pNode->bn_type){
		return pNode->bn_inter.bn_num;
	}
	else{
		return pNode->bn_leaf.bn_num;
	}
}

int bt_search_branch(btnode_t * pNode, btk_t key){
	int i;
	for(i=0; i<pNode->bn_inter.bn_num; i++){
		if(bt_key_cmp(pNode->bn_inter.bn_entry[i].bn_key, key)<0)
			continue;
		else
			return i;
	}
	return BTREE_FAIL;
}

int bt_search_leaf(btnode_t * pNode, btk_t key){
	int i;
	for(i=0; i<pNode->bn_leaf.bn_num; i++){
		if(bt_key_cmp(pNode->bn_leaf.bn_data[i], key)<0)
			continue;
		else
			return i;
	}
	return BTREE_FAIL;
}

int bt_exactsearch_leaf(btnode_t * pNode, btk_t key){
	int i;
	for(i=0; i<pNode->bn_leaf.bn_num; i++){
		if(bt_key_cmp(pNode->bn_leaf.bn_data[i], key) != 0)
			continue;
		else
			return i;
	}
	return BTREE_FAIL;
}


int bt_branch_real_add(btinter_t * pinter, bti_t idx){
	bti_t * tmpidxs = pinter->bn_entry;
	int i,j;
	for(i=0; i<pinter->bn_num; i++){
		if(bt_key_cmp(idx.bn_key, tmpidxs[i].bn_key)>0)
			continue;
		else{
			break;
		}
	}

	for(j=pinter->bn_num; j>i; j--){
		tmpidxs[j] = tmpidxs[j-1];
	}
	tmpidxs[i] = idx;
	pinter->bn_num++;
	return BTREE_OK;
}

static inline int bt_branch_split(btnode_t * pNode, btnode_t ** ppNewNode){
	if(INTER_KEY_NUM > pNode->bn_inter.bn_num){
		log_debug("The leaf no need split!\n");
		return BTREE_FAIL;
	}
	btnode_t * ptmp = bt_new_node(TYPE_INT);
	if(NULL == ptmp)
		return BTREE_FAIL;
	ptmp->bn_level = pNode->bn_level;
	ptmp->bn_type = TYPE_INT;
	memcpy(ptmp->bn_inter.bn_entry, pNode->bn_inter.bn_entry+INTER_KEY_NUM/2, sizeof(bti_t)*(INTER_KEY_NUM-INTER_KEY_NUM/2));
	pNode->bn_inter.bn_num = INTER_KEY_NUM/2;
	ptmp->bn_inter.bn_num = INTER_KEY_NUM-INTER_KEY_NUM/2;
	*ppNewNode = ptmp;
	return BTREE_OK;
}


modv_t bt_branch_add(btnode_t * pNode, modinfo_t * pinfo){
	if(pNode->bn_inter.bn_num == INTER_KEY_NUM){
		btnode_t * pnewNode = NULL;
		if(BTREE_FAIL == bt_branch_split(pNode, &pnewNode)){
			return MOD_FAIL;
		}
		if(NULL == pnewNode){
			return MOD_FAIL;
		}
		int ret = bt_key_cmp(pNode->bn_inter.bn_entry[pNode->bn_inter.bn_num-1].bn_key, pinfo->newnode.bn_key);
		if(ret > 0){
			bt_branch_real_add(&pNode->bn_inter, pinfo->newnode);
		}
		else{
			bt_branch_real_add(&pnewNode->bn_inter, pinfo->newnode);
		}
		pinfo->midkey = 1;
		pinfo->newnode.bn_key = pnewNode->bn_inter.bn_entry[pnewNode->bn_inter.bn_num-1].bn_key;
		pinfo->newnode.bn_ptr.bn_ptr = pnewNode;
		return MOD_NOK;
	}

	int oldnum = pNode->bn_inter.bn_num;
	btk_t oldkey = pNode->bn_inter.bn_entry[oldnum-1].bn_key;
	bt_branch_real_add(&pNode->bn_inter, pinfo->newnode);
	pinfo->newnode.bn_ptr.bn_ptr = NULL;
	if(BT_LVL_ROOT != pNode->bn_level){
		if(bt_key_cmp(oldkey, pNode->bn_inter.bn_entry[pNode->bn_inter.bn_num-1].bn_key) < 0){
			pinfo->midkey = 1;
			pinfo->newnode.bn_ptr.bn_ptr = NULL;
			pinfo->newnode.bn_key.bn_key = 0;
			return MOD_NOK;
		}
	}
	return MOD_OK;
}

void bt_branch_real_del(btinter_t * pbranch, int idx){
	int i;
	btp_t tmpptr = {0};
	tmpptr.bn_ptr = pbranch->bn_entry[idx].bn_ptr.bn_ptr;
	for(i=idx+1; i<pbranch->bn_num; i++){
		pbranch->bn_entry[i-1] = pbranch->bn_entry[i];
	}
	pbranch->bn_num--;
	bt_free_node(tmpptr);
}

static inline void bt_branch_move2left(btinter_t * psrc, btinter_t * pdst, int move_num){
	memcpy(pdst->bn_entry+pdst->bn_num, psrc->bn_entry, sizeof(bti_t)*move_num);
	pdst->bn_num += move_num;
	int i;
	for(i=0; i<(psrc->bn_num - move_num); i++){
		psrc->bn_entry[i] = psrc->bn_entry[i+move_num];
	}
	psrc->bn_num -= move_num;
}

static inline void bt_branch_move2right(btinter_t * psrc, btinter_t * pdst, int move_num){
	int idx = psrc->bn_num-move_num;
	int i;
	for(i=pdst->bn_num-1; i>=0; i--){
		pdst->bn_entry[i+move_num] = pdst->bn_entry[i];
	}
	memcpy(pdst->bn_entry, &psrc->bn_entry[idx], sizeof(bti_t)*move_num);
	pdst->bn_num += move_num;
	psrc->bn_num -= move_num;
}

static inline void bt_branch_rotate(btnode_t * plNode, btnode_t * pmNode, btnode_t * prNode, modinfo_t*  pbrot, rot_t mode, int idx){
	int i;
	int value = 0;
	int node_num = 0;
	btk_t oldkey[ORDNUM] = {0};
	btinter_t * pleft = NULL;
	btinter_t * pmid = NULL;
	btinter_t * pright = NULL;
	btinter_t * target = NULL;
	if(NULL != plNode){
		pleft = &plNode->bn_inter;
		value += pleft->bn_num;
		oldkey[LEFT] = pleft->bn_entry[pleft->bn_num-1].bn_key;
		node_num ++;
	}
	if(NULL != prNode){
		pright = &prNode->bn_inter;
		value += pright->bn_num;
		oldkey[RIGHT] = pright->bn_entry[pright->bn_num-1].bn_key;
		node_num ++;
	}
	pmid = &pmNode->bn_inter;
	value += pmid->bn_num;
	oldkey[MID] = pmid->bn_entry[pmid->bn_num-1].bn_key;
	node_num++;
	int num[ORDNUM] = {0};
	equal_divi(value, node_num, num);
	int move_num = 0;
	if(pleft != NULL && pright != NULL){
		idx += pleft->bn_num;
		if(ROT_ADD == mode){
			if(idx < num[LEFT]){
				target = pleft;
				if(num[LEFT] >= LEAF_KEY_NUM){
					num[LEFT]--;
					if(num[MID] < LEAF_KEY_NUM){
						num[MID]++;
					}
					else{
						num[RIGHT]++;
					}
				}
			}
			else if(idx < num[LEFT]+num[MID]){
				target = pmid;
				idx -= num[LEFT];
				if(num[MID] >= LEAF_KEY_NUM){
					num[MID]--;
					num[RIGHT]++;
				}
			}
			else{
				target = pright;
				idx -= (num[LEFT] + num[MID]);
			}
		}
	}
	
	else if(NULL != pleft){
		idx += pleft->bn_num;
		if(ROT_ADD == mode){
			if(idx <= num[LEFT]-1){
				target = pleft;
				if(num[LEFT] >= LEAF_KEY_NUM){
					num[LEFT]--;
					num[MID]++;
				}
			}
			else{
				idx -= num[LEFT];
				target = pmid;
			}
		}
	}
	else if(NULL != pright){
		num[RIGHT] = num[MID];
		num[MID] = num[LEFT];
		num[LEFT] = 0;
		if(ROT_ADD == mode){
			if(idx < num[MID]){
				target = pmid;
				if(num[MID] >= LEAF_KEY_NUM){
					num[MID]--;
					num[RIGHT]++;
				}
			}
			else{
				idx -= num[MID];
				target = pright;
			}
		}
	}
	if(NULL != pleft && NULL != pright){
		
		if((num[LEFT] < pleft->bn_num)&&
			(num[RIGHT] > pright->bn_num)){
			
			move_num = num[RIGHT] - pright->bn_num;
			bt_branch_move2right(pmid, pright, move_num);
			
			move_num = pleft->bn_num - num[LEFT];
			bt_branch_move2right(pleft, pmid, move_num);
		}
		
		else if((num[LEFT] > pleft->bn_num)&&
			(num[RIGHT] < pright->bn_num)){
			
			move_num = num[LEFT] - pleft->bn_num;
			bt_branch_move2left(pmid, pleft, move_num);
			
			move_num = pright->bn_num - num[RIGHT];
			bt_branch_move2left(pright, pmid, move_num);
		}
	}

	if(NULL != pleft){
		
		if(num[LEFT] < pleft->bn_num){
			move_num = pleft->bn_num - num[LEFT];
			bt_branch_move2right(pleft, pmid, move_num);
		}
		
		
		else if(num[LEFT] > pleft->bn_num){
			move_num = num[LEFT] - pleft->bn_num;
			bt_branch_move2left(pmid, pleft, move_num);
		}
	}

	if(NULL != pright){
		
		if(num[RIGHT] > pright->bn_num){
			move_num = num[RIGHT] - pright->bn_num;
			bt_branch_move2right(pmid, pright, move_num);
		}
		
		
		else if(num[RIGHT] < pright->bn_num){
			move_num = pright->bn_num - num[RIGHT];
			bt_branch_move2left(pright, pmid, move_num);
		}
	}

	if(0 != bt_key_cmp(oldkey[MID],pmid->bn_entry[pmid->bn_num-1].bn_key)){
		pbrot->midkey = 1;
	}
	if(NULL != pleft && 0 != bt_key_cmp(oldkey[LEFT], pleft->bn_entry[pleft->bn_num-1].bn_key)){
		pbrot->leftkey = 1;
	}
	if(NULL != pright && 0 != bt_key_cmp(oldkey[RIGHT], pright->bn_entry[pright->bn_num-1].bn_key)){
		pbrot->rightkey = 1;
	}
}

static inline void bt_branch_merge(btnode_t * pleft, btnode_t * pmid, btnode_t * pright, modinfo_t*  pinfo){
	int num = 0;
	int move_num = 0;
	if((pright == NULL) || (pleft != NULL && pleft != NULL && pleft->bn_inter.bn_num <= pright->bn_inter.bn_num)){
		num = (pleft->bn_inter.bn_num + pmid->bn_inter.bn_num)/2;
		move_num = pleft->bn_inter.bn_num;
		bt_branch_move2right(&pleft->bn_inter, &pmid->bn_inter, move_num);
		pinfo->invalidnode = LEFT;
	}
	else if((pleft == NULL) ||(pleft != NULL && pleft != NULL && pleft->bn_inter.bn_num >= pright->bn_inter.bn_num)){
		num = (pright->bn_inter.bn_num + pmid->bn_inter.bn_num)/2;
		move_num = pright->bn_inter.bn_num;
		bt_branch_move2left(&pright->bn_inter, &pmid->bn_inter,move_num);
		pinfo->invalidnode = RIGHT;
	}
	pinfo->midkey= 1;
}


modv_t bt_branch_del(btnode_t * pNode, int idx, modinfo_t * pinfo, ndflag_t flag){
	modv_t ret;
	bt_branch_real_del(&pNode->bn_inter, idx);
	if(idx == pNode->bn_inter.bn_num){
		switch(flag){
			case LEFT:
				pinfo->leftkey = 1;
				break;
			case MID:
				pinfo->midkey = 1;
				break;
			case RIGHT:
				pinfo->rightkey = 1;
				break;
			default:
				break;
		}
		ret = MOD_NOK;
	}
	if(pNode->bn_inter.bn_num < LEAF_KEY_NUM/2){
		ret = MOD_NOK;
	}
	else{
		pinfo->invalidnode = ORDNUM;
	}
	return ret;
}

static inline void bt_leaf_move2left(btleaf_t * psrc, btleaf_t * pdst, int move_num){
	if(0 == move_num)
		return;
	memcpy(pdst->bn_data+pdst->bn_num, psrc->bn_data, sizeof(btk_t)*move_num);
	pdst->bn_num += move_num;
	int i;
	for(i=0; i<(psrc->bn_num - move_num); i++){
		psrc->bn_data[i] = psrc->bn_data[i+move_num];
	}
	psrc->bn_num -= move_num;
}

static inline void bt_leaf_move2right(btleaf_t * psrc, btleaf_t * pdst, int move_num){
	int i;
	for(i=pdst->bn_num-1; i>=0; i--){
		pdst->bn_data[i+move_num] = pdst->bn_data[i];
	}
	memcpy(pdst->bn_data, psrc->bn_data+psrc->bn_num-move_num, sizeof(btk_t)*move_num);
	pdst->bn_num += move_num;
	psrc->bn_num -= move_num;
}


int bt_leaf_split(btnode_t * pNode, btnode_t ** ppNewNode){
	if(LEAF_KEY_NUM > pNode->bn_leaf.bn_num){
		log_debug("The leaf no need split!\n");
		return BTREE_FAIL;
	}
	btnode_t * ptmp = bt_new_node(pNode->bn_type);
	if(NULL == ptmp)
		return BTREE_FAIL;
	ptmp->bn_level = pNode->bn_level;
	ptmp->bn_leaf.lnode.next = pNode->bn_leaf.lnode.next;
	ptmp->bn_leaf.lnode.prev = &pNode->bn_leaf.lnode;
	if(NULL != pNode->bn_leaf.lnode.next){
		pNode->bn_leaf.lnode.next->prev = &ptmp->bn_leaf.lnode;
	}
	pNode->bn_leaf.lnode.next = &ptmp->bn_leaf.lnode;
	bt_leaf_move2right(&pNode->bn_leaf, &ptmp->bn_leaf, LEAF_KEY_NUM/2);
	*ppNewNode = ptmp;
	return BTREE_OK;
}


static inline void bt_leaf_real_add(btleaf_t * pleaf, int idx, btk_t key){
	btk_t * tmpkeys = pleaf->bn_data;
	if(0 == pleaf->bn_num){
		tmpkeys[0] = key;
	}
	else if(idx >= pleaf->bn_num){
		tmpkeys[idx] = key;
	}
	else if(bt_key_cmp(key, tmpkeys[idx]) < 0){
		int j;
		for(j=pleaf->bn_num; j>idx; j--){
			tmpkeys[j] = tmpkeys[j-1];
		}
		tmpkeys[idx] = key;
	}
	else{
		tmpkeys[idx+1] = key;
	}
	pleaf->bn_num++;
}

static inline void bt_leaf_real_del(btleaf_t * pleaf, int idx){
	int i;
	for(i=idx+1; i<pleaf->bn_num; i++){
		pleaf->bn_data[i-1] = pleaf->bn_data[i];
	}
	pleaf->bn_num--;
}



static inline void bt_leaf_rotate(btnode_t * plNode, btnode_t * pmNode, btnode_t * prNode, modinfo_t * pinfo, rot_t mode, int idx, btk_t key){
	int i;
	int value = 0;
	int node_num = 0;
	btk_t oldkey[ORDNUM] = {0};
	btleaf_t * pleft = NULL;
	btleaf_t * pmid = NULL;
	btleaf_t * pright = NULL;
	btleaf_t * target = NULL;
	if(NULL != plNode){
		pleft = &plNode->bn_leaf;
		value += pleft->bn_num;
		oldkey[LEFT] = pleft->bn_data[pleft->bn_num-1];
		node_num ++;
	}
	if(NULL != prNode){
		pright = &prNode->bn_leaf;
		value += pright->bn_num;
		oldkey[RIGHT] = pright->bn_data[pright->bn_num-1];
		node_num ++;
	}
	pmid = &pmNode->bn_leaf;
	value += pmid->bn_num;
	oldkey[MID] = pmid->bn_data[pmid->bn_num-1];
	node_num++;
	int num[ORDNUM] = {0};
	equal_divi(value, node_num, num);
	int move_num = 0;
	if(pleft != NULL && pright != NULL){
		idx += pleft->bn_num;
		if(ROT_ADD == mode){
			if(idx < num[LEFT]){
				target = pleft;
				if(num[LEFT] >= LEAF_KEY_NUM){
					num[LEFT]--;
					if(num[MID] < LEAF_KEY_NUM){
						num[MID]++;
					}
					else{
						num[RIGHT]++;
					}
				}
			}
			else if(idx < num[LEFT]+num[MID]){
				target = pmid;
				idx -= num[LEFT];
				if(num[MID] >= LEAF_KEY_NUM){
					num[MID]--;
					num[RIGHT]++;
				}
			}
			else{
				target = pright;
				idx -= (num[LEFT] + num[MID]);
			}
		}
	}
	
	else if(NULL != pleft){
		idx += pleft->bn_num;
		if(ROT_ADD == mode){
			if(idx <= num[LEFT]-1){
				target = pleft;
				if(num[LEFT] >= LEAF_KEY_NUM){
					num[LEFT]--;
					num[MID]++;
				}
			}
			else{
				idx -= num[LEFT];
				target = pmid;
			}
		}
	}
	else if(NULL != pright){
		num[RIGHT] = num[MID];
		num[MID] = num[LEFT];
		num[LEFT] = 0;
		if(ROT_ADD == mode){
			if(idx < num[MID]){
				target = pmid;
				if(num[MID] >= LEAF_KEY_NUM){
					num[MID]--;
					num[RIGHT]++;
				}
			}
			else{
				idx -= num[MID];
				target = pright;
			}
		}
	}
	if(NULL != pleft && NULL != pright){
	
		if((num[LEFT] < pleft->bn_num)&&
			(num[RIGHT] > pright->bn_num)){
			
			move_num = num[RIGHT] - pright->bn_num;
			bt_leaf_move2right(pmid, pright, move_num);
			
			move_num = pleft->bn_num - num[LEFT];
			bt_leaf_move2right(pleft, pmid, move_num);
		}
		
		else if((num[LEFT] > pleft->bn_num)&&
			(num[RIGHT] < pright->bn_num)){
			
			move_num = num[LEFT] - pleft->bn_num;
			bt_leaf_move2left(pmid, pleft, move_num);
			
			move_num = pright->bn_num - num[RIGHT];
			bt_leaf_move2left(pright, pmid, move_num);
		}
	}

	if(NULL != pleft){
		/
		if(num[LEFT] < pleft->bn_num){
			move_num = pleft->bn_num - num[LEFT];
			bt_leaf_move2right(pleft, pmid, move_num);
		}
		
		
		else if(num[LEFT] > pleft->bn_num){
			move_num = num[LEFT] - pleft->bn_num;
			bt_leaf_move2left(pmid, pleft, move_num);
		}
	}

	if(NULL != pright){
		
		if(num[RIGHT] > pright->bn_num){
			move_num = num[RIGHT] - pright->bn_num;
			bt_leaf_move2right(pmid, pright, move_num);
		}
		
		
		else if(num[RIGHT] < pright->bn_num){
			move_num = pright->bn_num - num[RIGHT];
			bt_leaf_move2left(pright, pmid, move_num);
		}
	}

	if(ROT_ADD == mode){
		bt_leaf_real_add(target, idx, key);
	}
	if(0 != bt_key_cmp(oldkey[MID],pmid->bn_data[pmid->bn_num-1])){
		pinfo->midkey = 1;
		log_debug("old mid key: %ld new mid key: %ld ", oldkey[MID].bn_key, pmid->bn_data[pmid->bn_num-1].bn_key);
	}
	if(NULL != pleft && 0 != bt_key_cmp(oldkey[LEFT], pleft->bn_data[pleft->bn_num-1])){
		pinfo->leftkey = 1;
		log_debug("old left key: %ld new left key: %ld ", oldkey[LEFT].bn_key, pleft->bn_data[pleft->bn_num-1].bn_key);
	}
	if(NULL != pright && 0 != bt_key_cmp(oldkey[RIGHT], pright->bn_data[pright->bn_num-1])){
		pinfo->rightkey = 1;
		log_debug("old right key: %ld new right key: %ld ", oldkey[RIGHT].bn_key, pright->bn_data[pright->bn_num-1].bn_key);
	}
	log_debug("\n");
}

static inline void bt_leaf_merge(btnode_t * pNode0, btnode_t * pNode1, btnode_t * pNode2, modinfo_t * pinfo){
	btleaf_t * pleft = NULL;
	if(NULL != pNode0) pleft = &pNode0->bn_leaf;
	btleaf_t * pmid = &pNode1->bn_leaf;
	btleaf_t * pright = NULL;
	if(NULL != pNode2) pright = &pNode2->bn_leaf;
	int move_num = 0;
	
	if(pright == NULL || (pright != NULL && pleft != NULL && pright->bn_num >= pleft->bn_num)){
		if(NULL != pleft->lnode.prev){
			pleft->lnode.prev->next = pleft->lnode.next;
		}
		if(NULL != pleft->lnode.next){
			pleft->lnode.next->prev = pleft->lnode.prev;
		}
		move_num = pleft->bn_num;
		bt_leaf_move2right(pleft,pmid,move_num);
		pinfo->invalidnode = LEFT;
	}
	
	else if(pleft == NULL || ((pright != NULL && pleft!= NULL) && pleft->bn_num >= pright->bn_num)){
		if(NULL != pright->lnode.prev){
			pright->lnode.prev->next = pright->lnode.next;
		}
		if(NULL != pright->lnode.next){
			pright->lnode.next->prev = pright->lnode.prev;
		}
		move_num = pright->bn_num;
		bt_leaf_move2left(pright,pmid, move_num);
		pinfo->midkey = 1;
		pinfo->invalidnode = RIGHT;
	}
}


modv_t bt_leaf_add(btpath_t path_node, btk_t key, modinfo_t * pinfo){
	btnode_t * pleft = path_node.pleft;
	btnode_t * pright = path_node.pright;
	btnode_t * pmid = path_node.pmid;
	int total = pmid->bn_leaf.bn_num;
	int bc_num = 1;
	
	if(NULL != pleft){
		total += pleft->bn_leaf.bn_num;
		bc_num++;
	}
	if(NULL != pright){
		total += pright->bn_leaf.bn_num;
		bc_num++;
	}
	
	int idx = path_node.mididx;
	if(pmid->bn_leaf.bn_num == LEAF_KEY_NUM){
		if(total == bc_num*LEAF_KEY_NUM){
			btnode_t * pnewNode = NULL;
			if(BTREE_FAIL == bt_leaf_split(pmid, &pnewNode)){
				return MOD_FAIL;
			}
			if(NULL == pnewNode){
				return MOD_FAIL;
			}
			int ret = bt_key_cmp(key, pmid->bn_leaf.bn_data[pmid->bn_leaf.bn_num-1]);
			if(ret < 0){
				bt_leaf_real_add(&pmid->bn_leaf, idx, key);
			}
			else{
				idx = bt_search_leaf(pnewNode, key);
				if(BTREE_FAIL == idx){
					idx = pnewNode->bn_leaf.bn_num-1;
				}
				bt_leaf_real_add(&pnewNode->bn_leaf, idx, key);
			}
			pinfo->midkey = 1;
			pinfo->newnode.bn_key = pnewNode->bn_leaf.bn_data[pnewNode->bn_leaf.bn_num-1];
			pinfo->newnode.bn_ptr.bn_ptr = pnewNode;
			return MOD_NOK;
		}
		else{
			bt_leaf_rotate(pleft, pmid, pright, pinfo, ROT_ADD, idx, key);
			return MOD_NOK;
		}
	}

	btk_t oldkey = pmid->bn_leaf.bn_data[pmid->bn_leaf.bn_num-1];
	bt_leaf_real_add(&pmid->bn_leaf, idx, key);
	if(BT_LVL_ROOT != pmid->bn_level){
		if(bt_key_cmp(oldkey, pmid->bn_leaf.bn_data[pmid->bn_leaf.bn_num-1]) < 0){
			pinfo->midkey = 1;
			pinfo->leftkey = 0;
			pinfo->rightkey = 0;
			return MOD_NOK;
		}
	}
	return MOD_OK;
}


modv_t bt_leaf_del(btpath_t path, modinfo_t * pinfo){
	modv_t ret;
	bt_leaf_real_del(&path.pmid->bn_leaf, path.mididx);
	if(path.mididx == path.pmid->bn_leaf.bn_num){
		pinfo->midkey = 1;
		ret = MOD_NOK;
	}
	if(path.pmid->bn_leaf.bn_num < LEAF_KEY_NUM/2){
		pinfo->invalidnode = MID;
		ret = MOD_NOK;
	}
	return ret;
}

static inline int bt_branch_update(btnode_t * pNode, int idx){
	if((0 > idx)||(pNode->bn_inter.bn_num <= idx)){
		log_debug("Branch update abnormal, idx:%d elem number:%d", idx, pNode->bn_inter.bn_num);
		exit(0);
	}
	btnode_t * tmpSon = pNode->bn_inter.bn_entry[idx].bn_ptr.bn_ptr;
	if(TYPE_INT == tmpSon->bn_type){
		pNode->bn_inter.bn_entry[idx].bn_key = tmpSon->bn_inter.bn_entry[tmpSon->bn_inter.bn_num-1].bn_key;
	}
	else{
		pNode->bn_inter.bn_entry[idx].bn_key = tmpSon->bn_leaf.bn_data[tmpSon->bn_leaf.bn_num-1];
	}
	if(idx == pNode->bn_inter.bn_num-1)
		return MOD_NOK;
	return MOD_OK;
}

modv_t bt_child_handle(btnode_t * pleft, btnode_t * pmid, btnode_t * pright, int idx, modinfo_t * pinfo){
	int total = bt_keynum(pmid);
	int bc_num = 1;
	modv_t ret = MOD_OK;
	if(NULL != pleft){
		total += bt_keynum(pleft);
		bc_num++;
	}
	if(NULL != pright){
		total += bt_keynum(pright);
		bc_num++;
	}

	if(TYPE_LEAF == pmid->bn_type){
		if(total >= bc_num*(LEAF_KEY_NUM/2)){
			btk_t key;
			bt_leaf_rotate(pleft, pmid, pright, pinfo, ROT_DEL, idx, key);
			pinfo->invalidnode = ORDNUM;
		}
		else{
			bt_leaf_merge(pleft, pmid, pright, pinfo);
			ret = MOD_NOK;
		}
	}
	else{
		if(total >= bc_num * (INTER_KEY_NUM/2)){
			btk_t key;
			bt_branch_rotate(pleft, pmid, pright, pinfo, ROT_DEL, idx);
			pinfo->invalidnode = ORDNUM;
		}
		else{
			bt_branch_merge(pleft, pmid, pright, pinfo);
			ret = MOD_NOK;
		}
	}
	return ret;
}


void bt_getpath_bykey(btnode_t * proot, btk_t key, btpath_t * path, int level){
	int i;
	if(NULL == proot){
		return;
	}
	btnode_t * pleft = NULL;
	btnode_t * pmid = proot;
	btnode_t * pright = NULL;
	for(i=0; i<level; i++){
		path[i].pleft = pleft;
		path[i].pmid = pmid;
		path[i].pright = pright;
		if(pmid->bn_type == TYPE_INT){
			path[i].mididx = bt_search_branch(pmid, key);
			if(path[i].mididx != BTREE_FAIL){
				if(path[i].mididx > 0){
					path[i].plfather = pmid;
					path[i].leftidx = path[i].mididx-1;
					pleft = pmid->bn_inter.bn_entry[path[i].mididx-1].bn_ptr.bn_ptr;
				}
				else if(NULL != pleft){
					path[i].plfather = pleft;
					path[i].leftidx = pleft->bn_inter.bn_num-1;
					pleft = pleft->bn_inter.bn_entry[pleft->bn_inter.bn_num-1].bn_ptr.bn_ptr;
				}
				
				if(path[i].mididx < pmid->bn_inter.bn_num-1){
					path[i].prfather = pmid;
					path[i].rightidx = path[i].mididx+1;
					pright = pmid->bn_inter.bn_entry[path[i].mididx+1].bn_ptr.bn_ptr;
				}
				else if(NULL != pright){
					path[i].prfather = pright;
					path[i].rightidx = 0;
					pright = pright->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
				}
				pmid = pmid->bn_inter.bn_entry[path[i].mididx].bn_ptr.bn_ptr;
			}
			else{
				path[i].mididx = pmid->bn_inter.bn_num-1;
				path[i].plfather = pmid;
				path[i].leftidx = path[i].mididx-1;
				pleft = pmid->bn_inter.bn_entry[path[i].leftidx].bn_ptr.bn_ptr;
				path[i].rightidx = 0;
				path[i].prfather = pright;
				if(NULL != pright){
					pright = pright->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
				}
				pmid = pmid->bn_inter.bn_entry[path[i].mididx].bn_ptr.bn_ptr;
			}
		}
		else if(pmid->bn_type == TYPE_LEAF){
			path[i].mididx = bt_search_leaf(pmid, key);
			if(BTREE_FAIL != path[i].mididx){
				if(path[i].mididx > 0){
					path[i].plfather = pmid;
					path[i].leftidx = path[i].mididx-1;
				}
				else if(NULL != pleft){
					path[i].plfather = pleft;
					path[i].leftidx = pleft->bn_leaf.bn_num-1;
				}
				
				if(path[i].mididx < pmid->bn_leaf.bn_num-1){
					path[i].prfather = pmid;
					path[i].rightidx = path[i].mididx+1;
				}
				else if(NULL != pright){
					path[i].prfather = pright;
					path[i].rightidx = 0;
				}
			}
			else{
				path[i].mididx = pmid->bn_leaf.bn_num-1;
				path[i].plfather = pmid;
				path[i].leftidx = path[i].mididx-1;
				path[i].rightidx = 0;
				path[i].prfather = pright;
			}
		}
		else{
			log_debug("the tree is invalid, please check!\n");
			exit(0);
		}

		log_debug("path[%d].idx:%d\n", i, path[i].mididx);
	}
}

int bt_branch_modify(btpath_t path, modinfo_t * pinfo){
	int idx = 0;
	int isUpdate = 0;
	modv_t ret = MOD_OK;
	btnode_t * pleft = NULL;
	btnode_t * pmid = NULL;
	btnode_t * pright = NULL;
	if(0 != pinfo->midkey){
		if(MOD_NOK == bt_branch_update(path.pmid, path.mididx)){
			isUpdate = 1;
		}
		else{
			pinfo->midkey = 0;
		}
	}
	if(0 != pinfo->leftkey){
		bt_branch_update(path.plfather, path.leftidx);
		if(0 == path.mididx){
			isUpdate = 1;
		}
		else{
			pinfo->leftkey = 0;
		}
	}

	if(MID == pinfo->invalidnode){
		if(NULL != path.plfather){
			pleft = path.plfather->bn_inter.bn_entry[path.leftidx].bn_ptr.bn_ptr;
		}
		pmid = path.pmid->bn_inter.bn_entry[path.mididx].bn_ptr.bn_ptr;
		if(NULL != path.prfather){
			pright = path.prfather->bn_inter.bn_entry[path.rightidx].bn_ptr.bn_ptr;
		}
		bt_child_handle(pleft, pmid, pright, idx, pinfo);
		if(0 != pinfo->leftkey){
			if(MOD_NOK == bt_branch_update(path.plfather, path.leftidx)){
				ret = MOD_NOK;
			}
			else{
				pinfo->leftkey = 0;
			}
		}
		if(0 != pinfo->midkey){
			if(MOD_NOK == bt_branch_update(path.pmid, path.mididx)){
				ret = MOD_NOK;
			}
			else{
				pinfo->midkey = 0;
			}
		}
		if(LEFT == pinfo->invalidnode){
			ret = bt_branch_del(path.plfather, path.leftidx, pinfo, LEFT);
		}
		else if(RIGHT == pinfo->invalidnode){
			ret = bt_branch_del(path.prfather, path.rightidx, pinfo, MID);
		}
	}
	else if(LEFT == pinfo->invalidnode){
		
		btnode_t * plleft = NULL;
		int llidx = 0;
		if(path.leftidx == 0){
			if(NULL != path.pleft){
				pleft = path.pleft->bn_inter.bn_entry[path.pleft->bn_inter.bn_num-1].bn_ptr.bn_ptr;
				plleft = path.pleft;
				llidx = path.pleft->bn_inter.bn_num-1;
			}
		}
		else{
			pleft = path.plfather->bn_inter.bn_entry[path.leftidx-1].bn_ptr.bn_ptr;
			plleft = path.plfather;
			llidx = path.leftidx-1;
		}
		if(NULL == path.plfather){
			pmid = path.pmid->bn_inter.bn_entry[path.mididx].bn_ptr.bn_ptr;
			pright = path.prfather->bn_inter.bn_entry[path.rightidx].bn_ptr.bn_ptr;
			path.plfather = path.pmid;
			path.leftidx = path.mididx;
		}
		else{
			pmid = path.plfather->bn_inter.bn_entry[path.leftidx].bn_ptr.bn_ptr;
			pright = path.pmid->bn_inter.bn_entry[path.mididx].bn_ptr.bn_ptr;
			path.prfather = path.pmid;
			path.rightidx= path.mididx;
		}
		bt_child_handle(pleft, pmid, pright, idx, pinfo);
		if(0 != pinfo->leftkey){
			if(MOD_NOK == bt_branch_update(plleft, llidx)){
				ret = MOD_NOK;
			}
		}
		if(0 != pinfo->midkey){
			if(MOD_NOK == bt_branch_update(path.plfather, path.leftidx)){
				ret = MOD_NOK;
			}
		}
		if(LEFT == pinfo->invalidnode){
			ret = bt_branch_del(plleft, llidx, pinfo, LEFT);
		}
		else if(RIGHT == pinfo->invalidnode){
			ret = bt_branch_del(path.prfather, path.rightidx, pinfo, MID);
		}
	}
	else if(RIGHT == pinfo->invalidnode){
		pinfo->invalidnode = ORDNUM;
		pleft = path.pmid->bn_inter.bn_entry[path.mididx].bn_ptr.bn_ptr;
		pmid = path.prfather->bn_inter.bn_entry[path.rightidx].bn_ptr.bn_ptr;
		btnode_t * prright = NULL;
		int rridx = 0;
		if(path.rightidx == path.prfather->bn_inter.bn_num-1){
			if(NULL != path.pright){
				pright = path.pright->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
				prright = path.pright;
				rridx = 0;
			}
		}
		else{
			pright = path.prfather->bn_inter.bn_entry[path.rightidx+1].bn_ptr.bn_ptr;
			prright = path.prfather;
			rridx = path.rightidx+1;
		}
		bt_child_handle(pleft, pmid, pright, idx, pinfo);
		if(0 != pinfo->leftkey){
			if(MOD_NOK == bt_branch_update(path.pmid, path.mididx)){
				ret = MOD_NOK;
			}
		}
		if(0 != pinfo->midkey){
			if(MOD_NOK == bt_branch_update(path.prfather, path.rightidx)){
				ret = MOD_NOK;
			}
		}
		if(LEFT == pinfo->invalidnode){
			ret = bt_branch_del(path.pmid, path.mididx, pinfo, MID);
		}
		else if(RIGHT == pinfo->invalidnode){
			ret = bt_branch_del(prright, rridx, pinfo, RIGHT);
		}
	}

	if(NULL != pinfo->newnode.bn_ptr.bn_ptr){
		ret = bt_branch_add(path.pmid, pinfo);
	}

	if((isUpdate == 1)&&(path.pmid->bn_level != BT_LVL_ROOT)){
		return MOD_NOK;
	}
	return ret;
}

int bt_insert(bptree_t * ptree, btk_t key){
	btpath_t path[BT_LVL_ROOT] = {0};
	modinfo_t ist_info = {0};
	ist_info.invalidnode = ORDNUM;
	modv_t ret = MOD_FAIL;
	int i = 0;

	bt_getpath_bykey(ptree->bpt_root, key, path, ptree->bpt_level);
	int cmp_ret = bt_key_cmp(path[ptree->bpt_level-1].pmid->bn_leaf.bn_data[path[ptree->bpt_level-1].mididx], key);
	if(0 == cmp_ret){
		log_debug("The key you want insert is exist!\n");
		return BTREE_OK;
	}
	else if(0 > cmp_ret){
		path[ptree->bpt_level-1].mididx++;
	}
	
	for(i=ptree->bpt_level-1; i>=0; i--){
		if(TYPE_LEAF == path[i].pmid->bn_type){
			ret = bt_leaf_add(path[i], key, &ist_info);
		}
		else if(MOD_OK == ret){
			break;
		}
		else if(MOD_FAIL == ret){
			return BTREE_FAIL;
		}
		else{
			ret = bt_branch_modify(path[i], &ist_info);
		}
	}
	
	if(MOD_NOK == ret){
		btnode_t * newroot = bt_new_node(TYPE_INT);
		btnode_t * newbranch = (btnode_t *)ist_info.newnode.bn_ptr.bn_ptr;
		btnode_t * tmpNode = ptree->bpt_root;
		btp_t ptr;
		if(NULL == newroot){
			log_debug("alloc new root for increase new level failed!\n");
			return BTREE_FAIL;
		}
		newroot->bn_level = BT_LVL_ROOT;
		if(tmpNode->bn_type == TYPE_LEAF){
			tmpNode->bn_level = BT_LVL_LEAF;
			newbranch->bn_level = BT_LVL_LEAF;
		}
		else{
			tmpNode->bn_level = BT_LVL_INT;
			newbranch->bn_level = BT_LVL_INT;
		}
		newroot->bn_inter.bn_entry[0].bn_key = bt_maxkey(tmpNode);
		newroot->bn_inter.bn_entry[0].bn_ptr.bn_ptr = tmpNode;
		newroot->bn_inter.bn_entry[1] = ist_info.newnode;
		newroot->bn_inter.bn_num = 2;
		ptree->bpt_level++;
		ptree->bpt_root = newroot;
	}
	else if(MOD_FAIL == ret){
		return BTREE_FAIL;
	}
	return BTREE_OK;
}

int bt_del(bptree_t * ptree, btk_t key){
	btpath_t path[BT_LVL_ROOT] = {0};
	modinfo_t del_info = {0};
	del_info.invalidnode = ORDNUM;
	modv_t ret = MOD_FAIL;
	btnode_t * ptarget = NULL;
	int i;

	bt_getpath_bykey(ptree->bpt_root, key, path, ptree->bpt_level);
	int cmp_ret = bt_key_cmp(path[ptree->bpt_level-1].pmid->bn_leaf.bn_data[path[ptree->bpt_level-1].mididx], key);
	if(0 != cmp_ret){
		log_debug("The key you want delete is not exist!\n");
		return BTREE_OK;
	}

	for(i=ptree->bpt_level-1; i>=0; i--){
		if(TYPE_LEAF == path[i].pmid->bn_type){
			ret = bt_leaf_del(path[i], &del_info);
		}
		else if(MOD_OK == ret){
			break;
		}
		else if(MOD_FAIL == ret){
			return BTREE_FAIL;
		}
		else{
			ret = bt_branch_modify(path[i], &del_info);
		}
	}

	if(MOD_NOK == ret){
		ptarget = ptree->bpt_root;
		if(ptarget->bn_type != TYPE_LEAF){
			if(ptarget->bn_inter.bn_num <= 1){
				btnode_t * pNode = (btnode_t *)ptarget->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
				pNode->bn_level = BT_LVL_ROOT;
				ptree->bpt_root = pNode;
				ptree->bpt_level --;
				del(ptarget);
			}
		}
		else{
			log_debug("there are only %d entries!\n",ptarget->bn_leaf.bn_num);
		}
	}
	return BTREE_OK;
}

int bt_tree_check(bptree_t * ptree){
	aque_t queue;
	btnode_t * pthis = NULL;
	btnode_t * prev = NULL;
	btnode_t * pson = NULL;
	int level = 0;
	btnode_t * pNode = ptree->bpt_root;
	while(1){
		level++;
		if(pNode->bn_type == TYPE_INT){
			pNode = (btnode_t *)pNode->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
		}
		else{
			break;
		}
	}
	if(level != ptree->bpt_level){
		log_debug("level is wrong\n");
		return BTREE_FAIL;
	}
	aque_init(&queue);
	aq_push(&queue,ptree->bpt_root);
	int i;
	while(queue.len>0){
		pthis = aq_pop(&queue);
		if(TYPE_INT == pthis->bn_type){
			if((INTER_KEY_NUM/2 > pthis->bn_inter.bn_num) && (BT_LVL_ROOT != pthis->bn_level)){
					log_debug("the INT Node[%ld] not enough!\n", pthis->bn_inter.bn_entry[pthis->bn_inter.bn_num-1].bn_key.bn_key);
					return BTREE_FAIL;
			}
			for(i=0; i<pthis->bn_inter.bn_num; i++){
				if(NULL == pthis->bn_inter.bn_entry[i].bn_ptr.bn_ptr){
					log_debug("the INT Node[%ld][%d] ptr is null!\n", pthis->bn_inter.bn_entry[i].bn_key.bn_key, i);
					return BTREE_FAIL;
				}
				else{
					pson = pthis->bn_inter.bn_entry[i].bn_ptr.bn_ptr;
				}
				if(TYPE_INT == pson->bn_type){
					if(bt_key_cmp(pthis->bn_inter.bn_entry[i].bn_key, pson->bn_inter.bn_entry[pson->bn_inter.bn_num-1].bn_key) != 0){
						log_debug("The key[%ld] not equal son[INT] max key!\n", pthis->bn_inter.bn_entry[i].bn_key.bn_key);
						return BTREE_FAIL;
					}
				}
				else if(TYPE_LEAF == pson->bn_type){
					if(bt_key_cmp(pthis->bn_inter.bn_entry[i].bn_key, pson->bn_leaf.bn_data[pson->bn_leaf.bn_num-1]) != 0){
						log_debug("The key[%ld] not equal son[LEAF] max key!\n", pthis->bn_inter.bn_entry[i].bn_key.bn_key);
						return BTREE_FAIL;
					}
				}
				else{
					log_debug("The Node[%ld]'s son node type[%d] is invalid!\n", pthis->bn_inter.bn_entry[i].bn_key.bn_key, pson->bn_type);
					return BTREE_FAIL;
				}
				if(i>0){
					if(bt_key_cmp(pthis->bn_inter.bn_entry[i-1].bn_key, pthis->bn_inter.bn_entry[i].bn_key) >= 0){
						log_debug("the INT Node[%ld][%d] key is not sorted!\n", pthis->bn_inter.bn_entry[i].bn_key.bn_key, i);
						return BTREE_FAIL;
					}
				}
				aq_push(&queue, pson);
			}
			if(NULL != prev){
				if(TYPE_INT == prev->bn_type){
					if(bt_key_cmp(prev->bn_inter.bn_entry[prev->bn_inter.bn_num-1].bn_key, pthis->bn_inter.bn_entry[0].bn_key) >= 0){
						if(prev->bn_level == pthis->bn_level){
							log_debug("prev node max key bigger than this node first key\n");
							return BTREE_FAIL;
						}
					}
				}
				else{
					log_debug("INT node's prev node is not INT\n");
					return BTREE_FAIL;
				}
			}
		}
		else if(TYPE_LEAF == pthis->bn_type){
			if((LEAF_KEY_NUM/2 > pthis->bn_leaf.bn_num) && (BT_LVL_ROOT != pthis->bn_level)){
				log_debug("the LEAF Node[%ld] not enough!\n", pthis->bn_leaf.bn_data[i].bn_key);
				return BTREE_FAIL;
			}
			for(i=0; i<pthis->bn_leaf.bn_num; i++){
				if(i>0){
					if(bt_key_cmp(pthis->bn_leaf.bn_data[i-1], pthis->bn_leaf.bn_data[i]) >= 0){
						log_debug("the LEAF Node[%ld][%d] key is not sorted!\n", pthis->bn_leaf.bn_data[i].bn_key, i);
						return BTREE_FAIL;
					}
				}
			}
			if(NULL != prev){
				if(TYPE_INT == prev->bn_type){
					if(bt_key_cmp(prev->bn_inter.bn_entry[prev->bn_inter.bn_num-1].bn_key, pthis->bn_leaf.bn_data[0]) <= 0){
						log_debug("last level node max key[%ld] smaller than this node first key[%ld]\n",
							prev->bn_inter.bn_entry[prev->bn_inter.bn_num-1].bn_key.bn_key, pthis->bn_leaf.bn_data[0].bn_key);
						return BTREE_FAIL;
					}
				}
				else if(TYPE_LEAF== prev->bn_type){
					if(bt_key_cmp(prev->bn_leaf.bn_data[prev->bn_leaf.bn_num-1], pthis->bn_leaf.bn_data[0]) >= 0){
						log_debug("prev node max key bigger than this node first key\n");
						return BTREE_FAIL;
					}
				}
				else
				{
					log_debug("LEAF node's prev node is invalid\n");
					return BTREE_FAIL;
				}
			}
		}
		else{
			log_debug("Node type is wrong!\n");
			return BTREE_FAIL;
		}
		prev = pthis;
	}
	return BTREE_OK;
}

void bt_init(bptree_t * ptree){
	ptree->bpt_leaf_nums = LEAF_KEY_NUM;
	ptree->bpt_branch_nums = INTER_KEY_NUM;
	ptree->bpt_level = 1;
	ptree->bpt_root = NULL;
}

void bt_create_root(bptree_t * ptree){
	ptree->bpt_root = bt_new_node(TYPE_LEAF);
	ptree->bpt_root->bn_level = BT_LVL_ROOT;
	ptree->bpt_root->bn_type = TYPE_LEAF;
	ptree->bpt_root->bn_leaf.bn_num = 0;
}
#if 1

int get_tree_leaf_num(btnode_t * proot){
	btleaf_t * pleaf = NULL;
	btnode_t * pNode = proot;
	while(pNode->bn_type != TYPE_LEAF){
		pNode = (btnode_t *)pNode->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
	}
	pleaf = &pNode->bn_leaf;
	struct list_head * plnode = &pleaf->lnode;
	int num = pleaf->bn_num;
	while(plnode->next != NULL){
		plnode = plnode->next;
		pleaf = (btleaf_t *)plnode;
		num += pleaf->bn_num;
	}
	return num;
}

void print_btree_info(bptree_t * ptree){
	log_debug("B+ Tree level num:%d\n", ptree->bpt_level);
	log_debug("B+ Tree branch node key num:%d\n", ptree->bpt_branch_nums);
	log_debug("B+ Tree leaf node key num:%d\n", ptree->bpt_leaf_nums);
	log_debug("B+ Tree have %d datas\n", get_tree_leaf_num(ptree->bpt_root));
}

void print_leaf(btleaf_t * pleaf, char * prefix){
	if(pleaf->bn_num <= 0){
		log_debug("There is no data, please insert!\n");
		return;
	}
	int i = 0;
	for(i=0; i<pleaf->bn_num-1; i++){
		printf("%s├────%ld\r\n",prefix, pleaf->bn_data[i].bn_key);
	}
	printf("%s└────%ld\r\n",prefix, pleaf->bn_data[i].bn_key);
}

void print_btree(bptree_t * ptree)
{
	if((NULL == ptree) ||
		(NULL != ptree && NULL == ptree->bpt_root)){
		return;
	}

	btpath_t path[BT_LVL_ROOT] = {0};
	int cusor = 0;
	path[cusor].pmid = ptree->bpt_root;
	path[cusor].mididx= 0;
	cusor++;
	btnode_t * tmpNode = NULL;
	btp_t ptr;
	char prefix[100] = {0};
	int pre_idx = 0;
	printf("Root\n");
	while(cusor){
		tmpNode = path[cusor-1].pmid;
		if(TYPE_LEAF != tmpNode->bn_type){
			if(path[cusor-1].mididx < tmpNode->bn_inter.bn_num){
				if(path[cusor-1].mididx == tmpNode->bn_inter.bn_num-1){
					printf("%s└────%ld\n", prefix, tmpNode->bn_inter.bn_entry[path[cusor-1].mididx].bn_key.bn_key);
					sprintf(prefix, "%s          ", prefix);
				}
				else{
					printf("%s├────%ld\n", prefix, tmpNode->bn_inter.bn_entry[path[cusor-1].mididx].bn_key.bn_key);
					sprintf(prefix, "%s│         ", prefix);
				}
				path[cusor].pmid = (btnode_t *)tmpNode->bn_inter.bn_entry[path[cusor-1].mididx].bn_ptr.bn_ptr;
				path[cusor-1].mididx ++;
				path[cusor].mididx = 0;
				cusor ++;
				pre_idx += 8;
				prefix[pre_idx] = 0;
			}
			else{
				cusor--;
				pre_idx -= 8;
				prefix[pre_idx] = 0;
			}
		}
		else{
			print_leaf(&tmpNode->bn_leaf, prefix);
			cusor --;
			pre_idx -= 8;
			prefix[pre_idx] = 0;
		}
	}
}
#endif

void write_node(btnode_t * pNode, int fd, int num){
	if(NULL == pNode)
		return;
	char buf[1024] = {0};
	int i = 0;
	if(pNode->bn_type == TYPE_INT){
		sprintf(buf, "\n%d ### INT %d :", num, pNode->bn_level);
		for(i=0; i<pNode->bn_inter.bn_num; i++){
			sprintf(buf, "%s - [ %ld : %ld ]", buf, (unsigned long)(pNode->bn_inter.bn_entry[i].bn_ptr.bn_ptr), pNode->bn_inter.bn_entry[i].bn_key.bn_key);
		}
	}
	else{
		sprintf(buf, "\n%d ### LEAF %d :", num, pNode->bn_level);
		for(i=0; i<pNode->bn_leaf.bn_num; i++){
			sprintf(buf, "%s - %ld", buf, pNode->bn_leaf.bn_data[i].bn_key);
		}
	}
	printf("%s\n", buf);
	write(fd, buf, strlen(buf));
}

void dump_tree(bptree_t * ptree, int fd){
	if((NULL == ptree) ||
		(NULL != ptree && NULL == ptree->bpt_root)){
		return;
	}
	btnode_t * pNode = NULL;
	char buf[NODE_SIZE];
	btnode_t * tmpNode = (btnode_t *)buf;
	aque_t queue;
	unsigned long long offset = 0;
	int num = 0;
	sprintf(buf, "\nData count:%d", get_tree_leaf_num(ptree->bpt_root));
	write(fd, buf, strlen(buf));
	aque_init(&queue);
	aq_push(&queue, ptree->bpt_root);
	while(queue.len > 0){
		pNode = aq_pop(&queue);
		if(pNode->bn_type == TYPE_INT){
			memcpy(buf, pNode, NODE_SIZE);
			int i;
			for(i=0; i<pNode->bn_inter.bn_num; i++){
				offset += 1;
				aq_push(&queue, pNode->bn_inter.bn_entry[i].bn_ptr.bn_ptr);
				tmpNode->bn_inter.bn_entry[i].bn_ptr.bn_ptr = (void *)offset;
			}
			pNode = tmpNode;
		}
		write_node(pNode, fd, num++);
	}
}


void load_tree(bptree_t * ptree, char * tree_name){
	char * keystr = NULL;
	char * remainstr = NULL;
	char line[200] = {0};
	char typestr[5] = {0};
	btype_t type;
	int key = 0;
	int ptr = 0;
	int level = 0;
	btnode_t * pNode = NULL;
	btnode_t * prev = NULL;
	bti_t * tmp = NULL;
	long file_seek = 0;
	int number = 0;
	if(ptree->bpt_root != NULL){
		return;
	}
	FILE * pfile = fopen(tree_name, "r");
	if(NULL == pfile){
		return;
	}
	aque_t queue;
	aque_init(&queue);
	do{
		if(NULL == fgets(line, 199, pfile)){
			log_debug("tree file is end!\n");
			break;
		}
		sscanf(line, "%d ### %s %d : %*s", &number, typestr, &level);
		if(strcmp(typestr, "INT") == 0){
			type = TYPE_INT;
		}
		else if(strcmp(typestr, "LEAF") == 0){
			type = TYPE_LEAF;
		}
		else{
			log_debug("[LOAD]type error\n");
			return;
		}
		pNode = bt_new_node(type);
		if(BT_LVL_ROOT == level){
			ptree->bpt_root = pNode;
		}
		if(TYPE_LEAF == type){
			if(NULL == prev){
				prev = pNode;
			}
			else{
				prev->bn_leaf.lnode.next = &pNode->bn_leaf.lnode;
				pNode->bn_leaf.lnode.prev = &prev->bn_leaf.lnode;
				prev = pNode;
			}
		}
		pNode->bn_level = level;
		tmp = aq_pop(&queue);
		if(NULL != tmp){
			tmp->bn_ptr.bn_ptr = (void *)pNode;
		}
		keystr = strchr(line, '-');
		int i = 0;
		while(keystr){
			if(TYPE_INT == type){
				sscanf(keystr, "- [%d : %d] -%*s", &ptr, &key);
				pNode->bn_inter.bn_entry[i].bn_key.bn_key = key;
				pNode->bn_inter.bn_entry[i].bn_ptr.bn_ptr = (void *)ptr;
				aq_push(&queue, &pNode->bn_inter.bn_entry[i]);
				pNode->bn_inter.bn_num++;
			}
			else{
				sscanf(keystr, "- %d -%*s", &key);
				pNode->bn_leaf.bn_data[i].bn_key = key;
				pNode->bn_leaf.bn_num++;
			}
			keystr += 1;
			keystr = strchr(keystr, '-');
			i++;
		}
	}
	while(queue.len>0);
	pNode = ptree->bpt_root;
	level = 0;
	while(1){
		level++;
		if(pNode->bn_type == TYPE_INT){
			pNode = (btnode_t *)pNode->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
		}
		else{
			break;
		}
	}
	ptree->bpt_level = level;
}

void save_tree_data(bptree_t * ptree, int fd){
	char buf[12];
	btleaf_t * pleaf = NULL;
	btnode_t * pNode = ptree->bpt_root;
	while(pNode->bn_type != TYPE_LEAF){
		pNode = (btnode_t *)pNode->bn_inter.bn_entry[0].bn_ptr.bn_ptr;
	}
	pleaf = &pNode->bn_leaf;
	while(pleaf != NULL){
		int i;
		memset(buf, 0, 12);
		for(i=0; i<pleaf->bn_num; i++){
			snprintf(buf, 12, "%ld\n", pleaf->bn_data[i].bn_key);
			write(fd, buf, strlen(buf));
		}
		pleaf = (btleaf_t *)pleaf->lnode.next;
	}
}

void print_prompt()
{
	log_debug("Insert node please press 'i'!\n");
	log_debug("Delete node please press 'd'!\n");
	log_debug("Print tree please press 'p'!\n");
	log_debug("Get prompt please press '?'!\n");
	log_debug("Quit this program please press 'q'!\n");
}

void print_eof()
{
	log_debug("#input order[insert/del/print/?/quit]:");
}
