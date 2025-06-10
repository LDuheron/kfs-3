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


static void __bDeleteEmptyLeaf(__bRes place){
	//merge with sibling;
	int sibling = __bFindSibling(place.node);
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



static  void __bDeleteLeaf(__bRes place){
	const __bDeleteFunc func[2] = {&__bDeleteNonEmptyLeaf, &__bDeleteEmptyLeaf}
	(*func[(*place.node).empty])(place);
}

__bRes __bMaxMin(__bRes place){
    __bNode* actual = (*place.node).children[place.rank];
    __bRes res = {NULL, 0};
    int steps = 0;
    while ((*actual).children[0]){
        steps++;
        actual =(*actual).children[(*actual).count];
        if (!(*actual).empty)
            res.rank = steps;
    }
    res.node = actual;
    return res;
}

__bRes __bMinMax(__bRes place){
    __bNode* actual = (*place.node).children[place.rank + 1];
    __bRes res = {NULL, 0};
    int steps = 0;
    while ((*actual).children[0]){
        steps++;
        actual =(*actual).children[0];
        if (!(*actual).empty)
            res.rank = steps;
    }
    res.node = actual;
    return res;
}

static __bRes __bClosest(__bRes place){
    __bRes minMax = __bMinMax(place);
    __bRes maxMin = __bMaxMin(place);
    if (minMax.rank < maxMin.rank){
        maxMin.rank = (*maxMin.node).count - 1;
        return maxMin;
    }
    minMax.rank = 0;
    return minMax;
}



static __bRes __bDeleteNode(__bRes place){
	const __bDeleteFunc func[2] = {&__bDeleteLeaf, &__bDeleteNode};
	__bRes	closest = __bClosest(place);
	(*place.node).dividors[place.rank] = (*closest.node).dividors[closest.rank];
	(*func[(bool) (*place.node).children[0]])(place);
	//return (closest);
}



__bRes __bFind(__bTree* tree, int value){
    __bRes res = {NULL, -1};
    __bNode actual = (*tree).root;
    __bNode potential = actual;
    bool found = false;
    while (!found && potential){
        actual = potential;
        res.rank = __bDichoFind(value, (*actual).dividors, (*actual).count);
        found = (*actual).dividors[index] == value;
        bool past = (*actual).dividors[index] < value;
        potential = (*actual).children[index + past];
    }
    res.node = actual;
    return res;
}

void __bDelete(__bTree* tree, int value){
	const __bDeleteFunc func[2] = {&__bDeleteLeaf, &__bDeleteNode};

	__bRes place = __bFind(tree, value);
    if (place.rank == -1)
        return;
	(*func[(bool) (*place.node).children[0]])(place);
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
