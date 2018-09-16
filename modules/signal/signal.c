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


#include <signal.h>

#include <lua.h>
#include <lauxlib.h>

#define register_constant_ligthuserdata(L, v)	\
	(lua_pushstring(L, #v), lua_pushlightuserdata(L, v), lua_rawset(L, -3))

#define register_constant(L, v)	\
	(lua_pushstring(L, #v), lua_pushinteger(L, v), lua_rawset(L, -3))

int
l_signal(lua_State *L) /* [-2, 0, v] */
{
	void (*fn)(int);
	void (*rv)(int);
	int sig;

	sig = luaL_checkinteger(L, 1);
	if (sig < 1 || sig >= NSIG)
		luaL_error(L, "invalid signal number %d", sig);
	if (!lua_islightuserdata(L, 2))
		luaL_error(L, "2nd argument is not ligthuserdata");
	fn = lua_touserdata(L, 2);
	if (fn == NULL)
		luaL_error(L, "2nd argument is NULL");

	rv = signal(sig, fn);
	if (rv == SIG_ERR)
		luaL_error(L, "signal");

	return 0;
}

LUALIB_API int
luaopen_signal(lua_State *L)
{
	luaL_Reg fns[] = {
		{"signal",	l_signal},
		{NULL,		NULL}
	};

	luaL_newlib(L, fns);

	register_constant_ligthuserdata(L, SIG_DFL);
	register_constant_ligthuserdata(L, SIG_IGN);
	register_constant_ligthuserdata(L, SIG_HOLD);

	register_constant(L, NSIG);

	register_constant(L, SIGHUP);
	register_constant(L, SIGINT);
	register_constant(L, SIGQUIT);
	register_constant(L, SIGILL);
	register_constant(L, SIGTRAP);
	register_constant(L, SIGABRT);
	register_constant(L, SIGIOT);
	register_constant(L, SIGEMT);
	register_constant(L, SIGFPE);
	register_constant(L, SIGKILL);
	register_constant(L, SIGBUS);
	register_constant(L, SIGSEGV);
	register_constant(L, SIGSYS);
	register_constant(L, SIGPIPE);
	register_constant(L, SIGALRM);
	register_constant(L, SIGTERM);
	register_constant(L, SIGURG);
	register_constant(L, SIGSTOP);
	register_constant(L, SIGTSTP);
	register_constant(L, SIGCONT);
	register_constant(L, SIGCHLD);
	register_constant(L, SIGTTIN);
	register_constant(L, SIGTTOU);
	register_constant(L, SIGIO);
	register_constant(L, SIGXCPU);
	register_constant(L, SIGXFSZ);
	register_constant(L, SIGVTALRM);
	register_constant(L, SIGPROF);
	register_constant(L, SIGWINCH);
	register_constant(L, SIGINFO);
	register_constant(L, SIGUSR1);
	register_constant(L, SIGUSR2);
	register_constant(L, SIGPWR);
	register_constant(L, SIGRTMIN);
	register_constant(L, SIGRTMAX);

	return 1;
}
