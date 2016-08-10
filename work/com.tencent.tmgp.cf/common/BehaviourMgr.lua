module(..., package.seeall)
ModuleMgr = require("common/ModuleMgr")

BehaviourMgr={}

function NewBehaviour(name)
	if not name then
		return
	end
	
	local proto=ModuleMgr.load(name)
	if not proto then
		return
	end
	if type(proto)~="table" then
		return
	end
	
	-- ����
	local obj = CS.UnityEngine.GameObject(name)
	CS.UnityEngine.Object.DontDestroyOnLoad(obj)
	local component=obj:AddComponent(typeof(CS.XLUA.LuaBehaviour))
	-- ʵ��
	inst = {}
	inst["gameObject"]=obj
	setmetatable(inst, inst)
	inst.__index=proto
	-- ��
	component:Bind(inst)
	-- ע��
	BehaviourMgr[obj]={obj=obj, name=name, proto=proto, inst=inst, component=component}
	
	return BehaviourMgr[obj]
end

function rebind()
	for _, info in pairs(BehaviourMgr) do
		info.component:Bind(info.inst)
	end
end