module(..., package.seeall)
luanet.import_type("WNEngine.LocalPlayer")
luanet.import_type("WNEngine.PlayerController")

GUI = CS.UnityEngine.GUI
Rect = CS.UnityEngine.Rect
Screen = CS.UnityEngine.Screen
GameTool = CS.WNGameBase.GameTool

function Fire(self)
	CS.XLUA.XLuaFramework.LoadAssembly("/data/local/tmp/behaviac.dll")
	CS.behaviac.WorkspaceDriver.Launch()
	local obj = CS.UnityEngine.GameObject("LocalPlayerAgent")
	CS.UnityEngine.Object.DontDestroyOnLoad(obj)
	local agent = obj:AddComponent(typeof(CS.behaviac.LocalPlayer))
	agent:btsetcurrent("PlayerAutoFire")
	agent:btexec()
	print(agent.CurrentBT)
end

function OnGUI(self)
	if (GUI.Button(Rect(Screen.width/2, 350, 140, 80), "fire")) then
		self:Fire()
	end
end