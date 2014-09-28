--Ч�������͵Ĺ���
EFFECT_RULE_CANT_REPEAT = 1;

--����������Ч����ʵ��
All_Effects = {};

--������ܳ���Effect�Ļ���
EffectActivatedObejct = class("EffectActivatedObejct", SkillActivatedObejct);

function EffectActivatedObejct:ctor(params)
    EffectActivatedObejct.super.ctor(self,params);
    
    cclog("EffectActivatedObejct:ctor");
    
    self.effects = {};
end

function EffectActivatedObejct:remove()
    cclog("EffectActivatedObejct:remove");
    
    EffectActivatedObejct.super.remove(self);
    
    --������������Ч��ɾ��
    self:RemoveAllEffects();
end

function EffectActivatedObejct:CheckAddEffect(add_effect)
    if (add_effect.rule == nil) then
        return true;
    end
    for key, effect in pairs(self.effects) do
        if (effect ~= nil and effect.rule ~= nil and effect.tid == add_effect.tid) then
            if (effect.rule == EFFECT_RULE_CANT_REPEAT or add_effect.rule == EFFECT_RULE_CANT_REPEAT) then
                return false;
            end
        end
    end
    return true;
end

function EffectActivatedObejct:Heartbeat()
    EffectActivatedObejct.super.Heartbeat(self);

    for key, effect in pairs(self.effects) do
        if (effect ~= nil) then
            effect:Heartbeat();
        end
    end
end

function EffectActivatedObejct:RemoveAllEffects()
    cclog("EffectActivatedObejct:RemoveAllEffects size="..#self.effects);
    
    local num = #self.effects;
    for i=1,num,1 do
        self.effects[1]:remove();   --ÿ��ɾ�����˶���ǰ�ƶ�������һֱ��ɾ����һ������
    end
end

function EffectActivatedObejct:OnAddEffect(effect)
    cclog("EffectActivatedObejct:OnAddEffect index="..effect.index);
    
    --self.effects[effect.index] = effect;
    
    self.effects[#self.effects+1] = effect;
    
    effect:OnAddEffect();
end

function EffectActivatedObejct:OnRemoveEffect(effect)
    cclog("EffectActivatedObejct:OnRemoveEffect size="..#self.effects);
    
    --self.effects[effect.index] = nil;
    
    local remove_map = {};
    local i = 0;
    for key, ef in pairs(self.effects) do
        i = i + 1;
        if (effect == ef) then
            remove_map[#remove_map+1] = i;
            break;
        end
    end
    
    if (table.nums(remove_map) ~= 0) then
        for k, v in pairs(remove_map) do
            table.remove(self.effects,v);
        end
    end
    
    cclog("EffectActivatedObejct:OnRemoveEffect end size="..#self.effects);
end