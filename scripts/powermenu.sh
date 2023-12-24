#!/bin/sh

case "$(printf "Shutdown\nReboot\nLock\n" | dmenu -l 10 -i -p "System:")" in
	"Shutdown") sudo poweroff ;;
	"Reboot") sudo reboot ;;
	"Lock") slock ;;
	*) exit 1 ;;
esac
