/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:12:36 by athierry          #+#    #+#             */
/*   Updated: 2025/07/01 22:49:18 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <stdio.h>
#define PRETTY_PRINT true

static void __rbRecPrint(char *str, __rbTree* tree, __rbNode* node, int depth, bool right){
	if (node == &(*tree).nill)
		return;
    int i = depth;
    if (PRETTY_PRINT)
        printf("%s\n", str);
	if ((*node).color == RED)
        printf("%s_\033[31m%d\033[0m \n", str, (*node).data.value);
    else
        printf("%s_%d\n", str, (*node).data.value);
    if (right)
        str[depth - 1] = ' ';
    str[depth] = ' ';
    str[depth + 1] = '|';
    str[depth + 2] = '\0';
	__rbRecPrint(str, tree, (*node).children[0], depth + 2, false);
	__rbRecPrint(str, tree, (*node).children[1], depth + 2, true);
    str[depth] = '\0';
}

void __rbPrint(__rbTree* tree){
	static char str[3000];
    str[0] = '\0';
	__rbRecPrint(str, tree, (*tree).root, 0, false);
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
	(*parent).children[(*node).elder] = pivot;
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

/*
void __rbRotate(__rbTree* tree, __rbNode* node, bool greater){
	__rbNode* parent = (*node).parent;
	__rbNode* pivot = (*node).children[greater];

	//turn pivot's `!greater` subtree into node's `greater` subtree
	(*node).children[greater] = (*pivot).children[!greater];
	(*parent).children[(*node).elder] = pivot;
    (*pivot).parent = parent;
	(*(*node).children[greater]).parent = node;
	(*(*node).children[greater]).elder = !(*(*node).children[greater]).elder; 

	//link node's parent to pivot
	(*parent).children[(*node).elder] = pivot;

	//put node on pivot's `!greater` side
	(*pivot).children[!greater] = node;
	(*node).parent = pivot;

	//reset in case node was root
	(*tree).root = (*tree).nill.children[0];
	(*(*tree).root).color = BLACK;
}


void __rbTransplant(__rbTree* tree, __rbNode* toNode, __rbNode* fromNode){
	(*(*toNode).parent).children[(*toNode).elder] = fromNode;
	(*fromNode).elder = (*toNode).elder;
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
*/
