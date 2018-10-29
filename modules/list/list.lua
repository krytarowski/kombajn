list = {}

function list.new()
	return {
		_back = nil,
		_current = nil,
		_list = nil,
		_size = 0
	}
end

function list.front(l)
	return l._list
end

function list.back(l)
	return l._back
end

function list.empty(l)
	return l._size > 0
end

function list.size(l)
	return l._size
end

function list.clear(l)
	while l._list do
		list.erase(l)
	end
end

function list.insert(l, v)
	if l._list == nil then
		l._list = {_prev = nil, _next = nil, _value = v}
		l._back = l._list
		l._current = l._list
		l._size = 1
	else
		l._list = {_prev = nil, _next = nil, _value = v}
		l._back = l._list
		l._current = l._list
		l._size = l._size + 1
	end
end

-- function list.erase(l, v)
-- 	l.
-- end

function list.push_back(l, v)
	l._list = { _next = , _value = v }
end

-- front
-- back
-- empty
-- size
-- clear
-- insert
-- erase
-- push_back
-- pop_back
-- push_front
-- pop_front
-- resize
-- swap
-- merge
-- splice
-- remove
-- reverse
-- unique
-- sort

-- next
-- prev
-- get
-- set

return list
