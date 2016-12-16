// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "qizong.h"

void create()
{
        set_name("������", ({ "ai laozhe", "ai" }));
        set("title", HIG "��ɽ��ʮ��������" NOR);
        set("long", "�����ǻ�ɽ�ĳ��ϰ����ߡ�һ������"
                    "���ϵ�����������η��\n");
        set("gender", "����");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 31);
        set("int", 35);
        set("con", 31);
        set("dex", 32);
        set("age", 66);
        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 2600);
        set("max_jing", 2600);
        set("neili", 5200);
        set("max_neili", 5200);
        set("jiali", 70);
        set("level", 30);
        set("combat_exp", 1900000);
        set("score", 70000);

        set_skill("cuff", 610);
        set_skill("force", 610);
        set_skill("blade", 610);
        set_skill("sword", 620);
        set_skill("dodge", 610);
        set_skill("parry", 600);
        set_skill("strike", 610);
        set_skill("zixia-shengong", 610);
        set_skill("huashan-neigong", 610);
        set_skill("huashan-shenfa", 620);
        set_skill("huashan-quan", 650);
        set_skill("huashan-zhang", 650);
        set_skill("poyu-quan", 610);
        set_skill("fanliangyi-dao", 610);
        set_skill("huashan-sword", 620);
        set_skill("hunyuan-zhang", 610);
        set_skill("feiyan-huixiang", 610);
        set_skill("literate", 640);
        set_skill("jianyi", 610);
        set_skill("martial-cognize", 610);

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "fanliangyi-dao");
        map_skill("blade", "fanliangyi-dao");
        map_skill("sword", "huashan-sword");
        map_skill("strike", "hunyuan-zhang");

        create_family("��ɽ��", 12, "����");

        set("inquiry", ([
                "��ϼ��" : "���Ǳ������ϵ��ڹ��ķ�����˵��ϼ����ȱ������һҳ����ϧ���������޷���͸������\n",
                "����"     : "���˵�˵�Щ���᣿\n",
        ]));

        set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "blade.sanshen" :),
                (: perform_action, "strike.wuji" :),
                (: perform_action, "cuff.leidong" :),
                (: exert_function, "powerup" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
        string ob_fam;

        ob_fam=query("family/family_name", ob);
        if (! permit_recruit(ob))
                return;

        if (ob_fam == "��ɽ��" && ob->query_skill("zixia-shengong", 1) < 120)
        {
                command("say �ҿ������ϼ�񹦻�ûѧ���Ұɣ������б���"
                        "��ϼ�ؼ���������ж���");
                return;
        }

        if ((int)ob->query_skill("sword", 1) < 150)
        {
                command("say �ҿ���Ľ�����ûѧ���Ұɣ���������������"
                        "�û�����̸ʲô�ϳ˽�����");
                return;
        }

        if (ob_fam == "��ɽ��" && (int)ob->query_skill("huashan-sword", 1) < 150 ||
            ob_fam == "��ɽ����" && (int)ob->query_skill("kuangfeng-jian", 1) < 150)
        {
                command("say ��ɽ�����Ϳ�罣���Ǳ��ɵ��ӱ��뾫ͨ���似��������"
                        "������������");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say �һ�ɽ�����������������ɣ��Ե���Ҫ����"
                        "���ڵ��з��棬�㻹���ò�������");
                return;
        }

        if (ob_fam == "��ɽ����")
        {
                command("say �㿴���㣬Ҳ���˽���֮�����ܺ��ߣ��ú���ϰ�书����Щ������");
                delete("family", ob);
        }

        command("say �ðɣ��Ҿ��������ˣ���Ҫ�����ǻ�ɽ�ɵ�����");
        command("recruit " + query("id", ob));
        if( query("class", ob) != "fighter" )
                set("class", "fighter", ob);
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "���������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fanliangyi-dao/sanshen",
                           "name"    : "���������",
                           "sk1"     : "fanliangyi-dao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : 26000, ]));
                break;

        case "˫�����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fanliangyi-dao/hebi",
                           "name"    : "���������",
                           "sk1"     : "fanliangyi-dao",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 600,
                           "shen"    : 26000, ]));
                break;

        case "��Ԫ�޼�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hunyuan-zhang/wuji",
                           "name"    : "��Ԫ�޼�",
                           "sk1"     : "hunyuan-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1600,
                           "shen"    : 28000, ]));
                break;

        case "�����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/feng",
                           "name"    : "�����",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 60,
                           "force"   : 150,
                           "gongxian": 600,
                           "shen"    : 30000, ]));
                break;

        case "�׶�����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/lei",
                           "name"    : "�׶�����",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "��ʯһ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/poyu-quan/po",
                           "name"    : "��ʯһ��",
                           "sk1"     : "poyu-quan",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "����������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/lian",
                           "name"    : "����������",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        case "����ʽ" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huashan-sword/jie",
                           "name"    : "����ʽ",
                           "sk1"     : "huashan-sword",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : 60000, ]));
                break;

        default:
                return 0;
        }
}

#include "zhanglao.h"