// This program is a part of NT MudLIB
// goodsd.c
// Written by Lonely@nitan.org

#include <ansi.h>
#include <command.h>

inherit F_DBASE;

#define NAME            0
#define ID              1
#define VALUE           2
#define TYPE            3
#define FILE            4
#define DESC            5

#define VIP1_RATE       95
#define VIP2_RATE       88
#define VIP3_RATE       80
#define GOODS_FILE      CONFIG_DIR "goods_list"

class goods {
        string id;
        string name;
        int value;
        string file;
        string type;
        string desc;
        int number;
}

int rate = 100;
nosave class goods *all_goods = ({});
void init_goods();
int clean_up() { return 1; }
void set_rate(int r) { rate = r; }
int query_rate() { return rate; }

void create()
{
        seteuid(ROOT_UID);
        set("name", "�����̳�");
        init_goods();
}

void init_goods()
{
        class goods item;
        string *all, *tmp;
        string file;
        string line;
        int i, n;

        all_goods = ({});

        if( file_size(GOODS_FILE) <= 0 ) {
                log_file("static/goods",sprintf("GOODS_D: GOODS_FILE no exits or havn't content.%s\n",
                        ctime(time())));
                return;
        }

        file = read_file(GOODS_FILE);
        if( !stringp(file) ) return;

        file = replace_string(file, "\r", "");
        all =  filter_array(explode(file, "\n") - ({ "" }), (: $1[0] != '#' :));
        if( !n = sizeof(all) ) {
                log_file("static/goods",sprintf("GOODS_D: Have not valid goods. %s\n",
                        ctime(time())));
                return;
        }

        for( i=0;i<n;i++ ) {
                reset_eval_cost();
                line = all[i];

                //line = remove_fringe_blanks(line);
                while( strlen(line) && line[0] == ' ' ) line = line[1..<1];
                tmp = explode(line, ":");
                if( sizeof(tmp) < 4 ) {
                        log_file("static/goods", sprintf("%s isn't a full line.\n", line));
                        break;
                }

                item = new(class goods);
                item->name = tmp[NAME];
                item->id = tmp[ID];
                item->value = to_int(tmp[VALUE]);
                item->type = tmp[TYPE];
                if( sizeof(tmp) > FILE )
                        item->file = tmp[FILE];
                if( sizeof(tmp) > DESC )
                        item->desc = tmp[DESC];
                item->number = sizeof(all_goods) + 1;
                all_goods += ({ item });
        }
}

string chinese_type(string type)
{
        switch(type)
        {
        case "object"   : return HIC "��Ʒ" NOR;
        case "pill"     : return HIM "��ҩ" NOR;
        case "special"  : return HIG "���켼��" NOR;
        case "special2" : return HIB "ת������" NOR;
        case "special3" : return HIM "ͼ�ڼ���" NOR;
        case "story"    : return WHT "����" NOR;
        case "enchase"  : return HIW "��Ƕ" NOR;
        case "symbol"   : return YEL "���" NOR;
        case "card"     : return HIY "��Ա��" NOR;
        case "gold"     : return HIY "�ƽ�" NOR;
        case "prop"     : return HIY "װ��" NOR;
        case "module"   : return HIG "��װ" NOR;
        case "element"  : return HIG "Ԫ��" NOR;
        case "package"  : return HIR "���" NOR;
        case "srv"      : return HIM "����" NOR;
        case "other"    : return HIR "����" NOR;
        default         : return HIR "δ֪" NOR;
        }
}

void log_buyinfo(object ob, class goods item)
{
        string buyinfo;

        buyinfo = MEMBER_D->db_query_member(ob, "buyinfo");
        buyinfo += sprintf("%s(%s)��%s���� %d $NT������Ʒ %s 1��\n",
                           ob->name(1),
                           query("id", ob),
                           TIME_D->replace_ctime(time()),
                           item->value,
                           item->name);

        MEMBER_D->db_set_member(ob, "buyinfo", buyinfo);
        MEMBER_D->db_add_member(ob, "buytimes", 1);
        MEMBER_D->db_add_member(ob, "buyvalue", item->value);
        MEMBER_D->db_set_member(ob, "last_buytime", time());
        MEMBER_D->db_set_member(ob, "last_buyob", item->name);
        MEMBER_D->db_set_member(ob, "last_buyvalue", item->value);
        return;
}

public varargs int show_goods(object me, string arg)
{
        class goods item;
        string msg;
        int len = 0;

        if( !sizeof(all_goods) ) {
                tell_object(me, sprintf("Ŀǰ%sû�п������Ķ�����\n", query("name")));
                return 1;
        }

        if( !arg ) arg = "all";

        msg  = sprintf("%sĿǰ�������»��\n\n" NOR, query("name"));
        msg += sprintf(HIW "%-6s%-16s%-16s%-11s%-10s%s\n" NOR,
                      "���", "����", "����", "�۸�($NT)", "����", "���ܼ�Ҫ");
        msg += HIG "------------------------------------------------------------------------------------------\n\n" NOR;
        foreach( item in all_goods ) {
                if( item->type == arg || arg == "all"  )
                {
#ifndef LONELY_IMPROVED
                        len = color_len(chinese_type(item->type));
#endif
                        msg += sprintf(HIW"(%3d) "HIC"%-16s"HIW"%-16s" HIY "%-11d"NOR"%-"+(10+len)+"s"CYN"%-50s\n" NOR,
                                      item->number,
                                      item->name,
                                      item->id,
                                      item->value,
                                      chinese_type(item->type),
                                      item->desc);
                }
        }

        msg += "\n";
        msg += HIG "�������Ķ��й�˵��������ǰ�뿼������� ���޲����ˡ���˻���\n" NOR;
        msg += HIG "�й������̳ǵ�˵�����������߱�($NT)�ķ�ʽ��������ָ�� help ntstore �鿴��\n" NOR;
        msg += HIG "------------------------------------------------------------------------------------------\n" NOR;
        msg += HIY "��ǰ�������������Ʒ���ۿ��� " + rate + "%�����ջ���Ŷ��\n" NOR;
        me->start_more(msg);
        return 1;
}
// ����ָ��Ԫ��
void get_element_id(string arg, object ob, int value, int num, class goods item)
{
        mapping props;
        mapping data;
        object obj;
        string *ks;
        string str, my_id, my_name; 
        int i, n, flag = 0;
        
        if( !objectp(ob) ) return;

        if( !arg )
        {
                write(HIG "����������Ҫ�����Ԫ��ID�������֣���add_skill���������ܣ����˳�(q)��Ԫ�ر�����˳���help element ��ѯ ��" NOR);
                input_to("get_element_id", ob, value, num, item);
                return;
        }

        if( arg == "q" || arg == "Q" )
                return;
                        
        if( num == 2 ) str = "value_2_props";
        else if( num == 3 ) str = "value_3_props";
        else if( num == 5 ) str = "value_5_props";
        else if( num == 10 )str = "value_10_props";
        else return;
        
        props = fetch_variable(str, get_object(EQUIPMENT_D));
        if( !mapp(props) || sizeof(props) < 1 ) return;
        
        ks = keys(props);
        if( member_array(arg, ks) != -1 )
        {
                my_id = arg;
                my_name = EQUIPMENT_D->chinese(my_id)+"Ԫ��"; 
                data = ([]); 
                data["element"] = my_id;
                data["name"] = my_name; 
                obj = TEMPLATE_D->create_object("/inherit/template/element/element", my_id, data); 
                obj->set_name(my_name, ({my_id, "element"})); 
                if( !MEMBER_D->player_pay(ob, value) )
                {
                        write("\n������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        destruct(obj);
                        return;
                }
                obj->move(ob, 1); 
                log_buyinfo(ob, item);
                write(HIG "\n����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return;
        } 
        else
        {
                n = sizeof(ks);
                for( i=0;i<n;i++ )
                {
                        if( props[ks[i]] == arg )
                        {
                                flag = 1;
                                my_id = ks[i];
                                my_name = EQUIPMENT_D->chinese(my_id)+"Ԫ��"; 
                                data = ([]); 
                                data["element"] = my_id;
                                data["name"] = my_name; 
                                obj = TEMPLATE_D->create_object("/inherit/template/element/element", my_id, data); 
                                obj->set_name(my_name, ({my_id, "element"})); 
                                if( !MEMBER_D->player_pay(ob, value) )
                                {
                                        write("\n������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                                        destruct(obj);
                                        return;
                                }
                                obj->move(ob, 1); 
                                log_buyinfo(ob, item);
                                write(HIG "\n����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                                return;
                        }
                }       
        }
        write("û�����Ԫ�أ���help element�˲�����ԣ�\n");
        return;
}  
        
// ����ָ��ͭ��
void get_tongren_id(string arg, object ob, int value, class goods item)
{
        object obj;
        string file;

        if( !objectp(ob) ) return;

        if( !arg )
        {
                write(HIG "\n����������Ҫ�����ͭ�˱�ţ���b4,m5�����˳�(q)��ͭ�˱�����˳���ʹ��ָ�� jingmai bh ��ѯ ��" NOR);
                input_to("get_tongren_id", ob, value, item);
                return;
        }

        if( arg == "q" || arg == "Q" )
                return;

        file = "/clone/tongren/tongren_" + arg + ".c";

        if( file_size(file) < 0 )
        {
                write(HIR "\n�������ͭ�˱���������������룡\n" NOR);
                write(HIG "\n����������Ҫ�����ͭ�˱�ţ���b4,m5�����˳�(q)��ͭ�˱�����˳���ʹ��ָ�� jingmai bh ��ѯ ��" NOR);
                input_to("get_tongren_id", ob, value, item);
                return;
        }

        obj = new(file);
        if( !objectp(obj) )
        {
                write("\n������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                return;
        }

        if( !MEMBER_D->player_pay(ob, value) )
        {
                write("\n������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                destruct(obj);
                return;
        }

        obj->move(ob, 1);

        log_buyinfo(ob, item);
        write(HIG "\n����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
        write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
        return;
}

public int buy_goods(object ob, string arg)
{
        string which;
        object item;
        mixed specials;
        int value, level;
        int i, k, n, vip, money;

        n = sizeof(all_goods);
        if( !n ) {
                write(sprintf("Ŀǰ%sû�п������Ķ�����\n", query("name")));
                return 1;
        }

        if( !MEMBER_D->is_member(ob) ) {
                write("�㻹û�г�ֵ���йس�ֵ��ʽ��������ָ�� help store �鿴��\n");
                return 1;
        }

        for( i=0; i<n; i++ ) {
                if( all_goods[i]->id == arg
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg )
                        break;
        }

        if( i >= n ) {
                write(HIR "������ʲô�� ��ʹ�� store show all ��ѯ��\n" NOR);
                return 1;

        }

        if( all_goods[i]->type == "manual" ) {
                write("�Բ��𣬸÷�������� admin �ֶ�ʵ�֣��뼰ʱ�� admin ��ϵ��\n");
                return 1;
        }

        vip   = MEMBER_D->db_query_member(ob, "vip");
        money = MEMBER_D->db_query_member(ob, "money");
        value = all_goods[i]->value;
        value = value*rate/100;
        if( vip == 3) value = value*VIP3_RATE/100;
        else if( vip == 2) value = value*VIP2_RATE/100;
        else if( vip == 1) value = value*VIP1_RATE/100;

        if( value < 1 ) value = 1;
        if( money < value) {
                write("�Բ����������߱�($NT)����������\n");
                return 1;
        }

        switch(all_goods[i]->type)
        {
        case "package":
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 1;
                }

                switch( all_goods[i]->id )
                {
                case "newbie" :
                        item = new("/clone/gift/xuanhuang");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/gift/jiuzhuan");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/gift/tianxiang");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/gift/puti-zi");
                        item->set_amount(50);
                        item->move(ob, 1);
                        item = new("/clone/medicine/yuqing");
                        item->set_amount(1000);
                        item->move(ob, 1);
                        item = new("/clone/fam/max/zhenyu");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/fam/max/longjia");
                        item->set_amount(20);
                        item->move(ob, 1);
                        item = new("/clone/fam/max/xuanhuang");
                        item->set_amount(20);
                        item->move(ob, 1);
                        addn("time_reward/quest", 21600, ob);
                        addn("balance", 100000000, ob);
                        break;
                case "wisdom":
                        item = new("/clone/goods/wisdom_armor");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_head");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_boots");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_surcoat");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_waist");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_wrists");
                        item->move(ob, 1);
                        item = new("/clone/goods/wisdom_cloth");
                        item->move(ob, 1);
                        break;

                case "yj-sword" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_sword");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-blade" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_blade");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-hammer" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_hammer");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-staff" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_staff");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-club" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_club");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-whip" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_whip");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-finger" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_finger");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-hands" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/sun_hands");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-armor" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_armor");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-cloth" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_cloth");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-head" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_head");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-boots" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_boots");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-waist" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_waist");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-wrists" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_wrists");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-surcoat" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_surcoat");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-ring" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_ring");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-neck" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_neck");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                case "yj-charm" :
                        level=query("level", ob)/10*10;
                        if( level < 10 ) level = 10;
                        for (k = 0; k < 3; k++)
                        {
                                item = new("/clone/goods/moon_charm");
                                set("enchase/level", level, item);
                                item->move(ob, 1);
                        }
                        break;
                default :
                        break;
                }

                //log_buyinfo(ob, items[0], value);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "object":
        case "pill":
        case "symbol":
        case "enchase":
                which = all_goods[i]->id;
                item = new(all_goods[i]->file);
                if( !objectp(item) ) {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 1;
                }

                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        destruct(item);
                        return 1;
                }

                if (which == "arena")
                        item->set_amount(5);
                else
                if (which == "putizi")
                        item->set_amount(20);
                else
                if (which == "jiuzhuan")
                        item->set_amount(10);
                else
                if (which == "yuqingsan")
                        item->set_amount(120);
                else
                if (which == "tianxiang")
                        item->set_amount(10);
                else
                if (which == "xuanhuang")
                        item->set_amount(5);

                item->move(ob, 1);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;
        case "srv":
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 1;
                }

                switch( all_goods[i]->id )
                {
                case "quitsave" :
                        ob->set_srv("quit_save", 86400*93);
                        break;
                case "startroom" :
                        ob->set_srv("start_room", 86400*183);
                        break;
                case "jiutoushe_4" :
                        ob->set_srv("enter_jtshe", 3600*4);
                        break;
                case "jiutoushe_12" :
                        ob->set_srv("enter_jtshe", 3600*12);
                        break;
                case "jiutoushe" :
                        ob->set_srv("enter_jtshe", 86400*7);
                        break;
                case "qiankun" :
                        addn("srv/qiankun_volume", 1, ob);
                        break;
                case "srv01" :
                        addn("time_reward/quest", 10800, ob);
                        break;
                case "srv02" : 
                        addn("time_reward/quest", 604800, ob); 
                        break; 
                case "srv03" : 
                        addn("time_reward/study", 10800, ob); 
                        break; 
                case "srv04" : 
                        addn("time_reward/study", 604800, ob); 
                        break; 
                }

                log_buyinfo(ob, all_goods[i]);
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;
                
        case "element":
                switch( all_goods[i]->id )
                {
                case "element2" :
                        write(HIG "����������Ҫ�����Ԫ��ID�������֣���add_skill���������ܣ����˳�(q)��Ԫ�ر�����˳���help element ��ѯ ��" NOR);
                                input_to("get_element_id", ob, value, 2, all_goods[i]);
                        return 1;
                        break;
                case "element3" :
                        write(HIG "����������Ҫ�����Ԫ��ID�������֣���add_skill���������ܣ����˳�(q)��Ԫ�ر�����˳���help element ��ѯ ��" NOR);
                                input_to("get_element_id", ob, value, 3, all_goods[i]);
                        return 1;
                        break;
                case "element5" :
                        write(HIG "����������Ҫ�����Ԫ��ID�������֣���add_skill���������ܣ����˳�(q)��Ԫ�ر�����˳���help element ��ѯ ��" NOR);
                                input_to("get_element_id", ob, value, 5, all_goods[i]);
                        return 1;
                        break;
                case "element10":
                        write(HIG "����������Ҫ�����Ԫ��ID�������֣���add_skill���������ܣ����˳�(q)��Ԫ�ر�����˳���help element ��ѯ ��" NOR);
                                input_to("get_element_id", ob, value, 10, all_goods[i]);
                        return 1;
                        break;
                default :
                        break;
                }
                return 1;
                                
        case "other":
                switch( all_goods[i]->id )
                {
                case "tongren" :
                        write(HIG "����������Ҫ�����ͭ�˱�ţ���b4,m5�����˳�(q)��ͭ�˱�����˳���ʹ��ָ�� jingmai bh ��ѯ ��" NOR);
                                input_to("get_tongren_id", ob, value, all_goods[i]);
                        return 1;
                        break;
                case "cleardie" :
                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                                return 1;
                        }
                        delete("combat/last_die", ob);
                        delete("combat/dietimes", ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                        write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                        return 1;
                default :
                        break;
                }
                return 1;
                
        case "card":
                arg = all_goods[i]->id;
                if( arg != "monthcard"
                &&  arg  != "seasoncard"
                &&  arg != "yearcard"
                &&  arg != "forevercard" ) {
                        write("û���������͵Ļ�Ա����\n");
                        return 0;
                }

                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("����ħ��ʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 1;
                }

                if( arg == "monthcard")
                        MEMBER_D->db_fee_member(ob, 31);
                else
                if( arg == "seasoncard")
                        MEMBER_D->db_fee_member(ob, 92);
                else
                if( arg == "yearcard")
                        MEMBER_D->db_fee_member(ob, 365);
                else
                if( arg == "forevercard")
                        MEMBER_D->db_fee_member(ob, 365, 1);

                log_buyinfo(ob, all_goods[i]);
                write(HIG "����ɹ� �� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "story":
                if( query("gift/"+all_goods[i]->id, ob)){
                        write("���Ѿ��й�������ù����ˣ�\n");
                        return 0;
                }
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("�������ʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 0;
                }
                addn("gift/"+all_goods[i]->id, 1, ob);
                addn(all_goods[i]->file, 1, ob);
                log_buyinfo(ob, all_goods[i]);

                write(HIG "����ɹ� �� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "gold" :
                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("����ƽ�ʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 1;
                }

                addn("balance", 100000000, ob);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "����ɹ� �� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "special":
                specials=keys(query("special_skill", ob));

                if( member_array(all_goods[i]->id, specials) != -1 ) {
                        write("�Բ������Ѿ���������⼼���ˣ�\n");
                        return 0;
                }

                if( sizeof(specials) >= 10 ) {
                        write("�Բ���һ���ʺ����ֻ��ӵ��ʮ�����⼼�ܣ�\n");
                        return 0;
                }

                if( !MEMBER_D->player_pay(ob, value) ) {
                        write("�������켼��ʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 0;
                }

                set("special_skill/"+all_goods[i]->id, 1, ob);
                log_buyinfo(ob, all_goods[i]);
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "special2":
                if( !query("special_skill", ob) )
                        specials = 0;
                else
                        specials=keys(query("special_skill", ob));

                if( query("reborn/times", ob)){
                        if( sizeof(specials) > 0 ) {
                                if( member_array(all_goods[i]->id, specials) != -1 ) {
                                        write("�Բ������Ѿ���������������ˣ�\n");
                                        return 1;
                                }
                        }

                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("������������ʧ�ܣ����뱾վADMIN��ϵ��\n");
                                return 0;
                        }

                        set("special_skill/"+all_goods[i]->id, 1, ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                        write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                        return 1;
                } else {
                        write("��Ŀǰ�������޷������������ܣ����½⣡\n");
                        return 0;
                }

        case "special3":
                if( !query("special_skill", ob) )
                        specials = 0;
                else
                        specials=keys(query("special_skill", ob));

                if( !query("quest_tuteng/end2", ob)){
                        if( sizeof(specials) > 0 ) {
                                if( member_array(all_goods[i]->id, specials) != -1 ) {
                                        write("�Բ������Ѿ������ͼ���ؼ��ˣ�\n");
                                        return 1;
                                }
                        }

                        if( !MEMBER_D->player_pay(ob, value) ) {
                                write("����ͼ���ؼ�ʧ�ܣ����뱾վADMIN��ϵ��\n");
                                return 0;
                        }
                        
                        // ����֮��
		        if( all_goods[i]->id == "diwang" )
		        {
				addn("int", 2, ob);
				addn("str", 2, ob);
				addn("con", 2, ob);
				addn("dex", 2, ob);
		        }

                        set("special_skill/"+all_goods[i]->id, 1, ob);
                        set("quest_tuteng/end2", 1, ob);
                        log_buyinfo(ob, all_goods[i]);
                        write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buyinfo " HIG " ��ѯ�� \n" NOR);
                        write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                        return 1;
                } else {
                        write("�Բ����㲻���ٹ�����༼�ܣ�ͼ���ؼ����ˣ����ɹ���1������\n");
                        return 0;
                }
        default:
                write("��Ч��Ʒ���࣡\n");
                return 0;
        }
}

public int do_look(object me, string arg)
{
        int n, i;
        object item;

        if( me->is_busy() ) {
                write("������æ���أ�\n");
                return 1;
        }

        n = sizeof(all_goods);
        if( !n ) {
                write(sprintf("Ŀǰ%sû�п������Ķ�����\n", query("name")));
                return 1;
        }

        for( i=0; i<n; i++ ) {
                if( all_goods[i]->id == arg
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d",all_goods[i]->number) == arg ) {
                        break;
                }
        }

        if( i >= n ) {
                write("���뿴ʲô��\n");
                return 1;
        }

        if( all_goods[i]->type != "object" &&
            all_goods[i]->type != "pill" ) {
                write(HIM + all_goods[i]->name+"("+all_goods[i]->id +")\n" NOR);
                write(HIC "���ܼ�Ҫ��" + all_goods[i]->desc + "\n" NOR);
                write(HIY "�۸�" + all_goods[i]->value + " $NT\n\n" NOR);
                return 1;
        }

        catch(call_other(all_goods[i]->file, "???"));
        item = find_object(all_goods[i]->file);
        if( !objectp(item) ) {
                write("���۵���Ʒ���Բ鿴����������ADMIN��ϵ��\n");
                return 1;
        }

        LOOK_CMD->look_item(me, item);
        write(HIC "���ܼ�Ҫ��" + all_goods[i]->desc + "\n" NOR);
        write(HIY "�۸�" + all_goods[i]->value + " $NT\n\n" NOR);

        return 1;
}