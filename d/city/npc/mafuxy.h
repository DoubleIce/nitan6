int do_ridexy()
{
        string hname;
        object ob = this_player();
        int i;
        string *yz_xy = ({
                HIC"�͵�"NOR,
                HIC"�����"NOR,
                HIC"����㳡"NOR,
                HIC"�����"NOR,
                HIC"�����"NOR,
                HIC"����"NOR,
                HIC"���Ŵ��"NOR,
                HIC"�����"NOR,
                HIC"���ȹ�"NOR,
                HIC"�ݵ�"NOR,
                HIC"��������"NOR,
                HIC"��������"NOR,
                HIC"�����"NOR,
                HIC"���ֽֿ�"NOR,
                HIC"���ڴ��"NOR,
        });
        if( query_temp("marks/horserent", ob) != 1 && query("age", ob)>14 )
                return notify_fail("С���Ӳſ��������������Ҫ��Ǯ��\n");
        switch (random(3))
        {
                case 1:
                        hname=MAG"������"NOR;
                        break;
                case 2:
                        hname=RED"�����"NOR;
                        break;
                default:
                        hname=HIY"������"NOR;
                        break;
        }
        message_vision(
"�������ָ�$Nǣ��һƥ"+hname+"��$N����Ծ����������������������·������һ��
���: �����ޡ�\n"NOR , ob );
        message_vision("\nֻ��$N������һ�У�"+hname+"�����͵��ȥ��\n",ob);
        for (i = 0;i < sizeof(yz_xy);i ++)
                tell_object(ob,yz_xy[i] + "\n");
        ob->move("/d/xiangyang/majiu");
        tell_room(environment(ob),query("name", ob)+"����"+hname+"һ·˳�����������ǡ�\n");
        message_vision("\n$N����һת��Ծ����������̬ʮ������������Ҳ��$Nһ��塣\n",ob);
        delete_temp("marks/horserent", ob);
        return 1;
}