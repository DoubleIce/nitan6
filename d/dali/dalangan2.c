//Room: /d/dali/dalangan2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�����в�");
        set("long",@LONG
����������в�����Ĵ󣬿������������е��㰸��ɫ���㣬��
�ŵ�������ƾ�ϸ���Ե����ڲ�ͬ�����̵Ĺ�Ʒ��Ʈ����ζ�����䵱
�е�һ����ͷ�ر����ۡ����������Ǳ���ļ�������
LONG);
        set("objects", ([
           __DIR__"npc/jisi1": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "down"  : __DIR__"dalangan1",
        ]));
	set("coor/x", -19000);
	set("coor/y", -6870);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/dlg2", 1, me);
        }
}