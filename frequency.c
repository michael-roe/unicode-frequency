#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <search.h>

static wchar_t cp1252[] = {
	0x20ac,
	0x201a,
	0x192,
	0x201e,
	0x2026,
	0x2020,
	0x2021,
	0x02c6,
	0x2030,
	0x0160,
	0x2039,
	0x0152,
	0x017d,
	0x2018,
	0x2019,
	0x201c,
	0x201d,
	0x2022,
	0x2013,
	0x2014,
	0x02dc,
	0x2122,
	0x0161,
	0x203a,
	0x0153,
	0x017e,
	0x0178,
	0
};

static wchar_t dp_repertoire[] = {
	0x108,
	0x109,
	0x11c,
	0x11d,
	0x124,
	0x125,
	0x134,
	0x135,
	0x15c,
	0x15d,
	0x174,
	0x175,
	0x176,
	0x177,
	0x14a,
	0x14b,
	0x166,
	0x167,
	0x218,
	0x219,
	0x21a,
	0x21b,
	0x102,
	0x103,
	0x16c,
	0x16d,
	0x150,
	0x151,
	0x170,
	0x171,
	/* Extended European Latin B */
	0x10c,
	0x10d,
	0x10e,
	0x10f,
	0x11a,
	0x11b,
	0x13d,
	0x13e,
	0x147,
	0x148,
	0x158,
	0x159,
	0x160,
	0x161,
	0x164,
	0x165,
	0x17d,
	0x17e,
	0x139,
	0x13a,
	0x154,
	0x155,
	0x16e,
	0x16f,
	0x122,
	0x123,
	0x136,
	0x137,
	0x13b,
	0x13c,
	0x145,
	0x146,
	0x156,
	0x157,
	0x100,
	0x101,
	0x112,
	0x113,
	0x12a,
	0x12b,
	0x14c,
	0x14d,
	0x16a,
	0x16b,
	/* Extended European Lation C */
	0x104,
	0x105,
	0x118,
	0x119,
	0x12e,
	0x12f,
	0x172,
	0x173,
	0x10a,
	0x10b,
	0x116,
	0x117,
	0x120,
	0x121,
	0x17b,
	0x17c,
	0x16a,
	0x16b,
	0x106,
	0x107,
	0x143,
	0x144,
	0x15a,
	0x15b,
	0x179,
	0x17a,
	0x10c,
	0x10d,
	0x160,
	0x161,
	0x17d,
	0x17e,
	0x110,
	0x111,
	0x126,
	0x127,
	0x141,
	0x142,
	/* Medievalist supplement */
	0x100,
	0x101,
	0x112,
	0x113,
	0x12a,
	0x12b,
	0x14c,
	0x14d,
	0x16a,
	0x16b,
	0x102,
	0x103,
	0x114,
	0x115,
	0x12c,
	0x12d,
	0x14e,
	0x14f,
	0x16c,
	0x16d,
	0x1fc,
	0x1fd,
	0x1e2,
	0x1e3,
	0xa734,
	0xa735,
	0x118,
	0x119,
	0x1ea,
	0x1eb,
	0x17f,
	0x1f7,
	0x1bf,
	0x21c,
	0x21d,
	0x232,
	0x233,
	0xa76b,
	0x204a,
	0xa76d,
	0xa75d,
	0xa770,
	0x180,
	0x111,
	0x127,
	0xa751,
	0xa753,
	0xa755,
	0xa765,
	/* Semitic and Indic transcription */
	0x1e0c,
	0x1e0d,
	0x1e24,
	0x1e25,
	0x1e32,
	0x1e33,
	0x1e37,
	0x1e39,
	0x1e42,
	0x1e43,
	0x1e40,
	0x1e41,
	0x1e46,
	0x1e47,
	0x1e44,
	0x1e45,
	0x1e5a,
	0x1e5b,
	0x1e5c,
	0x1e5d,
	0x1e62,
	0x1e63,
	0x1e6c,
	0x1e6d,
	0x1e92,
	0x1e93,
	0x100,
	0x101,
	0x112,
	0x113,
	0x12a,
	0x12b,
	0x14c,
	0x14d,
	0x16a,
	0x16b,
	0x1e96,
	0x1e2a,
	0x1e2b,
	0x15a,
	0x15b,
	0x160,
	0x161,
	0x1e94,
	0x1e95,
	0x2bf,
	0x2be,
	0
};

struct char_info {
  int count;
};

void add_to_table(wchar_t *wbuff)
{
char buff[80];
ENTRY e;
ENTRY *ep;

  wcstombs(buff, wbuff, sizeof(buff));
  e.key = buff;
  e.data = NULL;
  ep = hsearch(e, ENTER);
  if (ep)
  {
    if (ep->data == NULL)
    {
      wprintf(L"%04x %lc", wbuff[0], wbuff[0]);
      if (wbuff[1] != 0)
      {
        wprintf(L" %04x %lc", wbuff[1], wbuff[1]);
        if (wbuff[2] != 0)
        {
          wprintf(L" %04x %lc", wbuff[2], wbuff[2]);
        }
      }
      if (wcschr(dp_repertoire, wbuff[0]) == 0)
        wprintf(L"  ***");

      wprintf(L"\n");
      ep->data = (void *) malloc(sizeof(struct char_info));
      if (ep->data)
      {
        ((struct char_info *) ep->data)->count = 1;
      }
    }
    else
    {
      ((struct char_info *) ep->data)->count++;
    }
  }
}

int main(int argc, char **argv)
{
wint_t c, d, previous;
wchar_t wbuff[10];
int include_greek = 0;

  setlocale(LC_ALL, getenv("LANG"));
  hcreate(1024);
  fwprintf(stderr, L"%ls\n", cp1252);
  while ((c = fgetwc(stdin)) != WEOF)
  {
    if (c < 256)
    {
      /* Basic Latin, Latin-1 Supplement */
      /* do nothing */
    }
    else if (wcschr(cp1252, c))
    {
      /* Windows CP-1252 repertoire with Unicode encodings */
      /* do nothing */
    }
    else if ((c >= 0x35c) && (c <= 0x362))
    {
      /* Combining characters that link two characters */
      wbuff[0] = previous;
      wbuff[1] = c;
      d = fgetwc(stdin);
      wbuff[2] = d;
      ungetwc(d, stdin);
      wbuff[3] = 0;
      /* fwprintf(stderr, L"Double combining character %ls %x\n", wbuff, c); */
      add_to_table(wbuff);
    }
    else if ((c >= 0x300) && (c <= 0x36f))
    {
      /* combining characters */
      if ((previous < 0x300) || (previous >= 0x370))
      {
        wbuff[0] = previous;
        wbuff[1] = c;
        wbuff[2] = 0;
        add_to_table(wbuff);
      }
    }
    else if ((c >= 0x370) && (c <= 0x3ff))
    {
      /* Greek and Coptic */
      if (include_greek)
      {
        wbuff[0] = c;
	wbuff[1] = 0;
	add_to_table(wbuff);
      }
    }
    else if ((c >= 0x1f00) && (c <= 0x1fff))
    {
      /* Greek Extended */
      if (include_greek)
      {
        wbuff[0] = c;
        wbuff[1] = 0;
        add_to_table(wbuff);
      }
    }
    else
    {
      wbuff[0] = c;
      wbuff[1] = 0;
      add_to_table(wbuff);
    }
    previous = c;
  }
  return 0;
}
