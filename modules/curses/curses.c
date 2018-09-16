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
lud_WINDOW_wgetch(lua_State *L) /* [-1, +1, v] */
{
	struct lud_WINDOW *uw;
	int rv;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	rv = wgetch(uw->win);

	if (rv == ERR)
		luaL_error(L, "wgetch()");

	lua_pushinteger(L, rv);

	return 1;
}

int
lud_WINDOW_wprintw(lua_State *L) /* [-N, +0, v] */
{
	struct lud_WINDOW *uw;
	int rv;
	size_t i, N;
	int nameidx;
	const char *kind;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	for (i = 2, N = lua_gettop(L); i <= N; i++) {
		switch (lua_type(L, i)) {
		case LUA_TNIL:
			rv = wprintw(uw->win, "nil");
			break;
		case LUA_TNUMBER:
			if (lua_isinteger(L, i))
				rv = wprintw(uw->win, LUA_INTEGER_FMT,
				     (LUAI_UACINT)lua_tointeger(L, i));
			else
				rv = wprintw(uw->win, LUA_NUMBER_FMT,
				     (LUAI_UACNUMBER)lua_tonumber(L, i));
			break;
		case LUA_TBOOLEAN:
			rv = wprintw(uw->win, "%s",
			        lua_toboolean(L, i) ? "true" : "false");
			break;
		case LUA_TSTRING:
			rv = wprintw(uw->win, "%s", lua_tostring(L, i));
			break;
		case LUA_TTABLE:
		case LUA_TFUNCTION:
		case LUA_TUSERDATA:
		case LUA_TTHREAD:
		case LUA_TLIGHTUSERDATA:
		default:
			nameidx = luaL_getmetafield(L, i, "__name");
			if (nameidx == LUA_TSTRING)
				kind = lua_tostring(L, -1);
			else
				kind = luaL_typename(L, i);
			rv = wprintw(uw->win, "%s: %p", kind,
			    lua_topointer(L, i));
		}
	}

	if (rv != OK)
		luaL_error(L, "wprintw()");

	return 0;
}

int
lud_WINDOW_getbegyx(lua_State *L) /* [-1, +2, v] */
{
	int y, x;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	getbegyx(uw->win, y, x);

	lua_pushinteger(L, y);
	lua_pushinteger(L, x);

	return 2;
}

int
lud_WINDOW_getmaxyx(lua_State *L) /* [-1, +2, v] */
{
	int y, x;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	getmaxyx(uw->win, y, x);

	lua_pushinteger(L, y);
	lua_pushinteger(L, x);

	return 2;
}

int
lud_WINDOW_getyx(lua_State *L) /* [-1, +2, v] */
{
	int y, x;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	getyx(uw->win, y, x);

	lua_pushinteger(L, y);
	lua_pushinteger(L, x);

	return 2;
}

int
lud_WINDOW___tostring(lua_State *L) /* [-1, +1, v] */
{
	struct lud_WINDOW *uw;
	const char *name;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");
	lua_pushstring(L, uw->name);

	return 1;
}

int
lud_WINDOW___gc(lua_State *L) /* [-1, +0, v] */
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
		{"wgetch",	lud_WINDOW_wgetch},
		{"wprintw",	lud_WINDOW_wprintw},
		{"getbegyx",	lud_WINDOW_getbegyx},
		{"getmaxyx",	lud_WINDOW_getmaxyx},
		{"getyx",	lud_WINDOW_getyx},
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
