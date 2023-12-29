#!/bin/sh

#this script lets you change the refresh rate of monitor of your choice in multiple monitor setup.

screen=$(($(xdotool get_desktop)))
resolution=$(xrandr | awk -v var="$screen" -v count=0 '/.*\*.*/{count++; if(count==var)print $1}')
response=$(($(xrandr | awk -v var="$screen" -v count=0 '/.*\*.*/{count++;
	if(count==var)
for(i=2;i<=NF;i++)if($i!="+")print $i
}' | sed -E 's/(^[^.*]*).*/\1/' | tr " " "\n" | dmenu -m $((screen - 1)) -l 20 -i -p "choose refresh rate:")))
xrandr -s $resolution -r $response 2>/dev/null
