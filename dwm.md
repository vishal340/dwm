### The patch combo:

- Add combotag() and comboview() functions to [dwm.c][1]
- Replace tag and view function with combotag and comboview respectively in [dwm.c][1] and [config.h]
- Be aware that we will have to replace this in future patches if necessary

- The patch [ewmhtags](../../tree/master/patches/dwm-ewmhtags-6.2.diff) modifies view. So, you have to patch combo first then patch this.
- The patch [pertag](../../tree/master/patches/dwm-pertag-20200914-61bb8b2.diff) also modifies view. So, keep that in mind.

### Symlinks from scripts

Create symlink of startdwm, powermenu, power_profile, bluetooth_battery, refresh and screen_brightness in /usr/local/bin/.

Also, create a symlink of **dwm.desktop** and **startdwm** in /usr/share/xsessions/ and ~/.local/bin/ directory respectively.

### Tricky conflict with title

Here we two patches [notitle](../../tree/master/patches/dwm-notitle-20210715-138b405.diff) and [awesomebar](../../tree/master/patches/dwm-awesomebar-20230431-6.4.diff).
Awesomebar wants to show title with click to jump support but notitle won't show title.
So, while patching awesomebar one will have to ignore patching anything in buttonpress() function in [dwm.c][1].
Also ignore CLkWinTitle in [config.h][2].

[1](../master/dwm.c)
[2](../master/config.h)
