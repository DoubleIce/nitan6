#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�����ϰ�");
        set("long", @LONG
��첽�����˳����ϰ���ֻ�����ﲨ�ι��������Ͻ�ˮ��
����ȥ����������һ�鱮(bei)��ǰ�治Զ��������ľ�š�
LONG);
        set("outdoors", "jingzhou");
        set("exits", ([
                "south" : __DIR__"tulu1", 
                "north"  :__DIR__"qiao3",
        ]));
        set("item_desc", ([
                "bei" : WHT "\n\n\n            ��������������������������������\n"
                        "            ��                            ��\n"
                        "            ��" NOR + HIW "     ͨ      ��      ��" NOR +
                        WHT "     ��\n"
                        "            ��                            ��\n"
                        "            ��������������������������������\n\n\n" NOR,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2150);
	set("coor/z", 0);
	setup();
       
        replace_program(ROOM);
}