// suti7.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "�յ�");
        set("long", @LONG
�յ���ʫ���ն��������ֿ�������ʱ�ú���Ͳ����ɵġ��ն���
����ʫ�������£�������Ǯ���غ��ˣ����ʿŮ�����ᡣ���ź����
���ϣ���ɽʼ������ͨ��������ʮ�����ɣ�����ϯ�����̿ա�������
���Ǵ����������ӳ���š�ӳ�������յ������������ϵĵ�һ����
LONG);
        set("exits", ([
            "north"     : __DIR__"suti6",
            "south"     : __DIR__"road20",
        ]));
        set("objects", ([
            __DIR__"npc/shu-sheng" : 1,
        ]));
        set("outdoors", "xihu");
	set("coor/x", 790);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}