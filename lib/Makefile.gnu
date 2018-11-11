# ------------------------------------------------------ #
#  lib/Makefile  ( NTHU CS MapleBBS Ver 3.00 )           #
# ------------------------------------------------------ #
#  author : opus.bbs@bbs.cs.nthu.edu.tw	                 #
#  target : Makefile for MapleBBS library routines       #
#  create : 95/03/29                                     #
#  update : 95/12/15                                     #
# ------------------------------------------------------ #

MAKE	+= -f Makefile.gnu

ARCHI	:= $(shell uname -m)

CC	= clang
RANLIB	= ranlib
CPROTO	= $(which cproto) -E\"clang -pipe -E\" -I../include
CFLAGS	= -O2 -pipe -fomit-frame-pointer -Wunused -Wno-invalid-source-encoding -I../include

ifeq ($(ARCHI),x86_64)
CFLAGS	+= -m32
else
ifeq ($(ARCHI),amd64)
CFLAGS	+= -m32
endif
endif

# ------------------------------------------------------ #
# �U�C�� make rules ���ݭק�                             #
# ------------------------------------------------------ #

HDR	= dao.h dao.p

SRC	= acl.c       chrono32.c  file.c    isnot.c     radix32.c  shm.c     url_encode.c \
	  archiv32.c  dl_lib.c    hash32.c  keeplog.c   record.c   splay.c   xsort.c      \
	  attr_lib.c  dns.c       header.c  mak_dirs.c  rfc2047.c  string.c  xwrite.c

OBJ	= acl.o       chrono32.o  file.o    isnot.o     radix32.o  shm.o     url_encode.o \
	  archiv32.o  dl_lib.o    hash32.o  keeplog.o   record.o   splay.o   xsort.o      \
	  attr_lib.o  dns.o       header.o  mak_dirs.o  rfc2047.o  string.o  xwrite.o

.c.o:	; $(CC) $(CFLAGS) -c $*.c


all:	libdao.a


dao.p:	$(SRC)
	$(CPROTO) $> | sed '/querybuf/d' > dao.p


libdao.a: $(OBJ)
	ar rv $@ $?
	$(RANLIB) $@


clean:
	rm -fr $(GARBAGE) $(OBJ) libdao.a *.bak *.BAK *~


tags:
	ctags $(SRC) ../include/*.h
