### The patch combo:

- Add [combotag]() and comboview functions to dwm.c
- Replace tag and view function with combotag and comboview respectively in dwm.c and config.h
- Be aware that we will have to replace this in future patches if necessary

- The patch ewmhtags modifies view. So, you have to patch combo first then patch this.
- The patch pertag also modifies view. So, keep that in mind.

Create symlink of powermenu and power_profile in /usr/local/bin/.

Setup [slstatus](../blob/main/slstatus) as you need in its config.h file.
