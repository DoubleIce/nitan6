// Room: /d/huanggong/hubu.c

inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
����������֮��--������Ա�򳯵ĳ���.
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"youmen",
        ]));
	set("coor/x", -2780);
	set("coor/y", 7691);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}