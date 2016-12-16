// clone/shop/hesanqi.c
// Last modified by winder 2003.10.20
// ��ҵϵͳ�ĳ����׶Σ�С������������ߡ�

inherit NPC;
inherit F_BANKER;

#include <ansi.h>;

int do_join(string arg);
int do_unjoin(string arg);
int do_yao();
int do_decide();

void create()
{
        set_name("������", ({ "he sanqi", "he", "sanqi" }));
        set("long", @LONG
�����㵴ɽ���ֺ����ߣ������������Ϊ����ѧ���书��������
�Ÿ���⽵����н������⸱��⽵��������ı�ǡ�����һ���书��
���Ըʵ�������С����������������˵�������Ǻ����ྴ����
������������⽵ĺ�ֹǧ�򣬵�������⽶������������ˣ�������
�Ǻ����߲����ˡ�
LONG);
        set("gender", "����");
        set("age", 59);
        set("attitude", "peaceful");
        set("per", 21);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 30);

        set("max_qi", 3500);
        set("max_jing", 2000);
        set("neili", 3000);
        set("max_neili", 300);
        set("jiali", 200);

        set("combat_exp", 500000);
        set("shen_type", 1);

        set_skill("hand", 140);
        set_skill("cuff", 140);
        set_skill("parry", 140);
        set_skill("dodge", 140);

        set_skill("changquan", 140);
        set_skill("sanshou", 140);
        set_skill("yanfly", 140);

        map_skill("parry", "changquan");
        map_skill("cuff", "changquan");
        map_skill("hand", "sanshou");
        map_skill("dodge", "yanfly");

        prepare_skill("cuff", "changquan");
        prepare_skill("hand", "sanshou");

        set("inquiry", ([
                "���"     : "�����⣬���Լ���("HIY"join"CYN")��ҵЭ�ᡣ\n"NOR,
                "����"     : "�����⣬���Լ���("HIY"join"CYN")��ҵЭ�ᡣ\n"NOR,
                "��ҵЭ��" : "�����⣬���Լ���("HIY"join"CYN")��ҵЭ�ᡣ\n"NOR,
        ]));

        create_family("�㵴��", 5, "����");

        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
}

void init()
{
        add_action("do_check", "check");
        add_action("do_check", "chazhang");
        add_action("do_convert", "convert");
        add_action("do_convert", "duihuan");
        add_action("do_deposit", "deposit");
        add_action("do_deposit", "cun");
        add_action("do_withdraw", "withdraw");
        add_action("do_withdraw", "qu");
        add_action("do_join", "join");
        add_action("do_decide", "decide");
        add_action("do_yao", "yao3");
        add_action("do_unjoin", "unjoin");
        delete_temp("busy");
}

int do_join(string arg)
{
        object me = this_player(), ob = this_object();

        if (! arg || arg != "��ҵЭ��")
                return notify_fail(CYN+query("name", ob)+"һ�㣬˵������Ҫ����ʲô������������ҵЭ�ᡣ\n"NOR);
        if( query("is_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"������ü��˵�����㲻���Ѿ�������ҵЭ����ô��\n"NOR);
        if( query("bad_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"��Цһ����˵������Ȼ���Ѿ���������ҵЭ�ᣬ�ֻ���������\n"NOR);
        tell_object(me,CYN+query("name", ob)+"���˵�ͷ��˵��������Ĵ���("HIY"decide"NOR+CYN")������ҵЭ��ô���ɿ�������ˣ�\n"NOR);
        set_temp("want_join", 1, me);
        return 1;
}

int do_unjoin(string arg)
{
        object me = this_player(), ob = this_object();

        if (! arg || arg != "��ҵЭ��")
                return notify_fail(CYN+query("name", ob)+"������ü��˵�������������ʲô��˵�����岻���ġ�\n"NOR);
        if( !query("is_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"��Цһ����û���㡣\n"NOR);
        tell_object(me,CYN+query("name", ob)+"̾�˿�����˵�������������ҵЭ�ᣬ�Ժ�ɲ��ܷ��ڡ��������("HIY"decide"NOR+CYN")��ô��ô��\n"NOR);
        set_temp("want_tuoli", 1, me);
        return 1;
}

int do_decide()
{
        object ob, me = this_player();

        if( query_temp("want_join", me) )
        {
                message_vision(HIC "$N" HIC "����$n" HIC "΢Ц�����������Ǯ������֮��Ժ�úøɰɡ�\n" NOR, this_object(), me);

                set("is_vendor", 1, me);
                delete_temp("want_join", me);

                ob = new(__DIR__"shangling");
                ob->move(this_object());
                command("giveshanglingto"+query("id", me));
                return 1;
        }
        else
                if( query_temp("want_tuoli", me) )
                {
                        message_vision(HIC "$N" CYN "����$n" HIC "���ͷ���˸���־���Ӵ��Ժ��������޹ϸ�\n" NOR, this_object(), me);
                        delete("is_vendor", me);
                        set("bad_vendor", 1, me);
                        delete_temp("want_tuoli", me);

                        if (objectp(ob = present("shang ling", me)));
                        {
                                message_vision(HIR "$N" HIR "��$n" HIR "��" NOR + ob->name(1) + HIR "ע���ˡ�\n" NOR, this_object(), me);
                                destruct(ob);
                        }
                        return 1;
                 }

         return notify_fail(CYN+query("name", ob)+"������һ�ۣ�������ü��û���㡣\n"NOR);
}

int do_yao()
{
        object ob, me = this_player();
        
        ob = this_object();
        if( query("bad_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"���ͷ������߿����߿������ֻ���������\n"NOR);

        if( !query("is_vendor", me) )
                return notify_fail(CYN+query("name", ob)+"������һ�ۣ�û���㡣\n"NOR);

        if (objectp(present("shang ling", me)))
                return notify_fail(CYN+query("name", ob)+"������ü�����ҵ��죬�����ⶼҪƭ����Ȼ�Ǽ��̵��ϡ�\n"NOR);

        if( query_temp("shang-ling", me) )
                return notify_fail(CYN+query("name", ob)+"��ü�����ղ��Ҳ��ǲŸ�����һ��ô����ô���Ū���ˣ�\n"NOR);

        if( SHOP_D->is_owner(query("id", me)) )
                return notify_fail(CYN+query("name", ob)+"΢Ц���������ڲ����Ѿ�������ô����Ҫ������\n"NOR);

        ob = new(__DIR__"shangling");
        ob->move(this_object());
        set_temp("shang-ling", 1, me);
        command("giveshanglingto"+query("id", me));
        command("say �Է��ļһ��Լ����ܺã������������ҡ�");
        return 1;
}