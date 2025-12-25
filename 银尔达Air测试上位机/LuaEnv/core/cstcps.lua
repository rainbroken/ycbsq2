
-- 加载TCP服务端池
Tcps = {}
Tcps.Count = function() return CS.YEDTestTools.Newsletter.Pools.Tcps.Count end

Tcps.Add = function() 
	CS.YEDTestTools.Newsletter.Pools.Tcps:Add() 
	Tcps.Refresh()
end

Tcps.Remove = function() 
	CS.YEDTestTools.Newsletter.Pools.Tcps:Remove()
	Tcps.Refresh()
end

Tcps.RemoveAt = function(index) 
	CS.YEDTestTools.Newsletter.Pools.Tcps:RemoveAt(index)
	Tcps.Refresh()
end

Tcps.Clear = function()
	local num = Tcps.Count()
	for i = 0, num - 1 do CS.YEDTestTools.Newsletter.Pools.Tcps:Remove() end
	Tcps.Refresh()
end

Tcps.Reset = function(index) 
	local state = CS.YEDTestTools.Newsletter.Pools.Tcps:Reset(index)
	Tcps.Refresh()
	return state
end

Tcps.Get = function(index)
	return CS.YEDTestTools.Newsletter.Pools.Tcps:Get(index - 1)
end

Tcps.Client = function(index)
	local clis = {}
	local cli = Tcps.Get(index):GetPointKeys()
	if cli.Length > 0 then	-- 已连接设备数量大于 0 开始遍历
		for i = 0, cli.Length - 1 do
			if cli[i] ~= 'SENDALL' then
				table.insert(clis,cli[i])
			end
		end
	end
	return clis
end

Tcps.Write = function(index,client,data,hex)
	local u = Tcps.Get(index)
	if u == nil then return false end
	return u:Write(data,hex == true,client)
end

Tcps.On = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	local topic = "tcps_" .. isRx .. "_" .. id
	if isRx == "receive" then
		Tcps.Get(id).LuaRxTopic = "tcps_receive_" .. id
	else
		Tcps.Get(id).LuaTxTopic = "tcps_sent_" .. id
	end
	apiSetCb(topic, function(data)
		func(id,data.key,data.msg) 
	end)
end

Tcps.OnDT = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	if isRx == "receive" then
		Tcps.Get(id).LuaRxFunc = func
	else
		Tcps.Get(id).LuaTxFunc = func
	end
end

Tcps.Refresh = function() 
	local num = Tcps.Count()
	for i = 1, 100 do Tcps[i] = nil end 
	for i = 1, num do 
		Tcps[i] = Tcps.Get(i)
	end
end

Tcps.Refresh()
