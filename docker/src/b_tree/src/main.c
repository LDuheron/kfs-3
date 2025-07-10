/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:44:32 by athierry          #+#    #+#             */
/*   Updated: 2025/07/10 17:40:10 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bTree.h"

void gdb(void){
	return;
}

int main(void){
	__bTree	tree;
	tree.root = malloc(sizeof(*tree.root));
	(*tree.root).children[0] = NULL;
	(*tree.root).parent = NULL;
	(*tree.root).count = 0;
	(*tree.root).root = true;
	(*tree.root).empty = true;
	(*tree.root).full = false;
	for (int i = 0; i < 10; i++){
		__bInsert(&tree, i);
		__bPrint(&tree);
	}
	for (int i = 20; i > 9; i--){
		__bInsert(&tree, i);
		__bPrint(&tree);
	}
	for (int i = 0; i < 10; i++){
		__bDelete(&tree, i);
		__bPrint(&tree);
	}
	for (int i = 20; i > 9; i--){
		__bDelete(&tree, i);
		__bPrint(&tree);
	}
}
