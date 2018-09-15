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


#include <string.h>
#include <stdlib.h>

#include <lua.h>
#include <lauxlib.h>

#include <curses.h>

struct lud_WINDOW {
	WINDOW *win;
	const char *name;
};

int
l_initscr(lua_State *L) /* [-0, +1, v] */
{
	struct lud_WINDOW *uw;
	WINDOW *win;

	win = initscr();

	if (win == NULL)
		luaL_error(L, "initscr()");

	uw = (struct lud_WINDOW *)lua_newuserdata(L, sizeof(*uw));

	/* Zero uw in case of potential errors and passing it to g/c */
	memset(uw, 0, sizeof(*uw));

	luaL_getmetatable(L, "curses:window");
	lua_setmetatable(L, -2);

	uw->win = win;
	uw->name = strdup("stdscr");
	if (uw->name == NULL)
		luaL_error(L, "strdup()");

	return 1;
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
l_echo(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = echo();

	if (rv != OK)
		luaL_error(L, "echo()");

	return 0;
}

int
l_noecho(lua_State *L) /* [-0, +0, v] */
{
	int rv;

	rv = noecho();

	if (rv != OK)
		luaL_error(L, "noecho()");

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
l_newwin(lua_State *L) /* [-5, +1, -] */
{
	struct lud_WINDOW *uw;
	const char *name;
	int lines, cols, begin_y, begin_x;

	name = luaL_checkstring(L, 1);
	if (name == NULL)
		luaL_error(L, "name cannot be unset");

	lines = luaL_checkinteger(L, 2);
	cols = luaL_checkinteger(L, 3);
	begin_y = luaL_checkinteger(L, 4);
	begin_x = luaL_checkinteger(L, 5);
	uw = (struct lud_WINDOW *)lua_newuserdata(L, sizeof(*uw));

	/* Zero uw in case of potential errors and passing it to g/c */
	memset(uw, 0, sizeof(*uw));

	luaL_getmetatable(L, "curses:window");
	lua_setmetatable(L, -2);

	uw->win = newwin(lines, cols, begin_y, begin_x);
	if (uw->win == NULL)
		luaL_error(L, "newwin()");
	uw->name = strdup(name);
	if (uw->win == NULL)
		luaL_error(L, "strdup()");

	return 1;
}

int
lud_WINDOW_keypad(lua_State *L) /* [-2, +0, v] */
{
	struct lud_WINDOW *uw;
	int flag;
	int rv;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");
	flag = lua_toboolean(L, 2);

	rv = keypad(uw->win, flag);

	if (rv != OK)
		luaL_error(L, "keypad()");

	return 0;
}

int
lud_WINDOW___tostring(lua_State *L) /* [-0, +0, -] */
{
	struct lud_WINDOW *uw;
	const char *name;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");
	lua_pushstring(L, uw->name);

	return 1;
}

int
lud_WINDOW___gc(lua_State *L) /* [-0, +0, -] */
{
	int rv;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	/* Never delete stdscr */
	if (uw->win && uw->win != stdscr) {
		rv = delwin(uw->win);
		if (rv != OK)
			luaL_error(L, "delwin(%p)", uw->win);
		/* Zero in case of calling twice g/c for this object */
		uw->win = NULL;
	}
	if (uw->name)
		free((void *)uw->name);
	uw->name = NULL;

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
		{"echo",	l_echo},
		{"noecho",	l_noecho},
		{"raw",		l_raw},
		{"noraw",	l_noraw},
		{"start_color",	l_start_color},
		{"newwin",	l_newwin},
		{NULL,		NULL}
	};

	static luaL_Reg lud_WINDOW_fns[] = {
		{"keypad",	lud_WINDOW_keypad},
		{"__tostring",	lud_WINDOW___tostring},
		{"__gc",	lud_WINDOW___gc},
		{NULL,		NULL}
	};

	luaL_newmetatable(L, "curses:window");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, lud_WINDOW_fns, 0);

	luaL_newlib(L, fns);

	return 1;
}
