/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:18:46 by athierry          #+#    #+#             */
/*   Updated: 2025/07/01 17:02:01 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RBTREE_H
#define _RBTREE_H

#include <stdbool.h>
#include <limits.h>
#include <sys/types.h>

typedef struct __rbData{
    int value;
} __rbData;

typedef enum __rbColor{
    RED = 0,
    BLACK = 1
}__rbColor;

typedef struct __rbNode{
    struct __rbNode* parent;
    struct __rbNode* children[2];
    __rbData  data;
    __rbColor color;
    bool    elder; //true if right child of parent
}__rbNode;

typedef struct __rbTree{
    __rbNode  nill; // by (our) convention, root is (*nill).children[0]: I don't think we need to store the root separately. If so, we might skip the tree structure all together, just need to initiate a nill node (and in any case, having the nill as first address in the structure allow for (ptr == tree) instead of (ptr == &(*tree).nill), saving some dereferencing
    __rbNode* root;
}__rbTree;

typedef void (*__rbTransplantFunc)(__rbTree* tree, __rbNode* toNode, __rbNode* fromNode);
typedef __rbNode *(*__rbInsertBalanceFunc)(__rbTree*, __rbNode*, __rbNode*);
typedef __rbNode* (*__rbDeleteFunc)(__rbTree* tree, __rbNode* conflict, __rbNode* sibling);



__rbNode* __rbFind(__rbTree* tree, ssize_t size);
void __rbInsert(__rbTree* tree, __rbNode* node);
void __rbDelete(__rbTree* tree, __rbNode* node);
void __rbInit(__rbTree* tree);
void __rbRotate(__rbTree* tree, __rbNode* node, bool greater);
void __rbTransplant(__rbTree* tree, __rbNode* toNode, __rbNode* fromNode);
__rbNode* __rbBestFit(__rbTree* tree, int value);
void __rbPrint(__rbTree* tree);

#endif
