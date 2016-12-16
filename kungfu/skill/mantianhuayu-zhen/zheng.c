// zheng.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ����ս���жԶ��������롣\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("���������в�û�����Ű�����\n");

        if (weapon->query_amount() < 20)
                return notify_fail("����Ҫ�ж�ʮö���������ʩչ������롣\n");

        if ((skill = me->query_skill("mantianhuayu-zhen", 1)) < 100)
                return notify_fail("������컨�������벻����죬����֪��ô�������롣\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷��������롣\n");

        if( query("neili", me)<150 )
                return notify_fail("�����������ˡ�\n");

        addn("neili", -100, me);
        weapon->add_amount(-10);

        msg= HIY "$N" HIY "����Ծ������һ�ţ���ʱ����һƬ��â��"
             "����" + weapon->name() + HIY "�缱�籩��һ��ֱ��$n"
             HIY "��ȥ��\n" NOR;

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);
        if (random(my_exp) > ob_exp)
        {
                n = 1 + random(2);
                if (random(my_exp) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 4) > ob_exp) n += 1 + random(2);
                msg += HIR "���$p" HIR "һ���Һ���������$P" HIR "������" HIR +
                       chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIR "��\n" NOR;
                target->receive_wound("qi", skill / 4 + random(skill / 4), me);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+100+n*10);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += "����$p" HIG "�����$P" HIG "���������" +
                       weapon->name() + HIG "��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}