// qiankun-xinfa Ǭ����Ų���ķ�

#include <ansi.h>

inherit BOOK;

void setup()
{
}

void create()
{
        set_name("��Ƥ", ({ "qiankunbook", "skin" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", @LONG
����һ����Ƥ��һ����ë��һ��⻬����һ���ǡ�����ʥ
���ķ���Ǭ����Ų�ơ�ʮһ���֡�ԭ����������ֵ�һ��
����Ǭ����Ų�ơ��ķ����ഫ��������ɽ������������
LONG );
                set("material", "paper");
                set("skill", ([
                        "name"         : "qiankun-danuoyi",
                        "family_name"  : "����",
                        "exp_required" : 1000000,
                        "jing_cost"    : 200,
                        "difficulty"   : 45,
                        "max_skill"    : 380,
                        "need" : ([ "sanscrit" : 200 ]),
                ]) );
        }
}