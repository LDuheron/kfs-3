/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:20:46 by athierry          #+#    #+#             */
/*   Updated: 2025/07/11 16:48:36 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bTree.h"

static void __bFree(__bNode* node){
	free(node);
}

static __bRes __bMergeNode(__bRes place){
	//delete element
	for (int i = place.rank + 1; i < (*place.node).count; i++){
		(*place.node).dividors[i - 1] = (*place.node).dividors[i];
		(*place.node).children[i] = (*place.node).children[i + 1];
		(*(*place.node).children[i]).rank -= 1;
	}
	(*place.node).count -= 1;
	//ensure right sibling
	if ((*place.node).rank == (*(*place.node).parent).count - 1)
		place.node = (*(*place.node).parent).children[(*place.node).rank - 1];
	//insert parent
	(*place.node).dividors[(*place.node).count++] = (*(*place.node).parent).dividors[(*place.node).rank];
	//insert sibling
	__bNode* sibling = (*(*place.node).parent).children[(*place.node).rank + 1];
	for (int i = 0; i < (*sibling).count; i++){
		(*(*sibling).children[i]).rank = (*place.node).count;
		(*place.node).children[(*place.node).count] = (*sibling).children[i];
		(*place.node).dividors[(*place.node).count++] = (*sibling).dividors[i];
	}
	(*(*sibling).children[(*sibling).count]).rank = (*place.node).count;
	(*place.node).children[(*place.node).count] = (*sibling).children[(*sibling).count];
	__bFree(sibling);
	place.rank = (*place.node).rank;
	place.node = (*place.node).parent;
	return place;
}





static __bRes __bBalanceEmptyNode(__bTree* tree, __bRes merged){
	(void) tree;
	int sibling = __bFindNonEmptySibling(merged.node);
	__bRes place;
	if (sibling)
		place = __bRotateNode(merged, sibling);
	else
		place = __bMergeNode(merged);
	return place;
}



static __bRes __bBalanceNonEmptyNode(__bTree* tree, __bRes merged){
	(void) tree;
	for (int i = merged.rank + 1; i < (*merged.node).count; i++){
		(*merged.node).dividors[i - 1] = (*merged.node).dividors[i];
		(*merged.node).dividors[i] = (*merged.node).dividors[i + 1]; // think again
	}
	(*merged.node).count -= 1;
	(*merged.node).empty = (*merged.node).count == BVALUE / 2;
	merged.node = NULL;
	return merged;
}


typedef __bRes (*__bBalanceFunc)(__bTree*, __bRes);

static void __bBalance(__bTree* tree, __bRes merged){
	__bBalanceFunc func[2] = {&__bBalanceNonEmptyNode, &__bBalanceEmptyNode};
	while (merged.node)
		merged = (*func[(*merged.node).empty])(tree, merged);
}



static __bRes __bMergeLeaf(__bRes place){
	//delete element
	for (int i = place.rank; i < (*place.node).count; i++)
		(*place.node).dividors[i] = (*place.node).dividors[i + 1];
	(*place.node).count -= 1;
	//ensure right sibling
	if ((*place.node).rank == (*(*place.node).parent).count - 1)
		place.node = (*(*place.node).parent).children[(*place.node).rank - 1];
	//insert parent
	(*place.node).dividors[(*place.node).count++] = (*(*place.node).parent).dividors[(*place.node).rank];
	//insert sibling
	__bNode* sibling = (*(*place.node).parent).children[(*place.node).rank + 1];
	for (int i = 0; i < (*sibling).count; i++){
		(*place.node).dividors[(*place.node).count++] = (*sibling).dividors[i];
	}
	__bFree(sibling);
	place.rank = (*place.node).rank;
	place.node = (*place.node).parent;
	return place;
}



static void __bDeleteEmptyLeaf(__bTree* tree, __bRes place){
	int sibling = __bFindNonEmptySibling(place.node);
	if (sibling)
		__bRotateLeaf(place, sibling);
	else{
		place = __bMergeLeaf(place);
		__bBalance(tree, place);
	}
}



static void __bDeleteNonEmptyLeaf(__bTree* tree, __bRes place){
	(void) tree;
	//memmove;
	int count = (*place.node).count;
	for (int i = place.rank; i < count; i++)
		(*place.node).dividors[i] = (*place.node).dividors[i + 1];
	(*place.node).count -= 1;
	place.node = NULL;
}



static  void __bDeleteLeaf(__bTree* tree, __bRes place){
	const __bDeleteFunc func[2] = {&__bDeleteNonEmptyLeaf, &__bDeleteEmptyLeaf};
	(*func[(*place.node).empty])(tree, place);
}



static void __bDeleteNode(__bTree* tree, __bRes place){
	__bRes	closest = __bClosest(place);
	(*place.node).dividors[place.rank] = (*closest.node).dividors[closest.rank];
	__bDeleteLeaf(tree, closest);
}

__bRes __bFind(__bNode* node, int value){
	//int i = 0;
	__bRes res;
	res.node = node;
	res.rank = value;
	// WRONG
	return res;
}

void __bDelete(__bTree* tree, int value){
	const __bDeleteFunc func[2] = {&__bDeleteLeaf, &__bDeleteNode};

	__bRes place = __bFind((*tree).root, value);
	if (place.rank == -1)
		return;
	(*func[(bool) (*place.node).children[0]])(tree, place);
	(*(*tree).root).empty = false;
}
