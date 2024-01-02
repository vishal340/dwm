/* See LICENSE file for copyright and license details. */ /* alt-tab
                                                             configuration */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const char *fonts[] = {"monospace:size=10"};
static const char dmenufont[] = "monospace:size=10";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#005577";
static const char normmarkcolor[] =
    "#775500"; /*border color for marked client*/
static const char selmarkcolor[] =
    "#775577"; /*border color for marked client on focus*/

static const char *colors[][4] = {
    /*               fg         bg         border     mark   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2, normmarkcolor},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan, selmarkcolor},
    [SchemeHid] = {col_cyan, col_gray1, col_cyan},
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;
const char *spcmd1[] = {"bitwarden-desktop", NULL};
const char *spcmd2[] = {"qalculate-qt", NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"Bitwarden", spcmd1},
    {"calculator", spcmd2},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor
       float x,y,w,h         floatborderpx*/
    {NULL, "bitwarden", NULL, ~0, 1, -1, 0, 0, 48, 27, 1},
    {NULL, "qalculate-qt", NULL, ~0, 1, -1, 0, 0, 48, 27, 1},
    {NULL, "steam", NULL, 1 << 7, 0, -1, 0, 0, 48, 27, 1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"

/* mouse scroll resize */
static const int scrollsensetivity =
    30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},     {"HHH", grid},       {"TTT", bstack},
    {"===", bstackhoriz}, {"III", horizontal},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, comboview, {.ui = 1 << TAG}},                                  \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, combotag, {.ui = 1 << TAG}},                   \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *clipmenu[] = {"clipmenu", NULL};
static const char *kbdbrightnessup[] = {
    "brightnessctl", "--device=asus::kbd_backlight", "s", "1+", NULL};
static const char *kbdbrightnessdown[] = {
    "brightnessctl", "--device=asus::kbd_backlight", "s", "1-", NULL};
static const char *termcmd[] = {"alacritty", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {0, 0x1008FF02, spawn, SHCMD("screen_brightness 1")},
    {0, 0x1008FF03, spawn, SHCMD("screen_brightness 2")},
    {0, 0x1008FF05, spawn, {.v = kbdbrightnessup}},
    {0, 0x1008FF06, spawn, {.v = kbdbrightnessdown}},
    {0, 0x1008FF12, spawn, SHCMD("volume_change 2")},
    {0, 0x1008FF11, spawn, SHCMD("volume_change 1")},
    {0, 0x1008FF13, spawn, SHCMD("volume_change 3")},
    {MODKEY, XK_Tab, spawn, SHCMD("$HOME/Downloads/dwm/scripts/switch.sh")},
    {0, XK_Print, spawn, SHCMD("$HOME/Downloads/dwm/scripts/screenshot.sh")},
    {ShiftMask, XK_Print, spawn,
     SHCMD("$HOME/Downloads/dwm/scripts/screenshotsel.sh")},
    {MODKEY | ShiftMask, XK_e, spawn, SHCMD("powermenu")},
    {MODKEY | ShiftMask, XK_p, spawn, SHCMD("power_profile")},
    {MODKEY, XK_p, spawn, SHCMD("$HOME/Downloads/dwm/dmenu_run_history")},
    {MODKEY | ShiftMask, XK_r, spawn,
     SHCMD("$HOME/Downloads/dwm/scripts/refresh.sh")},
    {MODKEY, XK_c, spawn, {.v = clipmenu}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_s, togglesticky, {0}},
    {MODKEY, XK_j, focusstackvis, {.i = +1}},
    {MODKEY, XK_k, focusstackvis, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, focusstackhid, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, focusstackhid, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_q, comboview, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_e, setlayout, {.v = &layouts[6]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[4]}},
    {MODKEY | ShiftMask, XK_g, setlayout, {.v = &layouts[5]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY | ControlMask, XK_space, focusmaster, {0}},
    {MODKEY, XK_0, comboview, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, combotag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_s, show, {0}},
    {MODKEY | ControlMask | ShiftMask, XK_s, showall, {0}},
    {MODKEY | ShiftMask, XK_h, hide, {0}},
    {MODKEY, XK_Right, viewnext, {0}},
    {MODKEY, XK_Left, viewprev, {0}},
    {MODKEY | ShiftMask, XK_Right, tagtonext, {0}},
    {MODKEY | ShiftMask, XK_Left, tagtoprev, {0}},
    {MODKEY, XK_y, togglescratch, {.ui = 0}},
    {MODKEY, XK_u, togglescratch, {.ui = 1}},
    {MODKEY, XK_x, togglescratch, {.ui = 2}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY, XK_semicolon, togglemark, {0}},
    {MODKEY | ShiftMask, XK_semicolon, swapfocus, {0}},
    {MODKEY | ControlMask | ShiftMask, XK_semicolon, swapclient, {0}},
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
    /* width change         height change */
    {+scrollsensetivity, 0},
    {-scrollsensetivity, 0},
    {0, +scrollsensetivity},
    {0, -scrollsensetivity},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkStatusText, 0, Button1, sigstatusbar, {.i = 1}},
    {ClkStatusText, 0, Button2, sigstatusbar, {.i = 2}},
    {ClkStatusText, 0, Button3, sigstatusbar, {.i = 3}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, resizemousescroll, {.v = &scrollargs[0]}},
    {ClkClientWin, MODKEY, Button5, resizemousescroll, {.v = &scrollargs[1]}},
    {ClkClientWin, MODKEY, Button6, resizemousescroll, {.v = &scrollargs[2]}},
    {ClkClientWin, MODKEY, Button7, resizemousescroll, {.v = &scrollargs[3]}},
    {ClkTagBar, 0, Button1, comboview, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, combotag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
