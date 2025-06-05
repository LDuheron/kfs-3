/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:16:33 by athierry          #+#    #+#             */
/*   Updated: 2025/06/04 20:28:14 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void __bRotateLeafLower(__bRes place){
	__bNode *node = place.node;
	__bNode parent = (*node).parent;
	__bNode *sibling = (*node).parent.children[(*node).rank - 1];
	for (int i = place.rank; i > 0; i--)
		(*node).dividors[i] = (*node).dividors[i - 1];
	(*node).dividors[0] = (*parent).dividors[(*node).rank - 1];
	(*parent).dividors[(*node).rank - 1] = (*sibling).dividors[(*sibling).count - 1];
	place.node = sibling;
	place.rank = (*sibling).count - 1;
	return place;
}

void __bRotateLeafGreater(__bRes place){
	__bNode *node = place.node;
	__bNode parent = (*node).parent;
	__bNode *sibling = (*node).parent.children[(*node).rank + 1];
	for (int i = place.rank; i < (*node).count - 1; i++)
		(*node).dividors[i] = (*node).dividors[i + 1];
	(*node).dividors[(*node).count - 1] = (*parent).dividors[(*node).rank];
	(*parent).dividors[(*node).rank] = (*sibling).dividors[0];
	place.node = sibling;
	place.rank = 0;
	return place;
}

void __bRotateNodeLower(__bRes place){
	__bNode *node = place.node;
	__bNode parent = (*node).parent;
	__bNode *sibling = (*node).parent.children[(*node).rank - 1];
	for (int i = place.rank; i > 0; i--){
		(*node).dividors[i] = (*node).dividors[i - 1];
		(*node).children[i] = (*node).children[i - 1];
		(*(*node).children[i]).rank++;
	}
	(*node).dividors[0] = (*parent).dividors[(*node).rank - 1];
	(*parent).dividors[(*node).rank - 1] = (*sibling).dividors[(*sibling).count - 1];
	place.node = sibling;
	place.rank = (*sibling).count - 1;
	return place;
}


void __bRotateNodeGreater(__bRes place){
	__bNode *node = place.node;
	__bNode parent = (*node).parent;
	__bNode *sibling = (*node).parent.children[(*node).rank + 1];
	for (int i = place.rank; i < (*node).count; i++)
		(*node).dividors[i] = (*node).dividors[i + 1];
	(*node).dividors[(*node).count] = (*parent).dividors[(*node).rank];
	(*parent).dividors[(*node).rank] = (*sibling).dividors[0];
	place.node = sibling;
	place.rank = 0;
	return place;
}

void __bRotateNodeGreater(__bRes place){
	__bNode *node = place.node;
	__bNode parent = (*node).parent;
	__bNode *sibling = (*node).parent.children[(*node).rank + 1];
	for (int i = place.rank; i < (*node).count; i++){
		(*node).dividors[i] = (*node).dividors[i + 1];
		(*node).children[i] = (*node).children[i + 1];
		(*(*node).children[i]).rank--;
	}
	(*node).dividors[(*node).count] = (*parent).dividors[(*node).rank];
	//(*node).children
	(*parent).dividors[(*node).rank] = (*sibling).dividors[0];
	place.node = sibling;
	place.rank = 0;
	return place;
}

__bRotateLeaf(__bRes place, int sibling){
	const __bRotateFunc func[2] = {&__bRotateLeafLower, &__bRotateLeafGreater};
	__bRotateFunc	rotation = func[sibling > 0];
	sibling -= 2 * sibling * (sibling < 0);
	while (sibling--)
		place = (*rotation)(place);
}

__bRotate(__bRes place, int sibling){
	__bRotateFunc func[2] = {&__bRotateLower, &__bRotateRight};
	__bRotateFunc rotate = func[sibling > 0];
	if (sibling < 0)
		sibling *= -1;
	while (sibling--)
		place = (*rotate)(place);
}

