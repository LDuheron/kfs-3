/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:24 by athierry          #+#    #+#             */
/*   Updated: 2025/07/10 18:13:43 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bTree.h"



//Return the greatest index for which dividors[index] <= value, 0 if none;
int __bDichoFind(int value, __bData* dividors, int max){
	int min = 0;
	while (min != max){
		// int diff = max - min; ???
		int mid = (max - min) / 2;
		bool gt = (value > dividors[min + mid].value);
		min += gt * (mid + 1);
		mid += (max - min) % 2;
		max -= !gt * mid;
	}
	return min;
}



// b has to be even !!! 
__bNode* __bSplit(__bTree* tree, __bNode* node, __bData* data, __bNode* greaterValues){
	__bData		dividors[BVALUE + 1];
	__bNode*	children[BVALUE + 2];
	int index = __bDichoFind((*data).value, (*node).dividors, BVALUE);
	int i= 0;
	children[0] = (*node).children[0];
	while (i < index){
		dividors[i] = (*node).dividors[i];
		i++;
		children[i] = (*node).children[i];
	}
	dividors[i++] = *data;
	children[i] = greaterValues;	
	while (i < BVALUE + 1){
		dividors[i] = (*node).dividors[i - 1];
		i++;
		children[i] = (*node).children[i - 1];
	}
	__bNode* newNode = malloc(sizeof(*newNode));
	for (int i = 0; i < BVALUE / 2; i++){
		(*node).dividors[i] = dividors[i];
		(*node).children[i] = children[i];
		if ((*node).children[i])
			(*(*node).children[i]).rank = i;
		(*newNode).dividors[i] = dividors[i + BVALUE / 2 + 1];
		(*newNode). children[i] = children[i + BVALUE / 2 + 1];
		if ((*newNode).children[i])
			(*(*newNode).children[i]).rank = i;
	}

	(*node).children[BVALUE / 2] = children[BVALUE / 2];
	(*newNode).children[BVALUE / 2] = children[BVALUE + 1];


	if ((*newNode).children[BVALUE / 2])
		(*(*newNode).children[BVALUE / 2]).rank = BVALUE / 2;
	if ((*node).children[BVALUE / 2])
		(*(*node).children[BVALUE / 2]).rank = BVALUE / 2;
	(*newNode).count = (*node).count = BVALUE / 2;
	(*newNode).full = (*node).full = false;
	(*newNode).empty = (*node).empty = true;
	(*newNode).dividors[BVALUE - 1] = dividors[BVALUE / 2]; // Implementation specific
								//
	//__bNode* root = malloc(sizeof(root));
    //free(root);
	return (newNode);
}



void __bNewRootIfRoot(__bTree* tree, __bNode* node){
	if ((*node).parent)
		return;
	__bNode* root = malloc(sizeof(root));
	if (!root)
		return;
	(*root).parent = NULL;
	(*root).rank = (*root).count = 0;
	(*root).children[0] = node;
	(*root).full = false;
	(*root).empty = true;
	(*root).root = true;
	(*node).parent = root;
	(*tree).root = root;
	return;
}



void __bInsert(__bTree* tree, int value){
	__bNode* node = (*tree).root;
	static __bData data;
	(data).value = value;
	(data).data = NULL;
	int index = -1;
	while ((*node).children[0]){
		index = __bDichoFind(value, (*node).dividors, (*node).count);
		node = (*node).children[index];
	}
	__bNode* greaterValues = NULL;
	do{
        (*node).full = (*node).count == BVALUE;
        if ((*node).full){
            greaterValues = __bSplit(tree, node, &data, greaterValues);
            data = (*greaterValues).dividors[BVALUE - 1]; // Implementation specific
            __bNewRootIfRoot(tree, node);
            node = (*node).parent;
        }
        index = __bDichoFind(data.value, (*node).dividors, (*node).count);
        for (int i = (*node).count; i > index; i--){
            (*node).dividors[i] = (*node).dividors[i - 1];
            (*node).children[i + 1] = (*node).children[i];
            if ((*node).children[i + 1])
                (*(*node).children[i + 1]).rank += 1;
        }
        //(*node).dividors[index++] = *data;
        (*node).dividors[index++].value = data.value;
        if (greaterValues)
            (*greaterValues).rank = index;
        (*node).children[index] = greaterValues;
        (*node).count += 1;
	}while ((*node).full);
}
