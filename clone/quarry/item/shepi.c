#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("��Ƥ", ({ "she pi", "she", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + RED "������Ƥ��ʵؼ��ͣ���Ϊ������\n" NOR);
                set("base_unit", "��");
                set("base_value", 4000);
                set("base_weight", 600);
        }
        setup();
        set_amount(1);
}