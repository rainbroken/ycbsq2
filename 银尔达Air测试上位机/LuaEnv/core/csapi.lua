
-- 按语言文件读取文本
RLanguage = CS.YEDTestTools.Langs.RLang

-- 加载消息显示类
Msg = {}

-- 层级窗口
Msg.Info = CS.YEDTestTools.Utility.MsgInfo
Msg.Error = CS.YEDTestTools.Utility.MsgError
Msg.Warn = CS.YEDTestTools.Utility.MsgWarn
Msg.OkCancel = CS.YEDTestTools.Utility.MsgOkCancel
Msg.YesNo = CS.YEDTestTools.Utility.MsgYesNo
Msg.Input = CS.YEDTestTools.Utility.MsgInput

-- 非层级窗口
Msg.InfoA = function(msg,noicon) CS.SharpExModule.Ex_Form.MsgInfo(msg,RLanguage("提示",1114),noicon == true) end
Msg.ErrorA = function(msg) CS.SharpExModule.Ex_Form.MsgError(msg,RLanguage("提示",1114)) end
Msg.WarnA = function(msg) CS.SharpExModule.Ex_Form.MsgWarn(msg,RLanguage("提示",1114)) end
Msg.OkCancelA = function(msg) return CS.SharpExModule.Ex_Form.MsgOkCancel(msg,RLanguage("提示",1114)) end
Msg.YesNoA = function(msg) return CS.SharpExModule.Ex_Form.MsgYesNo(msg,RLanguage("提示",1114)) end
Msg.InputA = function(msg,value) return CS.SharpExModule.InputDialog.ShowInputDialog(CS.SharpExModule.InputDialog.InputTypes.ALL,msg,value,RLanguage("输入对话框",1119),RLanguage("确定",1117),RLanguage("取消",1118)) end


-- 保护模式调用函数
cscallfunc = function (func,data,key)
	if type(func) ~= "function" then return data end
    local result, info = pcall(func,data,key)
    if not result then
        log.error("function call","run failed\r\n"..apiAscii2Utf8(tostring(info)))
		return data
    end
	return info
end

-- 编码类型获取
Encoding = {}
Encoding.GetEncoding = function(coding) return CS.System.Text.Encoding.GetEncoding(coding)end
Encoding.UTF8 = Encoding.GetEncoding("UTF-8")
Encoding.GB2312 = Encoding.GetEncoding("GB2312")
Encoding.Unicode = Encoding.GetEncoding("Unicode")

-- 清除 UI 日志
log.Clear = function() CS.YEDTestTools.ExTools.LuaForm._Box:btnClear_Click(nil,nil) end

-- 变量监视界面
Var = {}
Var.IsExist = function(name) return CS.YEDTestTools.ExTools.LuaForm._Box:VarIsExist(name) end
Var.Set = function(name,value) return CS.YEDTestTools.ExTools.LuaForm._Box:VarSet(name,value) end
Var.Get = function(name) return CS.YEDTestTools.ExTools.LuaForm._Box:VarGet(name) end
Var.Add = function(name,remark,value) return CS.YEDTestTools.ExTools.LuaForm._Box:VarAdd(name,remark,value) end

-- 快捷命令列表
QuickCmd = {}
QuickCmd.Get = function(row) 
 local name = CS.YEDTestTools.ExTools.CmdForm._Box:DgvGetCmd(row - 1,1)
 local formt = CS.YEDTestTools.ExTools.CmdForm._Box:DgvGetCmd(row - 1,2)
 local data = CS.YEDTestTools.ExTools.CmdForm._Box:DgvGetCmd(row - 1,3)
 local delay = CS.YEDTestTools.ExTools.CmdForm._Box:DgvGetCmd(row - 1,4)
 local active = CS.YEDTestTools.ExTools.CmdForm._Box:DgvGetCmd(row - 1,5)
 return data,name,formt,delay,active
end

QuickCmd.Count = function() return CS.YEDTestTools.ExTools.CmdForm._Box:DgvGetCount() end

-- 退出运行
AppExit = function() return CS.YEDTestTools.ExTools.LuaForm._Box:LuaExit() end