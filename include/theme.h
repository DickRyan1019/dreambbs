/*-------------------------------------------------------*/
/* theme.h      ( NTHU CS MapleBBS Ver 3.10 )            */
/*-------------------------------------------------------*/
/* target : custom theme                                 */
/* create : 09/07/28                                     */
/* update : 17/07/26                                     */
/*-------------------------------------------------------*/


#ifndef THEME_H
#define THEME_H

/* ----------------------------------------------------- */
/* �Ȧs��                                                */
/* ----------------------------------------------------- */

#define NEWMAILMSG              "\x1b[41;37;5m �l�t�Ķi�ӤF! \x1b[0;1;33;44m"
#define NEWPASSMSG              "\x1b[42;37;5m ���쯫���d��! \x1b[0;1;33;44m"

#define ICON_GAMBLED_BRD        "\x1b[1;31m��\x1b[m"    /* �|���L�����ݪO */
#define ICON_VOTED_BRD          "\x1b[1;33m��\x1b[m"    /* �|��벼�����ݪO */

//�U�@������ɶ�����
#define NEXTPUSHTIME 15

/* ----------------------------------------------------- */
/* ���C��w�q�A�H�Q�����ק�                            */
/* ----------------------------------------------------- */

#define ANSIRESET       "\x1b[m"        /* �פ��C�� */

#define COLOR1          "\x1b[34;46m"   /* footer/feeter ���e�q�C�� */
#define COLOR2          "\x1b[31;47m"   /* footer/feeter ����q�C�� */
#define COLOR3          "\x1b[30;47m"   /* neck ���C�� */
#define COLOR4          "\x1b[1;44m"    /* ���� ���C�� */
#define COLOR5          "\x1b[34;47m"   /* more ���Y�����D�C�� */
#define COLOR6          "\x1b[37;44m"   /* more ���Y�����e�C�� */
#define COLOR7          "\x1b[0m"       /* �@�̦b�u�W���C�� */


/* ----------------------------------------------------- */
/* �ϥΪ̦W���C��                                        */
/* ----------------------------------------------------- */

#define COLOR_PAL       "\x1b[1;32m"
#define COLOR_BAD       "\x1b[1;31m"
#define COLOR_CLOAK     "\x1b[1;35m"
#define COLOR_BOTH      "\x1b[1;36m"
#define COLOR_OPAL      "\x1b[1;33m"
#define COLOR_BOARDPAL  "\x1b[36m"

/* ----------------------------------------------------- */
/* ����m                                              */
/* ----------------------------------------------------- */



/* ----------------------------------------------------- */
/* �T���r��G*_neck() �ɪ� necker ����X�өw�q�b�o       */
/* ----------------------------------------------------- */

#define NECKBOARD  "  [��]�D��� [��]�\\Ū [����]��� [c]�g�� [y]���J [/]�j�M [s]�ݪO [h]����\n" \
                   "\x1b[30;47m  %-7s��  �O            %-33s�H�� �O    �D     \x1b[m"

//#define NECKGEM1 \
//                   "  [��]���} [��]�s�� [f]�Ҧ� [C]�Ȧs [F]��H [Z]�U�� [h]���� "

#define NECKGEM1 \
                   "  [��]���} [��]�s�� [f]�Ҧ� [C]�Ȧs [h]���� "
                   /*r2.20170802: disable some tips in case of confusion*/

#define NECKGEM2   "\x1b[44m" \
                   "  �s��     �D              �D                            [�s      ��] [��  ��]\x1b[m"

#define NECKPOST \
                   "  [��]���} [��]�\\Ū [^P]�o�� [b]�Ƨѿ� [d]�R�� [V]�벼 [TAB]��ذ� [h]����\n" \
                   "\x1b[30;47m  �s��    �� ��  �@  ��       ��  ��  ��  �D                                  \x1b[m"

#define NECKMAIL \
                   "  [��]���} [��]Ū�H [d]�R�� [R]�^�H [s]�H�H [x]��K [y]�s�զ^�H [h]����\n\x1b[44m" \
                   "  �s��    �� ��  �@ ��          �H  ��  ��  �D                                \x1b[m"

#define NECKVOTE \
                   "  [��]���} [v]�벼 [R]���G [E]�ק� [^P]�|�� [^Q]�d��/����/��� [h]����\n\x1b[44m" \
                   "  �s��  �}����  �D��H       ��  ��  �v  ��                                  \x1b[m"

#define NECKINNBBS "  [��]���} [^P]�s�W [d]�R�� [E]�s�� [/]�j�M [Enter]�Բ�\n" \
            COLOR3 "  �s��            ��         �e%*s                                               \x1b[m"


// cache.101119

#define NECKER_VOTE     "  [��]���} [R]���G [^P]�|�� [E]�ק� [V]�w�� [^Q]��� [o]�W�� [h]����\n" \

#define NECKER_VOTEALL  "  [��/��]�W�U [PgUp/PgDn]�W�U�� [Home/End]���� [��]�벼 [��][q]���}\n" \


/* ----------------------------------------------------- */
/* �T���r��Gmore() �ɪ� footer ����X�өw�q�b�o         */
/* ----------------------------------------------------- */


/* itoc.010914.����: ��@�g�A�ҥH�s FOOTER�A���O 78 char */

#define FOOTER_POST     \
    COLOR1 " �峹��Ū " COLOR2 " (ry)�^�� (=\\[]<>-+;'`)�D�D (|?QA)�j�M���D�@�� (kj)�W�U�g (C)�Ȧs   "

#define FOOTER_MORE     \
    COLOR1 " �s�� P.%d (%d%%) " COLOR2 " (h)���� [PgUp][PgDn][0][$]���� (/n)�j�M (C)�Ȧs (��q)���� "


/* ----------------------------------------------------- */
/* �T���r��Gxo_foot() �ɪ� feeter ����X�өw�q�b�o      */
/* ----------------------------------------------------- */


/* itoc.010914.����: �C��h�g�A�ҥH�s FEETER�A���O 78 char */

#define FEETER_INNBBS   \
    COLOR1 " ��H�]�w " COLOR2 " (��/��)�W�U (PgUp/PgDn)�W�U�� (Home/End)���� (��)(q)���}           "

#define FEETER_VOTEALL  \
    COLOR1 " �벼���� " COLOR2 " (��/��)�W�U (PgUp/PgDn)�W�U�� (Home/End)���� (��)�벼 (��)(q)���}  "

/* ----------------------------------------------------- */
/* ��ñ�G���x�ӷ�ñ�W                                    */
/* ----------------------------------------------------- */

#ifndef ORIGIN_TAG
#define ORIGIN_TAG \
    "--\n" \
    "\x1b[1;44;32m  ��\x1b[0;32;44m��   \x1b[1;37m�_�_     \x1b[30m�i�v�� �i�v�i �i�v�v �i�v�i �i�g�p �i   �i�v�i �i���i �i�v\x1b[31m�� \x1b[m\n" \
    "\x1b[1;32;44m��\x1b[42m��\x1b[0;44;32m�i��\x1b[1m��\x1b[0;32;44m�� \x1b[1;37m�_�_ \x1b[0;37;44m�i  �i �i�b�� �i�b�b �i�b�i �p�p�p �i   �i�b�i �i���i �i  �i \x1b[m\n" \
    "\x1b[1;36;42m�ڤ��j�a �G�G���| \x1b[37m�i�b�� �i  �i �i�b�b �i  �i �p�p�p �i�b �i  �i �i  �i �i�b�� \x1b[m\n" \
    "\x1b[1;32m�� Origin:\x1b[33m <bbs.ccns.ncku.edu.tw>  \x1b[31m�� From:\x1b[36m %-34.34s \x1b[m\n"
#endif  // ORIGIN_TAG

#define MODIFY_TAG    "\x1b[1;32m�� Modify: \x1b[33m<%s> \x1b[m%s"

#define ANONYMOUS_TAG "--\n\x1b[1;32m�� Origin: \x1b[33m%s \x1b[37m<%s> \x1b[m\n\x1b[1;31m�� From: \x1b[36m%s\x1b[m\n"

#define EMAIL_TAG     "\x1b[1;32m�� E-mail: \x1b[36m%s\x1b[m\n"

/* ----------------------------------------------------- */
/* ��L�T���r��                                          */
/* ----------------------------------------------------- */

//for M3_USE_PFTERM
#define FILEDFG            (0)
#define FILEDBG            (7)

#endif                          /* THEME_H */
