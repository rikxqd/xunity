module(..., package.seeall)

GUI = CS.UnityEngine.GUI
Rect = CS.UnityEngine.Rect
Screen = CS.UnityEngine.Screen

function ExportDll(self)
	CS.XLUA.XLuaFramework.Export("Assembly-CSharp", "/data/local/tmp/cf.dll")
	print("exported...")
end

function OnGUI(self)
	if (GUI.Button(Rect(Screen.width/2, 250, 140, 80), "export")) then
		self:ExportDll()
	end
end