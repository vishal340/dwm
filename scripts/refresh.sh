#!/bin/sh

#this script lets you change the refresh rate of monitor of your choice in multiple monitor setup.

screens=$(($(xrandr | grep -o 'Screen ' | wc -l)))
echo $screens
if [ $screens -eq 1 ]; then
	resolution=$(xrandr | awk '/.*\*.*/{print $1}')
	response=$(($(xrandr | awk '/.*\*.*/{
for(i=2;i<=NF;i++)if($i!="+")print $i
}' | sed -E 's/(.*)\..*/\1/' | tr " " "\n" | dmenu -l 20 -i -p "choose refresh rate:")))
	xrandr -s $resolution -r $response
else
	choice=0
	mon=0
	for j in $(seq $screens); do
		choice=$(($(echo $j | dmenu -l 1 -m $((j - 1)) -p "Enter:")))
		if [ $choice -gt 0 ]; then
			mon=$((j))
			break
		fi
	done
	resolution=$(xrandr | awk -v var="$mon" '/.*\*.*/{count++; if(count==var)print $1}')
	response=$(($(xrandr | awk -v var="$mon" '/.*\*.*/{count++;
	if(count==var)
for(i=2;i<=NF;i++)if($i!="+")print $i
}' | sed -E 's/(.*)\..*/\1/' | tr " " "\n" | dmenu -m $((mon)) -l 20 -i -p "choose refresh rate:")))
	xrandr -s $resolution -r $response
fi
