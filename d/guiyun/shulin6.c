// Room: /d/guiyun/shulin6.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "�����");
        set("long",@LONG
����һƬС���֡��������̲�����ï�ܵ������š���Ҷ�ķ�϶��
ż������һֻС�񱻾�������ʮ�־��š�
LONG
);
        set("objects",([
                __DIR__"obj/shizi" : 1,
        ]));  
        set("exits",([
                "west" : __DIR__"shulin4",
        ]) );
        set("outdoors", "guiyun");
        set("coor/x", 310);
        set("coor/y", -810);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}