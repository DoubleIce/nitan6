inherit NPC;
#include <ansi.h>

void create()
{
        set_name("ľ������", ({ "mufang guanshi", "guanshi" }) );
        set("gender", "����" );
        set("age", 50);
        set("long", "����ľ�����£�ר��ľ����\n");
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("inquiry", ([
             	"��ľͷ" : "�����������ʵʵ���Ҿ�ľͷ��û���ҵ����⣬������ȥ������",
               
        ]));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting())
	{
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment()) return;
         
        if( query_temp("job_name", ob) != "��ľͷ")return ;

        if (! (present("ju zi", ob)))
        {
        	command("hmm"+query("id", ob));
        	command("say �㻹û�칤�߰ɣ�ȥ����Ʒ������үҪ��������\n");
        	return;
        }

        if( !(query_temp("job_name", ob) != "��ľͷ") )
        {
        	command("nod"+query("id", ob));
                command("say ��Ү�ɴ�ү�Ը������İɣ�����������ľ(" HIY
                        "ju mutou" NOR + CYN ")���ˡ�\n" NOR);
        }
}