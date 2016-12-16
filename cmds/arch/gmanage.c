// Cmds:/cmds/usr/gmanage.c
 
inherit F_CLEAN_UP;

#ifndef GAMBLE_D
#define GAMBLE_D          "/adm/daemons/gambled"
#endif

int main(object me, string arg)
{

        if (! SECURITY_D->valid_grant(me, "(arch)")) 
                return 0; 

        GAMBLE_D->start_manage(me);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : gmanage 

����ָ�����ڹ�������ϵͳ��

HELP );
    return 1;
}