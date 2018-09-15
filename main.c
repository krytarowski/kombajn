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
#include <lualib.h>
#include <lauxlib.h>

#include <err.h>
#include <stdlib.h>

#ifndef KOMBAJNDIR
#define KOMBAJNDIR "./"
#endif

#define _PATH_KOMBAJN	KOMBAJNDIR "kombajn.lua"

int
main(int argc, char **argv)
{
	lua_State *L;
	int rv;

	L = luaL_newstate();
	if (L == NULL)
		err(EXIT_FAILURE, "luaL_newstate");

	luaL_openlibs(L);

	lua_getglobal(L, "package");
	/* stack: table:package */
	lua_getfield(L, -1, "cpath");
	/* stack: table:package string:cpath */
	lua_pushstring(L, ";" KOMBAJNDIR "modules/?/?.so");
	/* stack: table:package string:cpath string:';./modules/?/?.so' */
	lua_concat(L, 2);
	/* stack: table:package string:cpath */
	lua_setfield(L, -2, "cpath");
	/* stack: table:package */
	lua_pop(L, 1);
	/* stack: */

	if ((rv = luaL_loadfile(L, _PATH_KOMBAJN)) != LUA_OK)
		errx(EXIT_FAILURE, "luaL_loadfile error (%d): %s", rv,
		    lua_tostring(L, -1));

	if ((rv = lua_pcall(L, 0, LUA_MULTRET, 0)) != LUA_OK)
		errx(EXIT_FAILURE, "lua_pcall error (%d): %s", rv,
		    lua_tostring(L, -1));

	lua_close(L);

	return EXIT_SUCCESS;
}
