/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:20:46 by athierry          #+#    #+#             */
/*   Updated: 2025/06/04 19:17:23 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

static int __bFindSibling(__bNode* node){
	int res = 0;
	//if (!node || ! (*node).parent)
	//return res;
	__bNode* siblings = (*node).parent.children;
	int rank = (*node).rank;
	for (int i = 1; i < (*node).parent.count - rank; i++){
		if (!(*(siblings + rank + i)).empty){
			res = i;
			break;
		}
	}
	int min = res && res < rank ? res: rank;
	for (int i = 1; i < min; i++){
		if (!(*(siblings + rank - i)).empty){
			res = -i;
			break;
		}
	}
	return res;
}


static void __bMergeNode(&place){

}

static void __bMergeLeaf(&place){
}

typedef void	(*__bRotateFunc)(__bRes, int);


static void __bDeleteLeafEmpty(__bRes place){
	//merge with sibling;
	int sibling = __bFindSibling(place.node);
	if (sibling)
		place = __bRotateLeaf(place, sibling);
	else{
		place = __bMergeLeaf(place);
		__bBalance(tree, place);
	}
}

static void __bDeleteLeaf(__bRes place){
	//memmove;
	int count = (*place.node).count;
	for (int i = place.rank; i < count; i++)
		(*place.node).children[i] = (*place.node).children[i + 1];
	(*place.node).count -= 1;
	place.node = NULL;
}

/*
   static __bRes __bDeleteNodeEmpty(__bRes place){
   __bRes replacement = __bFindReplacement(place);
   if (replacement.node)
   place = __bReplace(place, replacement);
   else
   place = __bMergeNode(place);
   return place;
   }
   */

static __bRes __bDeleteNode(__bRes place){
	__bRes	closest = __bClosest(place);
	(*place.node).dividors[place.rank] = (*closest.node).dividors[closest.rank];
	return (closest);
}

void __bDelete(__bTree* tree, int value){
	const __bDeleteFunc func[2][2] = {{&__bDeleteLeaf, &__bDeleteLeafEmpty},
		{&__bDeleteNode, &__bDeleteNode}};

	__bRes place = __bFind(tree, value);
	(*func[!(*node).children[0]][(*node).empty])(place);
	(*(*tree).root).empty = false;
}







//if (!(*place.node).empty){
//__bRes	closest = __bClosest(place);
//(*place.node).dividors[place.rank] = (*closest.node).dividors[closest.rank];
//place = closest;
//}
//else{
//int sibling = __bFindSibling(place.node);
//if (sibling)
//__bRotate(place, sibling);
//else
//__bMerge(&place);
//}
//}
//}
