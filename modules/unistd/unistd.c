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


#include <lua.h>
#include <lauxlib.h>

#include <unistd.h>

int
l_sleep(lua_State *L) /* [-1, +1, v] */
{
	int seconds;

	/* stack: integer:seconds */
	seconds = luaL_checkinteger(L, 1);
	/* stack: integer:seconds */

	/*
	 * A non-zero return value indicates signal
	 * interruption and the number unslept seconds.
	 */
	seconds = sleep(seconds);

	lua_pushinteger(L, seconds);
	/* stack: integer:seconds integer:seconds */

	return 1;
}

LUALIB_API int
luaopen_unistd(lua_State *L)
{
	luaL_Reg fns[] = {
		{"sleep",	l_sleep},
		{NULL,		NULL}
	};

	luaL_newlib(L, fns);

	return 1;
}
