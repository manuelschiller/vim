/* vi:set ts=8 sts=4 sw=4 noet:
 *
 * VIM - Vi IMproved		by Bram Moolenaar
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 * See README.txt for an overview of the Vim source code.
 */

#include "vim.h"

#ifdef AMIGA
# include <time.h>	/* for time() */
#endif

/*
 * Vim originated from Stevie version 3.6 (Fish disk 217) by GRWalter (Fred)
 * It has been changed beyond recognition since then.
 *
 * Differences between version 7.4 and 8.x can be found with ":help version8".
 * Differences between version 6.4 and 7.x can be found with ":help version7".
 * Differences between version 5.8 and 6.x can be found with ":help version6".
 * Differences between version 4.x and 5.x can be found with ":help version5".
 * Differences between version 3.0 and 4.x can be found with ":help version4".
 * All the remarks about older versions have been removed, they are not very
 * interesting.
 */

#include "version.h"

char		*Version = VIM_VERSION_SHORT;
static char	*mediumVersion = VIM_VERSION_MEDIUM;

#if defined(HAVE_DATE_TIME) || defined(PROTO)
# if (defined(VMS) && defined(VAXC)) || defined(PROTO)
char	longVersion[sizeof(VIM_VERSION_LONG_DATE) + sizeof(__DATE__)
						      + sizeof(__TIME__) + 3];

    void
init_longVersion(void)
{
    /*
     * Construct the long version string.  Necessary because
     * VAX C can't concatenate strings in the preprocessor.
     */
    strcpy(longVersion, VIM_VERSION_LONG_DATE);
    strcat(longVersion, __DATE__);
    strcat(longVersion, " ");
    strcat(longVersion, __TIME__);
    strcat(longVersion, ")");
}

# else
    void
init_longVersion(void)
{
    char *date_time = __DATE__ " " __TIME__;
    char *msg = _("%s (%s, compiled %s)");
    size_t len = strlen(msg)
		+ strlen(VIM_VERSION_LONG_ONLY)
		+ strlen(VIM_VERSION_DATE_ONLY)
		+ strlen(date_time);

    longVersion = alloc(len);
    if (longVersion == NULL)
	longVersion = VIM_VERSION_LONG;
    else
	vim_snprintf(longVersion, len, msg,
		      VIM_VERSION_LONG_ONLY, VIM_VERSION_DATE_ONLY, date_time);
}
# endif
#else
char	*longVersion = VIM_VERSION_LONG;

    void
init_longVersion(void)
{
    // nothing to do
}
#endif

static char *(features[]) =
{
#ifdef HAVE_ACL
	"+acl",
#else
	"-acl",
#endif
#ifdef AMIGA		/* only for Amiga systems */
# ifdef FEAT_ARP
	"+ARP",
# else
	"-ARP",
# endif
#endif
#ifdef FEAT_ARABIC
	"+arabic",
#else
	"-arabic",
#endif
	"+autocmd",
#ifdef FEAT_AUTOCHDIR
       "+autochdir",
#else
       "-autochdir",
#endif
#ifdef FEAT_AUTOSERVERNAME
	"+autoservername",
#else
	"-autoservername",
#endif
#ifdef FEAT_BEVAL_GUI
	"+balloon_eval",
#else
	"-balloon_eval",
#endif
#ifdef FEAT_BEVAL_TERM
	"+balloon_eval_term",
#else
	"-balloon_eval_term",
#endif
#ifdef FEAT_BROWSE
	"+browse",
#else
	"-browse",
#endif
#ifdef NO_BUILTIN_TCAPS
	"-builtin_terms",
#endif
#ifdef SOME_BUILTIN_TCAPS
	"+builtin_terms",
#endif
#ifdef ALL_BUILTIN_TCAPS
	"++builtin_terms",
#endif
#ifdef FEAT_BYTEOFF
	"+byte_offset",
#else
	"-byte_offset",
#endif
#ifdef FEAT_JOB_CHANNEL
	"+channel",
#else
	"-channel",
#endif
#ifdef FEAT_CINDENT
	"+cindent",
#else
	"-cindent",
#endif
#ifdef FEAT_CLIENTSERVER
	"+clientserver",
#else
	"-clientserver",
#endif
#ifdef FEAT_CLIPBOARD
	"+clipboard",
#else
	"-clipboard",
#endif
	"+cmdline_compl",
	"+cmdline_hist",
#ifdef FEAT_CMDL_INFO
	"+cmdline_info",
#else
	"-cmdline_info",
#endif
#ifdef FEAT_COMMENTS
	"+comments",
#else
	"-comments",
#endif
#ifdef FEAT_CONCEAL
	"+conceal",
#else
	"-conceal",
#endif
#ifdef FEAT_CRYPT
	"+cryptv",
#else
	"-cryptv",
#endif
#ifdef FEAT_CSCOPE
	"+cscope",
#else
	"-cscope",
#endif
	"+cursorbind",
#ifdef CURSOR_SHAPE
	"+cursorshape",
#else
	"-cursorshape",
#endif
#if defined(FEAT_CON_DIALOG) && defined(FEAT_GUI_DIALOG)
	"+dialog_con_gui",
#else
# if defined(FEAT_CON_DIALOG)
	"+dialog_con",
# else
#  if defined(FEAT_GUI_DIALOG)
	"+dialog_gui",
#  else
	"-dialog",
#  endif
# endif
#endif
#ifdef FEAT_DIFF
	"+diff",
#else
	"-diff",
#endif
#ifdef FEAT_DIGRAPHS
	"+digraphs",
#else
	"-digraphs",
#endif
#ifdef FEAT_GUI_MSWIN
# ifdef FEAT_DIRECTX
	"+directx",
# else
	"-directx",
# endif
#endif
#ifdef FEAT_DND
	"+dnd",
#else
	"-dnd",
#endif
#ifdef EBCDIC
	"+ebcdic",
#else
	"-ebcdic",
#endif
#ifdef FEAT_EMACS_TAGS
	"+emacs_tags",
#else
	"-emacs_tags",
#endif
#ifdef FEAT_EVAL
	"+eval",
#else
	"-eval",
#endif
	"+ex_extra",
#ifdef FEAT_SEARCH_EXTRA
	"+extra_search",
#else
	"-extra_search",
#endif
	"-farsi",
#ifdef FEAT_SEARCHPATH
	"+file_in_path",
#else
	"-file_in_path",
#endif
#ifdef FEAT_FIND_ID
	"+find_in_path",
#else
	"-find_in_path",
#endif
#ifdef FEAT_FLOAT
	"+float",
#else
	"-float",
#endif
#ifdef FEAT_FOLDING
	"+folding",
#else
	"-folding",
#endif
#ifdef FEAT_FOOTER
	"+footer",
#else
	"-footer",
#endif
	    /* only interesting on Unix systems */
#if !defined(USE_SYSTEM) && defined(UNIX)
	"+fork()",
#endif
#ifdef FEAT_GETTEXT
# ifdef DYNAMIC_GETTEXT
	"+gettext/dyn",
# else
	"+gettext",
# endif
#else
	"-gettext",
#endif
#ifdef FEAT_HANGULIN
	"+hangul_input",
#else
	"-hangul_input",
#endif
#if (defined(HAVE_ICONV_H) && defined(USE_ICONV)) || defined(DYNAMIC_ICONV)
# ifdef DYNAMIC_ICONV
	"+iconv/dyn",
# else
	"+iconv",
# endif
#else
	"-iconv",
#endif
#ifdef FEAT_INS_EXPAND
	"+insert_expand",
#else
	"-insert_expand",
#endif
#ifdef FEAT_JOB_CHANNEL
	"+job",
#else
	"-job",
#endif
#ifdef FEAT_JUMPLIST
	"+jumplist",
#else
	"-jumplist",
#endif
#ifdef FEAT_KEYMAP
	"+keymap",
#else
	"-keymap",
#endif
#ifdef FEAT_EVAL
	"+lambda",
#else
	"-lambda",
#endif
#ifdef FEAT_LANGMAP
	"+langmap",
#else
	"-langmap",
#endif
#ifdef FEAT_LIBCALL
	"+libcall",
#else
	"-libcall",
#endif
#ifdef FEAT_LINEBREAK
	"+linebreak",
#else
	"-linebreak",
#endif
#ifdef FEAT_LISP
	"+lispindent",
#else
	"-lispindent",
#endif
	"+listcmds",
	"+localmap",
#ifdef FEAT_LUA
# ifdef DYNAMIC_LUA
	"+lua/dyn",
# else
	"+lua",
# endif
#else
	"-lua",
#endif
#ifdef FEAT_MENU
	"+menu",
#else
	"-menu",
#endif
#ifdef FEAT_SESSION
	"+mksession",
#else
	"-mksession",
#endif
#ifdef FEAT_MODIFY_FNAME
	"+modify_fname",
#else
	"-modify_fname",
#endif
#ifdef FEAT_MOUSE
	"+mouse",
#  ifdef FEAT_MOUSESHAPE
	"+mouseshape",
#  else
	"-mouseshape",
#  endif
# else
	"-mouse",
#endif

#if defined(UNIX) || defined(VMS)
# ifdef FEAT_MOUSE_DEC
	"+mouse_dec",
# else
	"-mouse_dec",
# endif
# ifdef FEAT_MOUSE_GPM
	"+mouse_gpm",
# else
	"-mouse_gpm",
# endif
# ifdef FEAT_MOUSE_JSB
	"+mouse_jsbterm",
# else
	"-mouse_jsbterm",
# endif
# ifdef FEAT_MOUSE_NET
	"+mouse_netterm",
# else
	"-mouse_netterm",
# endif
#endif

#ifdef __QNX__
# ifdef FEAT_MOUSE_PTERM
	"+mouse_pterm",
# else
	"-mouse_pterm",
# endif
#endif

#if defined(UNIX) || defined(VMS)
# ifdef FEAT_MOUSE_XTERM
	"+mouse_sgr",
# else
	"-mouse_sgr",
# endif
# ifdef FEAT_SYSMOUSE
	"+mouse_sysmouse",
# else
	"-mouse_sysmouse",
# endif
# ifdef FEAT_MOUSE_URXVT
	"+mouse_urxvt",
# else
	"-mouse_urxvt",
# endif
# ifdef FEAT_MOUSE_XTERM
	"+mouse_xterm",
# else
	"-mouse_xterm",
# endif
#endif

#ifdef FEAT_MBYTE_IME
# ifdef DYNAMIC_IME
	"+multi_byte_ime/dyn",
# else
	"+multi_byte_ime",
# endif
#else
	"+multi_byte",
#endif
#ifdef FEAT_MULTI_LANG
	"+multi_lang",
#else
	"-multi_lang",
#endif
#ifdef FEAT_MZSCHEME
# ifdef DYNAMIC_MZSCHEME
	"+mzscheme/dyn",
# else
	"+mzscheme",
# endif
#else
	"-mzscheme",
#endif
#ifdef FEAT_NETBEANS_INTG
	"+netbeans_intg",
#else
	"-netbeans_intg",
#endif
#ifdef FEAT_NUM64
	"+num64",
#else
	"-num64",
#endif
#ifdef FEAT_GUI_MSWIN
# ifdef FEAT_OLE
	"+ole",
# else
	"-ole",
# endif
#endif
#ifdef FEAT_EVAL
	"+packages",
#else
	"-packages",
#endif
#ifdef FEAT_PATH_EXTRA
	"+path_extra",
#else
	"-path_extra",
#endif
#ifdef FEAT_PERL
# ifdef DYNAMIC_PERL
	"+perl/dyn",
# else
	"+perl",
# endif
#else
	"-perl",
#endif
#ifdef FEAT_PERSISTENT_UNDO
	"+persistent_undo",
#else
	"-persistent_undo",
#endif
#ifdef FEAT_PRINTER
# ifdef FEAT_POSTSCRIPT
	"+postscript",
# else
	"-postscript",
# endif
	"+printer",
#else
	"-printer",
#endif
#ifdef FEAT_PROFILE
	"+profile",
#else
	"-profile",
#endif
#ifdef FEAT_PYTHON
# ifdef DYNAMIC_PYTHON
	"+python/dyn",
# else
	"+python",
# endif
#else
	"-python",
#endif
#ifdef FEAT_PYTHON3
# ifdef DYNAMIC_PYTHON3
	"+python3/dyn",
# else
	"+python3",
# endif
#else
	"-python3",
#endif
#ifdef FEAT_QUICKFIX
	"+quickfix",
#else
	"-quickfix",
#endif
#ifdef FEAT_RELTIME
	"+reltime",
#else
	"-reltime",
#endif
#ifdef FEAT_RIGHTLEFT
	"+rightleft",
#else
	"-rightleft",
#endif
#ifdef FEAT_RUBY
# ifdef DYNAMIC_RUBY
	"+ruby/dyn",
# else
	"+ruby",
# endif
#else
	"-ruby",
#endif
	"+scrollbind",
#ifdef FEAT_SIGNS
	"+signs",
#else
	"-signs",
#endif
#ifdef FEAT_SMARTINDENT
	"+smartindent",
#else
	"-smartindent",
#endif
#ifdef FEAT_SOUND
	"+sound",
#else
	"-sound",
#endif
#ifdef FEAT_SPELL
	"+spell",
#else
	"-spell",
#endif
#ifdef STARTUPTIME
	"+startuptime",
#else
	"-startuptime",
#endif
#ifdef FEAT_STL_OPT
	"+statusline",
#else
	"-statusline",
#endif
	"-sun_workshop",
#ifdef FEAT_SYN_HL
	"+syntax",
#else
	"-syntax",
#endif
	    /* only interesting on Unix systems */
#if defined(USE_SYSTEM) && defined(UNIX)
	"+system()",
#endif
#ifdef FEAT_TAG_BINS
	"+tag_binary",
#else
	"-tag_binary",
#endif
	"-tag_old_static",
	"-tag_any_white",
#ifdef FEAT_TCL
# ifdef DYNAMIC_TCL
	"+tcl/dyn",
# else
	"+tcl",
# endif
#else
	"-tcl",
#endif
#ifdef FEAT_TERMGUICOLORS
	"+termguicolors",
#else
	"-termguicolors",
#endif
#ifdef FEAT_TERMINAL
	"+terminal",
#else
	"-terminal",
#endif
#if defined(UNIX)
/* only Unix can have terminfo instead of termcap */
# ifdef TERMINFO
	"+terminfo",
# else
	"-terminfo",
# endif
#endif
#ifdef FEAT_TERMRESPONSE
	"+termresponse",
#else
	"-termresponse",
#endif
#ifdef FEAT_TEXTOBJ
	"+textobjects",
#else
	"-textobjects",
#endif
#ifdef FEAT_TEXT_PROP
	"+textprop",
#else
	"-textprop",
#endif
#if !defined(UNIX)
/* unix always includes termcap support */
# ifdef HAVE_TGETENT
	"+tgetent",
# else
	"-tgetent",
# endif
#endif
#ifdef FEAT_TIMERS
	"+timers",
#else
	"-timers",
#endif
#ifdef FEAT_TITLE
	"+title",
#else
	"-title",
#endif
#ifdef FEAT_TOOLBAR
	"+toolbar",
#else
	"-toolbar",
#endif
	"+user_commands",
#ifdef FEAT_VARTABS
	"+vartabs",
#else
	"-vartabs",
#endif
	"+vertsplit",
	"+virtualedit",
	"+visual",
	"+visualextra",
#ifdef FEAT_VIMINFO
	"+viminfo",
#else
	"-viminfo",
#endif
	"+vreplace",
#ifdef MSWIN
# ifdef FEAT_VTP
	"+vtp",
# else
	"-vtp",
# endif
#endif
#ifdef FEAT_WILDIGN
	"+wildignore",
#else
	"-wildignore",
#endif
#ifdef FEAT_WILDMENU
	"+wildmenu",
#else
	"-wildmenu",
#endif
	"+windows",
#ifdef FEAT_WRITEBACKUP
	"+writebackup",
#else
	"-writebackup",
#endif
#if defined(UNIX) || defined(VMS)
# ifdef FEAT_X11
	"+X11",
# else
	"-X11",
# endif
#endif
#ifdef FEAT_XFONTSET
	"+xfontset",
#else
	"-xfontset",
#endif
#ifdef FEAT_XIM
	"+xim",
#else
	"-xim",
#endif
#ifdef MSWIN
# ifdef FEAT_XPM_W32
	"+xpm_w32",
# else
	"-xpm_w32",
# endif
#else
# ifdef HAVE_XPM
	"+xpm",
# else
	"-xpm",
# endif
#endif
#if defined(UNIX) || defined(VMS)
# ifdef USE_XSMP_INTERACT
	"+xsmp_interact",
# else
#  ifdef USE_XSMP
	"+xsmp",
#  else
	"-xsmp",
#  endif
# endif
# ifdef FEAT_XCLIPBOARD
	"+xterm_clipboard",
# else
	"-xterm_clipboard",
# endif
#endif
#ifdef FEAT_XTERM_SAVE
	"+xterm_save",
#else
	"-xterm_save",
#endif
	NULL
};

static int included_patches[] =
{   /* Add new patch number below this line */
/**/
    1897,
/**/
    1896,
/**/
    1895,
/**/
    1894,
/**/
    1893,
/**/
    1892,
/**/
    1891,
/**/
    1890,
/**/
    1889,
/**/
    1888,
/**/
    1887,
/**/
    1886,
/**/
    1885,
/**/
    1884,
/**/
    1883,
/**/
    1882,
/**/
    1881,
/**/
    1880,
/**/
    1879,
/**/
    1878,
/**/
    1877,
/**/
    1876,
/**/
    1875,
/**/
    1874,
/**/
    1873,
/**/
    1872,
/**/
    1871,
/**/
    1870,
/**/
    1869,
/**/
    1868,
/**/
    1867,
/**/
    1866,
/**/
    1865,
/**/
    1864,
/**/
    1863,
/**/
    1862,
/**/
    1861,
/**/
    1860,
/**/
    1859,
/**/
    1858,
/**/
    1857,
/**/
    1856,
/**/
    1855,
/**/
    1854,
/**/
    1853,
/**/
    1852,
/**/
    1851,
/**/
    1850,
/**/
    1849,
/**/
    1848,
/**/
    1847,
/**/
    1846,
/**/
    1845,
/**/
    1844,
/**/
    1843,
/**/
    1842,
/**/
    1841,
/**/
    1840,
/**/
    1839,
/**/
    1838,
/**/
    1837,
/**/
    1836,
/**/
    1835,
/**/
    1834,
/**/
    1833,
/**/
    1832,
/**/
    1831,
/**/
    1830,
/**/
    1829,
/**/
    1828,
/**/
    1827,
/**/
    1826,
/**/
    1825,
/**/
    1824,
/**/
    1823,
/**/
    1822,
/**/
    1821,
/**/
    1820,
/**/
    1819,
/**/
    1818,
/**/
    1817,
/**/
    1816,
/**/
    1815,
/**/
    1814,
/**/
    1813,
/**/
    1812,
/**/
    1811,
/**/
    1810,
/**/
    1809,
/**/
    1808,
/**/
    1807,
/**/
    1806,
/**/
    1805,
/**/
    1804,
/**/
    1803,
/**/
    1802,
/**/
    1801,
/**/
    1800,
/**/
    1799,
/**/
    1798,
/**/
    1797,
/**/
    1796,
/**/
    1795,
/**/
    1794,
/**/
    1793,
/**/
    1792,
/**/
    1791,
/**/
    1790,
/**/
    1789,
/**/
    1788,
/**/
    1787,
/**/
    1786,
/**/
    1785,
/**/
    1784,
/**/
    1783,
/**/
    1782,
/**/
    1781,
/**/
    1780,
/**/
    1779,
/**/
    1778,
/**/
    1777,
/**/
    1776,
/**/
    1775,
/**/
    1774,
/**/
    1773,
/**/
    1772,
/**/
    1771,
/**/
    1770,
/**/
    1769,
/**/
    1768,
/**/
    1767,
/**/
    1766,
/**/
    1765,
/**/
    1764,
/**/
    1763,
/**/
    1762,
/**/
    1761,
/**/
    1760,
/**/
    1759,
/**/
    1758,
/**/
    1757,
/**/
    1756,
/**/
    1755,
/**/
    1754,
/**/
    1753,
/**/
    1752,
/**/
    1751,
/**/
    1750,
/**/
    1749,
/**/
    1748,
/**/
    1747,
/**/
    1746,
/**/
    1745,
/**/
    1744,
/**/
    1743,
/**/
    1742,
/**/
    1741,
/**/
    1740,
/**/
    1739,
/**/
    1738,
/**/
    1737,
/**/
    1736,
/**/
    1735,
/**/
    1734,
/**/
    1733,
/**/
    1732,
/**/
    1731,
/**/
    1730,
/**/
    1729,
/**/
    1728,
/**/
    1727,
/**/
    1726,
/**/
    1725,
/**/
    1724,
/**/
    1723,
/**/
    1722,
/**/
    1721,
/**/
    1720,
/**/
    1719,
/**/
    1718,
/**/
    1717,
/**/
    1716,
/**/
    1715,
/**/
    1714,
/**/
    1713,
/**/
    1712,
/**/
    1711,
/**/
    1710,
/**/
    1709,
/**/
    1708,
/**/
    1707,
/**/
    1706,
/**/
    1705,
/**/
    1704,
/**/
    1703,
/**/
    1702,
/**/
    1701,
/**/
    1700,
/**/
    1699,
/**/
    1698,
/**/
    1697,
/**/
    1696,
/**/
    1695,
/**/
    1694,
/**/
    1693,
/**/
    1692,
/**/
    1691,
/**/
    1690,
/**/
    1689,
/**/
    1688,
/**/
    1687,
/**/
    1686,
/**/
    1685,
/**/
    1684,
/**/
    1683,
/**/
    1682,
/**/
    1681,
/**/
    1680,
/**/
    1679,
/**/
    1678,
/**/
    1677,
/**/
    1676,
/**/
    1675,
/**/
    1674,
/**/
    1673,
/**/
    1672,
/**/
    1671,
/**/
    1670,
/**/
    1669,
/**/
    1668,
/**/
    1667,
/**/
    1666,
/**/
    1665,
/**/
    1664,
/**/
    1663,
/**/
    1662,
/**/
    1661,
/**/
    1660,
/**/
    1659,
/**/
    1658,
/**/
    1657,
/**/
    1656,
/**/
    1655,
/**/
    1654,
/**/
    1653,
/**/
    1652,
/**/
    1651,
/**/
    1650,
/**/
    1649,
/**/
    1648,
/**/
    1647,
/**/
    1646,
/**/
    1645,
/**/
    1644,
/**/
    1643,
/**/
    1642,
/**/
    1641,
/**/
    1640,
/**/
    1639,
/**/
    1638,
/**/
    1637,
/**/
    1636,
/**/
    1635,
/**/
    1634,
/**/
    1633,
/**/
    1632,
/**/
    1631,
/**/
    1630,
/**/
    1629,
/**/
    1628,
/**/
    1627,
/**/
    1626,
/**/
    1625,
/**/
    1624,
/**/
    1623,
/**/
    1622,
/**/
    1621,
/**/
    1620,
/**/
    1619,
/**/
    1618,
/**/
    1617,
/**/
    1616,
/**/
    1615,
/**/
    1614,
/**/
    1613,
/**/
    1612,
/**/
    1611,
/**/
    1610,
/**/
    1609,
/**/
    1608,
/**/
    1607,
/**/
    1606,
/**/
    1605,
/**/
    1604,
/**/
    1603,
/**/
    1602,
/**/
    1601,
/**/
    1600,
/**/
    1599,
/**/
    1598,
/**/
    1597,
/**/
    1596,
/**/
    1595,
/**/
    1594,
/**/
    1593,
/**/
    1592,
/**/
    1591,
/**/
    1590,
/**/
    1589,
/**/
    1588,
/**/
    1587,
/**/
    1586,
/**/
    1585,
/**/
    1584,
/**/
    1583,
/**/
    1582,
/**/
    1581,
/**/
    1580,
/**/
    1579,
/**/
    1578,
/**/
    1577,
/**/
    1576,
/**/
    1575,
/**/
    1574,
/**/
    1573,
/**/
    1572,
/**/
    1571,
/**/
    1570,
/**/
    1569,
/**/
    1568,
/**/
    1567,
/**/
    1566,
/**/
    1565,
/**/
    1564,
/**/
    1563,
/**/
    1562,
/**/
    1561,
/**/
    1560,
/**/
    1559,
/**/
    1558,
/**/
    1557,
/**/
    1556,
/**/
    1555,
/**/
    1554,
/**/
    1553,
/**/
    1552,
/**/
    1551,
/**/
    1550,
/**/
    1549,
/**/
    1548,
/**/
    1547,
/**/
    1546,
/**/
    1545,
/**/
    1544,
/**/
    1543,
/**/
    1542,
/**/
    1541,
/**/
    1540,
/**/
    1539,
/**/
    1538,
/**/
    1537,
/**/
    1536,
/**/
    1535,
/**/
    1534,
/**/
    1533,
/**/
    1532,
/**/
    1531,
/**/
    1530,
/**/
    1529,
/**/
    1528,
/**/
    1527,
/**/
    1526,
/**/
    1525,
/**/
    1524,
/**/
    1523,
/**/
    1522,
/**/
    1521,
/**/
    1520,
/**/
    1519,
/**/
    1518,
/**/
    1517,
/**/
    1516,
/**/
    1515,
/**/
    1514,
/**/
    1513,
/**/
    1512,
/**/
    1511,
/**/
    1510,
/**/
    1509,
/**/
    1508,
/**/
    1507,
/**/
    1506,
/**/
    1505,
/**/
    1504,
/**/
    1503,
/**/
    1502,
/**/
    1501,
/**/
    1500,
/**/
    1499,
/**/
    1498,
/**/
    1497,
/**/
    1496,
/**/
    1495,
/**/
    1494,
/**/
    1493,
/**/
    1492,
/**/
    1491,
/**/
    1490,
/**/
    1489,
/**/
    1488,
/**/
    1487,
/**/
    1486,
/**/
    1485,
/**/
    1484,
/**/
    1483,
/**/
    1482,
/**/
    1481,
/**/
    1480,
/**/
    1479,
/**/
    1478,
/**/
    1477,
/**/
    1476,
/**/
    1475,
/**/
    1474,
/**/
    1473,
/**/
    1472,
/**/
    1471,
/**/
    1470,
/**/
    1469,
/**/
    1468,
/**/
    1467,
/**/
    1466,
/**/
    1465,
/**/
    1464,
/**/
    1463,
/**/
    1462,
/**/
    1461,
/**/
    1460,
/**/
    1459,
/**/
    1458,
/**/
    1457,
/**/
    1456,
/**/
    1455,
/**/
    1454,
/**/
    1453,
/**/
    1452,
/**/
    1451,
/**/
    1450,
/**/
    1449,
/**/
    1448,
/**/
    1447,
/**/
    1446,
/**/
    1445,
/**/
    1444,
/**/
    1443,
/**/
    1442,
/**/
    1441,
/**/
    1440,
/**/
    1439,
/**/
    1438,
/**/
    1437,
/**/
    1436,
/**/
    1435,
/**/
    1434,
/**/
    1433,
/**/
    1432,
/**/
    1431,
/**/
    1430,
/**/
    1429,
/**/
    1428,
/**/
    1427,
/**/
    1426,
/**/
    1425,
/**/
    1424,
/**/
    1423,
/**/
    1422,
/**/
    1421,
/**/
    1420,
/**/
    1419,
/**/
    1418,
/**/
    1417,
/**/
    1416,
/**/
    1415,
/**/
    1414,
/**/
    1413,
/**/
    1412,
/**/
    1411,
/**/
    1410,
/**/
    1409,
/**/
    1408,
/**/
    1407,
/**/
    1406,
/**/
    1405,
/**/
    1404,
/**/
    1403,
/**/
    1402,
/**/
    1401,
/**/
    1400,
/**/
    1399,
/**/
    1398,
/**/
    1397,
/**/
    1396,
/**/
    1395,
/**/
    1394,
/**/
    1393,
/**/
    1392,
/**/
    1391,
/**/
    1390,
/**/
    1389,
/**/
    1388,
/**/
    1387,
/**/
    1386,
/**/
    1385,
/**/
    1384,
/**/
    1383,
/**/
    1382,
/**/
    1381,
/**/
    1380,
/**/
    1379,
/**/
    1378,
/**/
    1377,
/**/
    1376,
/**/
    1375,
/**/
    1374,
/**/
    1373,
/**/
    1372,
/**/
    1371,
/**/
    1370,
/**/
    1369,
/**/
    1368,
/**/
    1367,
/**/
    1366,
/**/
    1365,
/**/
    1364,
/**/
    1363,
/**/
    1362,
/**/
    1361,
/**/
    1360,
/**/
    1359,
/**/
    1358,
/**/
    1357,
/**/
    1356,
/**/
    1355,
/**/
    1354,
/**/
    1353,
/**/
    1352,
/**/
    1351,
/**/
    1350,
/**/
    1349,
/**/
    1348,
/**/
    1347,
/**/
    1346,
/**/
    1345,
/**/
    1344,
/**/
    1343,
/**/
    1342,
/**/
    1341,
/**/
    1340,
/**/
    1339,
/**/
    1338,
/**/
    1337,
/**/
    1336,
/**/
    1335,
/**/
    1334,
/**/
    1333,
/**/
    1332,
/**/
    1331,
/**/
    1330,
/**/
    1329,
/**/
    1328,
/**/
    1327,
/**/
    1326,
/**/
    1325,
/**/
    1324,
/**/
    1323,
/**/
    1322,
/**/
    1321,
/**/
    1320,
/**/
    1319,
/**/
    1318,
/**/
    1317,
/**/
    1316,
/**/
    1315,
/**/
    1314,
/**/
    1313,
/**/
    1312,
/**/
    1311,
/**/
    1310,
/**/
    1309,
/**/
    1308,
/**/
    1307,
/**/
    1306,
/**/
    1305,
/**/
    1304,
/**/
    1303,
/**/
    1302,
/**/
    1301,
/**/
    1300,
/**/
    1299,
/**/
    1298,
/**/
    1297,
/**/
    1296,
/**/
    1295,
/**/
    1294,
/**/
    1293,
/**/
    1292,
/**/
    1291,
/**/
    1290,
/**/
    1289,
/**/
    1288,
/**/
    1287,
/**/
    1286,
/**/
    1285,
/**/
    1284,
/**/
    1283,
/**/
    1282,
/**/
    1281,
/**/
    1280,
/**/
    1279,
/**/
    1278,
/**/
    1277,
/**/
    1276,
/**/
    1275,
/**/
    1274,
/**/
    1273,
/**/
    1272,
/**/
    1271,
/**/
    1270,
/**/
    1269,
/**/
    1268,
/**/
    1267,
/**/
    1266,
/**/
    1265,
/**/
    1264,
/**/
    1263,
/**/
    1262,
/**/
    1261,
/**/
    1260,
/**/
    1259,
/**/
    1258,
/**/
    1257,
/**/
    1256,
/**/
    1255,
/**/
    1254,
/**/
    1253,
/**/
    1252,
/**/
    1251,
/**/
    1250,
/**/
    1249,
/**/
    1248,
/**/
    1247,
/**/
    1246,
/**/
    1245,
/**/
    1244,
/**/
    1243,
/**/
    1242,
/**/
    1241,
/**/
    1240,
/**/
    1239,
/**/
    1238,
/**/
    1237,
/**/
    1236,
/**/
    1235,
/**/
    1234,
/**/
    1233,
/**/
    1232,
/**/
    1231,
/**/
    1230,
/**/
    1229,
/**/
    1228,
/**/
    1227,
/**/
    1226,
/**/
    1225,
/**/
    1224,
/**/
    1223,
/**/
    1222,
/**/
    1221,
/**/
    1220,
/**/
    1219,
/**/
    1218,
/**/
    1217,
/**/
    1216,
/**/
    1215,
/**/
    1214,
/**/
    1213,
/**/
    1212,
/**/
    1211,
/**/
    1210,
/**/
    1209,
/**/
    1208,
/**/
    1207,
/**/
    1206,
/**/
    1205,
/**/
    1204,
/**/
    1203,
/**/
    1202,
/**/
    1201,
/**/
    1200,
/**/
    1199,
/**/
    1198,
/**/
    1197,
/**/
    1196,
/**/
    1195,
/**/
    1194,
/**/
    1193,
/**/
    1192,
/**/
    1191,
/**/
    1190,
/**/
    1189,
/**/
    1188,
/**/
    1187,
/**/
    1186,
/**/
    1185,
/**/
    1184,
/**/
    1183,
/**/
    1182,
/**/
    1181,
/**/
    1180,
/**/
    1179,
/**/
    1178,
/**/
    1177,
/**/
    1176,
/**/
    1175,
/**/
    1174,
/**/
    1173,
/**/
    1172,
/**/
    1171,
/**/
    1170,
/**/
    1169,
/**/
    1168,
/**/
    1167,
/**/
    1166,
/**/
    1165,
/**/
    1164,
/**/
    1163,
/**/
    1162,
/**/
    1161,
/**/
    1160,
/**/
    1159,
/**/
    1158,
/**/
    1157,
/**/
    1156,
/**/
    1155,
/**/
    1154,
/**/
    1153,
/**/
    1152,
/**/
    1151,
/**/
    1150,
/**/
    1149,
/**/
    1148,
/**/
    1147,
/**/
    1146,
/**/
    1145,
/**/
    1144,
/**/
    1143,
/**/
    1142,
/**/
    1141,
/**/
    1140,
/**/
    1139,
/**/
    1138,
/**/
    1137,
/**/
    1136,
/**/
    1135,
/**/
    1134,
/**/
    1133,
/**/
    1132,
/**/
    1131,
/**/
    1130,
/**/
    1129,
/**/
    1128,
/**/
    1127,
/**/
    1126,
/**/
    1125,
/**/
    1124,
/**/
    1123,
/**/
    1122,
/**/
    1121,
/**/
    1120,
/**/
    1119,
/**/
    1118,
/**/
    1117,
/**/
    1116,
/**/
    1115,
/**/
    1114,
/**/
    1113,
/**/
    1112,
/**/
    1111,
/**/
    1110,
/**/
    1109,
/**/
    1108,
/**/
    1107,
/**/
    1106,
/**/
    1105,
/**/
    1104,
/**/
    1103,
/**/
    1102,
/**/
    1101,
/**/
    1100,
/**/
    1099,
/**/
    1098,
/**/
    1097,
/**/
    1096,
/**/
    1095,
/**/
    1094,
/**/
    1093,
/**/
    1092,
/**/
    1091,
/**/
    1090,
/**/
    1089,
/**/
    1088,
/**/
    1087,
/**/
    1086,
/**/
    1085,
/**/
    1084,
/**/
    1083,
/**/
    1082,
/**/
    1081,
/**/
    1080,
/**/
    1079,
/**/
    1078,
/**/
    1077,
/**/
    1076,
/**/
    1075,
/**/
    1074,
/**/
    1073,
/**/
    1072,
/**/
    1071,
/**/
    1070,
/**/
    1069,
/**/
    1068,
/**/
    1067,
/**/
    1066,
/**/
    1065,
/**/
    1064,
/**/
    1063,
/**/
    1062,
/**/
    1061,
/**/
    1060,
/**/
    1059,
/**/
    1058,
/**/
    1057,
/**/
    1056,
/**/
    1055,
/**/
    1054,
/**/
    1053,
/**/
    1052,
/**/
    1051,
/**/
    1050,
/**/
    1049,
/**/
    1048,
/**/
    1047,
/**/
    1046,
/**/
    1045,
/**/
    1044,
/**/
    1043,
/**/
    1042,
/**/
    1041,
/**/
    1040,
/**/
    1039,
/**/
    1038,
/**/
    1037,
/**/
    1036,
/**/
    1035,
/**/
    1034,
/**/
    1033,
/**/
    1032,
/**/
    1031,
/**/
    1030,
/**/
    1029,
/**/
    1028,
/**/
    1027,
/**/
    1026,
/**/
    1025,
/**/
    1024,
/**/
    1023,
/**/
    1022,
/**/
    1021,
/**/
    1020,
/**/
    1019,
/**/
    1018,
/**/
    1017,
/**/
    1016,
/**/
    1015,
/**/
    1014,
/**/
    1013,
/**/
    1012,
/**/
    1011,
/**/
    1010,
/**/
    1009,
/**/
    1008,
/**/
    1007,
/**/
    1006,
/**/
    1005,
/**/
    1004,
/**/
    1003,
/**/
    1002,
/**/
    1001,
/**/
    1000,
/**/
    999,
/**/
    998,
/**/
    997,
/**/
    996,
/**/
    995,
/**/
    994,
/**/
    993,
/**/
    992,
/**/
    991,
/**/
    990,
/**/
    989,
/**/
    988,
/**/
    987,
/**/
    986,
/**/
    985,
/**/
    984,
/**/
    983,
/**/
    982,
/**/
    981,
/**/
    980,
/**/
    979,
/**/
    978,
/**/
    977,
/**/
    976,
/**/
    975,
/**/
    974,
/**/
    973,
/**/
    972,
/**/
    971,
/**/
    970,
/**/
    969,
/**/
    968,
/**/
    967,
/**/
    966,
/**/
    965,
/**/
    964,
/**/
    963,
/**/
    962,
/**/
    961,
/**/
    960,
/**/
    959,
/**/
    958,
/**/
    957,
/**/
    956,
/**/
    955,
/**/
    954,
/**/
    953,
/**/
    952,
/**/
    951,
/**/
    950,
/**/
    949,
/**/
    948,
/**/
    947,
/**/
    946,
/**/
    945,
/**/
    944,
/**/
    943,
/**/
    942,
/**/
    941,
/**/
    940,
/**/
    939,
/**/
    938,
/**/
    937,
/**/
    936,
/**/
    935,
/**/
    934,
/**/
    933,
/**/
    932,
/**/
    931,
/**/
    930,
/**/
    929,
/**/
    928,
/**/
    927,
/**/
    926,
/**/
    925,
/**/
    924,
/**/
    923,
/**/
    922,
/**/
    921,
/**/
    920,
/**/
    919,
/**/
    918,
/**/
    917,
/**/
    916,
/**/
    915,
/**/
    914,
/**/
    913,
/**/
    912,
/**/
    911,
/**/
    910,
/**/
    909,
/**/
    908,
/**/
    907,
/**/
    906,
/**/
    905,
/**/
    904,
/**/
    903,
/**/
    902,
/**/
    901,
/**/
    900,
/**/
    899,
/**/
    898,
/**/
    897,
/**/
    896,
/**/
    895,
/**/
    894,
/**/
    893,
/**/
    892,
/**/
    891,
/**/
    890,
/**/
    889,
/**/
    888,
/**/
    887,
/**/
    886,
/**/
    885,
/**/
    884,
/**/
    883,
/**/
    882,
/**/
    881,
/**/
    880,
/**/
    879,
/**/
    878,
/**/
    877,
/**/
    876,
/**/
    875,
/**/
    874,
/**/
    873,
/**/
    872,
/**/
    871,
/**/
    870,
/**/
    869,
/**/
    868,
/**/
    867,
/**/
    866,
/**/
    865,
/**/
    864,
/**/
    863,
/**/
    862,
/**/
    861,
/**/
    860,
/**/
    859,
/**/
    858,
/**/
    857,
/**/
    856,
/**/
    855,
/**/
    854,
/**/
    853,
/**/
    852,
/**/
    851,
/**/
    850,
/**/
    849,
/**/
    848,
/**/
    847,
/**/
    846,
/**/
    845,
/**/
    844,
/**/
    843,
/**/
    842,
/**/
    841,
/**/
    840,
/**/
    839,
/**/
    838,
/**/
    837,
/**/
    836,
/**/
    835,
/**/
    834,
/**/
    833,
/**/
    832,
/**/
    831,
/**/
    830,
/**/
    829,
/**/
    828,
/**/
    827,
/**/
    826,
/**/
    825,
/**/
    824,
/**/
    823,
/**/
    822,
/**/
    821,
/**/
    820,
/**/
    819,
/**/
    818,
/**/
    817,
/**/
    816,
/**/
    815,
/**/
    814,
/**/
    813,
/**/
    812,
/**/
    811,
/**/
    810,
/**/
    809,
/**/
    808,
/**/
    807,
/**/
    806,
/**/
    805,
/**/
    804,
/**/
    803,
/**/
    802,
/**/
    801,
/**/
    800,
/**/
    799,
/**/
    798,
/**/
    797,
/**/
    796,
/**/
    795,
/**/
    794,
/**/
    793,
/**/
    792,
/**/
    791,
/**/
    790,
/**/
    789,
/**/
    788,
/**/
    787,
/**/
    786,
/**/
    785,
/**/
    784,
/**/
    783,
/**/
    782,
/**/
    781,
/**/
    780,
/**/
    779,
/**/
    778,
/**/
    777,
/**/
    776,
/**/
    775,
/**/
    774,
/**/
    773,
/**/
    772,
/**/
    771,
/**/
    770,
/**/
    769,
/**/
    768,
/**/
    767,
/**/
    766,
/**/
    765,
/**/
    764,
/**/
    763,
/**/
    762,
/**/
    761,
/**/
    760,
/**/
    759,
/**/
    758,
/**/
    757,
/**/
    756,
/**/
    755,
/**/
    754,
/**/
    753,
/**/
    752,
/**/
    751,
/**/
    750,
/**/
    749,
/**/
    748,
/**/
    747,
/**/
    746,
/**/
    745,
/**/
    744,
/**/
    743,
/**/
    742,
/**/
    741,
/**/
    740,
/**/
    739,
/**/
    738,
/**/
    737,
/**/
    736,
/**/
    735,
/**/
    734,
/**/
    733,
/**/
    732,
/**/
    731,
/**/
    730,
/**/
    729,
/**/
    728,
/**/
    727,
/**/
    726,
/**/
    725,
/**/
    724,
/**/
    723,
/**/
    722,
/**/
    721,
/**/
    720,
/**/
    719,
/**/
    718,
/**/
    717,
/**/
    716,
/**/
    715,
/**/
    714,
/**/
    713,
/**/
    712,
/**/
    711,
/**/
    710,
/**/
    709,
/**/
    708,
/**/
    707,
/**/
    706,
/**/
    705,
/**/
    704,
/**/
    703,
/**/
    702,
/**/
    701,
/**/
    700,
/**/
    699,
/**/
    698,
/**/
    697,
/**/
    696,
/**/
    695,
/**/
    694,
/**/
    693,
/**/
    692,
/**/
    691,
/**/
    690,
/**/
    689,
/**/
    688,
/**/
    687,
/**/
    686,
/**/
    685,
/**/
    684,
/**/
    683,
/**/
    682,
/**/
    681,
/**/
    680,
/**/
    679,
/**/
    678,
/**/
    677,
/**/
    676,
/**/
    675,
/**/
    674,
/**/
    673,
/**/
    672,
/**/
    671,
/**/
    670,
/**/
    669,
/**/
    668,
/**/
    667,
/**/
    666,
/**/
    665,
/**/
    664,
/**/
    663,
/**/
    662,
/**/
    661,
/**/
    660,
/**/
    659,
/**/
    658,
/**/
    657,
/**/
    656,
/**/
    655,
/**/
    654,
/**/
    653,
/**/
    652,
/**/
    651,
/**/
    650,
/**/
    649,
/**/
    648,
/**/
    647,
/**/
    646,
/**/
    645,
/**/
    644,
/**/
    643,
/**/
    642,
/**/
    641,
/**/
    640,
/**/
    639,
/**/
    638,
/**/
    637,
/**/
    636,
/**/
    635,
/**/
    634,
/**/
    633,
/**/
    632,
/**/
    631,
/**/
    630,
/**/
    629,
/**/
    628,
/**/
    627,
/**/
    626,
/**/
    625,
/**/
    624,
/**/
    623,
/**/
    622,
/**/
    621,
/**/
    620,
/**/
    619,
/**/
    618,
/**/
    617,
/**/
    616,
/**/
    615,
/**/
    614,
/**/
    613,
/**/
    612,
/**/
    611,
/**/
    610,
/**/
    609,
/**/
    608,
/**/
    607,
/**/
    606,
/**/
    605,
/**/
    604,
/**/
    603,
/**/
    602,
/**/
    601,
/**/
    600,
/**/
    599,
/**/
    598,
/**/
    597,
/**/
    596,
/**/
    595,
/**/
    594,
/**/
    593,
/**/
    592,
/**/
    591,
/**/
    590,
/**/
    589,
/**/
    588,
/**/
    587,
/**/
    586,
/**/
    585,
/**/
    584,
/**/
    583,
/**/
    582,
/**/
    581,
/**/
    580,
/**/
    579,
/**/
    578,
/**/
    577,
/**/
    576,
/**/
    575,
/**/
    574,
/**/
    573,
/**/
    572,
/**/
    571,
/**/
    570,
/**/
    569,
/**/
    568,
/**/
    567,
/**/
    566,
/**/
    565,
/**/
    564,
/**/
    563,
/**/
    562,
/**/
    561,
/**/
    560,
/**/
    559,
/**/
    558,
/**/
    557,
/**/
    556,
/**/
    555,
/**/
    554,
/**/
    553,
/**/
    552,
/**/
    551,
/**/
    550,
/**/
    549,
/**/
    548,
/**/
    547,
/**/
    546,
/**/
    545,
/**/
    544,
/**/
    543,
/**/
    542,
/**/
    541,
/**/
    540,
/**/
    539,
/**/
    538,
/**/
    537,
/**/
    536,
/**/
    535,
/**/
    534,
/**/
    533,
/**/
    532,
/**/
    531,
/**/
    530,
/**/
    529,
/**/
    528,
/**/
    527,
/**/
    526,
/**/
    525,
/**/
    524,
/**/
    523,
/**/
    522,
/**/
    521,
/**/
    520,
/**/
    519,
/**/
    518,
/**/
    517,
/**/
    516,
/**/
    515,
/**/
    514,
/**/
    513,
/**/
    512,
/**/
    511,
/**/
    510,
/**/
    509,
/**/
    508,
/**/
    507,
/**/
    506,
/**/
    505,
/**/
    504,
/**/
    503,
/**/
    502,
/**/
    501,
/**/
    500,
/**/
    499,
/**/
    498,
/**/
    497,
/**/
    496,
/**/
    495,
/**/
    494,
/**/
    493,
/**/
    492,
/**/
    491,
/**/
    490,
/**/
    489,
/**/
    488,
/**/
    487,
/**/
    486,
/**/
    485,
/**/
    484,
/**/
    483,
/**/
    482,
/**/
    481,
/**/
    480,
/**/
    479,
/**/
    478,
/**/
    477,
/**/
    476,
/**/
    475,
/**/
    474,
/**/
    473,
/**/
    472,
/**/
    471,
/**/
    470,
/**/
    469,
/**/
    468,
/**/
    467,
/**/
    466,
/**/
    465,
/**/
    464,
/**/
    463,
/**/
    462,
/**/
    461,
/**/
    460,
/**/
    459,
/**/
    458,
/**/
    457,
/**/
    456,
/**/
    455,
/**/
    454,
/**/
    453,
/**/
    452,
/**/
    451,
/**/
    450,
/**/
    449,
/**/
    448,
/**/
    447,
/**/
    446,
/**/
    445,
/**/
    444,
/**/
    443,
/**/
    442,
/**/
    441,
/**/
    440,
/**/
    439,
/**/
    438,
/**/
    437,
/**/
    436,
/**/
    435,
/**/
    434,
/**/
    433,
/**/
    432,
/**/
    431,
/**/
    430,
/**/
    429,
/**/
    428,
/**/
    427,
/**/
    426,
/**/
    425,
/**/
    424,
/**/
    423,
/**/
    422,
/**/
    421,
/**/
    420,
/**/
    419,
/**/
    418,
/**/
    417,
/**/
    416,
/**/
    415,
/**/
    414,
/**/
    413,
/**/
    412,
/**/
    411,
/**/
    410,
/**/
    409,
/**/
    408,
/**/
    407,
/**/
    406,
/**/
    405,
/**/
    404,
/**/
    403,
/**/
    402,
/**/
    401,
/**/
    400,
/**/
    399,
/**/
    398,
/**/
    397,
/**/
    396,
/**/
    395,
/**/
    394,
/**/
    393,
/**/
    392,
/**/
    391,
/**/
    390,
/**/
    389,
/**/
    388,
/**/
    387,
/**/
    386,
/**/
    385,
/**/
    384,
/**/
    383,
/**/
    382,
/**/
    381,
/**/
    380,
/**/
    379,
/**/
    378,
/**/
    377,
/**/
    376,
/**/
    375,
/**/
    374,
/**/
    373,
/**/
    372,
/**/
    371,
/**/
    370,
/**/
    369,
/**/
    368,
/**/
    367,
/**/
    366,
/**/
    365,
/**/
    364,
/**/
    363,
/**/
    362,
/**/
    361,
/**/
    360,
/**/
    359,
/**/
    358,
/**/
    357,
/**/
    356,
/**/
    355,
/**/
    354,
/**/
    353,
/**/
    352,
/**/
    351,
/**/
    350,
/**/
    349,
/**/
    348,
/**/
    347,
/**/
    346,
/**/
    345,
/**/
    344,
/**/
    343,
/**/
    342,
/**/
    341,
/**/
    340,
/**/
    339,
/**/
    338,
/**/
    337,
/**/
    336,
/**/
    335,
/**/
    334,
/**/
    333,
/**/
    332,
/**/
    331,
/**/
    330,
/**/
    329,
/**/
    328,
/**/
    327,
/**/
    326,
/**/
    325,
/**/
    324,
/**/
    323,
/**/
    322,
/**/
    321,
/**/
    320,
/**/
    319,
/**/
    318,
/**/
    317,
/**/
    316,
/**/
    315,
/**/
    314,
/**/
    313,
/**/
    312,
/**/
    311,
/**/
    310,
/**/
    309,
/**/
    308,
/**/
    307,
/**/
    306,
/**/
    305,
/**/
    304,
/**/
    303,
/**/
    302,
/**/
    301,
/**/
    300,
/**/
    299,
/**/
    298,
/**/
    297,
/**/
    296,
/**/
    295,
/**/
    294,
/**/
    293,
/**/
    292,
/**/
    291,
/**/
    290,
/**/
    289,
/**/
    288,
/**/
    287,
/**/
    286,
/**/
    285,
/**/
    284,
/**/
    283,
/**/
    282,
/**/
    281,
/**/
    280,
/**/
    279,
/**/
    278,
/**/
    277,
/**/
    276,
/**/
    275,
/**/
    274,
/**/
    273,
/**/
    272,
/**/
    271,
/**/
    270,
/**/
    269,
/**/
    268,
/**/
    267,
/**/
    266,
/**/
    265,
/**/
    264,
/**/
    263,
/**/
    262,
/**/
    261,
/**/
    260,
/**/
    259,
/**/
    258,
/**/
    257,
/**/
    256,
/**/
    255,
/**/
    254,
/**/
    253,
/**/
    252,
/**/
    251,
/**/
    250,
/**/
    249,
/**/
    248,
/**/
    247,
/**/
    246,
/**/
    245,
/**/
    244,
/**/
    243,
/**/
    242,
/**/
    241,
/**/
    240,
/**/
    239,
/**/
    238,
/**/
    237,
/**/
    236,
/**/
    235,
/**/
    234,
/**/
    233,
/**/
    232,
/**/
    231,
/**/
    230,
/**/
    229,
/**/
    228,
/**/
    227,
/**/
    226,
/**/
    225,
/**/
    224,
/**/
    223,
/**/
    222,
/**/
    221,
/**/
    220,
/**/
    219,
/**/
    218,
/**/
    217,
/**/
    216,
/**/
    215,
/**/
    214,
/**/
    213,
/**/
    212,
/**/
    211,
/**/
    210,
/**/
    209,
/**/
    208,
/**/
    207,
/**/
    206,
/**/
    205,
/**/
    204,
/**/
    203,
/**/
    202,
/**/
    201,
/**/
    200,
/**/
    199,
/**/
    198,
/**/
    197,
/**/
    196,
/**/
    195,
/**/
    194,
/**/
    193,
/**/
    192,
/**/
    191,
/**/
    190,
/**/
    189,
/**/
    188,
/**/
    187,
/**/
    186,
/**/
    185,
/**/
    184,
/**/
    183,
/**/
    182,
/**/
    181,
/**/
    180,
/**/
    179,
/**/
    178,
/**/
    177,
/**/
    176,
/**/
    175,
/**/
    174,
/**/
    173,
/**/
    172,
/**/
    171,
/**/
    170,
/**/
    169,
/**/
    168,
/**/
    167,
/**/
    166,
/**/
    165,
/**/
    164,
/**/
    163,
/**/
    162,
/**/
    161,
/**/
    160,
/**/
    159,
/**/
    158,
/**/
    157,
/**/
    156,
/**/
    155,
/**/
    154,
/**/
    153,
/**/
    152,
/**/
    151,
/**/
    150,
/**/
    149,
/**/
    148,
/**/
    147,
/**/
    146,
/**/
    145,
/**/
    144,
/**/
    143,
/**/
    142,
/**/
    141,
/**/
    140,
/**/
    139,
/**/
    138,
/**/
    137,
/**/
    136,
/**/
    135,
/**/
    134,
/**/
    133,
/**/
    132,
/**/
    131,
/**/
    130,
/**/
    129,
/**/
    128,
/**/
    127,
/**/
    126,
/**/
    125,
/**/
    124,
/**/
    123,
/**/
    122,
/**/
    121,
/**/
    120,
/**/
    119,
/**/
    118,
/**/
    117,
/**/
    116,
/**/
    115,
/**/
    114,
/**/
    113,
/**/
    112,
/**/
    111,
/**/
    110,
/**/
    109,
/**/
    108,
/**/
    107,
/**/
    106,
/**/
    105,
/**/
    104,
/**/
    103,
/**/
    102,
/**/
    101,
/**/
    100,
/**/
    99,
/**/
    98,
/**/
    97,
/**/
    96,
/**/
    95,
/**/
    94,
/**/
    93,
/**/
    92,
/**/
    91,
/**/
    90,
/**/
    89,
/**/
    88,
/**/
    87,
/**/
    86,
/**/
    85,
/**/
    84,
/**/
    83,
/**/
    82,
/**/
    81,
/**/
    80,
/**/
    79,
/**/
    78,
/**/
    77,
/**/
    76,
/**/
    75,
/**/
    74,
/**/
    73,
/**/
    72,
/**/
    71,
/**/
    70,
/**/
    69,
/**/
    68,
/**/
    67,
/**/
    66,
/**/
    65,
/**/
    64,
/**/
    63,
/**/
    62,
/**/
    61,
/**/
    60,
/**/
    59,
/**/
    58,
/**/
    57,
/**/
    56,
/**/
    55,
/**/
    54,
/**/
    53,
/**/
    52,
/**/
    51,
/**/
    50,
/**/
    49,
/**/
    48,
/**/
    47,
/**/
    46,
/**/
    45,
/**/
    44,
/**/
    43,
/**/
    42,
/**/
    41,
/**/
    40,
/**/
    39,
/**/
    38,
/**/
    37,
/**/
    36,
/**/
    35,
/**/
    34,
/**/
    33,
/**/
    32,
/**/
    31,
/**/
    30,
/**/
    29,
/**/
    28,
/**/
    27,
/**/
    26,
/**/
    25,
/**/
    24,
/**/
    23,
/**/
    22,
/**/
    21,
/**/
    20,
/**/
    19,
/**/
    18,
/**/
    17,
/**/
    16,
/**/
    15,
/**/
    14,
/**/
    13,
/**/
    12,
/**/
    11,
/**/
    10,
/**/
    9,
/**/
    8,
/**/
    7,
/**/
    6,
/**/
    5,
/**/
    4,
/**/
    3,
/**/
    2,
/**/
    1,
/**/
    0
};

/*
 * Place to put a short description when adding a feature with a patch.
 * Keep it short, e.g.,: "relative numbers", "persistent undo".
 * Also add a comment marker to separate the lines.
 * See the official Vim patches for the diff format: It must use a context of
 * one line only.  Create it by hand or use "diff -C2" and edit the patch.
 */
static char *(extra_patches[]) =
{   /* Add your patch description below this line */
/**/
    NULL
};

    int
highest_patch(void)
{
    // this relies on the highest patch number to be the first entry
    return included_patches[0];
}

#if defined(FEAT_EVAL) || defined(PROTO)
/*
 * Return TRUE if patch "n" has been included.
 */
    int
has_patch(int n)
{
    int		i;

    for (i = 0; included_patches[i] != 0; ++i)
	if (included_patches[i] == n)
	    return TRUE;
    return FALSE;
}
#endif

    void
ex_version(exarg_T *eap)
{
    /*
     * Ignore a ":version 9.99" command.
     */
    if (*eap->arg == NUL)
    {
	msg_putchar('\n');
	list_version();
    }
}

/*
 * Output a string for the version message.  If it's going to wrap, output a
 * newline, unless the message is too long to fit on the screen anyway.
 * When "wrap" is TRUE wrap the string in [].
 */
    static void
version_msg_wrap(char_u *s, int wrap)
{
    int		len = (int)vim_strsize(s) + (wrap ? 2 : 0);

    if (!got_int && len < (int)Columns && msg_col + len >= (int)Columns
								&& *s != '\n')
	msg_putchar('\n');
    if (!got_int)
    {
	if (wrap)
	    msg_puts("[");
	msg_puts((char *)s);
	if (wrap)
	    msg_puts("]");
    }
}

    static void
version_msg(char *s)
{
    version_msg_wrap((char_u *)s, FALSE);
}

/*
 * List all features aligned in columns, dictionary style.
 */
    static void
list_features(void)
{
    list_in_columns((char_u **)features, -1, -1);
}

/*
 * List string items nicely aligned in columns.
 * When "size" is < 0 then the last entry is marked with NULL.
 * The entry with index "current" is inclosed in [].
 */
    void
list_in_columns(char_u **items, int size, int current)
{
    int		i;
    int		ncol;
    int		nrow;
    int		cur_row = 1;
    int		item_count = 0;
    int		width = 0;
#ifdef FEAT_SYN_HL
    int		use_highlight = (items == (char_u **)features);
#endif

    /* Find the length of the longest item, use that + 1 as the column
     * width. */
    for (i = 0; size < 0 ? items[i] != NULL : i < size; ++i)
    {
	int l = (int)vim_strsize(items[i]) + (i == current ? 2 : 0);

	if (l > width)
	    width = l;
	++item_count;
    }
    width += 1;

    if (Columns < width)
    {
	// Not enough screen columns - show one per line
	for (i = 0; i < item_count; ++i)
	{
	    version_msg_wrap(items[i], i == current);
	    if (msg_col > 0 && i < item_count - 1)
		msg_putchar('\n');
	}
	return;
    }

    // The rightmost column doesn't need a separator.
    // Sacrifice it to fit in one more column if possible.
    ncol = (int) (Columns + 1) / width;
    nrow = item_count / ncol + (item_count % ncol ? 1 : 0);

    // "i" counts columns then rows.  "idx" counts rows then columns.
    for (i = 0; !got_int && i < nrow * ncol; ++i)
    {
	int idx = (i / ncol) + (i % ncol) * nrow;

	if (idx < item_count)
	{
	    int last_col = (i + 1) % ncol == 0;

	    if (idx == current)
		msg_putchar('[');
#ifdef FEAT_SYN_HL
	    if (use_highlight && items[idx][0] == '-')
		msg_puts_attr((char *)items[idx], HL_ATTR(HLF_W));
	    else
#endif
		msg_puts((char *)items[idx]);
	    if (idx == current)
		msg_putchar(']');
	    if (last_col)
	    {
		if (msg_col > 0 && cur_row < nrow)
		    msg_putchar('\n');
		++cur_row;
	    }
	    else
	    {
		while (msg_col % width)
		    msg_putchar(' ');
	    }
	}
	else
	{
	    // this row is out of items, thus at the end of the row
	    if (msg_col > 0)
	    {
		if (cur_row < nrow)
		    msg_putchar('\n');
		++cur_row;
	    }
	}
    }
}

    void
list_version(void)
{
    int		i;
    int		first;
    char	*s = "";

    /*
     * When adding features here, don't forget to update the list of
     * internal variables in eval.c!
     */
    init_longVersion();
    msg(longVersion);
#ifdef MSWIN
# ifdef FEAT_GUI_MSWIN
#  ifdef VIMDLL
#   ifdef _WIN64
    msg_puts(_("\nMS-Windows 64-bit GUI/console version"));
#   else
    msg_puts(_("\nMS-Windows 32-bit GUI/console version"));
#   endif
#  else
#   ifdef _WIN64
    msg_puts(_("\nMS-Windows 64-bit GUI version"));
#   else
    msg_puts(_("\nMS-Windows 32-bit GUI version"));
#   endif
#  endif
#  ifdef FEAT_OLE
    msg_puts(_(" with OLE support"));
#  endif
# else
#  ifdef _WIN64
    msg_puts(_("\nMS-Windows 64-bit console version"));
#  else
    msg_puts(_("\nMS-Windows 32-bit console version"));
#  endif
# endif
#endif
#if defined(MACOS_X)
# if defined(MACOS_X_DARWIN)
    msg_puts(_("\nmacOS version"));
# else
    msg_puts(_("\nmacOS version w/o darwin feat."));
# endif
#endif

#ifdef VMS
    msg_puts(_("\nOpenVMS version"));
# ifdef HAVE_PATHDEF
    if (*compiled_arch != NUL)
    {
	msg_puts(" - ");
	msg_puts((char *)compiled_arch);
    }
# endif

#endif

    /* Print the list of patch numbers if there is at least one. */
    /* Print a range when patches are consecutive: "1-10, 12, 15-40, 42-45" */
    if (included_patches[0] != 0)
    {
	msg_puts(_("\nIncluded patches: "));
	first = -1;
	/* find last one */
	for (i = 0; included_patches[i] != 0; ++i)
	    ;
	while (--i >= 0)
	{
	    if (first < 0)
		first = included_patches[i];
	    if (i == 0 || included_patches[i - 1] != included_patches[i] + 1)
	    {
		msg_puts(s);
		s = ", ";
		msg_outnum((long)first);
		if (first != included_patches[i])
		{
		    msg_puts("-");
		    msg_outnum((long)included_patches[i]);
		}
		first = -1;
	    }
	}
    }

    /* Print the list of extra patch descriptions if there is at least one. */
    if (extra_patches[0] != NULL)
    {
	msg_puts(_("\nExtra patches: "));
	s = "";
	for (i = 0; extra_patches[i] != NULL; ++i)
	{
	    msg_puts(s);
	    s = ", ";
	    msg_puts(extra_patches[i]);
	}
    }

#ifdef MODIFIED_BY
    msg_puts("\n");
    msg_puts(_("Modified by "));
    msg_puts(MODIFIED_BY);
#endif

#ifdef HAVE_PATHDEF
    if (*compiled_user != NUL || *compiled_sys != NUL)
    {
	msg_puts(_("\nCompiled "));
	if (*compiled_user != NUL)
	{
	    msg_puts(_("by "));
	    msg_puts((char *)compiled_user);
	}
	if (*compiled_sys != NUL)
	{
	    msg_puts("@");
	    msg_puts((char *)compiled_sys);
	}
    }
#endif

#ifdef FEAT_HUGE
    msg_puts(_("\nHuge version "));
#else
# ifdef FEAT_BIG
    msg_puts(_("\nBig version "));
# else
#  ifdef FEAT_NORMAL
    msg_puts(_("\nNormal version "));
#  else
#   ifdef FEAT_SMALL
    msg_puts(_("\nSmall version "));
#   else
    msg_puts(_("\nTiny version "));
#   endif
#  endif
# endif
#endif
#ifndef FEAT_GUI
    msg_puts(_("without GUI."));
#else
# ifdef FEAT_GUI_GTK
#  ifdef USE_GTK3
    msg_puts(_("with GTK3 GUI."));
#  else
#   ifdef FEAT_GUI_GNOME
     msg_puts(_("with GTK2-GNOME GUI."));
#   else
     msg_puts(_("with GTK2 GUI."));
#   endif
# endif
# else
#  ifdef FEAT_GUI_MOTIF
    msg_puts(_("with X11-Motif GUI."));
#  else
#   ifdef FEAT_GUI_ATHENA
#    ifdef FEAT_GUI_NEXTAW
    msg_puts(_("with X11-neXtaw GUI."));
#    else
    msg_puts(_("with X11-Athena GUI."));
#    endif
#   else
#     ifdef FEAT_GUI_PHOTON
    msg_puts(_("with Photon GUI."));
#     else
#      if defined(MSWIN)
    msg_puts(_("with GUI."));
#      else
#	if defined(TARGET_API_MAC_CARBON) && TARGET_API_MAC_CARBON
    msg_puts(_("with Carbon GUI."));
#	else
#	 if defined(TARGET_API_MAC_OSX) && TARGET_API_MAC_OSX
    msg_puts(_("with Cocoa GUI."));
#	 else
#	 endif
#	endif
#      endif
#    endif
#   endif
#  endif
# endif
#endif
    version_msg(_("  Features included (+) or not (-):\n"));

    list_features();
    if (msg_col > 0)
	msg_putchar('\n');

#ifdef SYS_VIMRC_FILE
    version_msg(_("   system vimrc file: \""));
    version_msg(SYS_VIMRC_FILE);
    version_msg("\"\n");
#endif
#ifdef USR_VIMRC_FILE
    version_msg(_("     user vimrc file: \""));
    version_msg(USR_VIMRC_FILE);
    version_msg("\"\n");
#endif
#ifdef USR_VIMRC_FILE2
    version_msg(_(" 2nd user vimrc file: \""));
    version_msg(USR_VIMRC_FILE2);
    version_msg("\"\n");
#endif
#ifdef USR_VIMRC_FILE3
    version_msg(_(" 3rd user vimrc file: \""));
    version_msg(USR_VIMRC_FILE3);
    version_msg("\"\n");
#endif
#ifdef USR_EXRC_FILE
    version_msg(_("      user exrc file: \""));
    version_msg(USR_EXRC_FILE);
    version_msg("\"\n");
#endif
#ifdef USR_EXRC_FILE2
    version_msg(_("  2nd user exrc file: \""));
    version_msg(USR_EXRC_FILE2);
    version_msg("\"\n");
#endif
#ifdef FEAT_GUI
# ifdef SYS_GVIMRC_FILE
    version_msg(_("  system gvimrc file: \""));
    version_msg(SYS_GVIMRC_FILE);
    version_msg("\"\n");
# endif
    version_msg(_("    user gvimrc file: \""));
    version_msg(USR_GVIMRC_FILE);
    version_msg("\"\n");
# ifdef USR_GVIMRC_FILE2
    version_msg(_("2nd user gvimrc file: \""));
    version_msg(USR_GVIMRC_FILE2);
    version_msg("\"\n");
# endif
# ifdef USR_GVIMRC_FILE3
    version_msg(_("3rd user gvimrc file: \""));
    version_msg(USR_GVIMRC_FILE3);
    version_msg("\"\n");
# endif
#endif
    version_msg(_("       defaults file: \""));
    version_msg(VIM_DEFAULTS_FILE);
    version_msg("\"\n");
#ifdef FEAT_GUI
# ifdef SYS_MENU_FILE
    version_msg(_("    system menu file: \""));
    version_msg(SYS_MENU_FILE);
    version_msg("\"\n");
# endif
#endif
#ifdef HAVE_PATHDEF
    if (*default_vim_dir != NUL)
    {
	version_msg(_("  fall-back for $VIM: \""));
	version_msg((char *)default_vim_dir);
	version_msg("\"\n");
    }
    if (*default_vimruntime_dir != NUL)
    {
	version_msg(_(" f-b for $VIMRUNTIME: \""));
	version_msg((char *)default_vimruntime_dir);
	version_msg("\"\n");
    }
    version_msg(_("Compilation: "));
    version_msg((char *)all_cflags);
    version_msg("\n");
#ifdef VMS
    if (*compiler_version != NUL)
    {
	version_msg(_("Compiler: "));
	version_msg((char *)compiler_version);
	version_msg("\n");
    }
#endif
    version_msg(_("Linking: "));
    version_msg((char *)all_lflags);
#endif
#ifdef DEBUG
    version_msg("\n");
    version_msg(_("  DEBUG BUILD"));
#endif
}

static void do_intro_line(int row, char_u *mesg, int add_version, int attr);

/*
 * Show the intro message when not editing a file.
 */
    void
maybe_intro_message(void)
{
    if (BUFEMPTY()
	    && curbuf->b_fname == NULL
	    && firstwin->w_next == NULL
	    && vim_strchr(p_shm, SHM_INTRO) == NULL)
	intro_message(FALSE);
}

/*
 * Give an introductory message about Vim.
 * Only used when starting Vim on an empty file, without a file name.
 * Or with the ":intro" command (for Sven :-).
 */
    void
intro_message(
    int		colon)		/* TRUE for ":intro" */
{
    int		i;
    int		row;
    int		blanklines;
    int		sponsor;
    char	*p;
    static char	*(lines[]) =
    {
	N_("VIM - Vi IMproved"),
	"",
	N_("version "),
	N_("by Bram Moolenaar et al."),
#ifdef MODIFIED_BY
	" ",
#endif
	N_("Vim is open source and freely distributable"),
	"",
	N_("Help poor children in Uganda!"),
	N_("type  :help iccf<Enter>       for information "),
	"",
	N_("type  :q<Enter>               to exit         "),
	N_("type  :help<Enter>  or  <F1>  for on-line help"),
	N_("type  :help version8<Enter>   for version info"),
	NULL,
	"",
	N_("Running in Vi compatible mode"),
	N_("type  :set nocp<Enter>        for Vim defaults"),
	N_("type  :help cp-default<Enter> for info on this"),
    };
#ifdef FEAT_GUI
    static char	*(gui_lines[]) =
    {
	NULL,
	NULL,
	NULL,
	NULL,
#ifdef MODIFIED_BY
	NULL,
#endif
	NULL,
	NULL,
	NULL,
	N_("menu  Help->Orphans           for information    "),
	NULL,
	N_("Running modeless, typed text is inserted"),
	N_("menu  Edit->Global Settings->Toggle Insert Mode  "),
	N_("                              for two modes      "),
	NULL,
	NULL,
	NULL,
	N_("menu  Edit->Global Settings->Toggle Vi Compatible"),
	N_("                              for Vim defaults   "),
    };
#endif

    /* blanklines = screen height - # message lines */
    blanklines = (int)Rows - ((sizeof(lines) / sizeof(char *)) - 1);
    if (!p_cp)
	blanklines += 4;  /* add 4 for not showing "Vi compatible" message */

    /* Don't overwrite a statusline.  Depends on 'cmdheight'. */
    if (p_ls > 1)
	blanklines -= Rows - topframe->fr_height;
    if (blanklines < 0)
	blanklines = 0;

    /* Show the sponsor and register message one out of four times, the Uganda
     * message two out of four times. */
    sponsor = (int)time(NULL);
    sponsor = ((sponsor & 2) == 0) - ((sponsor & 4) == 0);

    /* start displaying the message lines after half of the blank lines */
    row = blanklines / 2;
    if ((row >= 2 && Columns >= 50) || colon)
    {
	for (i = 0; i < (int)(sizeof(lines) / sizeof(char *)); ++i)
	{
	    p = lines[i];
#ifdef FEAT_GUI
	    if (p_im && gui.in_use && gui_lines[i] != NULL)
		p = gui_lines[i];
#endif
	    if (p == NULL)
	    {
		if (!p_cp)
		    break;
		continue;
	    }
	    if (sponsor != 0)
	    {
		if (strstr(p, "children") != NULL)
		    p = sponsor < 0
			? N_("Sponsor Vim development!")
			: N_("Become a registered Vim user!");
		else if (strstr(p, "iccf") != NULL)
		    p = sponsor < 0
			? N_("type  :help sponsor<Enter>    for information ")
			: N_("type  :help register<Enter>   for information ");
		else if (strstr(p, "Orphans") != NULL)
		    p = N_("menu  Help->Sponsor/Register  for information    ");
	    }
	    if (*p != NUL)
		do_intro_line(row, (char_u *)_(p), i == 2, 0);
	    ++row;
	}
    }

    /* Make the wait-return message appear just below the text. */
    if (colon)
	msg_row = row;
}

    static void
do_intro_line(
    int		row,
    char_u	*mesg,
    int		add_version,
    int		attr)
{
    char_u	vers[20];
    int		col;
    char_u	*p;
    int		l;
    int		clen;
#ifdef MODIFIED_BY
# define MODBY_LEN 150
    char_u	modby[MODBY_LEN];

    if (*mesg == ' ')
    {
	vim_strncpy(modby, (char_u *)_("Modified by "), MODBY_LEN - 1);
	l = (int)STRLEN(modby);
	vim_strncpy(modby + l, (char_u *)MODIFIED_BY, MODBY_LEN - l - 1);
	mesg = modby;
    }
#endif

    /* Center the message horizontally. */
    col = vim_strsize(mesg);
    if (add_version)
    {
	STRCPY(vers, mediumVersion);
	if (highest_patch())
	{
	    /* Check for 9.9x or 9.9xx, alpha/beta version */
	    if (isalpha((int)vers[3]))
	    {
		int len = (isalpha((int)vers[4])) ? 5 : 4;
		sprintf((char *)vers + len, ".%d%s", highest_patch(),
							 mediumVersion + len);
	    }
	    else
		sprintf((char *)vers + 3, ".%d", highest_patch());
	}
	col += (int)STRLEN(vers);
    }
    col = (Columns - col) / 2;
    if (col < 0)
	col = 0;

    /* Split up in parts to highlight <> items differently. */
    for (p = mesg; *p != NUL; p += l)
    {
	clen = 0;
	for (l = 0; p[l] != NUL
			 && (l == 0 || (p[l] != '<' && p[l - 1] != '>')); ++l)
	{
	    if (has_mbyte)
	    {
		clen += ptr2cells(p + l);
		l += (*mb_ptr2len)(p + l) - 1;
	    }
	    else
		clen += byte2cells(p[l]);
	}
	screen_puts_len(p, l, row, col, *p == '<' ? HL_ATTR(HLF_8) : attr);
	col += clen;
    }

    /* Add the version number to the version line. */
    if (add_version)
	screen_puts(vers, row, col, 0);
}

/*
 * ":intro": clear screen, display intro screen and wait for return.
 */
    void
ex_intro(exarg_T *eap UNUSED)
{
    screenclear();
    intro_message(TRUE);
    wait_return(TRUE);
}
