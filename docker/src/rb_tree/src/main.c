/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:44:32 by athierry          #+#    #+#             */
/*   Updated: 2025/07/04 20:15:39 by athierry         ###   ########.fr       */
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
    for (int i = 0; i < 20; i++){
        __rbNode* node = malloc(sizeof(*node));
        (*node).data.value = i;
        (*node).children[0] = &tree.nill;
        (*node).children[1] = &tree.nill;
        __rbInsert(&tree, node);
        __rbPrint(&tree);
    }
    for (int i = 40; i > 19; i--){
        __rbNode* node = malloc(sizeof(*node));
        (*node).data.value = i;
        (*node).children[0] = &tree.nill;
        (*node).children[1] = &tree.nill;
        __rbInsert(&tree, node);
        __rbPrint(&tree);
    }

    __rbPrint(&tree);
    __rbNode* node = malloc(sizeof(*node));
    (*node).data.value = 20;
    (*node).children[0] = &tree.nill;
    (*node).children[1] = &tree.nill;
    __rbPrint(&tree);
    __rbInsert(&tree, node);
    __rbPrint(&tree);
    __rbNode* node2 = __rbFind(&tree, 15);// 7 or 15, or 25
    gdb();
    __rbDelete(&tree, node2);
    free(node2);

    __rbPrint(&tree);
    for (int i = 0; i < 20; i++){
        __rbNode* node = __rbFind(&tree, i);	
        if (i == 4)
            gdb();
        if (node != &tree.nill){
            __rbDelete(&tree, node);
            free(node);
        }
        __rbPrint(&tree);
    }
    for (int i = 40; i > 19; i--){
        __rbNode* node = __rbFind(&tree, i);	
        if (node != &tree.nill){
            __rbDelete(&tree, node);
            free(node);
        }
        __rbPrint(&tree);
    }
    node = __rbFind(&tree, 20);	
    if (node != &tree.nill)
        __rbDelete(&tree, node);
    __rbPrint(&tree);
}
