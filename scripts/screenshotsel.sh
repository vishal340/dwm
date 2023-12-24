#!/bin/sh
mkdir -p $HOME/Pictures/screenshots/ && scrot $HOME/Pictures/screenshots/%m-%d-%Y-%H%M%S.png --select --line mode=edge
