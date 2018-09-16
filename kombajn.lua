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

local curses = require('curses')
local unistd = require('unistd')
local argv = require('args')

local stdscr = curses.initscr()

print = function(...) return stdscr:wprintw(...) end

curses.cbreak()
curses.noecho()
stdscr:keypad(true)
curses.start_color()

local A_BOLD=curses.A_BOLD

stdscr:wattron(A_BOLD)
print("hello bold world!\n")
stdscr:wattroff(A_BOLD)
begy, begx = stdscr:getbegyx()
maxy, maxx = stdscr:getmaxyx()
cury, curx = stdscr:getyx()
print("begy=" .. begy .. ", begx=" .. begx .. ", maxy=" .. maxy .. ", maxx=" .. maxx .. ", cury=" .. cury .. " curx=" .. curx .. '\n')

repeat
	local key = stdscr:wgetch()
	print(string.format("%c", key))
until key == curses.KEY_F1

curses.endwin()
