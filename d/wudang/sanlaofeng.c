inherit ROOM;

void create()
{
        set("short", "���Ϸ�");
        set("long", @LONG
�˴����䵱ɽ���Ϸ壬ֻ���������ͻأ�������ޱȣ����˶಻
�ҷŵ��ڴ����ͷ羰��
LONG );
        set("exits", ([
                "northdown": __DIR__"wuyaling",
                "southup"  : __DIR__"wulaofeng",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -340);
        set("coor/z", 120);
        setup();
        replace_program(ROOM);
}