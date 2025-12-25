crypto = {}

function crypto.crc16_modbus_hex(hex)
	local crc = CS.YEDTestTools.LuaEnv.LuaApis.ModbusCrc16ByHexString(hex)
	if type(crc) == type('') then return crc end
	return nil
end

function crypto.crc16_modbus(hex)
	local crc = CS.YEDTestTools.LuaEnv.LuaApis.ModbusCrc16ByBytes(hex)
	if type(crc) == type('') then return crc end
	return nil
end