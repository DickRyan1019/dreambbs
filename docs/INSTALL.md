# ��B�[����U

�o�g��󻡩��ֳt�w�˪���k,

��L�̷s�w�ˬ���������i�Ѧ�: https://github.com/ccns/dreamlandbbs/wiki ���e

�����P�²��e���̵L�p���ɳo�� source code �H�Τ��ְѦҤ�� ( �]�A Maple-itoc �����������оǸ�� )

�o��Ȩ̾ڥثe�i�H���զ��\���������ӰO��


## 0. �@�~�t�����ҡG

CentOS 5 ~ 7 32-bit �U���ӳ��i�H�˰_�� ( 7 �n�� Alt-Arch ���� )

Debian GNU/Linux 32 bit �U�ثe�٨S���sĶ���\@@ , �٦b���դ�


## 1. �w�˧@�~�t�Τά�������:

�@�~�t�γ����e�����L�F, �M�󳡤��h��ĳ���˦n 

`openssh-server` `nano` `vim` `make` `gcc` `git` `xinetd` ���{��


## 2. �إ� BBS �b��:

�ثe�����է�������b���إߦn, �H�קK�����v�����D

�H�U�Ȭ������ѦҤ�k�A�]�i�H `useradd` �B `groupadd` �����O���N�C


**== �H�U�� root �v�� !! ==**

    # mkdir /home/bbs
    # vipw

�Y�ϥ� Linux , �i��i�J�s�边��, �b�̫�@��[�W:

    bbs:x:9999:994:BBS Administrator:/home/bbs:/bin/bash

*(���D�O�I�_���ɶq�� /etc/passwd �̦C�X��L�ϥΪ̪��榡�@��)*

*(�]�n�`�N UID �O�_�P�ɮ׸̨�L���쪺�ϥΪ̭���, �H�K�X�{�v�����D)*


���U�ӽs�� `/etc/group` �ӼW�[�W�� `bbs` �s��, �ۤv�ثe�O�� `vim` �s��

�Y�������s�边���������]�i�� `nano` �Ψ�L��²�����s�边�����ӭק�

    # vim /etc/group

�b���ɳ̫�@��[�W:

    bbs:x:994:bbs

*(���D�O�I�_���� `/etc/group` �̦C�X��L�ϥΪ̪��榡�@��)*

*(�n�`�N UID �O�_�P�ɮ׸̨�L���쪺�ϥΪ̭���, �H�K�X�{�v�����D)*


�M��]�w bbs(�޲z��) ���K�X

    # passwd bbs

�O�o�N bbs ���a�ؿ��֦��̳]�w�����ۤv

    # chown -R bbs:bbs /home/bbs

�D���b�᳡���]�w����!


## 3. �U�� BBS �{��:

== �H�U�� bbs ���v���Y�i!! ==

    $ cd /home/bbs; git clone https://github.com/ccns/dreamlandbbs

���۶i�h dreamlandbbs �D�ؿ�

## 4. �]�w�sĶ�����ɮ�

���۱N�d�Ҹ̪��]�w�� `sample/config.h` �ƻs�� `include/` �ؿ��̫�,
�ǳƶ}�l�]�w�P�sĶ:

    $ cp sample/config.h include/

���۽s�� `include/config.h` �ɮ�:

    $ vim -c 'set fencs=big5' -c 'e!' src/include/config.h   ## �ĥ� lantw44.bbs<at>ptt.cc ����ĳ, ��vim�q�s�X�u�� Big5 �o�ؿ��

�t�`�N���M�צ��ϥαĥ� **BSD ���v����**�� piaip's more �\Ū�{�� (�b src/maple/pmore)

�Y�z�P�N�ӱ��v���Τ������ϥΤ覡�A�аȥ��N `include/config.h` ���������w�q�G

    #undef M3_USE_PMORE

�ץ���

    #define M3_USE_PMORE

�Y�z���P�N�ӱ��v�Τ��ݨϥθӮM��A�Цۦ�� `maple/Makefile` �̷Ӭ������ܭק�]�w�A

�Χ�H�U�C���O������ `Makefile` �ɮפ�, �S���sĶ pmore �M�� branch (�ثe�� `more.170818` )��A�H�K�~��w�ˡG

    $ git checkout more.170818

## 5. �T�{ BBS �ؿ��[�c�t�m

�]�w������, �����n��۰���sĶ���O, �ӬO���˵� BBS �a�ؿ��U�������ؿ����c, �T�{�w����t�m

�Y�z�� BBS �a�ؿ�( `/home/bbs` )�U�S������ source code ( `dreamlandbbs/` ) �H�~�����, 

�άO�|�����x������ BBS �B�@���n���ؿ����c, �i�Ѧҥ������ثe�b sample/bbs �U���d�ҥؿ�

���d�ҥؿ��O�M�� WindTopBBS-3.02-20040420-SNAP ���[�c�ӭק諸
( �Ѧҳs��: http://ftp.isu.edu.tw/pub/Unix/BBS/WindTop/WindTopBBS-3.02-20040420-SNAP.tgz )

�Y�o�{�������X���B, �Ц��\����{����, �A�ۦ�վ�ק�.

����H�U���O�i�Ͻd�ҥؿ��[�c�����w�˨� BBS �a�ؿ� �U:

    $ cp -r sample/bbs/* ~/;cp sample/bbs/.BRD ~/

## 6. �sĶ BBS ������

���۴N�}�l�sĶ�o!

    $ make clean linux install

�ثe���լO�b CentOS 32bit ���ҤU (Debian GNU/Linux 32bit �U�٨S�sĶ���\)
�p�G�����ܼƳ����w�q�쪺�|���ӴN�O�i�H���Q�sĶ����

## 7. �t�����ҽծջP�]�w

�M��O�o�t�ΰ��楿�`�Ƶ{:

    $ crontab sample/crontab

(�̭����]�w�վ��٦��ܦh�٨S��z,
 ��ĳ�ۦ��˵��̭����]�w�O�_�ŦX�ݨD, �H�Φۤv�վ�̭��@�ǵ{����������|)

�ܩ�b�]�wbbs�������Ҫ�����

�b�Ұ� bbsd �D�{���e, �аȥ��������{�����Ұ�

    $ /home/bbs/bin/camera
    $ /home/bbs/bin/account
    $ /home/bbs/bin/acpro
    $ /home/bbs/bin/makefw

�άO�ۦ殳 `sample/bbs/sh` �̭��� `start.sh` �o�� shell script �h����]�i�H

����n���� port 23 �� telnet �s�u����, �Х� root �v������:

    # /home/bbs/bin/bbsd

�Y�i, �Y�n���ѳs�u�� port �s�� > 3000, �h�H bbs �v������Y�i, �p:

    $ /home/bbs/bin/bbsd 3456

����}���۰ʰ��檺����, �i�H�Ѧ� `sample/bbs/sh/start.sh` �����e

�Φۤv�إ� `/etc/rc.d/rc.local` �ɮ׼g�i�h:

```

#! /bin/sh
# MapleBBS-WindTop-DreamBBS

su -c bbs '/home/bbs/bin/camera'
su -c bbs '/home/bbs/bin/account'
su -c bbs '/home/bbs/bin/acpro'
su -c bbs '/home/bbs/bin/makefw'

```

�ýT�{�w�� `rc.local` ���v���]�w���u�i����v(`+x`)

�ҥH�Y�n�� xinetd ����telnet�s�u�� BBS �D�{��, �i�ӥH�U�]�w:

(�w��xinetd�M���, �N�H�U���e�ƻs�� /etc/xinetd.d/telnet ��[�쥻�L���ɮ�])

```

service telnet
{
        disable         = no
        flags           = REUSE
        socket_type     = stream
        wait            = yes
        user            = bbs
        server          = /home/bbs/bin/bbsd
        server_args     = -i
}

```

�� standalone �Ұ�: �N /etc/rc.local �����e�A�[�W:

```

# �e��..
su -c bbs '/home/bbs/bin/bbsd 3456'  # �j��3000���ƥ�port�i�o�˳]�w
/home/bbs/bin/bbsd                   # port 23 �Ъ����� root �v���Ұ�

```

�z�פW����~���N�i�H�s�i�Ӧۤv�Ұʪ� BBS �{���F�C


���n�`�N CentOS �@�~�t�Τ��O�_�� `firewalld` `iptables` ��������]�w�צ�s�u

�Y���Цۤv�Ѿ\������ƶi��]�w�C

�ۤv�O��:

    # firewall-cmd --zone=public --permanent --add-port=23/tcp
    # firewall-cmd --zone=public --permanent --add-port=3456/tcp

���᪽�����s�Ұ�:

    # service firewalld restart 

�Y�i��������������]�w


�H�W���j�P�w�˰O���ԭz, �Y����L�ɥR, �N�|�ɧ֧�s������� (�Y����L�}�o���� branch �]�i�H�Ѧ�)

�w�靈����̸��L�ѦҨô��X������ĳ :)


