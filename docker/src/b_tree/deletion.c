/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:20:46 by athierry          #+#    #+#             */
/*   Updated: 2025/06/11 20:24:45 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

static __bRes __bMergeNode(&place){

}


static void __bBalance(__bTree* tree, __bRes merged){
	while (merged.node){
		if ((*merged.node).empty){

		}
		else{
			for (int i = merged.rank + 1; i < (*merged.node).count; i++){
				(*merged.node).dividors[i - 1] = (*merged.node).dividors[i];
				(*merged.node).children[i] = (*merged.node).dividors[i + 1]; // think again
				(*merged.node).count -= 1;
				(*merged.node).empty = (*merged.node).count == BVALUE / 2;
			}

		}
	}
}



static __bRes __bMergeLeaf(__bRes place){
	//delete element
	for (int i = place.rank; i < (*place.node).count; i++)
		(*place.node).dividors[i] = (*place.node).dividors[i + 1];
	(*place.node).count -= 1;
	//ensure right sibling
	if ((*place.node).rank == (*(*place.node).parent).count - 1){
		place.node = (*(*place.node).parent).children[(*place.node).rank - 1];
	}
	//insert parent
	(*place.node).dividors[(*place.node).count++] = (*(*place.node).parent).dividors[(*place.node).rank];
	//insert sibling
	__bNode* sibling = (*(*place.node).parent).children((*place.node).rank + 1);
	for (int i = 0; i < (*sibling).count; i++){
		(*place.node).dividors[(*place.node).count++] = (*sibling).dividors[i];
	}
	__bFree(sibling);
	place.rank = (*place.node).rank;
	place.node = (*place.node).parent;
	return place;
}



static void __bDeleteEmptyLeaf(__bRes place){
	int sibling = __bFindNonEmptySibling(place.node);
	if (sibling)
		place = __bRotateLeaf(place, sibling);
	else{
		place = __bMergeLeaf(place);
		__bBalance(tree, place);
	}
}



static void __bDeleteNonEmptyLeaf(__bRes place){
	//memmove;
	int count = (*place.node).count;
	for (int i = place.rank; i < count; i++)
		(*place.node).children[i] = (*place.node).children[i + 1];
	(*place.node).count -= 1;
	place.node = NULL;
}



static  void __bDeleteLeaf(__bRes place){
	const __bDeleteFunc func[2] = {&__bDeleteNonEmptyLeaf, &__bDeleteEmptyLeaf}
	(*func[(*place.node).empty])(place);
}



static __bRes __bDeleteNode(__bRes place){
	//const __bDeleteFunc func[2] = {&__bDeleteLeaf, &__bDeleteNode};
	__bRes	closest = __bClosest(place);
	(*place.node).dividors[place.rank] = (*closest.node).dividors[closest.rank];
	__bDeleteLeaf(closest);
	//(*func[(bool) (*place.node).children[0]])(place);
	//return (closest);
}



void __bDelete(__bTree* tree, int value){
	const __bDeleteFunc func[2] = {&__bDeleteLeaf, &__bDeleteNode};

	__bRes place = __bFind(tree, value);
	if (place.rank == -1)
		return;
	(*func[(bool) (*place.node).children[0]])(place);
	(*(*tree).root).empty = false;
}
