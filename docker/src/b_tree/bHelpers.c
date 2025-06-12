/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bHelpers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:51:07 by athierry          #+#    #+#             */
/*   Updated: 2025/06/11 18:54:42 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bTree.h"

static int __bFindNonEmptySibling(__bNode* node){
	int res = 0;
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


static __bRes __bMaxMin(__bRes place){
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



static __bRes __bMinMax(__bRes place){
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



static __bRes __bFind(__bTree* tree, int value){
	__bRes res = {NULL, -1};
	__bNode actual = (*tree).root;
	__bNode potential = actual;
	bool found = false;
	while (!found && potential){
		actual = potential;
		int index = __bDichoFind(value, (*actual).dividors, (*actual).count);
		found = (*actual).dividors[index] == value;
		bool past = (*actual).dividors[index] < value;
		potential = (*actual).children[index + past];
		res.rank += found * (1 + index);
	}
	res.node = actual;
	return res;
}

