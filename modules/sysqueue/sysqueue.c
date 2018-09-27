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


#include <sys/types.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>

struct entry {
	TAILQ_ENTRY(entry) entries;
	int type; /* Lua type */
	union {
		void *udata;
		int boolean;
		LUA_NUMBER number;
		LUA_INTEGER integer;
		struct {
			char *string;
			size_t size;
		};
	};
};

TAILQ_HEAD(tailhead, entry);

struct lud_TAILQ {
	struct tailhead *headp;
	const char *name;
};

int
l_TAILQ_INIT(lua_State *L) /* [-0, +1, v] */
{
	struct lud_TAILQ *ut;
	const char *name;

	name = luaL_checkstring(L, 1);
	if (name == NULL)
		luaL_error(L, "name cannot be unset");

	ut = (struct lud_TAILQ *)lua_newuserdata(L, sizeof(*ut));

	memset(ut, 0, sizeof(*ut));

	luaL_getmetatable(L, "sysqueue:tailq");
	lua_setmetatable(L, -2);

	ut->headp = malloc(sizeof(*ut->headp));
	if (ut->headp == NULL)
		luaL_error(L, "malloc()");
	ut->name = strdup(name);
	if (ut->name == NULL) {
		free(ut->headp);
		luaL_error(L, "strdup()");
	}

	TAILQ_INIT(ut->headp);

	return 1;
}

int
lud_TAILQ___tostring(lua_State *L) /* [-1, +1, v] */
{
	struct lud_TAILQ *ut;
	const char *name;

	ut = (struct lud_TAILQ *)luaL_checkudata(L, 1, "sysqueue:tailq");
	lua_pushstring(L, ut->name);

	return 1;
}

int
lud_TAILQ___gc(lua_State *L) /* [-1, +0, v] */
{
	int rv;
	struct lud_TAILQ *ut;

	ut = (struct lud_TAILQ *)luaL_checkudata(L, 1, "sysqueue:tailq");

	if (ut->headp) {
		while (TAILQ_FIRST(ut->headp) != NULL) {
			switch (TAILQ_FIRST(ut->headp)->type) {
			case LUA_TNIL:
			case LUA_TBOOLEAN:
			case LUA_TLIGHTUSERDATA:
			case LUA_TNUMBER:
				/* No additional buffers */
				break;
			case LUA_TSTRING:
				if (TAILQ_FIRST(ut->headp)->string) {
					free(TAILQ_FIRST(ut->headp)->string);
					TAILQ_FIRST(ut->headp)->string = NULL;
				}
				break;
			default:
				luaL_error(L, "unexpected Lua type %d",
				           TAILQ_FIRST(ut->headp));
			}
			TAILQ_REMOVE(ut->headp, TAILQ_FIRST(ut->headp), entries);
		}
		ut->headp = NULL;
	}
	if (ut->name)
		free((void *)ut->name);
	ut->name = NULL;

	return 0;
}

LUALIB_API int
luaopen_sysqueue(lua_State *L)
{
	static luaL_Reg fns[] = {
		{"TAILQ_INIT",	l_TAILQ_INIT},
		{NULL,		NULL}
	};

	static luaL_Reg lud_TAILQ_fns[] = {
		{"__tostring",	lud_TAILQ___tostring},
		{"__gc",	lud_TAILQ___gc},
		{NULL,		NULL}
	};

	luaL_newmetatable(L, "sysqueue:tailq");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, lud_TAILQ_fns, 0);

	luaL_newlib(L, fns);

	return 1;
}
