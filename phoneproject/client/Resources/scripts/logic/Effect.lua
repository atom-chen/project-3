--����������Ч��������
EFFECT_CHANGE_MOVE_SPEED = 1;

--Ч���Ļ��࣬���뱻����ʹ��
Effect = class("Effect");
Effect.index = 0;

function Effect:create(master, tid, params)
    
    effect = nil;
    
    local effectconfig_table = GetTable("effectconfig");
    local type = tonumber(effectconfig_table:GetRecByColName(tid, "type"));
    
    if (All_Effects[type] ~= nil) then
        Effect.index = Effect.index + 1;
        
        --�ȸ������ʹ���һ��effect��������ʼ������
        effect = clone(All_Effects[type]);
        effect.master = master;
        effect.index = Effect.index;
        effect.tid = tid;
        
        --effect�ĳ�ʼ������
        effect:init(params);
        
        --��������ظ�����֮��ľ�return��
        if (master:CheckAddEffect(effect) == false) then
            Effect.index = Effect.index - 1;
            return nil;
        end
        
        --֪ͨmaster������effect
        effect.master:OnAddEffect(effect);
        
        cclog("effect type="..effect.classname);
    end
    
    return effect;
end

function Effect:init(params)
    cclog("Effect:init");
    
    local effectconfig_table = GetTable("effectconfig");
    
    self.rule = tonumber(effectconfig_table:GetRecByColName(self.tid, "rule")); --�Ƿ���Ժ���ͬtid�Ľ��е��ӵ�
end

function Effect:remove()
    cclog("Effect:remove selftype="..self.classname.." index="..self.index);
    self:UndoEffect(self.master);
    self.master:OnRemoveEffect(self);
end

function Effect:Heartbeat()
end

function Effect:DoEffect(master)
    cclog("Effect:DoEffect");
end

function Effect:UndoEffect(master)
    cclog("Effect:UndoEffect");
end

function Effect:OnAddEffect()
    self:DoEffect(self.master);
end

--��ʱ�Զ���ʧ��Ч�������뱻����ʹ��
TimeEffect = class("TimeEffect",Effect);

function TimeEffect:init(params)
    cclog("TimeEffect:init");

    TimeEffect.super.init(self, params);

    local effectconfig_table = GetTable("effectconfig");

    self.total_time = tonumber(effectconfig_table:GetRecByColName(self.tid, "life"));
    self.life_tick_count = 0;
end

function TimeEffect:Heartbeat()
    self.life_tick_count = self.life_tick_count + 1;
    if (self.life_tick_count >= self.total_time/BaseScene.instance.maplogic.tick_time) then
        self:remove();
    end
end

--�ƴε�Ч�������뱻����ʹ��
CountEffect = class("CountEffect",Effect);

function CountEffect:init(params)
    cclog("CountEffect:init");
    
    CountEffect.super.init(self, params);
    
    local effectconfig_table = GetTable("effectconfig");
    
    self.count_tick_count = 0;
    self.total_count = tonumber(effectconfig_table:GetRecByColName(self.tid, "count"));
    self.delay = tonumber(effectconfig_table:GetRecByColName(self.tid, "count_delay"));
    self.interval = tonumber(effectconfig_table:GetRecByColName(self.tid, "count_interval"));
end

function CountEffect:OnAddEffect()
    if (self.delay == 0) then
        self.delay = -1;
        self:DoEffect(self.master);
        
        if (self.total_count > 0) then
            self.total_count = self.total_count - 1;
            if (self.total_count <= 0) then
                self:remove();
            end
        end
    end
end

function CountEffect:Heartbeat()
    self.count_tick_count = self.self.count_tick_count + 1;
    if (self.delay > 0) then
        if (self.count_tick_count >= self.delay/BaseScene.instance.maplogic.tick_time) then
            self.count_tick_count = 0;
            self.delay = -1;
            
            self:DoEffect(self.master);
            
            if (self.total_count > 0) then
                self.total_count = self.total_count - 1;
                if (self.total_count <= 0) then
                    self:remove();
                end
            end
        end
    elseif (self.interval >= 0) then
        if (self.count_tick_count >= self.interval/BaseScene.instance.maplogic.tick_time) then
            self.count_tick_count = 0;
            
            self:DoEffect(self.master);
            
            if (self.total_count > 0) then
                self.total_count = self.total_count - 1;
                if (self.total_count <= 0) then
                    self:remove();
                end
            end
        end
    end
end

--������ƶ��ٶȸı�
ChangeMoveSpeed_Effect = class("ChangeMoveSpeed_Effect", TimeEffect)

function ChangeMoveSpeed_Effect:init(params)
    ChangeMoveSpeed_Effect.super.init(self, params);
    
    local effectconfig_table = GetTable("effectconfig");
    
    self.change_speed = tonumber(effectconfig_table:GetRecByColName(self.tid, "change_speed"));
    self.animation = effectconfig_table:GetRecByColName(self.tid, "animation");
end

function ChangeMoveSpeed_Effect:DoEffect(master)
    cclog("ChangeMoveSpeed_Effect:DoEffect");
    
    master:ChangeSpeed(self.change_speed);
    
    if (self.animation ~= nil and self.animation ~= "") then
        local sprite = CCSprite:create();
        sprite:setScale(0.8);   --TODO
        local param = aeditor.AEParamAmmend:create();
        local pos = GET_POS_CENTOR();
        param:AddPos(1, master:GetPos());
        param:AddSprite("effect",sprite);
        
        self.sprite = sprite;
        self.handler = BaseScene.instance.actionRunner:RunAeActionWithParam(BaseScene.instance.uilayer_container, GET_PATH(g_resource_path["aeditor"],self.animation),param,nil,nil);
    end
end

function ChangeMoveSpeed_Effect:UndoEffect(master)
    cclog("ChangeMoveSpeed_Effect:UndoEffect");
    
    master:ChangeSpeed(1/self.change_speed);
    
    if (self.handler ~= nil) then
        BaseScene.instance.actionRunner:RemoveByHandle(self.handler);
    end
end

function ChangeMoveSpeed_Effect:Heartbeat()
    ChangeMoveSpeed_Effect.super.Heartbeat(self);
    
    self.sprite:setPosition(self.master.x, self.master.y);
end

All_Effects[EFFECT_CHANGE_MOVE_SPEED] = ChangeMoveSpeed_Effect.new();