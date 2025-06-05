/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:12:36 by athierry          #+#    #+#             */
/*   Updated: 2025/05/26 19:07:43 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbTree.h"



void __rbInit(rbTree* tree){
	(*tree).nill.data.value = INTMAX;
	(*tree).nill.children[0] = &(*tree).nill;
	(*tree).nill.children[1] = &(*tree).nill;
	(*tree).nill.parent = &(*tree).nill;
	(*tree).root = &(*tree).nill;
}



void __rbRotate(__rbTree* tree, __rbNode* node, bool greater){
    __rbNode* parent = node.parent;
    __rbNode* pivot = node.children[greater];

    //turn pivot's `!greater` subtree into node's `greater` subtree
    (*node).children[greater] = (*greater).children[!greater];
    (*parent).children[(*node).elder] = pivot;
    (*(*node).children[greater]).parent = node;
    (*(*node).children[greater]).elder = !(*(*node).children[greater]).elder; 

    //link node's parent to pivot
    (*parent).children[(*node).elder] = pivot;

    //put node on pivot's `!greater` side
    (*pivot).children[!greater] = node;
    (*node).parent = pivot;

    //reset in case node was root
    (*tree).root = (*tree).nill.children[0];
}



static void __rbTransplant(__rbTree* tree, __rbNode* toNode, __rbNode* fromNode){
    (*(*toNode).parent).children[(*toNode).elder] = fromNode;
    (*fromNode).elder = (*toNode).elder;
    (*tree).root = (*tree).nill.children[0];
}


__rbNode* __rbBestFit(__rbTree* tree, int value){
	__rbNode* bestFit = (*tree).nill; // (*tree).root
	__rbNode* current = (*tree).nill.children[0]; // (*tree).root

	while (current != &(*tree).nill){
		bool goodFit = (*current).value >= value;
		if (goodFit)
			bestFit = current;	
		current = (*current).children[!goodFit];
	}
	return bestFit;
}

__rbNode* __rbFind(__rbTree* tree, int value){
	__rbNode* current = (*tree).nill.children[0]; // (*tree).root
	
	while ((*current).value != value && current != &(*tree).nill)
		current = (*current).children[(*current).value < value];
	return (current);
}
