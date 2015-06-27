#!/bin/bash
mkdir -p Blur Soft
rm -rfv Blur/* Soft/*

for i in `number 0 119 3`
do
  echo $i
  convert Frames/lasp$i.png -blur 100x30 png24:Blur/lasp$i.png
  composite -blend 100x100 Frames/lasp$i.png Blur/lasp$i.png png24:Soft/lasp$i.png
done
