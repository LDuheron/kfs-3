/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:13:00 by athierry          #+#    #+#             */
/*   Updated: 2025/05/26 18:38:03 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbTree.h"



static __rbNode* __rbInsertBalanceRed(__rbTree* tree, __rbNode* node, __rbNode* uncle){
	(*(*node).parent).color = BLACK;
	(*uncle).color = BLACK;
	(*(*uncle).parent).color = RED;
	return ((*uncle).parent);
}



static __rbNode* __rbInsertBalanceBlack(__rbTree* tree, __rbNode* node, __rbNode* uncle){
	if ((*node).elder == (*(*node).parent).elder){
		node = (*node).parent;
		__rbRotate(tree, node, (*node).elder);
	}
	(*(*node).parent).color = BLACK;
	(*(*(node).parent).parent).color = RED;
	__rbRotate(tree, (*(*node).parent).parent, );
	return (node);
}



static void __rbInsertBalance(__rbTree* tree, __rbNode* node){
	__rbInsertBalanceFunc func[2] = [&__rbInsertBalanceBlack, &__rbInsertBalanceRed];

	while((*node).color == RED){
		__rbNode* uncle = (*(*(*node).parent).parent).children[!(*(*node).parent).elder];
		node = (*func[(*uncle).color])(tree, node, uncle);
	}
}



void __rbInsert(__rbTree* tree, __rbNode* node){
	__rbNode* actual = &(*tree).nill;
	__rbNode* potential = (*tree).root;

	while (potential != &(*tree).nill){
		actual = potential;
		potential = (*potential).children[(*node).data.value < (*potential).data.value];
	}

	(*node).parent = actual;
	(*node).children[0] = &(*tree).nill;
	(*node).children[1] = &(*tree).nill;
	(*node).color = RED;

	if (actual == &(*tree).nill){
		(*tree).root = node;
		(*tree).nill.children[0] = node;
		(*node).color = BLACK;
	}
	else{
		(*actual).children[(*node).data.value < (*actual).data.value] = node;
		__rbInsertBalance(tree, node);
	}
}
