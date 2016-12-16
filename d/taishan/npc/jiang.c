// jiang ����ʤ
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit NPC;

void create()
{
        seteuid(getuid());

        set_name("����ʤ", ({ "jiang baisheng", "jiang", "baisheng" }) );
        set("gender", "����" );
        set("age", 30);
        set("long", "������������κ��˫֮����֮�ױ��ӳ���\n");
        set("attitude", "heroism");
        set("generation",0);
        set("winner","none");

        set("str", 25);
        set("con", 25);
        set("int", 25);
        set("dex", 25);

        set("max_qi", 400);
        set("eff_qi", 400);
        set("qi", 400);
        set("max_jing", 200);
        set("jing", 200);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 30);
        set("shen_type", 0);

        set("no_clean_up",1);
        set("combat_exp", 50000);

        set_skill("force", 80); 
        set_skill("unarmed", 100);
        set_skill("dodge", 80);
        set_skill("parry", 80);

        set("fight_times", 0);        

        setup();
        
}

int accept_fight(object ob)
{
        object me  = this_object();
                
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("jing",query("max_jing",  me), me);
        set("neili",query("max_neili",  me), me);

        if ( me->is_fighting()) return 0;

        if ( !present(ob, environment()) ) return 0;

        if( query("fight_times", me) >= 10 )
                return notify_fail("����ʤ�Ѿ�ȫ��������ſ�ڵ��ϴ�ڵش��Ŵ�����\n");        

        addn("fight_times", 1, me);

        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        
        return 1;
}

int checking(object me, object ob)
{
        object obj;
        int my_max_qi, his_max_qi;

        if ( !present(ob, environment()) ) return 1; 

        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);

        if( me->is_fighting() ) 
        {
                if( (query("qi", me)*100/my_max_qi) <= 80 )
                {
                        say(GRN "\n����ʤ˵���� κ���������£����ò����� �����˼������Ųߣ����޲��ˣ����޲�ʤ��\n" NOR);
                        say(GRN "\n����ʤ˵���� κ����һ�仰�����°��´���������ֱǰ�� ����ѩ�����ﴳ����ɽ�𺣾͸�ȥ��\n" NOR);
                        message_vision(HIY "\n����ʤ˵�꣬ȫ����֪������ð������һ����������������������ȭ��Ҳ���ͺö౶��\n" NOR, ob);

                        set("eff_qi",query("max_qi",  me), me);
                        set("qi",query("max_qi",  me), me);
                        set("jing",query("max_jing",  me), me);
                        set("neili",query("max_neili",  me), me);
                }
                else if( (query("qi", ob)*100/his_max_qi)<50 )
                {
                        say(GRN "\n����ʤ˵���� ������С�Ӹ��һ�����һ����أ���ȥ����ʮ�������ɣ�\n");
                        return 1;
                }

                if ( present(ob, environment()) ) call_out("checking", 1, me, ob);
        }

        return 1;  
}