/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:44:32 by athierry          #+#    #+#             */
/*   Updated: 2025/07/04 21:27:56 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bTree.h"
#include <stdlib.h>

void gdb(void){
	return;
}

int main(void){
	__bTree	tree;
	for (int i = 0; i < 10; i++){
		__bInsert(&tree, i);
		//__rbPrint(&tree);
	}
	for (int i = 20; i > 9; i--){
		__rbInsert(&tree, i);
	}
	for (int i = 0; i < 10; i++){
		__bDelete(&tree, i);
	}
	for (int i = 20; i > 9; i--){
		__bDelete(&tree, i);
	}
}
