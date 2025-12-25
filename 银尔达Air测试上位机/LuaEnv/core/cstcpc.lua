
-- 加载TCP客户端池
Tcpc = {}
Tcpc.Count = function() return CS.YEDTestTools.Newsletter.Pools.Tcpc.Count end

Tcpc.Add = function() 
	CS.YEDTestTools.Newsletter.Pools.Tcpc:Add() 
	Tcpc.Refresh()
end

Tcpc.Remove = function() 
	CS.YEDTestTools.Newsletter.Pools.Tcpc:Remove()
	Tcpc.Refresh()
end

Tcpc.RemoveAt = function(index) 
	CS.YEDTestTools.Newsletter.Pools.Tcpc:RemoveAt(index)
	Tcpc.Refresh()
end

Tcpc.Clear = function()
	local num = Tcpc.Count()
	for i = 0, num - 1 do CS.YEDTestTools.Newsletter.Pools.Tcpc:Remove() end
	Tcpc.Refresh()
end

Tcpc.Reset = function(index) 
	local state = CS.YEDTestTools.Newsletter.Pools.Tcpc:Reset(index)
	Tcpc.Refresh()
	return state
end

Tcpc.Get = function(index)
	return CS.YEDTestTools.Newsletter.Pools.Tcpc:Get(index - 1)
end

Tcpc.Write = function(index,data,hex)
	local u = Tcpc.Get(index)
	if u == nil then return false end
	return u:Write(data,hex == true)
end

Tcpc.On = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	local topic = "tcpc_" .. isRx .. "_" .. id
	if isRx == "receive" then
		Tcpc.Get(id).LuaRxTopic = "tcpc_receive_" .. id
	else
		Tcpc.Get(id).LuaTxTopic = "tcpc_sent_" .. id
	end
	apiSetCb(topic, function(data) func(id,data) end)
end

Tcpc.OnDT = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	if isRx == "receive" then
		Tcpc.Get(id).LuaRxFunc = func
	else
		Tcpc.Get(id).LuaTxFunc = func
	end
end

Tcpc.Refresh = function() 
	local num = Tcpc.Count()
	for i = 1, 100 do Tcpc[i] = nil end 
	for i = 1, num do 
		Tcpc[i] = Tcpc.Get(i)
	end
end

Tcpc.Refresh()
