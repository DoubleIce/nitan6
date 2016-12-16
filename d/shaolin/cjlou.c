// Room: /d/shaolin/cjlou.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "�ؾ���һ¥");
        set("long", @LONG
����Ϊ��ԭ�𷨵���Դ�������´˴��ؾ�֮�������º�����ƥ��
���ﶼ���������飬�߼��������ܣ���ܼ��������һ��ͨ�еĿ�
϶�����Ŵ�����м䣬����ط������ɳ���������Ŀ�⼰�����㿴��
���Ϸ��˼����𾭡�
LONG );
        set("exits", ([
                "east" : __DIR__"zhulin5",
                "up" : __DIR__"cjlou1",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/dao-yi" : 1,
                CLASS_D("shaolin") + "/wuming" : 1,
                "d/shaolin/obj/fojing1"+random(2) : 1,
                "d/shaolin/obj/fojing2"+random(2) : 1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (! present("shou yu", me) &&
            (objectp(present("daoyi chanshi", environment(me)))))
        {
                if (dir == "up" )
                {
                        return notify_fail("��һ˵��: ��δ�����ɣ������϶�¥��\n");
                }
        }
        return ::valid_leave(me, dir);
}