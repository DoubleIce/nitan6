//  Room:  /d/lanzhou/street3.c

inherit  ROOM;

void  create  ()
{
        set("short",  "���Ӵ����");
        set("long",  @LONG
����һ����������ʯ��ֵ���������ͷ���졣����·��������
��ϡ�٣������ĵغ������塣����ͨ����Ժ��������һƬ���֣����ֺ�
��Լ�ɼ�һ����Ժ��
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"jintian",
                "south" : __DIR__"cuiying",
                "east"  : __DIR__"street2",
                "west"  : __DIR__"westgate",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15760);
	set("coor/y", 3820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}