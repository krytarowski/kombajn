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

#define register_constant(L,v)	\
	(lua_pushstring(L, #v), lua_pushinteger(L, v), lua_rawset(L, -3))

#define register_pointer(L,v)	\
	(lua_pushstring(L, #v), lua_pushlightuserdata(L, v), lua_rawset(L, -3))

#define KEY_F1 KEY_F(1)
#define KEY_F2 KEY_F(2)
#define KEY_F3 KEY_F(3)
#define KEY_F4 KEY_F(4)
#define KEY_F5 KEY_F(5)
#define KEY_F6 KEY_F(6)
#define KEY_F7 KEY_F(7)
#define KEY_F8 KEY_F(8)
#define KEY_F9 KEY_F(9)
#define KEY_F10 KEY_F(10)
#define KEY_F11 KEY_F(11)
#define KEY_F12 KEY_F(12)
#define KEY_F13 KEY_F(13)
#define KEY_F14 KEY_F(14)
#define KEY_F15 KEY_F(15)
#define KEY_F16 KEY_F(16)
#define KEY_F17 KEY_F(17)
#define KEY_F18 KEY_F(18)
#define KEY_F19 KEY_F(19)
#define KEY_F20 KEY_F(20)
#define KEY_F21 KEY_F(21)
#define KEY_F22 KEY_F(22)
#define KEY_F23 KEY_F(23)
#define KEY_F24 KEY_F(24)
#define KEY_F25 KEY_F(25)
#define KEY_F26 KEY_F(26)
#define KEY_F27 KEY_F(27)
#define KEY_F28 KEY_F(28)
#define KEY_F29 KEY_F(29)
#define KEY_F30 KEY_F(30)
#define KEY_F31 KEY_F(31)
#define KEY_F32 KEY_F(32)
#define KEY_F33 KEY_F(33)
#define KEY_F34 KEY_F(34)
#define KEY_F35 KEY_F(35)
#define KEY_F36 KEY_F(36)
#define KEY_F37 KEY_F(37)
#define KEY_F38 KEY_F(38)
#define KEY_F39 KEY_F(39)
#define KEY_F40 KEY_F(40)
#define KEY_F41 KEY_F(41)
#define KEY_F42 KEY_F(42)
#define KEY_F43 KEY_F(43)
#define KEY_F44 KEY_F(44)
#define KEY_F45 KEY_F(45)
#define KEY_F46 KEY_F(46)
#define KEY_F47 KEY_F(47)
#define KEY_F48 KEY_F(48)
#define KEY_F49 KEY_F(49)
#define KEY_F50 KEY_F(50)
#define KEY_F51 KEY_F(51)
#define KEY_F52 KEY_F(52)
#define KEY_F53 KEY_F(53)
#define KEY_F54 KEY_F(54)
#define KEY_F55 KEY_F(55)
#define KEY_F56 KEY_F(56)
#define KEY_F57 KEY_F(57)
#define KEY_F58 KEY_F(58)
#define KEY_F59 KEY_F(59)
#define KEY_F60 KEY_F(60)
#define KEY_F61 KEY_F(61)
#define KEY_F62 KEY_F(62)
#define KEY_F63 KEY_F(63)

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
	if (uw->name == NULL)
		luaL_error(L, "strdup()");

	return 1;
}

int
l_border(lua_State *L) /* [-8, +0, v] */
{
	int rv;
	chtype ls, rs, ts, bs, tl, tr, bl, br;

	ls = luaL_checkinteger(L, 1);
	rs = luaL_checkinteger(L, 2);
	ts = luaL_checkinteger(L, 3);
	bs = luaL_checkinteger(L, 4);
	tl = luaL_checkinteger(L, 5);
	tr = luaL_checkinteger(L, 6);
	bl = luaL_checkinteger(L, 7);
	br = luaL_checkinteger(L, 8);

	rv = border(ls, rs, ts, bs, tl, tr, bl, br);
	if (rv != OK)
		luaL_error(L, "border()");

	return 0;
}

int
l_use_env(lua_State *L) /* [-1, +0, v] */
{
	bool value;

	value = lua_toboolean(L, 1);

	use_env(value);

	return 0;
}

int
l_filter(lua_State *L) /* [-0, +0, v] */
{

	filter();

	return 0;
}

int
l_ripoffline(lua_State *L) /* [-0, +0, v] */
{
#if 0 // not yet
	int rv;

	rv = ripoffline();

	if (rv != OK)
		luaL_error(L, "ripoffline()");
#endif

	return 0;
}

int
l_COLOR_PAIR(lua_State *L) /* [-1, +1, v] */
{
	int n;

	n = luaL_checkinteger(L, 1);

	lua_pushinteger(L, COLOR_PAIR(n));

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
lud_WINDOW_is_keypad(lua_State *L) /* [-1, +1, v] */
{
	struct lud_WINDOW *uw;
	bool flag;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	flag = is_keypad(uw->win);

	lua_pushboolean(L, flag ? 1 : 0);

	return 1;
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
lud_WINDOW_wattron(lua_State *L) /* [-2, +0, v] */
{
	int rv;
	int attr;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");
	attr = luaL_checkinteger(L, 2);

	rv = wattron(uw->win, attr);

	if (rv != OK)
		luaL_error(L, "wattron()");

	return 0;
}

int
lud_WINDOW_wattroff(lua_State *L) /* [-2, +0, v] */
{
	int rv;
	int attr;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");
	attr = luaL_checkinteger(L, 2);

	rv = wattroff(uw->win, attr);

	if (rv != OK)
		luaL_error(L, "wattroff()");

	return 0;
}

int
lud_WINDOW_wattrset(lua_State *L) /* [-2, +0, v] */
{
	int rv;
	int attr;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");
	attr = luaL_checkinteger(L, 2);

	rv = wattrset(uw->win, attr);

	if (rv != OK)
		luaL_error(L, "wattrset()");

	return 0;
}

int
lud_WINDOW_wmove(lua_State *L) /* [-3, +0, v] */
{
	int rv;
	int y, x;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");
	y = luaL_checkinteger(L, 2);
	x = luaL_checkinteger(L, 3);

	rv = wmove(uw->win, y, x);

	if (rv != OK)
		luaL_error(L, "wmove()");

	return 0;
}

int
lud_WINDOW_wrefresh(lua_State *L) /* [-1, +0, v] */
{
	int rv;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	rv = wrefresh(uw->win);

	if (rv != OK)
		luaL_error(L, "wrefresh()");

	return 0;
}

int
lud_WINDOW_box(lua_State *L) /* [-3, +0, v] */
{
	int rv;
	chtype vertical, horizontal;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	vertical = luaL_checkinteger(L, 2);
	horizontal = luaL_checkinteger(L, 3);

	rv = box(uw->win, vertical, horizontal);

	return rv;
}

int
lud_WINDOW_wborder(lua_State *L) /* [-9, +0, v] */
{
	int rv;
	chtype ls, rs, ts, bs, tl, tr, bl, br;
	struct lud_WINDOW *uw;

	uw = (struct lud_WINDOW *)luaL_checkudata(L, 1, "curses:window");

	ls = luaL_checkinteger(L, 2);
	rs = luaL_checkinteger(L, 3);
	ts = luaL_checkinteger(L, 4);
	bs = luaL_checkinteger(L, 5);
	tl = luaL_checkinteger(L, 6);
	tr = luaL_checkinteger(L, 7);
	bl = luaL_checkinteger(L, 8);
	br = luaL_checkinteger(L, 9);

	rv = wborder(uw->win, ls, rs, ts, bs, tl, tr, bl, br);
	if (rv != OK)
		luaL_error(L, "border()");

	return 0;
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

	/* Never delete stdscr and curscr */
	if (uw->win && uw->win != stdscr && uw->win != curscr) {
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

int
curses___index(lua_State *L)
{
	struct lud_WINDOW *uw;
	WINDOW *win;

	/* Argument 1 is self, skip */
	const char *__index = luaL_checkstring(L, 2);

	if (strcmp(__index, "curscr") == 0) {
		uw = (struct lud_WINDOW *)lua_newuserdata(L, sizeof(*uw));

		/* Zero uw in case of potential errors and passing it to g/c */
		memset(uw, 0, sizeof(*uw));

		luaL_getmetatable(L, "curses:window");
		lua_setmetatable(L, -2);

		uw->win = curscr;
		uw->name = strdup("curscr");
		if (uw->name == NULL)
			luaL_error(L, "strdup()");
	} else if (strcmp(__index, "stdscr") == 0) {
		uw = (struct lud_WINDOW *)lua_newuserdata(L, sizeof(*uw));

		/* Zero uw in case of potential errors and passing it to g/c */
		memset(uw, 0, sizeof(*uw));

		luaL_getmetatable(L, "curses:window");
		lua_setmetatable(L, -2);

		uw->win = stdscr;
		uw->name = strdup("stdscr");
		if (uw->name == NULL)
			luaL_error(L, "strdup()");
	} else if (strcmp(__index, "COLS") == 0) {
		lua_pushinteger(L, COLS);
	} else if (strcmp(__index, "LINES") == 0) {
		lua_pushinteger(L, LINES);
	} else if (strcmp(__index, "COLORS") == 0) {
		lua_pushinteger(L, COLORS);
	} else if (strcmp(__index, "COLOR_PAIRS") == 0) {
		lua_pushinteger(L, COLOR_PAIRS);
	} else if (strcmp(__index, "ESCDELAY") == 0) {
		lua_pushinteger(L, ESCDELAY);
	} else if (strcmp(__index, "TABSIZE") == 0) {
		lua_pushinteger(L, TABSIZE);
	} else {
		luaL_error(L, "Type cannot be indexed");
	}

	return 1;
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
		{"border",	l_border},
		{"use_env",	l_use_env},
		{"filter",	l_filter},
		{"ripoffline",	l_ripoffline},
		{"COLOR_PAIR",	l_COLOR_PAIR},
		{NULL,		NULL}
	};

	static luaL_Reg lud_WINDOW_fns[] = {
		{"keypad",	lud_WINDOW_keypad},
		{"is_keypad",	lud_WINDOW_is_keypad},
		{"wgetch",	lud_WINDOW_wgetch},
		{"wprintw",	lud_WINDOW_wprintw},
		{"getbegyx",	lud_WINDOW_getbegyx},
		{"getmaxyx",	lud_WINDOW_getmaxyx},
		{"getyx",	lud_WINDOW_getyx},
		{"wattron",	lud_WINDOW_wattron},
		{"wattroff",	lud_WINDOW_wattroff},
		{"wattrset",	lud_WINDOW_wattrset},
		{"wmove",	lud_WINDOW_wmove},
		{"wrefresh",	lud_WINDOW_wrefresh},
		{"box",		lud_WINDOW_box},
		{"wborder",	lud_WINDOW_wborder},
		{"__tostring",	lud_WINDOW___tostring},
		{"__gc",	lud_WINDOW___gc},
		{NULL,		NULL}
	};

	luaL_newmetatable(L, "curses:window");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, lud_WINDOW_fns, 0);

	/* Put all curses(3) routines to a shared table with constants. */
	luaL_newlib(L, fns);

	/* Add a metatable with a __index routine */
	luaL_newmetatable(L, "curses:variables");
	lua_pushcfunction(L, curses___index);
	lua_setfield(L, -2, "__index");
	lua_setmetatable(L, -2);

	/* Symbols returned in keypad mode */
	register_constant(L, KEY_MIN);
	register_constant(L, KEY_BREAK);
	register_constant(L, KEY_DOWN);
	register_constant(L, KEY_UP);
	register_constant(L, KEY_LEFT);
	register_constant(L, KEY_RIGHT);
	register_constant(L, KEY_HOME);
	register_constant(L, KEY_BACKSPACE);

	register_constant(L, KEY_F1);
	register_constant(L, KEY_F2);
	register_constant(L, KEY_F3);
	register_constant(L, KEY_F4);
	register_constant(L, KEY_F5);
	register_constant(L, KEY_F6);
	register_constant(L, KEY_F7);
	register_constant(L, KEY_F8);
	register_constant(L, KEY_F9);
	register_constant(L, KEY_F10);
	register_constant(L, KEY_F11);
	register_constant(L, KEY_F12);
	register_constant(L, KEY_F13);
	register_constant(L, KEY_F14);
	register_constant(L, KEY_F15);
	register_constant(L, KEY_F16);
	register_constant(L, KEY_F17);
	register_constant(L, KEY_F18);
	register_constant(L, KEY_F19);
	register_constant(L, KEY_F20);
	register_constant(L, KEY_F21);
	register_constant(L, KEY_F22);
	register_constant(L, KEY_F23);
	register_constant(L, KEY_F24);
	register_constant(L, KEY_F25);
	register_constant(L, KEY_F26);
	register_constant(L, KEY_F27);
	register_constant(L, KEY_F28);
	register_constant(L, KEY_F29);
	register_constant(L, KEY_F30);
	register_constant(L, KEY_F31);
	register_constant(L, KEY_F32);
	register_constant(L, KEY_F33);
	register_constant(L, KEY_F34);
	register_constant(L, KEY_F35);
	register_constant(L, KEY_F36);
	register_constant(L, KEY_F37);
	register_constant(L, KEY_F38);
	register_constant(L, KEY_F39);
	register_constant(L, KEY_F40);
	register_constant(L, KEY_F41);
	register_constant(L, KEY_F42);
	register_constant(L, KEY_F43);
	register_constant(L, KEY_F44);
	register_constant(L, KEY_F45);
	register_constant(L, KEY_F46);
	register_constant(L, KEY_F47);
	register_constant(L, KEY_F48);
	register_constant(L, KEY_F49);
	register_constant(L, KEY_F50);
	register_constant(L, KEY_F51);
	register_constant(L, KEY_F52);
	register_constant(L, KEY_F53);
	register_constant(L, KEY_F54);
	register_constant(L, KEY_F55);
	register_constant(L, KEY_F56);
	register_constant(L, KEY_F57);
	register_constant(L, KEY_F58);
	register_constant(L, KEY_F59);
	register_constant(L, KEY_F60);
	register_constant(L, KEY_F61);
	register_constant(L, KEY_F62);
	register_constant(L, KEY_F63);

	register_constant(L, KEY_DL);
	register_constant(L, KEY_IL);
	register_constant(L, KEY_DC);
	register_constant(L, KEY_IC);
	register_constant(L, KEY_EIC);
	register_constant(L, KEY_CLEAR);
	register_constant(L, KEY_EOS);
	register_constant(L, KEY_EOL);
	register_constant(L, KEY_SF);
	register_constant(L, KEY_SR);
	register_constant(L, KEY_NPAGE);
	register_constant(L, KEY_PPAGE);
	register_constant(L, KEY_STAB);
	register_constant(L, KEY_CTAB);
	register_constant(L, KEY_CATAB);
	register_constant(L, KEY_ENTER);
	register_constant(L, KEY_SRESET);
	register_constant(L, KEY_RESET);
	register_constant(L, KEY_PRINT);
	register_constant(L, KEY_LL);

	register_constant(L, KEY_A1);
	register_constant(L, KEY_A3);
	register_constant(L, KEY_B2);
	register_constant(L, KEY_C1);
	register_constant(L, KEY_C3);

	register_constant(L, KEY_BTAB);
	register_constant(L, KEY_BEG);
	register_constant(L, KEY_CANCEL);
	register_constant(L, KEY_CLOSE);
	register_constant(L, KEY_COMMAND);
	register_constant(L, KEY_COPY);
	register_constant(L, KEY_CREATE);
	register_constant(L, KEY_END);
	register_constant(L, KEY_EXIT);
	register_constant(L, KEY_FIND);
	register_constant(L, KEY_HELP);
	register_constant(L, KEY_MARK);
	register_constant(L, KEY_MESSAGE);
	register_constant(L, KEY_MOVE);
	register_constant(L, KEY_NEXT);
	register_constant(L, KEY_OPEN);
	register_constant(L, KEY_OPTIONS);
	register_constant(L, KEY_PREVIOUS);
	register_constant(L, KEY_REDO);
	register_constant(L, KEY_REFERENCE);
	register_constant(L, KEY_REFRESH);
	register_constant(L, KEY_REPLACE);
	register_constant(L, KEY_RESTART);
	register_constant(L, KEY_RESUME);
	register_constant(L, KEY_SAVE);
	register_constant(L, KEY_SBEG);
	register_constant(L, KEY_SCANCEL);
	register_constant(L, KEY_SCOMMAND);
	register_constant(L, KEY_SCOPY);
	register_constant(L, KEY_SCREATE);
	register_constant(L, KEY_SDC);
	register_constant(L, KEY_SDL);
	register_constant(L, KEY_SELECT);
	register_constant(L, KEY_SEND);
	register_constant(L, KEY_SEOL);
	register_constant(L, KEY_SEXIT);
	register_constant(L, KEY_SFIND);
	register_constant(L, KEY_SHELP);
	register_constant(L, KEY_SHOME);
	register_constant(L, KEY_SIC);
	register_constant(L, KEY_SLEFT);
	register_constant(L, KEY_SMESSAGE);
	register_constant(L, KEY_SMOVE);
	register_constant(L, KEY_SNEXT);
	register_constant(L, KEY_SOPTIONS);
	register_constant(L, KEY_SPREVIOUS);
	register_constant(L, KEY_SPRINT);
	register_constant(L, KEY_SREDO);
	register_constant(L, KEY_SREPLACE);
	register_constant(L, KEY_SRIGHT);
	register_constant(L, KEY_SRSUME);
	register_constant(L, KEY_SSAVE);
	register_constant(L, KEY_SSUSPEND);
	register_constant(L, KEY_SUNDO);
	register_constant(L, KEY_SUSPEND);
	register_constant(L, KEY_UNDO);
	register_constant(L, KEY_MOUSE);
	register_constant(L, KEY_RESIZE);
	register_constant(L, KEY_MAX);
	register_constant(L, KEY_CODE_YES);

	/* Attribute definitions */
	register_constant(L, A_NORMAL);
	register_constant(L, A_STANDOUT);
	register_constant(L, A_UNDERLINE);
	register_constant(L, A_REVERSE);
	register_constant(L, A_BLINK);
	register_constant(L, A_DIM);
	register_constant(L, A_BOLD);
	register_constant(L, A_BLANK);
	register_constant(L, A_INVIS);
	register_constant(L, A_PROTECT);
	register_constant(L, A_ALTCHARSET);
	register_constant(L, A_ATTRIBUTES);
	register_constant(L, A_CHARTEXT);
	register_constant(L, A_COLOR);

	/* Wide character attributes */
	register_constant(L, WA_ATTRIBUTES);
	register_constant(L, WA_NORMAL);
	register_constant(L, WA_STANDOUT);
	register_constant(L, WA_UNDERLINE);
	register_constant(L, WA_REVERSE);
	register_constant(L, WA_BLINK);
	register_constant(L, WA_DIM);
	register_constant(L, WA_BOLD);
	register_constant(L, WA_INVIS);
	register_constant(L, WA_PROTECT);
	register_constant(L, WA_ALTCHARSET);
	register_constant(L, WA_LOW);
	register_constant(L, WA_TOP);
	register_constant(L, WA_HORIZONTAL);
	register_constant(L, WA_VERTICAL);
	register_constant(L, WA_LEFT);
	register_constant(L, WA_RIGHT);

	/* Attribute character set definitions */
	register_constant(L, ACS_RARROW);
	register_constant(L, ACS_LARROW);
	register_constant(L, ACS_UARROW);
	register_constant(L, ACS_DARROW);
	register_constant(L, ACS_BLOCK);
	register_constant(L, ACS_DIAMOND);
	register_constant(L, ACS_CKBOARD);
	register_constant(L, ACS_DEGREE);
	register_constant(L, ACS_PLMINUS);
	register_constant(L, ACS_BOARD);
	register_constant(L, ACS_LANTERN);
	register_constant(L, ACS_LRCORNER);
	register_constant(L, ACS_URCORNER);
	register_constant(L, ACS_ULCORNER);
	register_constant(L, ACS_LLCORNER);
	register_constant(L, ACS_PLUS);
	register_constant(L, ACS_HLINE);
	register_constant(L, ACS_S1);
	register_constant(L, ACS_S9);
	register_constant(L, ACS_LTEE);
	register_constant(L, ACS_RTEE);
	register_constant(L, ACS_BTEE);
	register_constant(L, ACS_TTEE);
	register_constant(L, ACS_VLINE);
	register_constant(L, ACS_BULLET);
	register_constant(L, ACS_S3);
	register_constant(L, ACS_S7);
	register_constant(L, ACS_LEQUAL);
	register_constant(L, ACS_GEQUAL);
	register_constant(L, ACS_PI);
	register_constant(L, ACS_NEQUAL);
	register_constant(L, ACS_STERLING);
	register_constant(L, ACS_SBBS);
	register_constant(L, ACS_BBSS);
	register_constant(L, ACS_BSSB);
	register_constant(L, ACS_SSBB);
	register_constant(L, ACS_SSSS);
	register_constant(L, ACS_BSBS);
	register_constant(L, ACS_SSSB);
	register_constant(L, ACS_SBSS);
	register_constant(L, ACS_SSBS);
	register_constant(L, ACS_BSSS);
	register_constant(L, ACS_SBSB);

	/* Wide alternate character set definitions */
	register_pointer(L, WACS_RARROW);
	register_pointer(L, WACS_LARROW);
	register_pointer(L, WACS_UARROW);
	register_pointer(L, WACS_DARROW);
	register_pointer(L, WACS_BLOCK);
	register_pointer(L, WACS_DIAMOND);
	register_pointer(L, WACS_CKBOARD);
	register_pointer(L, WACS_DEGREE);
	register_pointer(L, WACS_PLMINUS);
	register_pointer(L, WACS_BOARD);
	register_pointer(L, WACS_LANTERN);
	register_pointer(L, WACS_LRCORNER);
	register_pointer(L, WACS_URCORNER);
	register_pointer(L, WACS_ULCORNER);
	register_pointer(L, WACS_LLCORNER);
	register_pointer(L, WACS_PLUS);
	register_pointer(L, WACS_HLINE);
	register_pointer(L, WACS_S1);
	register_pointer(L, WACS_S9);
	register_pointer(L, WACS_LTEE);
	register_pointer(L, WACS_RTEE);
	register_pointer(L, WACS_BTEE);
	register_pointer(L, WACS_TTEE);
	register_pointer(L, WACS_VLINE);
	register_pointer(L, WACS_BULLET);
	register_pointer(L, WACS_S3);
	register_pointer(L, WACS_S7);
	register_pointer(L, WACS_LEQUAL);
	register_pointer(L, WACS_GEQUAL);
	register_pointer(L, WACS_PI);
	register_pointer(L, WACS_NEQUAL);
	register_pointer(L, WACS_STERLING);

	/* Color definitions (ANSI color numbers) */
	register_constant(L, COLOR_BLACK);
	register_constant(L, COLOR_RED);
	register_constant(L, COLOR_GREEN);
	register_constant(L, COLOR_YELLOW);
	register_constant(L, COLOR_BLUE);
	register_constant(L, COLOR_MAGENTA);
	register_constant(L, COLOR_CYAN);
	register_constant(L, COLOR_WHITE);

	return 1;
}
