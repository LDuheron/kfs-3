/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:51:24 by athierry          #+#    #+#             */
/*   Updated: 2025/04/24 18:13:47 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GDT_H
#   define GDT_H

#include "stdint.h"

#define ERROR 1
#define SUCCESS 0
#define FLAG 0xCF
#define LIMIT 0xFFFFFFFF

#define LOWER_16_BITS(x) ((x) & 0xFFFF)
#define BITS_16_TO_20(x) (((x) >> 16) & 0x0F)
#define BITS_16_TO_24(x) (((x) >> 16) & 0xFF)
#define BITS_24_TO_32(x) (((x) >> 24) & 0xFF)
#define ISOLATE_BITS_4_TO_8(x) ((x) & 0xF0)

#define KERNEL_MODE 0x90
#define USER_MODE 0xF0
#define CODE_MODE 0x0A
#define DATA_MODE 0x02

struct  gdt_segment_descriptor_struct {
    uint16_t   limit;
    uint16_t   baseLow;
    uint8_t    baseMid;
    uint8_t    accessByte;
    uint8_t    flags;
    uint8_t    baseHigh;
}__attribute__((packed));

struct  gdt_ptr_struct {
    uint16_t	limit;
    uint32_t	base;
}__attribute__((packed));

void initGdt();

extern void writeGdtToRegisters(struct gdt_ptr_struct*);
#endif
