/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:13:00 by athierry          #+#    #+#             */
/*   Updated: 2025/07/04 18:42:55 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"



static __rbNode* __rbInsertBalanceRed(__rbTree* tree, __rbNode* node, __rbNode* uncle){
	__rbNode *parent = (*node).parent;
	(*parent).color = BLACK;
	(*uncle).color = BLACK;
	(*(*parent).parent).color = RED;
	(*tree).nill.color = BLACK;
	return ((*parent).parent);
}



static __rbNode* __rbInsertBalanceBlack(__rbTree* tree, __rbNode* node, __rbNode* uncle){
	(void)uncle;
	__rbNode *parent = (*node).parent;
	if ((*node).elder != (*parent).elder){
		__rbRotate(tree, parent, (*node).elder);
		node = parent;
		parent = (*node).parent;
	}
	(*parent).color = BLACK;
	(*(*parent).parent).color = RED;
	__rbNode* cpnode = (*parent).parent;
	__rbRotate(tree, (*parent).parent, (*parent).elder);
	(*tree).nill.color = BLACK;
	return (cpnode);
}



static void __rbInsertBalance(__rbTree* tree, __rbNode* node){
	const __rbInsertBalanceFunc func[2] = {&__rbInsertBalanceBlack, &__rbInsertBalanceRed};
	__rbNode* parent = (*node).parent;
	while((*parent).color == RED){
		__rbNode* uncle = (*(*parent).parent).children[!(*parent).elder];
		node = (*func[(*uncle).color])(tree, node, uncle);
		parent = (*node).parent;
	}
}



void __rbInsert(__rbTree* tree, __rbNode* node){
	__rbNode* actual = &(*tree).nill;
	__rbNode* potential = (*tree).root;

	while (potential != &(*tree).nill){
		actual = potential;
		potential = (*potential).children[(*node).data.value > (*potential).data.value];
	}

	(*node).parent = actual;
	(*node).children[0] = &(*tree).nill;
	(*node).children[1] = &(*tree).nill;
	(*node).color = RED;

	if (actual == &(*tree).nill){
		(*tree).root = node;
		(*tree).nill.children[0] = node;
		(*node).color = BLACK;
		(*node).elder = false;
	}
	else{
		(*actual).children[(*node).data.value > (*actual).data.value] = node;
		(*node).elder = (*node).data.value > (*actual).data.value;
		__rbInsertBalance(tree, node);
	}
	(*(*tree).root).color = BLACK;
}
