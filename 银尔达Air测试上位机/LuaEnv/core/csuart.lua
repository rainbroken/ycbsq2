
-- 加载串口池
Uart = {}

Uart.Parity = {}
Uart.Parity.None = CS.System.IO.Ports.Parity.None
Uart.Parity.Even = CS.System.IO.Ports.Parity.Even
Uart.Parity.Odd = CS.System.IO.Ports.Parity.Odd
Uart.Parity.Mark = CS.System.IO.Ports.Parity.Mark
Uart.Parity.Space = CS.System.IO.Ports.Parity.Space

Uart.StopBits = {}
Uart.StopBits.None = CS.System.IO.Ports.StopBits.None
Uart.StopBits.One = CS.System.IO.Ports.StopBits.One
Uart.StopBits.Two = CS.System.IO.Ports.StopBits.Two
Uart.StopBits.OnePointFive = CS.System.IO.Ports.StopBits.OnePointFive

Uart.Handshake = {}
Uart.Handshake.None = CS.System.IO.Ports.Handshake.None
Uart.Handshake.RequestToSend = CS.System.IO.Ports.Handshake.RequestToSend
Uart.Handshake.RequestToSendXOnXOff = CS.System.IO.Ports.Handshake.RequestToSendXOnXOff
Uart.Handshake.XOnXOff = CS.System.IO.Ports.Handshake.XOnXOff

Uart.Count = function() return CS.YEDTestTools.Newsletter.Pools.Uart.Count end

Uart.GetPortName = function()
	local ports = {}
	local port = CS.System.IO.Ports.SerialPort.GetPortNames()
	if port.Length > 0 then	-- 端口数量大于 0 开始遍历
		for i = 0, port.Length - 1 do
			table.insert(ports,port[i])
		end
	end
	return ports
end

Uart.Add = function() 
	CS.YEDTestTools.Newsletter.Pools.Uart:Add() 
	Uart.Refresh()
end

Uart.Remove = function() 
	CS.YEDTestTools.Newsletter.Pools.Uart:Remove()
	Uart.Refresh()
end

Uart.RemoveAt = function(index) 
	CS.YEDTestTools.Newsletter.Pools.Uart:RemoveAt(index)
	Uart.Refresh()
end

Uart.Clear = function()
	local num = Uart.Count()
	for i = 0, num - 1 do CS.YEDTestTools.Newsletter.Pools.Uart:Remove() end
	Uart.Refresh()
end

Uart.Reset = function(index) 
	local state = CS.YEDTestTools.Newsletter.Pools.Uart:Reset(index)
	Uart.Refresh()
	return state
end

Uart.Get = function(index)
	return CS.YEDTestTools.Newsletter.Pools.Uart:Get(index - 1)
end

Uart.Write = function(index,data,hex)
	local u = Uart.Get(index)
	if u == nil then return false end
	return u:Write(data,hex == true)
end

Uart.On = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	local topic = "uart_" .. isRx .. "_" .. id
	if isRx == "receive" then
		Uart.Get(id).LuaRxTopic = "uart_receive_" .. id
	else
		Uart.Get(id).LuaTxTopic = "uart_sent_" .. id
	end
	apiSetCb(topic, function(data) func(id,data) end)
end


Uart.OnDT = function(id,event,func)
	local isRx = event == "receive" and "receive" or "sent"
	if isRx == "receive" then
		Uart.Get(id).LuaRxFunc = func
	else
		Uart.Get(id).LuaTxFunc = func
	end
end

Uart.Refresh = function() 
	local num = Uart.Count()
	for i = 1, 100 do Uart[i] = nil end 
	for i = 1, num do 
		Uart[i] = Uart.Get(i)
	end 
end

Uart.Refresh()
uart = Uart
