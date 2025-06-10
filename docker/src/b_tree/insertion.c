/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:24 by athierry          #+#    #+#             */
/*   Updated: 2025/05/30 22:37:38 by athierry         ###   ########.fr       */
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



void __bNewRootIfRoot(__bTree* tree, __bNode* node){
    if ((*node).parent)
        return;
    __bNode* root = malloc(sizeof(__bNode));
    (*root).parent = null;
    (*root).rank = (*root).count = 0;
    (*root).children[0] = node;
    (*root).full = false;
    (*root).empty = true;
    (*tree).root = (*node).parent = root;
}



// b has to be even !!! 
__bNode* __bSplit(__bTree* tree, __bNode* node, __bData* data, __bNode* greaterValues){
    __bData		dividors[BVALUE + 1];
    __bNode*	children[BVALUE + 2];
    int index = __bDichoFind((*data).value, (*node).dividors, BVALUE + 1);
    int i= 0;
    children[0] = (*node).children[0];
    while (i < index){
        dividors[i] = (*node).dividors[i];
        i++;
        children[i] = (*node).children[i];
    }
    dividors[i++] = data;
    children[i] = greater values;	
    while (i < BVALUE + 1){
        dividors[i] = (*node).dividors[i - 1];
        i++;
        children[i] = (*node).children[i - 1];
    }
    for (int i = 0; i < BVALUE / 2; i++){
        (*node).dividors[i] = dividors[i];
        (*node).children[i] = children[i];
        (*NewNode).children[i].rank = (*node).children[i].rank = i;
        (*newNode).dividors[i] = dividors[i + BVALUE / 2 + 1];
        (*newNode). children [i] = children [i + BVALUE / 2 + 1];
    }
    (*node).children[BVALUE / 2] = children[BVALUE / 2];
    (*newNode).children[BVALUE / 2] = children[BVALUE + 1];
    (*NewNode).children[BVALUE / 2].rank = (*node).children[BVALUE / 2].rank = BVALUE / 2;
    (*newNode).count = (*node).count = BVALUE / 2;
    (*newNode).full = (*node).full = false;
    (*newNode).empty = (*node).empty = true;
    (*newNode).divisors[BVALUE] = divisors[BVALUE / 2]; // Implementation specific
    return (newNode);
}



void __bInsert(__bTree* tree, __bData* data){
    __bNode* node = (*tree).root;
    while ((*node).children[0]){
        int index = __bDichoFind((*data).value, (*node).dividors, (*node).count);
        node = (*node).children[index];
    }
    __bNode* greaterValues = NULL;
    while ((*node).full){
        greaterValues = __bSplit(tree, node, data, greaterValues);
        data = (*greaterValues).divisors[BVALUE]; // Implementation specific
        __bNewRootIfRoot(tree, node);
        node = (*node).parent;
    }
    int index = __bDichoFind((*data).value, (*node).dividors, (*node).count);
    for (int i = (*node).count; i > index; i--){
        (*node).dividors[i] = (*node).dividors[i - 1];
        (*node).children[i + 1] = (*node).dividors[i];
        (*(*node).children[i + 1]).rank += 1;
    }
    (*node).dividors[index++] = data;
    (*greaterValues).rank = index;
    (*node).children[index] = greaterValues;
    (*node).count += 1;
    (*node).full = (*node).count == BVALUE;
}
