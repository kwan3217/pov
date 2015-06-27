#!/bin/sh
#usage
#  ./MakeMpeg.sh framefile fps sound name
#framefile should be something like Frames/MovieName%04d.png

ffmpeg -threads 9 -f image2 -r $2 -i $1       -s 854x480 -b 1000k -pass 1 -f mp4 -y /dev/null
if [ -f $3 ]
then
ffmpeg -threads 9 -f image2 -r $2 -i $1 -i $3 -s 854x480 -b 1000k -pass 2        -y ${4}.mp4
else
ffmpeg -threads 9 -f image2 -r $2 -i $1       -b 2000k -pass 2        -y ${4}.mp4
fi

rm -v ffmpeg2pass-0.log


