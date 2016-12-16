#include <ansi.h>
#include <combat.h>

#define XING "��" HIY "Ⱥ����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/qixing-jian/xing", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XING "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" XING "��\n");

        if (me->query_skill("qixing-jian", 1) < 60)
                return notify_fail("�����ǽ�����Ϊ����������ʩչ" XING "��\n");

        if (me->query_skill_mapped("sword") != "qixing-jian")
                return notify_fail("��û�м������ǽ���������ʩչ" XING "��\n");

        if (me->query_skill("force") < 80)
                return notify_fail("���ڹ�����Ϊ����������ʩչ" XING "��\n");

        if( query("neili", me)<50 )
                return notify_fail("�����ڵ��������㣬����ʩչ" XING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����" + weapon->name() + HIY "һ�񣬵���ʯ��"
              "����������������˸��������㷱������$n" HIY "��\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 2);
                addn("neili", -30, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "��ʱ���һ�����񵲲�����"
                                           "�Ǳ�$N" HIR "������У���Ѫ�Ľ���\n" NOR);
        } else
        {
                addn("neili", -20, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "�������ң�����񵲿���$P"
                       CYN "�Ľ��С�\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}