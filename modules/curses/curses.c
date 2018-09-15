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

#include <curses.h>

struct lud_WINDOW {
	WINDOW *win;
	const char *name;
};

int
l_initscr(lua_State *L) /* [-0, +0, v] */
{
	WINDOW *w;

	w = initscr();

	if (w == NULL)
		luaL_error(L, "initscr()");

	return 0;
}

int
l_endwin(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = endwin();

	if (rv != OK)
		luaL_error(L, "endwin()");

	return 0;
}

int
l_cbreak(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = cbreak();

	if (rv != OK)
		luaL_error(L, "cbreak()");

	return 0;
}

int
l_nocbreak(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = nocbreak();

	if (rv != OK)
		luaL_error(L, "nocbreak()");

	return 0;
}

int
l_raw(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = raw();

	if (rv != OK)
		luaL_error(L, "raw()");

	return 0;
}

int
l_noraw(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = noraw();

	if (rv != OK)
		luaL_error(L, "noraw()");

	return 0;
}

int
l_start_color(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = start_color();

	if (rv != OK)
		luaL_error(L, "start_color()");

	return 0;
}

int
lud_WINDOW_new(lua_State *L) /* [-0, +0, -] */
{

	return 0;
}

int
lud_WINDOW___tostring(lua_State *L) /* [-0, +0, -] */
{

	return 0;
}

int
lud_WINDOW___gc(lua_State *L) /* [-0, +0, -] */
{

	return 0;
}

LUALIB_API int
luaopen_curses(lua_State *L)
{
	static luaL_Reg fns[] = {
		{"initscr",	l_initscr},
		{"endwin",	l_endwin},
		{"cbreak",	l_cbreak},
		{"nocbreak",	l_nocbreak},
		{"raw",		l_raw},
		{"noraw",	l_noraw},
		{"start_color",	l_start_color},
		{NULL,		NULL}
	};

	static luaL_Reg lud_WINDOW_fns[] = {
		{"new",		lud_WINDOW_new},
		{"__tostring",	lud_WINDOW___tostring},
		{"__gc",	lud_WINDOW___gc},
		{NULL,		NULL}
	};

	/* stack: */
	luaL_newmetatable(L, "curses:window");
	/* stack: metatable:'curses:window' */
	luaL_setfuncs(L, lud_WINDOW_fns, 0);
	/* stack: metatable:'curses:window' */

	luaL_newlib(L, fns);
	/* stack: metatable:'curses:window' libtable:fns */

	return 1;
}
