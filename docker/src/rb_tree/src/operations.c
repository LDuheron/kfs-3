/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:12:36 by athierry          #+#    #+#             */
/*   Updated: 2025/07/04 19:32:19 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <stdio.h>

static int __rbIsRb(__rbTree* tree, __rbNode* node){
	if (node == &(*tree).nill)
		return 1;
	int left = __rbIsRb(tree, (*node).children[0]);
	int right = __rbIsRb(tree, (*node).children[1]);
	if (left && left == right)
		left += (*node).color == BLACK;
	else 
		left = 0;
	return left;
}


static void __rbRecPrint(char *str, __rbTree* tree, __rbNode* node, int depth, bool right){
	//if nill, done
	if (node == &(*tree).nill)
		return;
	
	//modify string and print left subtree
	if (!right)
		str[2 * depth - 1] = ' ';
	else
		str[2 * depth - 1] = '|';
	str[2 * depth] = ' ';
	str[2 * depth + 1] = '|';
	__rbRecPrint(str, tree, (*node).children[0], depth + 1, false);

	//modify string and print node
        str[2 * depth - 1] = '|'; // mode 1
    //if (right) // mode 2
        //str[2 * depth - 1] = '|'; // mode 2
    //else // mode 2
        //str[2 * depth - 1] = ' '; // mode 2
	str[2 * depth] = '-'; // mode 1
	//str[2 * depth] = '_'; // mode 2
	str[2 * depth + 1] = '\0';
	if ((*node).color == RED)
		printf("%s\033[31m%d\033[0m", str, (*node).data.value);
	else
		printf("%s%d", str, (*node).data.value);
	if (DEBUG_PRINT && !__rbIsRb(tree, node))
		printf(" unbalanced");
	printf("\n");

    //if (!right) // mode 2
        //str[2 * depth - 1] = '|'; // mode 2
    //else // mode 2
        //str[2 * depth - 1] = ' '; // mode 2
	//modify string and print right subtree
	str[2 * depth] = ' ';
	if (!right)
		str[2 * depth + 1] = '|';
	else
		str[2 * depth - 1] = ' ';
	__rbRecPrint(str, tree, (*node).children[1], depth + 1, true);

}

void __rbPrint(__rbTree* tree){
	static char str[3000];
	str[0] = ' ';
	str[1] = '\0';
	__rbRecPrint(str + 1, tree, (*tree).root, 0, false);
	printf("\n");
}

void __rbInit(__rbTree* tree){
	(*tree).nill.data.value = INT_MAX;
	(*tree).nill.children[0] = &(*tree).nill;
	(*tree).nill.children[1] = &(*tree).nill;
	(*tree).nill.parent = &(*tree).nill;
	(*tree).nill.color = BLACK;
	(*tree).root = &(*tree).nill;
}




void __rbRotate(__rbTree* tree, __rbNode* node, bool greater){
	__rbNode* parent = (*node).parent;
	__rbNode* pivot = (*node).children[greater];

	//turn pivot's `!greater` subtree into node's `greater` subtree
	(*node).children[greater] = (*pivot).children[!greater];
	(*(*node).children[greater]).parent = node;
	(*(*node).children[greater]).elder = greater; 

	//link node's parent to pivot
	(*parent).children[(*node).elder] = pivot;
	(*pivot).parent = parent;
	(*pivot).elder = (*node).elder;

	//put node on pivot's `!greater` side
	(*pivot).children[!greater] = node;
	(*node).parent = pivot;
	(*node).elder = !greater;

	//reset in case node was root
	(*tree).root = (*tree).nill.children[0];
}


void __rbTransplant(__rbTree* tree, __rbNode* toNode, __rbNode* fromNode){
	(*(*toNode).parent).children[(*toNode).elder] = fromNode;
	(*fromNode).elder = (*toNode).elder;
	(*fromNode).parent = (*toNode).parent;
	(*tree).root = (*tree).nill.children[0];
}


__rbNode* __rbBestFit(__rbTree* tree, int value){
	__rbNode* bestFit = &(*tree).nill; // (*tree).root
	__rbNode* current = (*tree).nill.children[0]; // (*tree).root

	while (current != &(*tree).nill){
		bool goodFit = (*current).data.value >= value;
		if (goodFit)
			bestFit = current;	
		current = (*current).children[!goodFit];
	}
	return bestFit;
}


__rbNode* __rbFind(__rbTree* tree, ssize_t value){
	__rbNode* current = (*tree).nill.children[0]; // (*tree).root

	while ((*current).data.value != value && current != &(*tree).nill)
		current = (*current).children[(*current).data.value < value];
	return (current);
}
