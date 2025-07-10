/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:19:19 by athierry          #+#    #+#             */
/*   Updated: 2025/07/09 19:11:28 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bTree.h"

static void __rbRecPrint(char *str, __bTree* tree, __bNode* node, int depth, bool right){
	//if nill, done
	if (!node)
		return;
	
	//modify string and print left subtree
	if (!right)
		str[2 * depth - 1] = ' ';
	else
		str[2 * depth - 1] = '|';
	str[2 * depth] = ' ';
	str[2 * depth + 1] = '|';
	for (int i = 0; i < (*node).count / 2; i++)
		__rbRecPrint(str, tree, (*node).children[i], depth + 1, false);

	//modify string and print node
        str[2 * depth - 1] = '|';
	str[2 * depth] = '-';
	str[2 * depth + 1] = '\0';
	printf("%s", str);
	for (int i = 0; i < (*node).count; i++){
		printf("%d", (*node).dividors[i].value);
		if (i < (*node).count - 1)
			printf(", ");
	}
	printf("\n");
	

	//modify string and print right subtree
	str[2 * depth] = ' ';
	if (!right)
		str[2 * depth + 1] = '|';
	else
		str[2 * depth - 1] = ' ';
	for (int i = (*node).count / 2; i < (*node).count + 1; i++)
		__rbRecPrint(str, tree, (*node).children[1], depth + 1, true);
}

void __bPrint(__bTree* tree){
	static char str[3000];
	str[0] = ' ';
	str[1] = '\0';
	__rbRecPrint(str + 1, tree, (*tree).root, 0, false);
	printf("\n");
}
