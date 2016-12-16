// burning.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int count;

        if( query_temp("burning_up", me) )
                return notify_fail("����������ŭ���У�û�б�Ҫ�ٷ���һ�Ρ�\n");

        if (me->query_craze() < 1000)
                return notify_fail("�����ڻ�������ŭ���޷����Լ�ŭ��ȼ�ա�\n");

        message_vision(HIR "$N" HIR "һ�������Ŀ��ʱ����"
                       "���䣬���ͱ��ˣ��Ʋ��ɵ���\n" NOR, me);

        me->cost_craze(500 + random(300));
        count = me->query_skill("force") / 5;
        set_temp("burning_up", count, me);
        addn_temp("apply/attack", count, me);
        me->apply_condition("burning", 1);

        return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: burning|fenu

���ָ�����㽫���ڽ�����ķ�ŭ��й�������������Գ�ֵ�������
�Ĺ����������ڷ�йʱ�᲻�ϵ�������ķ�ŭ��ֱ������ƽ����ʱ��
���Զ��ָ���

HELP
        );
        return 1;
}