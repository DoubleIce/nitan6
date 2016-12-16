// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

#include "maze.h"

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ����ԼĪ���˶�ߵĴ�ʯ�鹹�ɵ���ʯ�󣬹�ģ�ƺ����󣬵�
̧����ȥ�����ܾ������ص�������Ᾱ�ʯ����ȫ��������·ͨ��ʯ��֮�⣬
��֮���г�������������������������ͷ����ʯ������һ��б����ʯ��(s
hibei)�������ڸ����С�
LONG );

        set("exits", ([
                "east"  : __DIR__"maze29",
                "south" : __DIR__"maze18",
                "west"  : __DIR__"maze3",
                "north" : __DIR__"maze57",
        ]));

        set("item_desc", ([
                "shibei" : "
�����������ز��ľ�����ɥ�޵ã�������������������δ���پ�������ƿ��
        �ס�
�������������಻ʳ���ɾ����ݡ�
�����Ŷ����������֣��ͱ�©��
�������������Ͳ�ʳ��Ϊ�����������ü��������������丣��
�������ģ������ڣ��޾̡�
�������壺��������Ȫʳ��
����������������Ļ�������޼���
����  �� �� �� �� ��
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 48, me);
        check_count(me, 48);
        return;
}