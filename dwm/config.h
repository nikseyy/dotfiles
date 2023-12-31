#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const int user_bh            = 25;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */

static const char *fonts[]          = {
    "Terminus:size=13",
};

static const char dmenufont[]       = "Terminus:size=13";

static const char col_allbg[]       = "#090a0b";
static const char col_selfg[]       = "#dcdcdd";
static const char col_norfg[]       = "#adaaaa";
static const char col_selbd[]       = "#dcdcdd";
static const char col_norbd[]       = "#090a0b";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
    [SchemeNorm] = { col_norfg, col_allbg, col_norbd },
    [SchemeSel]  = { col_selfg, col_selfg,  col_selbd  },
    [SchemeStatus]  = { col_selfg, col_allbg,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
    [SchemeTagsSel]  = { col_selfg, col_allbg,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_norfg, col_allbg,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_selfg, col_allbg,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_selfg, col_allbg,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "main", "ext" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
	{ "URxvt",    NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */ /* []= */
	{ "><>",      NULL },    /* no layout function means floating behavior */ /* ><> */
	{ "m",      monocle }, /* [M] */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_allbg, "-nf", col_selfg, "-sb", col_selbd, "-sf", col_norbd, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *flameshot[] = { "flameshot", "gui", NULL };
static const char *filemanager[] = { "urxvt", "-e", "ranger", NULL};
static const char *pulsemixer[] = { "urxvt", "-e", "pulsemixer", NULL};
static const char *htop[] = { "urxvt", "-e", "htop", NULL};
static const char *discord[] = { "discord", NULL};
static const char *keepassxc[] = { "keepassxc", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_i,      spawn,          {.v = keepassxc } },
    { MODKEY,                       XK_l,      spawn,          {.v = discord } },
    { MODKEY,                       XK_h,      spawn,          {.v = htop } },
    { MODKEY,                       XK_k,      spawn,          {.v = pulsemixer } },
    { MODKEY,                       XK_z,      spawn,          {.v = filemanager } },
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_p,      spawn,          {.v = firefox } },
    { 0,                            XK_Print,  spawn,          {.v = flameshot } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { 0,                            XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pamixer --allow-boost -i 5") },
    { 0,                            XF86XK_AudioLowerVolume,  spawn,          SHCMD("pamixer --allow-boost -d 5") },
    { 0,                            XF86XK_AudioMute,         spawn,          SHCMD("pamixer -t") },
    { 0,                            XF86XK_AudioMicMute,      spawn,          SHCMD("pamixer --source 1 -t") },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_t,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_y,      incnmaster,     {.i = -1 } },
    { MODKEY,		            XK_r,      zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,	            XK_q,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_slash,  focusstack,     {.i = +1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

