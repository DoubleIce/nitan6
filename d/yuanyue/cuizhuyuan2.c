// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "����԰"); 
        set("long", @LONG
�����������������ܾ��Ǵ���԰��������������ÿ�������°�
����ҹ��Բ��ɽׯ�����������Ǳ�����ˣ�һ�����Σ�һ����裬��
�Ǻ��˰������������ϧ�����ɺܾ��Ѿ�û��������ˣ����ǻ�ʱ��
�������ֵ��ǿ�����Ǯ���ƣ��긴һ�꣬����԰�е�����ҲԽ��Խ�١�
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "north":__DIR__"wuzhuxuan",
        ]) );
        
        set("item_desc", ([
                "bamboo": "������������ҡ�ڣ����ƺ������ۣ�pick������������\n",
                "����": "������������ҡ�ڣ����ƺ������ۣ�pick������������\n",
        ]) );
        set("coor/x",-610);
        set("coor/y",210);
        set("coor/z",80);
        setup();
} 
void init()
{
        add_action("do_pick", "pick");
} 
int do_pick(string arg)
{
        object bamboo;
        if ( !arg && arg != "bamboo" && arg != "����" )
                return notify_fail("��Ҫ��ʲô��\n");
        if((int) query("picked") <= 3)
        {
                write("������һ����������ӣ�С�ĵķ��ڻ��\n");
                bamboo = new("/clone/weapon/bamboo");
                bamboo->move(this_player());
                addn("picked",1);
           return 1;
        }
        else
        write("�����Ѿ������۹��ˣ���\n");
        return 1;
} 
void reset()
{
        :: reset();
        delete("picked");
}    