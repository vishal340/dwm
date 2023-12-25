/* See LICENSE file for copyright and license details. */ /* alt-tab
                                                             configuration */
static const unsigned int tabModKey =
    0x40; /* if this key is hold the alt-tab functionality stays acitve. This
             key must be the same as key that is used to active functin
             altTabStart `*/
static const unsigned int tabCycleKey =
    0x17; /* if this key is hit the alt-tab program moves one position forward
             in clients stack. This key must be the same as key that is used to
             active functin altTabStart */
static const unsigned int tabCycleKey2 = 0x31; /* grave key */
static const unsigned int tabPosY =
    1; /* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX =
    1; /* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab = 600; /* tab menu width */
static const unsigned int maxHTab = 200; /* tab menu height */

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
static const double defaultopacity = 0.8;
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
    {"calnulator", spcmd2},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6",
                             "7", "8", "9", "0", "-", "="};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor
       float x,y,w,h         floatborderpx*/
    {"microsoft-edge-stable", NULL, NULL, 1 << 1, 0, -1, 40, 23, 80, 45, 1},
    {"bitwarden-desktop", NULL, NULL, ~0, 1, -1, 0, 0, 48, 27, 1},
    {"qalculate-qt", NULL, NULL, ~0, 1, -1, 40, 23, 48, 27, 1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
#define FORCE_VSPLIT 1

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"HHH", grid}, {"TTT", bstack}, {"===", bstackhoriz},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *clipmenu[] = {"clipmenu", NULL};
static const char *brightnessup[] = {"brightnessctl", "s", "10+", NULL};
static const char *brightnessdown[] = {"brightnessctl", "s", "10-", NULL};
static const char *kbdbrightnessup[] = {
    "brightnessctl", "--device=asus::kbd_backlight", "s", "1+", NULL};
static const char *kbdbrightnessdown[] = {
    "brightnessctl", "--device=asus::kbd_backlight", "s", "1-", NULL};
static const char *up_vol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@",
                               "+10%", NULL};
static const char *down_vol[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@",
                                 "-10%", NULL};
static const char *mute_vol[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@",
                                 "toggle", NULL};
static const char *termcmd[] = {"alacritty", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {0, 0x1008FF02, spawn, {.v = brightnessup}},
    {0, 0x1008FF03, spawn, {.v = brightnessdown}},
    {0, 0x1008FF05, spawn, {.v = kbdbrightnessup}},
    {0, 0x1008FF06, spawn, {.v = kbdbrightnessdown}},
    {0, 0x1008FF12, spawn, {.v = mute_vol}},
    {0, 0x1008FF11, spawn, {.v = down_vol}},
    {0, 0x1008FF13, spawn, {.v = up_vol}},
    {0, XK_Print, spawn, SHCMD("$HOME/Downloads/dwm/scripts/screenshot.sh")},
    {ShiftMask, XK_Print, spawn,
     SHCMD("$HOME/Downloads/dwm/scripts/screenshotsel.sh")},
    {MODKEY | ShiftMask, XK_s, spawn, SHCMD("transset-df -a --dec .1")},
    {MODKEY | ShiftMask, XK_d, spawn, SHCMD("transset-df -a --inc .1")},
    {MODKEY | ShiftMask, XK_f, spawn, SHCMD("transset-df -a .75")},
    {MODKEY | ShiftMask, XK_e, spawn, SHCMD("powermenu")},
    {MODKEY | ShiftMask, XK_p, spawn,
     SHCMD("$HOME/Downloads/dwm/scripts/power_profile.sh")},
    {MODKEY, XK_p, spawn, SHCMD("$HOME/Downloads/dwm/dmenu_run_history")},
    {MODKEY, XK_c, spawn, {.v = clipmenu}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_s, togglesticky, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, XK_j, inplacerotate, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, inplacerotate, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_q, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[4]}},
    {MODKEY | ShiftMask, XK_g, setlayout, {.v = &layouts[5]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    // {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {Mod1Mask, XK_Tab, altTabStart, {.i = 1}},
    {Mod1Mask | ShiftMask, XK_Tab, altTabStart, {.i = 0}},
    {MODKEY, XK_y, togglescratch, {.ui = 0}},
    {MODKEY, XK_u, togglescratch, {.ui = 1}},
    {MODKEY, XK_x, togglescratch, {.ui = 2}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8) TAGKEYS(XK_0, 9) TAGKEYS(XK_minus, 10)
                TAGKEYS(XK_equal, 11){MODKEY | ShiftMask, XK_q, quit, {0}},
    {MODKEY, XK_semicolon, togglemark, {0}},
    {MODKEY, XK_o, swapfocus, {0}},
    {MODKEY | ShiftMask, XK_o, swapclient, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button1, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
