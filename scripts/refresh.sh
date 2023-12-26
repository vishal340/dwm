#!/bin/sh

responce=0
resolution=$(xrandr | awk '/.*\*.*/{print $1}')
responce=$(($(xrandr | awk '/.*\*.*/{
for(i=2;i<=NF;i++)if($i!="+")print $i 
}' | sed -E 's/(.*)\..*/\1/' | tr " " "\n" | dmenu -l 10 -i -p "choose refresh rate:" )))
exec xrandr -s $resolution -r $responce
