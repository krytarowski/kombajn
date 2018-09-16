/*	$NetBSD$	*/
/*-
 * Copyright (c) 2018 Kamil Rytarowski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <ctype.h>

#include <lua.h>
#include <lauxlib.h>

#define L_IS(type)						\
int								\
l_is##type(lua_State *L) /* [-1, +1, v] */			\
{								\
	int character;						\
								\
	character = luaL_checkinteger(L, 1);			\
								\
	lua_pushboolean(L, is##type((unsigned char)character));	\
								\
	return 1;						\
}

L_IS(alpha)
L_IS(upper)
L_IS(lower)
L_IS(digit)
L_IS(xdigit)
L_IS(alnum)
L_IS(space)
L_IS(punct)
L_IS(print)
L_IS(graph)
L_IS(cntrl)
L_IS(blank)

#define L_TO(type)						\
int								\
l_to##type(lua_State *L) /* [-1, +1, v] */			\
{								\
	int character;						\
								\
	character = luaL_checkinteger(L, 1);			\
								\
	lua_pushinteger(L, to##type((unsigned char)character));	\
								\
	return 1;						\
}

L_TO(upper)
L_TO(lower)

LUALIB_API int
luaopen_ctype(lua_State *L)
{
	luaL_Reg fns[] = {
		{"isalpha",	l_isalpha},
		{"isupper",	l_isupper},
		{"isdigit",	l_isdigit},
		{"isxdigit",	l_isxdigit},
		{"isalnum",	l_isalnum},
		{"isspace",	l_isspace},
		{"ispunct",	l_ispunct},
		{"isprint",	l_isprint},
		{"isgraph",	l_isgraph},
		{"iscntrl",	l_iscntrl},
		{"isblank",	l_isblank},
		{"isupper",	l_isupper},
		{"toupper",	l_toupper},
		{"tolower",	l_tolower},
		{NULL,		NULL}
	};

	luaL_newlib(L, fns);

	return 1;
}
