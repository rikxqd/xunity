module(..., package.seeall)
BehaviourMgr = require("common/BehaviourMgr")

ModuleLoaded={}

function load(name)
	if name==nil then
		return
	end
	
	local ret=require(name)
	if not ret then
		return
	end
	
	ModuleLoaded[name]=ret
	return ret
end

function reload(name)
	package.loaded[name]=nil
	load(name)
end

function realodall()
	for name, _ in pairs(ModuleLoaded) do
		reload(name)
	end
	
	BehaviourMgr.rebind()
end