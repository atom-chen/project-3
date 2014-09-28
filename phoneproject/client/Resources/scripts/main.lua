cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

g_resource_path = {}

--�ڳ���������ʱ���ʼ��·��
local function __INIT_RESOURCE_PATH()
		cclog("__INIT_RESOURCE_PATH");
		
		g_resource_path["ui"] = "ui/";
		g_resource_path["effect"] = "effect/";
		g_resource_path["sound"] = "sound/";
		g_resource_path["aeditor"] = "aeditor/";
		g_resource_path["scenes"] = "scenes/";
		g_resource_path["monsters"] = "monsters/";
		g_resource_path["towers"] = "towers/";
		g_resource_path["csv"] = "csv/";
		g_resource_path["particle"] = "effect/particle/";
		g_resource_path["animation"] = "effect/animation/";
		
		cclog("__INIT_RESOURCE_PATH ok.");
end

--�ڳ���������ʱ����Ҫ��ʼ����lua�ļ�
local function __LUA_FILE_FIST_INIT()
		cclog("__LUA_FILE_FIST_INIT");
		CalcCostMS("");
		
		--����ģ�����
		require ("scripts.framework.shared.functions")
		require ("scripts.framework.shared.Global")
		
		--ͨ��ģ�����
		require ("scripts.framework.manager.LNetworkMgr")

		--����ģ�����
		require ("scripts.scenes.BaseScene")
		require ("scripts.scenes.LoadingScene")
		require ("scripts.scenes.WelcomeScene")
		require ("scripts.scenes.MenuScene")
		require ("scripts.scenes.MoleScene")
		require ("scripts.scenes.ChooseMapScene")
		require ("scripts.scenes.MapScene")
		
		CalcCostMS("__LUA_FILE_FIST_INIT");
		cclog("__LUA_FILE_FIST_INIT ok.");
end

local function __INIT_ONE_CSV_TABLE(name, type)
		cclog("__INIT_ONE_CSV_TABLE "..name.." type= "..type);
		local ret = InitDataTables(g_resource_path["csv"], name, type);
		if (ret == 0) then
				cclog("__INIT_ONE_CSV_TABLE ok.");
		else
				cclog("__INIT_ONE_CSV_TABLE failed.");
		end
end

--�ڳ���������ʱ���ȡcsv�ļ�
local function __INIT_CSV_TABLES()
		cclog("__INIT_CSV_TABLES");
		CalcCostMS("");
		
		__INIT_ONE_CSV_TABLE("ctest",0);
		__INIT_ONE_CSV_TABLE("map1",0);
		__INIT_ONE_CSV_TABLE("mapconfig",0);
		__INIT_ONE_CSV_TABLE("monsterconfig",0);
		__INIT_ONE_CSV_TABLE("towerconfig",0);
		__INIT_ONE_CSV_TABLE("skillconfig",0);
		__INIT_ONE_CSV_TABLE("skillperformconfig",0);
		__INIT_ONE_CSV_TABLE("effectconfig",0);
		
		CalcCostMS("__INIT_CSV_TABLES");
		cclog("__INIT_CSV_TABLES ok.");
end

--������Ϸ�ĵ�һ������������
local function __RUN_FIRST_SCENE()
		cclog("__RUN_FIRST_SCENE");
		
		local p_firstscene = BaseScene:create(SCENE_TYPE_WELCOME);
		if nil ~= p_firstscene then
				CCDirector:sharedDirector():runWithScene(p_firstscene);
		else
				cclog("__RUN_FIRST_SCENE failed.");
		end
		
		cclog("__RUN_FIRST_SCENE ok.");
end

--�ڳ���������ʱ���ȡdat�ļ�
local function __INIT_DATA_MGR()
    cclog("__INIT_DATA_MGR");
    CalcCostMS("");
    
    local datamgr = DataMgr:sharedMgr();
    local assertsmgr = AssetsUpdateManager:GetInstance();
    if datamgr:LoadFromFile(GET_PATH(assertsmgr:GetDocumentPath(),"date.dat")) == false then
        datamgr:SaveToFile(GET_PATH(assertsmgr:GetDocumentPath(),"date.dat"));
    end
    
    CalcCostMS("__INIT_DATA_MGR");
    cclog("__INIT_DATA_MGR ok.");
end

--lua�ļ������������
local function main()
    cclog("************** LUA MAIN BEGIN **********")
    
    __INIT_RESOURCE_PATH();
    
    __INIT_DATA_MGR();
    
    __INIT_CSV_TABLES();
    
    __LUA_FILE_FIST_INIT();
    
    __RUN_FIRST_SCENE();
    
    cclog("************** LUA MAIN END ************")
end

xpcall(main, __G__TRACKBACK__)
