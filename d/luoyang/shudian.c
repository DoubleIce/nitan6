inherit ROOM;

void create()
{
        set("short", "��ɮ���");
        set("long", @LONG
������ϰ�մ�������������˵��ǰ��������ɽ�����³����ң���
֪ʲôԭ���ֻ����ף�ר������Ϊ����ֻ���������ܴ���ǰ����һ��
������
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"wroad7",
        ]));
        set("objects", ([
                __DIR__"npc/shudianboss" : 1,
        ]));

	set("coor/x", -7040);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}