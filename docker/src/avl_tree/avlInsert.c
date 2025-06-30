/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avlInsert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:58:59 by athierry          #+#    #+#             */
/*   Updated: 2025/06/23 21:47:06 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__avlTree.h"

void rotate(__avlTree* tree, __avlNode* node){
	int elder = (*node).elder;
	__avlNode* parent = (*node).parent;
	__avlNode* exchanged = (*node).children[!elder];
	(*node).parent = (*parent).parent;
	(*node).elder = (*parent).elder;
	if ((*node).parent)
		(*(*node).parent).children[(*parent).elder] = node;
	(*parent).children[elder] = exchanged;
	(*parent).elder = !elder;
	(*parent).parent = node;
	
	(*exchanged).parent = parent;
	(*exchanged).elder = elder;

	(*node).children[!elder] = parent;
}



void __avlBalance(__avlTree* tree, __avlNode* node, ){
	const char values[2] = {-1; 1};
	__avNode* parent;
	bool elder;
	do{
		parent = (*node).parent;
		elder = (*node).elder;
		char parentNewBf = (*parent).balanceFactor + values[elder];
		bool unbalanced = (parentNewBf == 2) || (parentNewBf == -2);
		if (unbalanced)
			node = (*func[elder][parentNewBf == -2])(node);
		else{
			node = parent;
			(*node).balanceFactor= parentNewBf;
		}
	}while(parent)
}



void __avlInsert(__avlTree* tree, __avlData data){
    char values[2] = {-1; 1};
	__avlNode* current = (*tree).root;
	__avlNode*	newNode = __avlNewNode(data);
	if (!current){
		(*tree).root = newNode;
		(*newNode).balanceFactor = 0;
		return;
	}
	__avlNode* potential = current;
	while (potential){
		current = potential;
        bool side = data.value <= (*current).data.value;
		potential = (*current).children[side];
	}
	(*current).children[data.value <= (*current).data.value] = newNode;
	(*newNode).balanceFactor = 0;
	(*newNode).parent = current;
	__avlBalance(tree, current);
}
