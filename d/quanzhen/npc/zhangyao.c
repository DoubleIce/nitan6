// zhangyao.c ��ҩ����

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("��ҩ����", ({"zhangyao"}));
        set("gender", "����");
        set("age", 28);
        set("class", "quanzhen");
        set("long",
                "����ȫ����е��ƹ�����ҩ��ĵ��ˡ�����Ͳ��󣬵�������\n"
                "�Ե������ϳɡ�\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 21);
        set("int", 22);
        set("con", 23);
        set("dex", 22);

        set("qi", 600);
        set("max_qi", 600);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 0);

        set("combat_exp", 30000);
        set("score", 20000);

        set_skill("array", 30);
        set_skill("force", 60);
        set_skill("xiantian-gong", 50);    //��������
        set_skill("sword", 60);
        set_skill("quanzhen-jian", 60);  //ȫ�潣
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 50);   //���㹦
        set_skill("parry", 60);
        set_skill("unarmed", 60);
        set_skill("strike", 60);
        set_skill("haotian-zhang", 50);    //�����
        set_skill("cuff", 60);
        set_skill("chunyang-quan", 50);    //����ȭ
        set_skill("literate", 50);
        set_skill("taoism", 40);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("strike", "haotian-zhang");
        map_skill("cuff", "chunyang-quan");
        prepare_skill("cuff", "chunyang-quan");
        prepare_skill("strike", "haotian-zhang");

        create_family("ȫ���", 4, "����");

        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/yellowrobe")->wear();
}

int accept_object(object who, object ob)
{
        object obj,obj1,obj2;
        object me=this_player();

        if( !who || environment(who) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, who) ) return notify_fail("��û�����������\n");

        if( query("name", ob) != HIB"�ڹ��"NOR
                 && query("id", ob) != "fuling" )
                    return notify_fail("��ҩ����ҡͷ�����ⲻ����ҩ�Ĳ��ϡ�\n");

        if( query("name", ob) == HIB"�ڹ��"NOR )
        {
                if(query_temp("fuling")) {
                        write(MAG"��ҩ������ϲ����׺����߶����ˣ��⸱���߸�������ˡ�\n"NOR);
                        obj=new("/clone/medicine/nostrum/guilinggao");
                        obj->move(who);
                        delete_temp("guijia");
                        delete_temp("fuling");
                        if(!(obj2=present("gui jia", this_player())))
                        destruct(obj2);
                        remove_call_out("destroying");
                        call_out("destroying", 1, me, ob);

                        return 1;
                }
                else {
                        if(query_temp("guijia")) {
                                write(YEL"��ҩ����ҡ��ҡͷ������������Ѿ����ˡ���\n"NOR);
                                return 0;
                        }
                        else {
                                set_temp("guijia",1);
                                write(WHT"��ҩ����Ц����������ˣ���ȱ�����ˡ�\n"NOR);
                                if(!(obj2=present("gui jia", this_player())))
                                destruct(obj2);
                                remove_call_out("destroying");
                                call_out("destroying", 1, me, ob);
                                return 1;
                        }
                }
        }
        if( query("id", ob) == "fuling" )
        {
                if(query_temp("guijia")) {
                        write(MAG"��ҩ������ϲ����׺����߶����ˣ��⸱���߸�������ˡ�\n"NOR);
                        obj=new("/clone/medicine/nostrum/guilinggao");
                        obj->move(who);
                        delete_temp("guijia");
                        delete_temp("fuling");
                        if(!(obj1=present("fuling", this_player())))
                        destruct(obj1);
                        remove_call_out("destroying");
                        call_out("destroying", 1, me, ob);
                        return 1;
                }
                else {
                        if(query_temp("fuling")) {
                                write(YEL"��ҩ����ҡ��ҡͷ�������������Ѿ����ˡ���\n"NOR);
                                return 0;
                        }
                        else {
                                set_temp("fuling",1);
                                write(WHT"��ҩ����Ц�����������ˣ���ȱ����ˡ�\n"NOR);
                                if(!(obj2=present("fuling", this_player())))
                                destruct(obj2);
                                remove_call_out("destroying");
                                call_out("destroying", 1, me, ob);
                                return 1;
                        }
                }
        }

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
void attempt_apprentice(object ob)
{
        command("say �Ҳ��յ��ӣ���ȥ�ұ�ĵ����ɡ�");
}