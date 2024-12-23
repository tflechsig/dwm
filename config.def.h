/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 4;  /* border pixel of windows */
static const unsigned int gappx       = 10; /* gap pixel between windows */
static const unsigned int snap        = 32; /* snap pixel */
static const int showbar              = 1;  /* 0 means no bar */
static const int topbar               = 1;  /* 0 means bottom bar */
static const int vertpad              = 10; /* vertical padding of bar */
static const int sidepad              = 10; /* horizontal padding of bar */
static const char buttonbar[]         = "";
static const int focusonwheel         = 0;
static const char *fonts[]            = { "JetBrains Mono Nerd Font:size=12" };
static const char col_polar_night1[]  = "#2E3440";
static const char col_polar_night2[]  = "#434C5E";
static const char col_snow1[]         = "#D8DEE9";
static const char col_snow2[]         = "#ECEFF4";
static const char col_frost[]         = "#88C0D0";
static const char *colors[][3]        = {
  /*                    fg                bg                border          */
  [SchemeNorm]      = { col_snow1       , col_polar_night1, col_polar_night2},
  [SchemeSel]       = { col_snow1       , col_polar_night1, col_frost       },
  [SchemeTagUnocc]  = { col_polar_night2, col_polar_night1, col_frost       },
};

/* tagging */
static const int num_tags = 4;
/*                                  Active   Inactive */
static const char *tag_symbols[] = {"", ""};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Gimp",     NULL,       NULL,       0,            1,           -1 },
  { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "טּ",      deck },
  { "",      monocle },
  { "",      tile },    /* first entry is default */
  { "",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEYALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[]  = { "rofi", "-show", "drun", NULL};
static const char *termcmd[]  = { "alacritty", NULL };

static const Key keys[] = {
  /* modifier             key        function        argument */
  { MODKEY,               XK_p,      spawn,          {.v = dmenucmd } },
  { MODKEY,               XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,               XK_b,      togglebar,      {0} },
  { MODKEY,               XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,               XK_k,      focusstack,     {.i = -1 } },
  { MODKEYALT,            XK_Tab,    focusstack,     {.i = +1 } },
  { MODKEYALT|ShiftMask,  XK_Tab,    focusstack,     {.i = -1 } },
  { MODKEY,               XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,               XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,               XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,               XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,               XK_space,  zoom,           {0} },
  { MODKEY,               XK_Tab,    view,           {0} },
  { MODKEY,               XK_c,      killclient,     {0} },
  { MODKEY,               XK_r,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,               XK_m,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,               XK_t,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,               XK_f,      setlayout,      {.v = &layouts[3]} },
  { MODKEY,               XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,     XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,               XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,               XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,     XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,     XK_period, tagmon,         {.i = +1 } },
  TAGKEYS(                XK_1,                      0)
  TAGKEYS(                XK_2,                      1)
  TAGKEYS(                XK_3,                      2)
  TAGKEYS(                XK_4,                      3)
  { MODKEY|ShiftMask,     XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask      button          function        argument */
	{ ClkButton,		        0,		          Button1,	      spawn,		      {.v = dmenucmd } },
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

