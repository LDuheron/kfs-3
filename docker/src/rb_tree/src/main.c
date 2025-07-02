/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:44:32 by athierry          #+#    #+#             */
/*   Updated: 2025/07/01 20:23:23 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <stdlib.h>

int main(void){
	__rbTree	tree;
	__rbInit(&tree);
	for (int i = 0; i < 10; i++){
		__rbNode* node = malloc(sizeof(*node));
		(*node).data.value = i;
		(*node).children[0] = &tree.nill;
		(*node).children[1] = &tree.nill;
		__rbInsert(&tree, node);
		__rbPrint(&tree);
	}
	for (int i = 20; i > 8; i--){
		__rbNode* node = malloc(sizeof(*node));
		(*node).data.value = i;
		(*node).children[0] = &tree.nill;
		(*node).children[1] = &tree.nill;
		__rbInsert(&tree, node);
		__rbPrint(&tree);
	}
}
