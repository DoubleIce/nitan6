// Room: /d/xiangyang/walln8.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "����ͷ");
        set("long", @LONG
�����������ı���ͷ��һЩ�α����ڳ�ͷѲ�ߣ�һ������
�������������ܸ����سǲ��ϣ�һЩ���������鹭�������
�ų��µĶ�����
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "southwest" : __DIR__"wallw7",
                "eastdown"  : __DIR__"walln6",
        ]));
        set("objects", ([
                __DIR__"npc/ya"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7850);
	set("coor/y", -720);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}