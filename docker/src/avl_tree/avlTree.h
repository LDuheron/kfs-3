/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avlTree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:42:20 by athierry          #+#    #+#             */
/*   Updated: 2025/06/12 18:35:56 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVLTREE_H__
#define __AVLTREE_H__

typedef struct __avlData{
	int	value;
	void*	data;
}



typedef struct __avlNode{
	__avlNode*	parent;
	__avlNode*	children[2];
	__avlData	data;
	char		balanceFactor;
bool elder;
}



typedef struct __alvTree{
	__avlNode*	root;
}

#endif
