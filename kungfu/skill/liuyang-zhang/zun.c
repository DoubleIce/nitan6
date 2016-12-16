// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY"�˻Ķ�����"NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int lvl;

        if( !query("reborn/times", me) )
                return notify_fail("�㻹û��ת������������������"+name()+"�ľ��衣\n");

        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");

        if( !target )
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name()+"ֻ�ܿ��ֲ���ʩչ��\n");

        if( !me->is_fighting(target) )
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !target || !target->is_character() )
                return notify_fail("��Ҫ��˭ʩչ"+name()+"��\n");

        if( !living(target) )
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if( me->query_skill_prepared("strike") != "liuyang-zhang" )
                return notify_fail("�㻹û�н���ɽ����������ң��÷�ֻ������޷�ʩչ"+name()+"��\n");

        if( (int)me->query_skill("force") < 1000 )
                return notify_fail("���ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( lvl = me->query_skill("liuyang-zhang", 1) < 1000 )
                return notify_fail("�����ɽ�����ƻ�򲻹����޷�ʩչ"+name()+"��\n");

        if( query("neili", me) < 2500 )
                return notify_fail("������������������޷�ʩչ"+name()+"��\n");

        msg = HIY "����$N" HIY "����ƮƮ�������裬��Ŀ����Ĭ���������������������ھ��������ڣ�\n"
              HIY "����ϼ������˫�Ƶķ���������������Ȼ$N" HIY "�㲽ǰ�ƣ�˫���ƿջ�����Ю��˿˿���⣬ֱ��$n" HIY "˫���ȥ��\n" NOR;

        msg += HIR "$n" HIR "ֻ���ؿ�һ�ƣ�һ˿����ֱ��θ�������һƬ�հ�ãȻ��֪���룡\n" NOR;

        target->affect_by("ss_poison",
                          ([ "level" : lvl * 2,
                             "id"    : query("id", me),
                             // "remain"   : -1,
                             "duration" : lvl / 100 + random(lvl / 10) ,
                          ]));
        // ��һ��
        ap = attack_power(me, "strike") + me->query_str()*20;
        dp = defense_power(target, "dodge") + target->query_str()*20;
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
        damage *= 2;

        addn_temp("apply/add_damage", 50, me);
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 300,
                                           HIR "$n" HIR "��Ȼ���ѣ����´󺧣�������̧���࿹�����ϵ�$N"
                                           HIR "����֬��ѩ��˫�ƾ�Ȼ�̺�ǧ��������\n"
                                           HIR "һ��֮�¶����Լ�˫��������ɢ�����޵ֵ�֮�������ʵʵ�����´��С�\n" NOR);

        } else
        {
                msg += CYN "$p" CYN "�ۼ�$P" CYN "������ӿ���鼱֮������˫�ۣ�����ֿ�����Ȼδռ�·硣\n" NOR;
        }
        addn_temp("apply/add_damage", -50, me);
        message_combatd(msg, me, target);

        msg = HIY "$N" HIY "һ��δ�ϣ�˲���������裬���ŷ����Ƴ�һ�ƣ���������Ŀ�ģ��ǻ���Ű׺��������ھ�ȷ����ӿһ�㱼��$n"HIY"��ǰ��\n" NOR;
        // �ڶ���
        ap = attack_power(me, "strike") + me->query_con()*20;
        dp = defense_power(target, "parry") + target->query_con()*20;

        if (ap / 2 + random(ap) > dp)
        {
                target->set_weak(5);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "���ƾ��������죬ȴ�ֱ��޿ɱܣ���$n" HIR "�ؿ�͸�����,ֱ���$n��Ǵ��ѡ�\n"
                                           HIR "$n" HIR "ֻ��������ǧ���������룬����һ��ӿ��һ��Ѫ���ӿ����缤������\n" NOR);

        } else
        {
                msg += CYN "ֻ��$p" CYN "����׼������һ�����������ӵ���ԴԴ���Ϲ�����ǻ��ס������Ӳ�������ƣ���Ҳ�����󰭡�\n" NOR;
        }

        message_combatd(msg, me, target);

        // ������
        msg = HIY "$N" HIY "����һԾ����Ȼ�ڿ����ɣ�����һ����߳���Ѹ���Ʈҡ���£�������Ӱ�����һ��޴��ѩ������$n" HIY "ͷ��ѹ�¡�\n" NOR;

        ap = attack_power(me, "strike") + me->query_dex()*20;
        dp = defense_power(target, "force") + target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(5);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                           HIR "ֻ����һ�����죬һ���ۻ���ƾ�����$n" HIR "����ը����˳��й��$n" HIR "������\n"
                                           HIR "$n" HIR "­��һ����ʹ��ȫ���������������һ����̱���ڵأ��������á�\n" NOR);

        } else
        {
                msg += CYN "$p" CYN "������������ӿ�����óȻ�мܡ������Ʋ���һ���鶯����Ȼ��ǧ��һ��֮�ʳ���������\n" NOR;
        }


        addn("neili", -1500, me);
        me->start_busy(2+random(2));
        message_combatd(msg, me, target);

        return 1;
}

