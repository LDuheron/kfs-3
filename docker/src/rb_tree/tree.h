/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:18:46 by athierry          #+#    #+#             */
/*   Updated: 2025/05/26 18:39:15 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct __rbData{
    int value;
}

typedef enum __rbColor{
    BLACK = 1,
    RED = 0
}

typedef struct __rbNode{
    __rbNode* parent;
    __rbNode* children[2];
    __rbData  data;
    __rbColor color;
    bool    elder;
}

typedef struct __rbTree{
    __rbNode  nill; // by (our) convention, root is (*nill).children[0]: I don't think we need to store the root separately. If so, we might skip the tree structure all together, just need to initiate a nill node (and in any case, having the nill as first address in the structure allow for (ptr == tree) instead of (ptr == &(*tree).nill), saving some dereferencing
    __rbNode* root;
}

typedef void (*__rbTransplantFunc)(__rbTree* tree, __rbNode* toNode, __rbNode* fromNode);
typedef __rbNode *(*__rbInsertBalanceFunc)(__rbTree*, __rbNode*, __rbNode*);
typedef __rbNode* (*__rbDeleteFunc)(__rbTree* tree, __rbNode* conflict, __rbNode* sibling);

void __rbRotate(__rbTree* tree, __rbNode* node, bool greater);
static void __rbTransplant(__rbTree* tree, __rbNode* toNode, __rbNode* fromNode);



void __rbFind(__rbTree* tree, size_t size);
void __rbInsert(__rbTree* tree, __rbNode* node);
void __rbDelete(rbTree* tree, rbNode* node);
