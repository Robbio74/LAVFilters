/*
 *      Copyright (C) 2011 Hendrik Leppkes
 *      http://www.1f0.de
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 */

#pragma once

// Load the dithering coefficients for this line
// reg   - register to load coefficients into
// line  - index of line to process (0 based)
// bits  - number of bits to dither (for 10 -> 8, set to 2)
#define PIXCONV_LOAD_DITHER_COEFFS(reg,line,bits,name)  \
  const uint16_t *name = dither_8x8_256[(line) % 8];    \
  reg = _mm_load_si128((const __m128i *)name);          \
  reg = _mm_srli_epi16(reg, 8-bits); /* shift to the required dithering strength */

// Load 8 16-bit pixels into a register, and dither them to 8 bit
// The 8-bit pixels will be in the low-bytes of the 8 16-bit parts
// reg   - register to store pixels in
// dreg  - register with dithering coefficients
// src   - memory pointer of the source
// shift - shift offset to 8-bit (ie. 2 for 10bit)
#define PIXCONV_LOAD_PIXEL16_DITHER(reg,dreg,src,shift)               \
  reg = _mm_load_si128((const __m128i *)(src)); /* load (aligned) */  \
  reg = _mm_adds_epu16(reg, dreg);              /* dither */          \
  reg = _mm_srli_epi16(reg, shift);             /* shift to 8-bit */

// Load 8 16-bit pixels into a register, and dither them to 8 bit
// The 8-bit pixels will be in the 8 low-bytes in the register
// reg   - register to store pixels in
// dreg  - register with dithering coefficients
// src   - memory pointer of the source
// shift - shift offset to 16-bit (ie. 6 for 10bit)
#define PIXCONV_LOAD_PIXEL16_DITHER_PACKED(reg,dreg,zero,src,shift)   \
  PIXCONV_LOAD_PIXEL16_DITHER(reg,dreg,src,shift) /* load unpacked */ \
  reg = _mm_packus_epi16(reg, zero);              /* pack */

// Load 16 8-bit pixels into a register
// reg   - register to store pixels in
// src   - memory pointer of the source
#define PIXCONV_LOAD_PIXEL8(reg,src) \
  reg = _mm_loadu_si128((const __m128i *)(src));     /* load (unaligned) */

// Load 16 8-bit pixels into a register, using aligned memory access
// reg   - register to store pixels in
// src   - memory pointer of the source
#define PIXCONV_LOAD_PIXEL8_ALIGNED(reg,src) \
  reg = _mm_load_si128((const __m128i *)(src));      /* load (aligned) */

// Load 8 16-bit pixels into a register, using aligned memory access
// reg   - register to store pixels in
// src   - memory pointer of the source
#define PIXCONV_LOAD_PIXEL16(reg,src,shift)                             \
  reg = _mm_load_si128((const __m128i *)(src));  /* load (aligned) */     \
  reg = _mm_slli_epi16(reg, shift);            /* shift to 16-bit */
