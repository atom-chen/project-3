Global = class("Global");
Global.timer_list = {};

--�ű���һ��һ�ε�tick����
function Global:Tick(dt)
		--cclog("Global:Tick dt="..dt);
		Global:ProcessTimer();
end

--����һ����ʱ��
function Global:CreateTimer(observer, timerid, timer_period, timer_count, timer_arg)
		if (Global.timer_list[timerid] ~= nil) then
				return false;
		end
		
		if (nil == observer or timer_count < 0 or timer_period <= 0) then
				return false;
		end
		
		Global.timer_list[timerid] = {obs = observer, id = timerid, period = timer_period, count = timer_count, countdown = timer_period, arg = timer_arg};
end

--ɾ��һ����ʱ��
function Global:RemoveTimer(timerid)
		Global.timer_list[timerid] = nil;
end

--��ʱ���Ĵ���������ÿһ���tick����
function Global:ProcessTimer()
		local k, v;
		for k,v in pairs (Global.timer_list) do
				if (v and (type(v) == "table")) then
						v.countdown = v.countdown - 1;
						if (v.countdown <= 0) then
								Global:EventTimer(v.obs, v.id, v.period, v.count, v.arg);
								v.countcown = v.period;
								if (v.count > 0) then
										v.count = v.count - 1;
										if (v.count <= 0) then
												Global.timer_list[k] = nil;
										end
								end
						end
				end
		end
end

--��ʱ�����ڵĴ����ַ����۲��ߵ�OnTimer������ȥ
function Global:EventTimer(obs, id, period, count, arg)
		obs:OnTimer(id, period, count, arg);
end