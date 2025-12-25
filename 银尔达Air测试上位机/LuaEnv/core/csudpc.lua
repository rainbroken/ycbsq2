
-- 加载UDP客户端池
Udpc = {}
Udpc.Count = function() return CS.YEDTestTools.Newsletter.Pools.Udpc.Count end

Udpc.Add = function() 
	CS.YEDTestTools.Newsletter.Pools.Udpc:Add() 
	Udpc.Refresh()
end

Udpc.Remove = function() 
	CS.YEDTestTools.Newsletter.Pools.Udpc:Remove()
	Udpc.Refresh()
end

Udpc.RemoveAt = function(index) 
	CS.YEDTestTools.Newsletter.Pools.Udpc:RemoveAt(index)
	Udpc.Refresh()
end

Udpc.Clear = function()
	local num = Udpc.Count()
	for i = 0, num - 1 do CS.YEDTestTools.Newsletter.Pools.Udpc:Remove() end
	Udpc.Refresh()
end

Udpc.Reset = function(index) 
	local state = CS.YEDTestTools.Newsletter.Pools.Udpc:Reset(index)
	Udpc.Refresh()
	return state
end

Udpc.Get = function(index)
	return CS.YEDTestTools.Newsletter.Pools.Udpc:Get(index - 1)
end

Udpc.Client = function(index)
	local clis = {}
	local cli = Udpc.Get(index):GetPointKeys()
	if cli.Length > 0 then	-- 设备数量大于 0 开始遍历
		for i = 0, cli.Length - 1 do
			if cli[i] ~= 'SENDALL' then
				table.insert(clis,cli[i])
			end
		end
	end
	return clis
end

Udpc.Write = function(index,client,data,hex)
	local u = Udpc.Get(index)
	if u == nil then return false end
	return u:Write(data,hex == true,client)
end

Udpc.On = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	local topic = "udpc_" .. isRx .. "_" .. id
	if isRx == "receive" then
		Udpc.Get(id).LuaRxTopic = "udpc_receive_" .. id
	else
		Udpc.Get(id).LuaTxTopic = "udpc_sent_" .. id
	end
	apiSetCb(topic, function(data)
		func(id,data.key,data.msg) 
	end)
end

Udpc.OnDT = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	if isRx == "receive" then
		Udpc.Get(id).LuaRxFunc = func
	else
		Udpc.Get(id).LuaTxFunc = func
	end
end

Udpc.Refresh = function() 
	local num = Udpc.Count()
	for i = 1, 100 do Udpc[i] = nil end 
	for i = 1, num do 
		Udpc[i] = Udpc.Get(i)
	end
end

Udpc.Refresh()
