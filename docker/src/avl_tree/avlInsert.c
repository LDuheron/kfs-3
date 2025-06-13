/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avlInsert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:58:59 by athierry          #+#    #+#             */
/*   Updated: 2025/06/12 20:27:20 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__avlTree.h"

void __avlBalance(__avlTree* tree, __avlNode* node, ){
const char values[2] = {-1; 1};
__avNode* parent;
bool elder;
do{
parent = (*node).parent;
elder = (*node).elder
char newParentBf = (*parent).balanceFactor + values[elder];
bool unbalanced = (newParentBf == 2) || (newParentBf == -2);
if (unbalanced)
node = (*func[elder][newParentBf == -2])(node);
else{
node = parent;
(*node).balanceFactor= newParentBf;
}
}while(parent)
}



void __avlInsert(__avlTree* tree, __avlData data){
	__avlNode* current = (*tree).root;
	__avlNode*	newNode = __avlNewNode(data);
	if (!current){
		(*tree).root = newNode;
		(*newNode).depth = 0;
		return;
	}
	__avlNode* potential = current;
	while (potential){
		current = potential;
		potential = (*current).children[data.value <= (*current).data.value];
	}
	(*current).children[data.value <= (*current).data.value] = newNode;
	(*newNode).depth = (*current).depth + 1;
	(*newNode).parent = current;
	__avlBalance(tree, current);
}
