#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "dao.h"

char*
str_add(
  char* dst, 
  char* src
)
{
  while ((*dst = *src))
  {
    src++;
    dst++;
  }
  return dst;
}

void
str_ansi(         /* strip ANSI code */
  char* dst, 
  char* str,
  int max
  )
{
  int ch, ansi;
  char* tail;

  for (ansi = 0, tail = dst + max - 1; (ch = *str); str++)
  {
    if (ch == '\n')
    {
      break;
    }
    else if (ch == '\033')
    {
      ansi = 1;
    }
    else if (ansi)
    {
      if ((ch < '0' || ch > '9') && ch != ';' && ch != '[')
        ansi = 0;
    }
    else
    {
      *dst++ = ch;
      if (dst >= tail)
        break;
    }
  }
  *dst = '\0';
}

void
str_cat(
  char* dst,
  char* s1,
  char* s2
)
{
  while ((*dst = *s1))
  {
    s1++;
    dst++;
  }

  while ((*dst++ = *s2++))
    ;
}
int
str_cmp(
  char* s1, 
  char* s2
)
{
  int c1, c2, diff;

  do
  {
    c1 = *s1++;
    c2 = *s2++;
    if (c1 >= 'A' && c1 <= 'Z')
      c1 |= 32;
    if (c2 >= 'A' && c2 <= 'Z')
      c2 |= 32;
    if ((diff = c1 - c2))
      return (diff);
  } while (c1);
  return 0;
}

/*-------------------------------------------------------*/
/* lib/str_decode.c	( NTHU CS MapleBBS Ver 3.00 )	 */
/*-------------------------------------------------------*/
/* target : included C for QP/BASE64 decoding		 */
/* create : 95/03/29				 	 */
/* update : 97/03/29				 	 */
/*-------------------------------------------------------*/

/* ----------------------------------------------------- */
/* QP code : "0123456789ABCDEF"				 */
/* ----------------------------------------------------- */


static int
qp_code(
  register int x
)
{
  if (x >= '0' && x <= '9')
    return x - '0';
  if (x >= 'a' && x <= 'f')
    return x - 'a' + 10;
  if (x >= 'A' && x <= 'F')
    return x - 'A' + 10;
  return -1;
}


/* ------------------------------------------------------------------ */
/* BASE64 :							      */
/* "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" */
/* ------------------------------------------------------------------ */


static int
base64_code(
  register int x
)
{
  if (x >= 'A' && x <= 'Z')
    return x - 'A';
  if (x >= 'a' && x <= 'z')
    return x - 'a' + 26;
  if (x >= '0' && x <= '9')
    return x - '0' + 52;
  if (x == '+')
    return 62;
  if (x == '/')
    return 63;
  return -1;
}


/* ----------------------------------------------------- */
/* 取 encode / charset					 */
/* ----------------------------------------------------- */


static inline int
isreturn(
  unsigned char c
)
{
  return c == '\r' || c == '\n';
}


static inline int 
is_space(
  unsigned char c
)
{
  return c == ' ' || c == '\t' || isreturn(c);
}


/* 取Content-Transfer-Encode 的第一個字元, 依照標準只可能是 q,b,7,8 這四個 */
char*
mm_getencode(
  unsigned char* str,
  char* code
)
{
  if (str)
  {
    /* skip leading space */
    while (is_space(*str))
      str++;

    if (!str_ncmp(str, "quoted-printable", 16))
    {
      *code = 'q';
      return str + 16;
    }
    if (!str_ncmp(str, "base64", 6))
    {
      *code = 'b';
      return str + 6;
    }
  }

  *code = 0;
  return str;
}


/* 取 charset */
void
mm_getcharset(
  const char* str,
  char* charset,
  int size		/* charset size */
)
{
  char* src, *dst, *end;
  char delim;
  int ch;

  *charset = '\0';

  if (!str)
    return;

  if (!(src = (char* ) strstr(str, "charset=")))
    return;

  src += 8;
  dst = charset;
  end = dst + size - 1;	/* 保留空間給 '\0' */
  delim = '\0';

  while ( (ch = *src++) )
  {
    if (ch == delim)
      break;

    if (ch == '\"')
    {
      delim = '\"';
      continue;
    }

    if (!is_alnum(ch) && ch != '-')
      break;

    *dst = ch;

    if (++dst >= end)
      break;
  }

  *dst = '\0';

  if (!str_cmp(charset, "iso-8859-1"))	/* 歷史包伏不可丟 */
    *charset = '\0';
}


/* ----------------------------------------------------- */
/* judge & decode QP / BASE64				 */
/* ----------------------------------------------------- */


/* PaulLiu.030410: 
   RFC 2047 (Header) QP 部分，裡面規定 '_' 表示 ' ' (US_ASCII的空白)
   而 RFC 2045 (Body) QP 部分，'_' 還是 '_'，沒有特殊用途
   所以在此 mmdecode 分二隻寫
*/

/* 解 Header 的 mmdecode */
static int
mmdecode_header(
  unsigned char* src,		/* Thor.980901: src和dst可相同, 但src一定有?或\0結束 */
  unsigned char encode,		/* Thor.980901: 注意, decode出的結果不會自己加上 \0 */
  unsigned char* dst
)
{
  unsigned char* t;
  int pattern, bits;
  int ch;

  t = dst;
  encode |= 0x20;		/* Thor: to lower */

  switch (encode)
  {
  case 'q':			/* Thor: quoted-printable */

    while ((ch = *src) && ch != '?')	/* Thor: Header 裡面 0 和 '?' 都是 delimiter */
    {
      if (ch == '=')
      {
	int x, y;

	x = *++src;
	y = x ? *++src : 0;
	if (isreturn(x))
	  continue;

	if ((x = qp_code(x)) < 0 || (y = qp_code(y)) < 0)
	  return -1;

	*t++ = (x << 4) + y;
      }
      else if (ch == '_')	/* Header 要把 '_' 換成 ' ' */
      {
	*t++ = ' ';
      }
      else
      {
	*t++ = ch;
      }
      src++;
    }
    return t - dst;

  case 'b':			/* Thor: base 64 */

    /* Thor: pattern & bits are cleared outside while() */
    pattern = 0;
    bits = 0;

    while ((ch = *src) && ch != '?')	/* Thor: Header 裡面 0 和 '?' 都是 delimiter */
    {
      int x;

      x = base64_code(*src++);
      if (x < 0)		/* Thor: ignore everything not in the base64,=,.. */
	continue;

      pattern = (pattern << 6) | x;
      bits += 6;		/* Thor: 1 code gains 6 bits */
      if (bits >= 8)		/* Thor: enough to form a byte */
      {
	bits -= 8;
	*t++ = (pattern >> bits) & 0xff;
      }
    }
    return t - dst;
  }

  return -1;
}


int
mmdecode(	/* 解 Header 的 mmdecode */
  unsigned char* src,		/* Thor.980901: src和dst可相同, 但src一定有?或\0結束 */
  unsigned char encode,		/* Thor.980901: 注意, decode出的結果不會自己加上 \0 */
  unsigned char* dst
)
{
  unsigned char* t;
  int pattern, bits;
  int ch;

  t = dst;
  encode |= 0x20;		/* Thor: to lower */

  switch (encode)
  {
  case 'q':			/* Thor: quoted-printable */

    while ( (ch = *src) )		/* Thor: 0 是 delimiter */
    {
      if (ch == '=')
      {
	int x, y;

	x = *++src;
	y = x ? *++src : 0;
	if (isreturn(x))
	  continue;

	if ((x = qp_code(x)) < 0 || (y = qp_code(y)) < 0)
	  return -1;

	*t++ = (x << 4) + y;
      }
      else
      {
	*t++ = ch;
      }
      src++;
    }
    return t - dst;

  case 'b':			/* Thor: base 64 */

    /* Thor: pattern & bits are cleared outside while() */
    pattern = 0;
    bits = 0;

    while ( (ch = *src) )		/* Thor: 0 是 delimiter */
    {
      int x;

      x = base64_code(*src++);
      if (x < 0)		/* Thor: ignore everything not in the base64,=,.. */
	continue;

      pattern = (pattern << 6) | x;
      bits += 6;		/* Thor: 1 code gains 6 bits */
      if (bits >= 8)		/* Thor: enough to form a byte */
      {
	bits -= 8;
	*t++ = (pattern >> bits) & 0xff;
      }
    }
    return t - dst;
  }

  return -1;
}


void
str_decode(
  unsigned char* str
)
{
  int adj;
  unsigned char* src, *dst;
  unsigned char buf[512];

  src = str;
  dst = buf;
  adj = 0;

  while (*src && (dst - buf) < sizeof(buf) - 1)
  {
    if (*src != '=')
    {				/* Thor: not coded */
      unsigned char* tmp = src;
      while (adj && *tmp && is_space(*tmp))
	tmp++;
      if (adj && *tmp == '=')
      {				/* Thor: jump over space */
	adj = 0;
	src = tmp;
      }
      else
	*dst++ = *src++;
    }
    else			/* Thor: *src == '=' */
    {
      unsigned char* tmp = src + 1;
      if (*tmp == '?')		/* Thor: =? coded */
      {
	/* "=?%s?Q?" for QP, "=?%s?B?" for BASE64 */
	tmp++;
	while (*tmp && *tmp != '?')
	  tmp++;
	if (*tmp && tmp[1] && tmp[2] == '?')	/* Thor: *tmp == '?' */
	{
	  int i = mmdecode_header(tmp + 3, tmp[1], dst);
	  if (i >= 0)
	  {
	    tmp += 3;		/* Thor: decode's src */
	    while (*tmp && *tmp++ != '?');	/* Thor: no ? end, mmdecode_header -1 */
	    /* Thor.980901: 0 也算 decode 結束 */
	    if (*tmp == '=')
	      tmp++;
	    src = tmp;		/* Thor: decode over */
	    dst += i;
	    adj = 1;		/* Thor: adjcent */
	  }
	}
      }

      while (src != tmp)	/* Thor: not coded */
	*dst++ = *src++;
    }
  }
  *dst = 0;
  strcpy(str, buf);
}


#if 0
int
main()
{
  char buf[1024] = "=?Big5?B?pl7C0CA6IFtNYXBsZUJCU11UbyB5dW5sdW5nKDE4SzRGTE0pIFtWQUxJ?=\n\t=?Big5?B?RF0=?=";

  str_decode(buf);
  puts(buf);

  buf[mmdecode("=A7=DA=A4@=AA=BD=B8I=A4=A3=A8=EC=A7=DA=BE=C7=AA=F8", 'q', buf)] = '\0';
  puts(buf);
}
#endif


char*
str_dup(
  char* src,
  int pad
)
{
  char* dst;

  dst = (char* ) malloc(strlen(src) + pad);
  strcpy(dst, src);
  return dst;
}

void
str_folder(
  char* fpath,
  char* folder,
  char* fname
)
{
  int ch;
  char* token = NULL;

  while ((ch = *folder++))
  {
    *fpath++ = ch;
    if (ch == '/')
      token = fpath;
  }
  if (*token != '.')
    token -= 2;
  strcpy(token, fname);
}

void
setdirpath(
  char* fpath, 
  char* direct, 
  char* fname
)
{
  int ch;
  char* target = NULL;

  while ((ch = *direct))
  {
    *fpath++ = ch;
    if (ch == '/')
      target = fpath;
    direct++;
  }

  strcpy(target, fname);
}
/* ----------------------------------------------------  */
/* E-mail address format				 */
/* ----------------------------------------------------  */
/* 1. user@domain					 */
/* 2. <user@domain>					 */
/* 3. user@domain (nick)				 */
/* 4. user@domain ("nick")				 */
/* 5. nick <user@domain>				 */
/* 6. "nick" <user@domain>				 */
/* ----------------------------------------------------  */

int
str_from(
  char* from, 
  char* addr, 
  char* nick
)
{
  char* str, *ptr, *langle;
  int cc;

  *nick = 0;

  langle = ptr = NULL;

  for (str = from; (cc = *str); str++)
  {
    if (cc == '<')
      langle = str;
    else if (cc == '@')
      ptr = str;
  }

  if (ptr == NULL)
  {
    strcpy(addr, from);
    return -1;
  }

  if (langle && langle < ptr && str[-1] == '>')
  {
    /* case 2/5/6 : name <mail_addr> */

    str[-1] = 0;
    if (langle > from)
    {
      ptr = langle - 2;
      if (*from == '"')
      {
	from++;
	if (*ptr == '"')
	  ptr--;
      }
      if (*from == '(')
      {
	from++;
	if (*ptr == ')')
	  ptr--;
      }
      ptr[1] = '\0';
      strcpy(nick, from);
      str_decode((unsigned char* )nick);
    }

    from = langle + 1;
  }
  else
  {
    /* case 1/3/4 */

    if (*--str == ')')
    {
      if (str[-1] == '"')
	str--;
      *str = 0;

      if ((ptr = (char* ) strchr(from, '(')))
      {
	ptr[-1] = 0;
	if (*++ptr == '"')
	  ptr++;

	strcpy(nick, ptr);
	str_decode((unsigned char* )nick);
      }
    }
  }

  strcpy(addr, from);
  return 0;
}

int
str_has(
  char* list,
  char* tag
)
{
  int cc, len;

    len = strlen(tag);
    for (;;)
    {
      cc = list[len];
      if ((!cc || cc == '/') && !str_ncmp(list, tag, len))
	return 1;

      for (;;)
      {
	cc = *list;
	if (!cc)
	  return 0;
	list++;
	if (cc == '/')
	  break;
      }
    }
}
int
str_hash2(
  char* str,
  int seed
)
{
  int cc;

  while ((cc = *str++))
  {
    seed = (seed << 7) - seed + cc;	/* 127 * seed + cc */
  }
  return (seed & 0x7fffffff);
}

int
str_hash(
  char* str,
  int seed
)
{
  int cc;

  while ((cc = *str++))
  {
    seed = (seed << 5) - seed + cc;	/* 31 * seed + cc */
  }
  return (seed & 0x7fffffff);
}

int
str_len(
  char* str
)
{
  int cc, len;

  for (len = 0; (cc = *str); str++)
  {
    if (cc != ' ')
      len++;
  }

  return len;
}

void
str_lower(
  char* dst, 
  char* src
)
{
  int ch;

  do
  {
    ch = *src++;
    if (ch >= 'A' && ch <= 'Z')
      ch |= 0x20;
    *dst++ = ch;
  } while (ch);
}

void
str_lowest(
  char* dst,
  char* src
)
{
  int ch;
  int in_chi = 0;	/* 1: 前一碼是中文字 */

  do
  {
    ch = *src++;
    if (in_chi || ch & 0x80)
      in_chi ^= 1;
    else if (ch >= 'A' && ch <= 'Z')
      ch |= 0x20;
    *dst++ = ch;
  } while (ch);
}

int
str_ncmp(
  char* s1, 
  char* s2,
  int n
)
{
  int c1, c2;

  while (n--)
  {
    c1 = *s1++;
    if (c1 >= 'A' && c1 <= 'Z')
      c1 |= 32;

    c2 = *s2++;
    if (c2 >= 'A' && c2 <= 'Z')
      c2 |= 32;

    if (c1 -= c2)
      return (c1);

    if (!c2)
      break;
  }

  return 0;
}

/*
 * str_ncpy() - similar to strncpy(3) but terminates string always with '\0'
 * if n != 0, and doesn't do padding
 */
void
str_ncpy(
  char* dst,
  char* src,
  int n
)
{
  char* end;

  end = dst + n - 1;

  do
  {
    n = (dst >= end) ? 0 : *src++;
    *dst++ = n;
  } while (n);
}

char*
str_ndup(
  char* src,
  int len
)
{
  char* dst, *str, *end;

  str = src;
  end = src + len;
  do
  {
    if (!*str++)
    {
      end = str;
      break;
    }
  } while (str < end);

  dst = (char* ) malloc(end - src);

  for (str = dst; (*str = *src); src++)
  {
    str++;
    if (src >= end)
    {
      *str = '\0';
      break;
    }
  }

  return dst;
}

#ifndef	PASSLEN
#define	PASSLEN 14
#endif


/* ----------------------------------------------------- */
/* password encryption					 */
/* ----------------------------------------------------- */

char* crypt();
static char pwbuf[PASSLEN];

char* 
genpasswd(
  char* pw
)
{
  char saltc[2];
  int i, c;

  if (!*pw)
    return pw;

  i = 9 * getpid();
  saltc[0] = i & 077;
  saltc[1] = (i >> 6) & 077;

  for (i = 0; i < 2; i++)
  {
    c = saltc[i] + '.';
    if (c > '9')
      c += 7;
    if (c > 'Z')
      c += 6;
    saltc[i] = c;
  }
  strcpy(pwbuf, pw);
  return crypt(pwbuf, saltc);
}


/* Thor.990214: 註解: 合密碼時, 傳回0 */
int
chkpasswd(
  char* passwd,
  char* test
)
{
  char* pw;
  
  /* if(!*passwd) return -1 */ /* Thor.990416: 怕有時passwd是空的 */
  str_ncpy(pwbuf, test, PASSLEN);
  pw = crypt(pwbuf, passwd);
  return (strncmp(pw, passwd, PASSLEN));
}
/* str_pat : wild card string pattern match support ? * \ */




int
str_pat(
  const char* str,
  const char* pat
)
{
  const char* xstr = NULL, *xpat;
  int cs, cp;

  xpat = NULL;

  while ((cs = *str))
  {
    cp = *pat++;
    if (cp == '*')
    {
      for (;;)
      {
	cp = *pat;

	if (cp == '\0')
	  return 1;

	pat++;

	if (cp != '*')
	{
	  xpat = pat;
	  xstr = str;
	  break;
	}
      }
    }

    str++;

    if (cp == '?')
      continue;

    if (cp == '\\')
      cp = *pat++;

#ifdef	CASE_IN_SENSITIVE
    if (cp >= 'A' && cp <= 'Z')
      cp += 0x20;

    if (cs >= 'A' && cs <= 'Z')
      cs += 0x20;
#endif

    if (cp == cs)
      continue;

    if (xpat == NULL)
      return 0;

    pat = xpat;
    str = ++xstr;
  }

  while ((cp = *pat))
  {
    if (cp != '*')
      return 0;

    pat++;
  }

  return 1;
}

#if 0
#define	STR_PAT(x, y)	printf("<%s, %s> : %d\n", x, y, str_pat(x, y))

main()
{
  STR_PAT("a", "a*");
  STR_PAT("abc", "a*");
  STR_PAT("abc", "a*c");
  STR_PAT("abc", "a?c");
  STR_PAT("level", "l*l");
  STR_PAT("level", "l*e*l");
  STR_PAT("lelelelel", "l*l*l*l");
}
#endif	/* TEST */
/* reverse the string */

char*
str_rev(
  char* dst,
  char* src
)
{
  int cc;

  *dst = '\0';

  while ((cc = *src))
  {
    *--dst = cc;
    src++;
  }
  return dst;
}

int
str_rle(			/* run-length encoding */
	unsigned char* str
)
{
	unsigned char* src, *dst;
	int cc, rl;

	dst = src = str;
	while ((cc = *src++))
	{
		if (cc > 8 && cc == src[0] && cc == src[1] && cc == src[2])
		{
			src += 2;
			rl = 4;
			while (*++src == cc)
			{
				if (++rl >= 255)
					break;
			}

			*dst++ = 8;
			*dst++ = rl;
		}
		*dst++ = cc;
	}

	*dst = '\0';
	return dst - str;
}

/* ------------------------------------------ */
/* mail / post 時，依據時間建立檔案，加上郵戳 */
/* ------------------------------------------ */
/* Input: fpath = directory;		      */
/* Output: fpath = full path;		      */
/* ------------------------------------------ */

void
str_stamp(
  char* str,
  time_t *chrono
)
{
  struct tm *ptime;

  ptime = localtime(chrono);
  /* Thor.990329: y2k */
  sprintf(str, "%02d/%02d/%02d",
    ptime->tm_year % 100, ptime->tm_mon + 1, ptime->tm_mday);
}

#ifndef	NULL
#define	NULL	(char* ) 0
#endif

char*  
str_str( 
  char* str, 
  char* tag                  /* non-empty lower case pattern */ 
)
{ 
  int cc, c1, c2;
  char* p1, *p2;

  cc = *tag++;
 
  while ((c1 = *str))
  {
    if (c1 >= 'A' && c1 <= 'Z')
      c1 |= 0x20;

    if (c1 == cc)
    {
      p1 = str;
      p2 = tag;

      do
      {
        c2 = *p2;
        if (!c2)
          return str;
 
        p2++;
        c1 = *++p1;
        if (c1 >= 'A' && c1 <= 'Z')
          c1 |= 0x20;
      } while (c1 == c2);
    }
 
    str++;
  }

  return NULL;
}

char*  
str_sub(
  char* str, 
  char* tag		/* non-empty lowest case pattern */ 
)
{ 
  int cc, c1, c2;
  char* p1, *p2;
  int in_chi = 0;	/* 1: 前一碼是中文字 */
  int in_chii;		/* 1: 前一碼是中文字 */

  cc = *tag++;
 
  while ( (c1 = *str) )
  {
    if (in_chi)
    {
      in_chi ^= 1;
    }
    else
    {
      if (c1 & 0x80)
	in_chi ^= 1;
      else if (c1 >= 'A' && c1 <= 'Z')
	c1 |= 0x20;

      if (c1 == cc)
      {
	p1 = str;
	p2 = tag;
	in_chii = in_chi;

	do
	{
	  c2 = *p2;
 	  if (!c2)
	    return str;
 
	  p2++;
	  c1 = *++p1;
	  if (in_chii || c1 & 0x80)
	    in_chii ^= 1;
	  else if (c1 >= 'A' && c1 <= 'Z')
	    c1 |= 0x20;
	} while (c1 == c2);
      }
    }
 
    str++;
  }

  return NULL;
}

char* 
str_tail(
  char* str
)
{
  while (*str)
  {
    str++;
  }
  return str;
}


/* static char datemsg[32]; */
static char datemsg[40];

char* 
Btime(
  time_t *clock
)
{
  struct tm *t = localtime(clock);

  /* Thor.990329: y2k */
  /* Thor.990413: 最後的空格是用在 mail.c的bsmtp末, 在時間和user間空一格用,
                  嗯... 不知道放在這的好處是不是連空格也一起共用:P */
  sprintf(datemsg, "%02d/%02d/%02d%3d:%02d:%02d ",
    t->tm_year % 100, t->tm_mon + 1, t->tm_mday,
    t->tm_hour, t->tm_min, t->tm_sec);
  return (datemsg);
}


char* 
Ctime(
  time_t *clock
)
{
  struct tm *t = localtime(clock);
  static char week[] = "日一二三四五六";

  sprintf(datemsg, "%d年%2d月%2d日%3d:%02d:%02d 星期%.2s",
    t->tm_year - 11, t->tm_mon + 1, t->tm_mday,
    t->tm_hour, t->tm_min, t->tm_sec, &week[t->tm_wday << 1]);
  return (datemsg);
}

char* 
Etime(
  time_t *clock
)
{
  strftime(datemsg, 22, "%D %T %a", localtime(clock));
  return (datemsg);
}

char* 
Atime( /* Thor.990125: 假裝ARPANET時間格式 */
  time_t *clock
)
{
  /* ARPANET format: Thu, 11 Feb 1999 06:00:37 +0800 (CST) */
  /* strftime(datemsg, 40, "%a, %d %b %Y %T %Z", localtime(clock)); */
  /* Thor.990125: time zone的傳回值不知和ARPANET格式是否一樣,先硬給,同sendmail*/
  strftime(datemsg, 40, "%a, %d %b %Y %T +0800 (CST)", localtime(clock));
  return (datemsg);
}

char* 
Now(void)
{
  time_t now;

  time(&now);
  return Btime(&now);
}

void
str_trim(			/* remove trailing space */
  char* buf
)
{
  char* p = buf;

  while (*p)
    p++;
  while (--p >= buf)
  {
    if (*p == ' ')
      *p = '\0';
    else
      break;
  }
}

char* 
str_ttl(
  char* title
)
{
  if (title[0] == 'R' && title[1] == 'e' && title[2] == ':')
  {
    title += 3;
    if (*title == ' ')
      title++;
  }

  return title;
}

/*-------------------------------------------------------*/ 
/* lib/str_xor.c     ( NTHU CS MapleBBS Ver 3.10 )   	 */ 
/*-------------------------------------------------------*/ 
/* author : thor.bbs@bbs.cs.nthu.edu.tw			 */
/* target : included C for str xor-ing (signed mail)	 */ 
/* create : 99/03/30                                     */ 
/* update :   /  /                                       */ 
/*-------------------------------------------------------*/ 
 
//unsigned char* 
void
str_xor(
  unsigned char* dst, /* Thor.990409: 任意長度任意binary seq, 至少要 src那麼長*/
  unsigned char* src  /* Thor.990409: 任意長度str, 不含 \0 */
                      /* Thor: 結果是將src xor到dst上, 若有0結果, 則不變 ,
			       所以dst長度必大於等於 src(以字串而言) */
)
{
  register int cc;
  for(; *src; src++, dst++)
  { 
    if ((cc = *src ^ *dst))
      *dst = cc;
  } 
} 

#if 0
main()
{
  char t[]="Hello";
  printf(str_xor(t,"he3"));
}
#endif

/* strlcat based on OpenBSDs strlcat */

/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(src) + MIN(siz, strlen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
size_t
strlcat(char* dst, const char* src, size_t siz)
{
        char* d = dst;
        const char* s = src;
        size_t n = siz;
        size_t dlen;

        /* Find the end of dst and adjust bytes left but don't go past end */
        while (n-- != 0 && *d != '\0')
                d++;
        dlen = d - dst;
        n = siz - dlen;

        if (n == 0)
                return(dlen + strlen(s));
        while (*s != '\0') {
                if (n != 1) {
                        *d++ = *s;
                        n--;
                }
                s++;
        }
        *d = '\0';

        return(dlen + (s - src));        /* count does not include NUL */
}

/* strlcpy based on OpenBSDs strlcpy */
/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */

size_t
strlcpy(char* dst, const char* src, size_t siz)
{
        char* d = dst;
        const char* s = src;
        size_t n = siz;

        /* Copy as many bytes as will fit */
        if (n != 0 && --n != 0) {
                do {
                        if ((*d++ = *s++) == 0)
                                break;
                } while (--n != 0);
        }

        /* Not enough room in dst, add NUL and traverse rest of src */
        if (n == 0) {
                if (siz != 0)
                        *d = '\0';                /* NUL-terminate dst */
                while (*s++)
                        ;
        }

        return(s - src - 1);        /* count does not include NUL */
}

