/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:03:18 by athierry          #+#    #+#             */
/*   Updated: 2025/06/30 17:43:06 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"



static __rbNode* __rbNephewGoodRed(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
    (*sibling).color = (*(*conflict).parent).color;
    (*(*conflict).parent).color = BLACK;
    (*(*sibling).children[!(*conflict).elder]).color = BLACK;
    __rbRotate(tree, (*conflict).parent, (*conflict).elder);
    return ((*tree).root);
}



static __rbNode* __rbNephewWrongRed(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
    (*(*sibling).children[!(*conflict).elder]).color = RED;
    (*sibling).color = BLACK;
    __rbRotate(tree, sibling, !(*conflict).elder);
    sibling = (*(*conflict).parent).children[!(*conflict).elder];
    return __rbNephewGoodRed(tree, conflict, sibling);
}



static __rbNode* __rbNephewBlack(__rbTree* tree, __rbNode* conflict, __rbNode* sibling){
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
    (*sibling).color = BLACK;
    (*(*conflict).parent).color = RED;
    __rbRotate(tree, (*conflict).parent, !(*conflict).elder);
    sibling = (*(*conflict).parent).children[!(*conflict).elder];
    return (__rbSiblingBlack(tree, conflict, sibling));
}



static void __rbDeleteBalance(__rbTree* tree, __rbNode* conflict){
    const __rbDeleteFunc func[2] = {&__rbSiblingRed, &__rbSiblingBlack};

    while (conflict != (*tree).root && (*conflict).color == BLACK){
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
