// wuyue-blade.c ���µ��� (jacki��1997/7/24)
// modified by Venus Oct.1997

inherit SKILL;

mapping *action = ({
([      "action" : "$N����$w��ӣ�һ�С���ȥ������������һת��һ����$n��$l��ȥ",
    "force" : 120,
    "dodge" : 10,
    "lvl" : 0,
    "skill_name" : "��ȥ����",
    "damage_type" : "����"
]),
([      "action" : "$Nһ�С�������¥���������㣬$wһ��һ�ƣ�ƽ�л���$n������",
    "force" : 160,
    "dodge" : 10,
    "damage" : 8,
    "lvl" : 10,
    "skill_name" : "������¥",
    "damage_type" : "����"
]),
([      "action" : "$N�鲽������һ�С��ƴ����¡�������һ��������ն��$n",
    "force" : 200,
    "dodge" : 15,
    "damage" : 20,
    "lvl" : 20,
    "skill_name" : "�ƴ�����",
    "damage_type" : "����"
]),
([      "action" : "$Nһ�С��ζ���ɽ����$w���϶��»���һ���󻡣���ֱ����$n",    
    "force" : 240,
    "dodge" : 25,
    "damage" : 35,
    "lvl" : 34,
    "skill_name" : "�ζ���ɽ",
    "damage_type" : "����"
]),
([      "action" : "$N�ಽš����һ�С����Ƕ��ǡ����������У�$w����$n���ؿ�",    
    "force" : 270,
    "dodge" : 30,
    "damage" : 50,
    "lvl" : 45,
    "skill_name" : "���Ƕ���",
    "damage_type" : "����"
]),
([      "action" : "$N����$w��ʹ��һ�С��¹����졹������ƬƬ��Ӱ����������$n",
    "force" : 300,
    "dodge" : 35,
    "damage" : 60,
    "lvl" : 59,
    "skill_name" : "�¹�����",
    "damage_type" : "����"
]),
([      "action" : "$Nһ�С����½��ԡ���ֻ�����쵶����˸�����ص�Ӱ��$n��ȫ��ӿȥ",
    "force" : 330,
    "dodge" : 40,
    "damage" : 90,
    "lvl" : 80,
    "skill_name" : "���½���",
    "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
    if( query("max_neili", me)<600 )
        return notify_fail("�������������\n");

    if ((int)me->query_skill("force") < 120)
        return notify_fail("����ڹ����̫ǳ��\n");

    if ((int)me->query_skill("blade", 1) < 80)
        return notify_fail("��Ļ���������򲻹���\n");

    if ((int)me->query_skill("blade", 1) < (int)me->query_skill("wuyue-blade", 1))
        return notify_fail("��ĵ���ˮƽ���ޣ��޷�������������µ�����\n");

    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
        if(level >= action[i]["lvl"])
            return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int) me->query_skill("wuyue-blade",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if( !objectp(weapon=query_temp("weapon", me) )
     || query("skill_type", weapon) != "blade" )
        return notify_fail("��ʹ�õ��������ԡ�\n");

    if( query("qi", me)<50 )
        return notify_fail("����������������µ�����\n");

    if( query("neili", me)<70 )
        return notify_fail("����������������µ�����\n");

    me->receive_damage("qi", 25);
    addn("neili", -61, me);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"wuyue-blade/" + action;
}