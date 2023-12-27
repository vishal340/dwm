#!/bin/sh

#this script lets you change the refresh rate of monitor of your choice in multiple monitor setup.

screens=$(($(xrandr | grep -o 'Screen ' | wc -l)))
if [ $screens -eq 1 ]; then
	resolution=$(xrandr | awk '/.*\*.*/{print $1}')
	response=$(($(xrandr | awk '/.*\*.*/{
for(i=2;i<=NF;i++)if($i!="+")print $i
}' | sed -E 's/(^[^.*]*).*/\1/' | tr " " "\n" | dmenu -l 20 -i -p "choose refresh rate:")))
	xrandr -s $resolution -r $response 2>/dev/null
else
	choice=-1
	choice=$(($(for j in $(seq $screens); do
		echo $j | dmenu -l 1 -m $((j - 1)) -p "Press Enter:" &
	done)))
	if [ $choice -gt 0 ]; then
		mon=$((choice - 1))
		pkill -9 dmenu 2>/dev/null
		resolution=$(xrandr | awk -v var="$choice" -v count=0 '/.*\*.*/{count++; if(count==var)print $1}')
		response=$(($(xrandr | awk -v var="$choice" -v count=0 '/.*\*.*/{count++;
	if(count==var)
for(i=2;i<=NF;i++)if($i!="+")print $i
}' | sed -E 's/(^[^.*]*).*/\1/' | tr " " "\n" | dmenu -m $mon -l 20 -i -p "choose refresh rate:")))
		xrandr -s $resolution -r $response 2>/dev/null
		exit
	fi
fi
