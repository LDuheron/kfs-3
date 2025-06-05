/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackPrinter.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:03:46 by athierry          #+#    #+#             */
/*   Updated: 2025/04/29 20:46:05 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKPRINTER_H
#define STACKPRINTER_H
#include "stdint.h"
#define UPPER_BITS(c) (((char) (c) & 0xf0) >> 4)
#define LOWER_BITS(c) ((char) (c) & 0x0f)
#define VGA_WIDTH 80
#define VGA_LENGTH 20
#define VGA_BUFFER_SIZE (VGA_WIDTH * VGA_LENGTH)
#define VGAWHITE 0x0f
#define VGARED 0x04
#define VGAGREEN 0x02

#define INT16REPLENGTH 9
#define LINESIZE 16

#define TRANS_VGA(x) ((x) | VGAWHITE << 8)

void writeStackToVga(const void *stack, int size, uint16_t* vgaBuffer);

#endif
