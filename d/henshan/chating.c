inherit ROOM;

void create()
{        
       set("short", "��ͤ");        
        set("long", @LONG
����һ��·�ߵ�С��ͤ����ɽ·���˳��ڴ˴�ЪЪ�š�ͤ������
�������Ӻͼ�֧���ʡ���Χ��һƬ���֡�
LONG );
    
       set("outdoors", "henshan");        

       set("exits", ([                
              "west"  : __DIR__"hsroad6",        
       ]));        

       set("objects", ([                
               __DIR__"npc/yuanziyi" :1,        
       ])); 
      
       set("no_clean_up", 0);        

	set("coor/x", -6920);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();        
       replace_program(ROOM);
}