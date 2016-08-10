module(..., package.seeall)
ModuleMgr = require("common/ModuleMgr")

GUI = CS.UnityEngine.GUI
Rect = CS.UnityEngine.Rect
Screen = CS.UnityEngine.Screen

function OnGUI(self)
	if (GUI.Button(Rect(Screen.width/2, 150, 140, 80), "Reload")) then
		print("realod all...")
		ModuleMgr.realodall()
	end
end