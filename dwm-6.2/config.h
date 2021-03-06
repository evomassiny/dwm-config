/* See LICENSE file for copyright and license details. */
#include "keys.h"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char * LOG_FILE = NULL;
//static char LOG_FILE[] = "/home/yvesmo/.dwm-log.log";

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
/* USER defined commands */
static const char *browser_cmd[]  = { "firefox", NULL };
// sound command
static const char *up_vol[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *down_vol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *screenshot[] = { "/home/yvesmo/bin/dwm/dwm-6.2/scripts/take_screenshot.sh", NULL };
// spotify commands
static const char *pause_song[] = {"dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.PlayPause", NULL};
static const char *next_song[] = {"dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Next", NULL};
static const char *previous_song[] = {"dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Previous", NULL};


/* key bindings */
static Key keys[] = {
	/* modifier             key    function        argument */
	{ MODKEY|ShiftMask,     CODE_return,    spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,     CODE_backspace, spawn,          {.v = browser_cmd } },
	{ MODKEY,               CODE_p,         spawn,          {.v = dmenucmd } },
	{ MODKEY,               CODE_b,         togglebar,      {0} },
	{ MODKEY,               CODE_j,         focusstack,     {.i = +1 } },
	{ MODKEY,               CODE_k,         focusstack,     {.i = -1 } },
	{ MODKEY,               CODE_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,               CODE_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,               CODE_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,               CODE_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,               CODE_return,    zoom,           {0} },
	{ MODKEY,               CODE_tab,       view,           {0} },
	{ MODKEY|ShiftMask,     CODE_c,         killclient,     {0} },
        // Sound Command
	{ MODKEY,               CODE_pageup,    spawn,           {.v = up_vol} },
	{ MODKEY,               CODE_pagedown,  spawn,           {.v = down_vol} },
        // Screenshot
	{ MODKEY,               CODE_screencap, spawn,           {.v = screenshot} },
        // layout config
	{ MODKEY,               CODE_t,         setlayout,      {.v = &layouts[0]} }, // tiled
	{ MODKEY,               CODE_f,         setlayout,      {.v = &layouts[1]} }, // floating
	{ MODKEY,               CODE_z,         setlayout,      {.v = &layouts[2]} }, // monocle layout
	{ MODKEY,               CODE_space,     setlayout,      {0} },
	{ MODKEY|ShiftMask,     CODE_q,         quit,           {0} },
	{ MODKEY|ShiftMask,     CODE_space,     togglefloating, {0} },
	{ MODKEY,               CODE_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     CODE_0,         tag,            {.ui = ~0 } },
        // moves between monitors
	{ MODKEY,               CODE_g,         focusmon,       {.i = -1 } },
	{ MODKEY,               CODE_m,         focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     CODE_g,         tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     CODE_m,         tagmon,         {.i = +1 } },
        // move between tags
	TAGKEYS(                CODE_1,                    0)
	TAGKEYS(                CODE_2,                    1)
	TAGKEYS(                CODE_3,                    2)
	TAGKEYS(                CODE_4,                    3)
	TAGKEYS(                CODE_5,                    4)
	TAGKEYS(                CODE_6,                    5)
	TAGKEYS(                CODE_7,                    6)
	TAGKEYS(                CODE_8,                    7)
	TAGKEYS(                CODE_9,                    8)
        {ShiftMask,             CODE_left_arrow,    move_focus_to_right_or_left_tag, {.i = -1}},
        {ShiftMask,             CODE_right_arrow,   move_focus_to_right_or_left_tag, {.i = +1}},
        // Spotify commands
	{ MODKEY,               CODE_end,           spawn,  {.v = pause_song} },
	{ MODKEY,               CODE_left_arrow,    spawn,  {.v = previous_song} },
	{ MODKEY,               CODE_right_arrow,   spawn,  {.v = next_song} },
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
