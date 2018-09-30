--	$NetBSD$
--
-- Copyright (c) 2018 Kamil Rytarowski
-- All rights reserved.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions
-- are met:
-- 1. Redistributions of source code must retain the above copyright
--    notice, this list of conditions and the following disclaimer.
-- 2. Redistributions in binary form must reproduce the above copyright
--    notice, this list of conditions and the following disclaimer in the
--    documentation and/or other materials provided with the distribution.
--
-- THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
-- ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
-- TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
-- PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
-- BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
-- POSSIBILITY OF SUCH DAMAGE.


local argv = require('args')
local curses = require('curses')
local ctype = require('ctype')
local signal = require('signal')
local unistd = require('unistd')

local stdscr = curses.initscr()

print = function(...) return stdscr:wprintw(...) end

curses.cbreak()
curses.noecho()
stdscr:keypad(true)
curses.start_color()

signal.signal(signal.SIGQUIT, signal.SIG_IGN)
signal.signal(signal.SIGTSTP, signal.SIG_IGN)
signal.signal(signal.SIGTTIN, signal.SIG_IGN)
signal.signal(signal.SIGTTOU, signal.SIG_IGN)
signal.signal(signal.SIGINT, signal.SIG_IGN)

local A_BOLD=curses.A_BOLD

stdscr:wattron(A_BOLD)
print("hello bold world!\n")
stdscr:wattroff(A_BOLD)
begy, begx = stdscr:getbegyx()
maxy, maxx = stdscr:getmaxyx()
cury, curx = stdscr:getyx()

repeat
	stdscr:wmove(1, 0)
	print("begy=" .. begy .. ", begx=" .. begx .. ", maxy=" .. maxy .. ", maxx=" .. maxx .. ", cury=" .. cury .. " curx=" .. curx .. '\n')
	curses.addbytes("BYTE$", 5)
	print("\n")
	local attr,pair = curses.attr_get()
	print(attr, pair)
	print("\n")
	curses.attrset(curses.A_UNDERLINE | curses.A_BOLD)
	print("Underlined-and-bold")
	curses.attrset(attr)
	print("\n")
	curses.addch(68)
	print("\n")
	curses.addchnstr("hakuna_matata", -1)
	print("\n")
	curses.bkgd(string.byte('.') | curses.A_STANDOUT)

	stdscr:wmove(cury, curx)

	local key = stdscr:wgetch()

	if key == curses.KEY_LEFT then
		if curx > begx then
			curx = curx - 1
		end
	elseif key == curses.KEY_RIGHT then
		if curx < maxx - 1 then
			curx = curx + 1
		end
	elseif key == curses.KEY_UP then
		if cury > begy then
			cury = cury - 1
		end
	elseif key == curses.KEY_DOWN then
		if cury < maxy - 1 then
			cury = cury + 1
		end
	elseif key == curses.KEY_HOME then
		curx = begx
	elseif key == curses.KEY_END then
		curx = maxx - 1
	elseif key == curses.KEY_BACKSPACE or key == 127 then
		if curx > begx then
			curx = curx - 1
			stdscr:wmove(cury, curx)
			print(' ')
		end
	elseif key == curses.KEY_RESIZE then
		maxy, maxx = stdscr:getmaxyx()
		if cury >= maxy then
			cury = maxy
		end
		if curx >= maxx then
			curx = maxx
		end
	elseif ctype.isprint(key) then
		print(string.format("%c", key))
		cury, curx = stdscr:getyx()
	end

	stdscr:wmove(maxy - 1, 0)
	print("key = " .. key .. " is_keypad=" .. tostring(stdscr:is_keypad()) .. "   ")
	stdscr:wmove(cury, curx)

until key == curses.KEY_F1

curses.endwin()
