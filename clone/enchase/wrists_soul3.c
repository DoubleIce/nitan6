#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "护腕之魂" NOR, ({"wrists soul3", "wrists", "soul3"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "这是一个护腕之魂。\n" NOR);
                set("unit", "个");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "wrists");
        set("status", 3);
        set("auto_load", 1);
        
        setup();
}

