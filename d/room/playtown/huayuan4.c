// Room: /d/playertown/huayuan4.c ��԰
// Build 199.12.10 bmw

inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long",
"������һ����שС���ϣ�����������������������������������м�\n"
"���洬���ڴ��棬����ǻ���س��Ÿ裬����һ��������������������\n"
"������һƬƬ���̵Ĳ�ƺ�����漸�Է����������ǣ���ͷ�����ţ�ż��\n"
"������һ��ɬЦ��\n"
);
        set("outdoors", "playertown");
//      set("no_clean_up", 0);
        set("exits", ([
                "north"        :        __DIR__"huayuan3",
                "south"        :        __DIR__"road10",
        ]));
        setup();
        replace_program(ROOM);
}