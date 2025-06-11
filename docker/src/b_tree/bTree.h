/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bTree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:13:01 by athierry          #+#    #+#             */
/*   Updated: 2025/06/11 18:54:02 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BTREE_H
#define __BTREE_H

#define BVALUE 14

typedef struct __bData{
	int	value;
	void*	data;
}

typedef struct __bNode{
	__bData		dividors[BVALUE];
	__bNode*	children[BVALUE + 1];
 	__bNode*	parent;
	int		rank; // index in parent's children array
	int		count; // size of array
	bool		root;
	bool		empty;
	bool		full;
}

typedef struct __bTree{
	__bNode*	root;
}

typedef struct __bRes{
    __bNode*    node;
    int         rank;
    //int         value;
}


typedef void	(*__bRotateFunc)(__bRes, int);

#endif

