inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
��������ϷԺ����Ա�������������ڵ������ź��ĵ�̺
�м�����Ա�������������������������һ������ǰ�����
���������ġ��㿴�����ǲ���Ҳ�붯�����ӹǣ�����
LONG);

        set("exits", ([
                "north" : __DIR__"xiyuan",
        ]));
        set("objects", ([
                __DIR__"npc/xizi1" : 1,
                __DIR__"npc/xizi2" : 1,
        ]));

        set("coor/x", -9050);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}