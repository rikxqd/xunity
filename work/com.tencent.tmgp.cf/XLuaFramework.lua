module(..., package.seeall)
ModuleMgr = require("common/ModuleMgr")
BehaviourMgr = require("common/BehaviourMgr")

BehaviourMgr.NewBehaviour("logic/ReloadGUI")
BehaviourMgr.NewBehaviour("logic/ExportDll")
BehaviourMgr.NewBehaviour("logic/AutoFire")