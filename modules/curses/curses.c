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
		{"border",	l_border},
		{"use_env",	l_use_env},
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
