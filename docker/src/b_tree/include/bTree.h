/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bTree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:13:01 by athierry          #+#    #+#             */
/*   Updated: 2025/07/10 17:32:18 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BTREE_H
#define __BTREE_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define BVALUE 4

typedef struct __bData{
	int	value;
	void*	data;
}__bData;

typedef struct __bNode{
	__bData		dividors[BVALUE];
	struct __bNode*	children[BVALUE + 1];
 	struct __bNode*	parent;
	int		rank; // index in parent's children array
	int		count; // size of array
	bool		root;
	bool		empty;
	bool		full;
}__bNode;

typedef struct __bTree{
	struct __bNode*	root;
}__bTree;

typedef struct __bRes{
    struct __bNode*    node;
    int         rank;
    //int         value;
}__bRes;


typedef __bRes	(*__bRotateFunc)(__bRes);
typedef void	(*__bDeleteFunc)(__bTree*, __bRes);

int __bFindNonEmptySibling(__bNode* node);
__bRes __bRotateNode(__bRes place, int sibling);
__bRes __bRotateLeaf(__bRes place, int sibling);
__bRes __bClosest(__bRes place);
int __bDichoFind(int value, __bData* dividors, int max);
void __bPrint(__bTree* tree);

void __bInsert(__bTree* tree, int value);
void __bDelete(__bTree* tree, int value);
#endif

