// honghua-shengong.c �컨��
// Last Modified by winder on Sep. 12 2001

#include <ansi.h>;
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
}
int valid_learn(object me)
{
        mapping skl = me->query_skills();
        string *sk;
        string skl_name = explode(__FILE__, "/")[<1][0..<3];
        int i = (int)me->query_skill("honghua-shengong", 1);
        int t = 1, j;

        if(i <= 100) for (j = 1; j < i / 10; j++) t *= 2;

        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");
        if(i <= 100)
        {
                if( i>10 && query("shen", me)<t*100 )
                        return notify_fail("�����������̫���ˣ��޷���������ĺ컨�񹦡�\n");
        }
        else
        {
                if( query("shen", me)<(51200+(i-100)*1000) )
                        return notify_fail("�����������̫���ˣ��޷���������ĺ컨�񹦡�\n");
        }
        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�컨��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"honghua-shengong/" + func;
}
int help(object me)
{
        write(HIM"\n�컨�񹦣�"NOR"\n");
        write(@HELP

    �컨������ڹ��������ơ����Ƽ��˹�֮�á�

        ѧϰҪ��
                �����ڹ�10��
                ��Ӧ������
HELP
        );
        return 1;
}