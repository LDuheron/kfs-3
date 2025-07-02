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

static void __rbPutnbr(char* str, int value){
	static char nbr[16];
	bool	neg = value < 0; 
	int i = 15;
	nbr[i--] = '\0';
	value += ((int) neg) * 2 * value;
	do{
		nbr[i--] = value % 10 + '0';
		value /= 10;
	} while (value);
	if (neg)
		nbr[i--] = '-';
	i++;
	while (i < 16)
		*(str++) = nbr[i++];
}

static void __rbRecPrint(char *str, __rbTree* tree, __rbNode* node, int depth, bool right){
	//int i = 0;
	//char* cp = str;
	if (node == &(*tree).nill)
		return;
	//while(i < depth - 1)
		//str[i++] = ' ';
	//if (depth)
		//str[i++] = '|';
	//str[i++] = '-';
	//str[i++] = ' ';
    //str[i++] = (*node).elder + 'd';
	//str[i++] = ' ';
    int i = depth;
    //*(str + i++) = '_';
	if ((*node).color == RED)
		*(str + i++) = '.';
	__rbPutnbr(str + i, (*node).data.value);
	printf("%s\n", str);
    if (right)
        str[depth - 1] = ' ';
    str[depth] = '|';
	__rbRecPrint(str, tree, (*node).children[0], depth + 1, false);
	__rbRecPrint(str, tree, (*node).children[1], depth + 1, true);
}

void __rbPrint(__rbTree* tree){
	static char str[3000];
    str[0] = '\0';
	__rbRecPrint(str, tree, (*tree).root, 0, false);
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
