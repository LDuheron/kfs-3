/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:03:18 by athierry          #+#    #+#             */
/*   Updated: 2025/07/03 22:22:50 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"



static __rbNode* __rbNephewGoodRed(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
	(*sibling).color = (*(*conflict).parent).color;
	(*(*conflict).parent).color = BLACK;
	(*(*sibling).children[!(*conflict).elder]).color = BLACK;
	__rbPrint(tree);
	__rbRotate(tree, (*conflict).parent, !(*conflict).elder);
	__rbPrint(tree);
	return ((*tree).root);
}



static __rbNode* __rbNephewWrongRed(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
    bool elder = (*conflict).elder;
	(*(*sibling).children[elder]).color = BLACK;
	(*sibling).color = RED;
	__rbPrint(tree);
	__rbRotate(tree, sibling, !elder);
	__rbPrint(tree);
	sibling = (*(*conflict).parent).children[!elder];
	return __rbNephewGoodRed(tree, conflict, sibling);
}



static __rbNode* __rbNephewBlack(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
	(void) tree;
	(*sibling).color = RED;
	return ((*conflict).parent);
}



static __rbNode* __rbSiblingBlack(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
	const __rbDeleteFunc func[4] = {&__rbNephewBlack, &__rbNephewWrongRed, &__rbNephewGoodRed, &__rbNephewGoodRed};

	bool elder = (*conflict).elder;
	int index = (*(*sibling).children[elder]).color + 2 *  (*(*sibling).children[!elder]).color  ; // ou l'inverse
	return ((*func[index])(tree, conflict, sibling));
}



static __rbNode* __rbSiblingRed(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
    bool elder = (*conflict).elder;
	(*sibling).color = BLACK;
	(*(*conflict).parent).color = RED;
	__rbRotate(tree, (*conflict).parent, !elder);
	__rbPrint(tree);
	sibling = (*(*conflict).parent).children[!elder];
	return (__rbSiblingBlack(tree, conflict, sibling));
}



static void __rbDeleteBalance(__rbTree* tree, __rbNode* conflict){
	const __rbDeleteFunc func[2] = {&__rbSiblingBlack, &__rbSiblingRed};

	while (conflict != (*tree).root && (*conflict).color == BLACK){
		__rbPrint(tree);
		__rbNode* sibling = (*(*conflict).parent).children[!(*conflict).elder];
		conflict = (*func[(*sibling).color])(tree, conflict, sibling);
	}
	(*conflict).color = BLACK;
}

static __rbNode* __rbMin(__rbNode* node){
	while ((*node).children[0])
		node = (*node).children[0];
	return node;
}

void __rbDelete(__rbTree* tree, __rbNode* node){
	__rbNode* conflict;
	__rbNode* reMoved = node;
	__rbColor reMovedColor = (*node).color;
	if ((*node).children[0] == &(*tree).nill){
		conflict = (*node).children[1];
		__rbTransplant(tree, node, conflict);
	}
	else if ((*node).children[1] == &(*tree).nill){
		conflict = (*node).children[0];
		__rbTransplant(tree, node, conflict);
	}
	else{
		reMoved = __rbMin((*node).children[1]);
		reMovedColor = (*reMoved).color;
		conflict = (*reMoved).children[0];
		if ((*reMoved).parent == node)
			(*conflict).parent = reMoved;
		else{
			__rbTransplant(tree, reMoved, (*reMoved).children[1]);
			(*reMoved).children[1] = (*node).children[1];
			(*(*reMoved).children[1]).parent = reMoved;
		}
		__rbTransplant(tree, node, reMoved);
		(*reMoved).children[0] = (*node).parent;
		(*(*reMoved).children[0]).parent = reMoved;
		(*reMoved).color = (*node).color;
	}
	if (reMovedColor == BLACK)
		__rbDeleteBalance(tree, conflict);
}
