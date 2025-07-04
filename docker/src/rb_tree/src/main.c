/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:44:32 by athierry          #+#    #+#             */
/*   Updated: 2025/07/03 18:28:34 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include <stdlib.h>

void gdb(void){
	return;
}

int main(void){
	__rbTree	tree;
	__rbInit(&tree);
	for (int i = 0; i < 10; i++){
		__rbNode* node = malloc(sizeof(*node));
        if (i == 4)
            gdb();
		(*node).data.value = i;
		(*node).children[0] = &tree.nill;
		(*node).children[1] = &tree.nill;
		__rbInsert(&tree, node);
		__rbPrint(&tree);
	}
	//for (int i = 20; i > 9; i--){
		//__rbNode* node = malloc(sizeof(*node));
		//(*node).data.value = i;
		//(*node).children[0] = &tree.nill;
		//(*node).children[1] = &tree.nill;
		//__rbInsert(&tree, node);
		//__rbPrint(&tree);
	//}
	for (int i = 0; i < 10; i++){
		__rbNode* node = __rbFind(&tree, i);	
		__rbDelete(&tree, node);
		__rbPrint(&tree);
	}
	//for (int i = 20; i > 9; i--){
		//__rbNode* node = __rbFind(&tree, i);	
		//__rbDelete(&tree, node);
		//__rbPrint(&tree);
	//}
}
