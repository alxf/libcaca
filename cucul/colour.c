/*
 *  libcucul      Canvas for ultrafast compositing of Unicode letters
 *  Copyright (c) 2002-2006 Sam Hocevar <sam@zoy.org>
 *                All Rights Reserved
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the Do What The Fuck You Want To
 *  Public License, Version 2, as published by Sam Hocevar. See
 *  http://sam.zoy.org/wtfpl/COPYING for more details.
 */

/** \file colour.c
 *  \version \$Id$
 *  \author Sam Hocevar <sam@zoy.org>
 *  \brief Colour handling
 *
 *  This file contains functions for converting colour values between
 *  various colourspaces.
 */

#include "config.h"

#include "cucul.h"
#include "cucul_internals.h"

static const uint16_t ansitab[16] =
{
    0xf000, 0xf008, 0xf080, 0xf088, 0xf800, 0xf808, 0xf880, 0xf888,
    0xf444, 0xf44f, 0xf4f4, 0xf4ff, 0xff44, 0xff4f, 0xfff4, 0xffff,
};

/* FIXME: could this be inlined? */

uint8_t _cucul_argb32_to_ansi8(uint32_t c)
{
    /* FIXME: we need nearest colour handling for non-ANSI */
    return (c & 0x0000000f) | ((c & 0x000f0000) >> 12);
}

uint8_t _cucul_argb32_to_ansi4fg(uint32_t c)
{
    /* FIXME: we need nearest colour handling for non-ANSI */
    return c & 0x0000000f;
}

uint8_t _cucul_argb32_to_ansi4bg(uint32_t c)
{
    /* FIXME: we need nearest colour handling for non-ANSI */
    return (c & 0x000f0000) >> 16;
}

void _cucul_argb32_to_argb4(uint32_t c, uint8_t argb[8])
{
    uint16_t fg = c & 0xffff;
    uint16_t bg = c >> 16;

    if(fg < 0x0016)
        fg = ansitab[fg];

    if(bg < 0x0016)
        bg = ansitab[bg];

    argb[0] = bg >> 12;
    argb[1] = (bg >> 8) & 0xf;
    argb[2] = (bg >> 4) & 0xf;
    argb[3] = bg & 0xf;

    argb[4] = fg >> 12;
    argb[5] = (fg >> 8) & 0xf;
    argb[6] = (fg >> 4) & 0xf;
    argb[7] = fg & 0xf;
}
