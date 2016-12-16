#include <ansi.h>
#include <combat.h>

#define GUI "��" HIR "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int ap, dp;
        int skill;

        if( userp(me) && !query("can_perform/pixie-jian/gui", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(GUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        skill = me->query_skill("pixie-jian", 1);

        if (skill < 100)
                return notify_fail("��ı�а����������죬����ʩչ" GUI "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�����ڵ��������㣬����ʩչ" GUI "��\n");

        if (me->query_skill_mapped("dodge") != "pixie-jian")
                return notify_fail("��û��׼��ʹ�ñ�а����������ʩչ" GUI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���Ӻ������ˣ��������ȣ����ι����쳣����$n"
              HIR "����Ʈ��������\n" NOR;

        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);

        dp=target->query_skill("parry")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$p" HIR "��ʱֻ���ۻ����ң�ֻ�ܽ����Ż�����"
                       "�����Գ�����\n" NOR;
                target->start_busy(ap / 45 + 2);
                me->start_busy(1);
        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN "����������û����"
                       "���κ�Ӱ�졣\n" NOR;
                me->start_busy(2);
        }
        addn("neili", -50, me);
        message_combatd(msg, me, target);

        return 1;
}