#!/bin/sh

case "$(printf "power-saver\nbalanced\nperformance\n" | dmenu -l 10 -i -p "System:")" in
	"power-saver") powerprofilesctl set power-saver ;;
	"balanced") powerprofilesctl set balanced ;;
	"performance") powerprofilesctl set performance ;;
	*) exit 1 ;;
esac
