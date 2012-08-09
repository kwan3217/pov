#!/bin/sh
#usage:
#  MakeMpegNoSound.sh image_prefix mpeg_suffix x/y(aspect)
mencoder -ovc lavc -of mpeg -mpegopts format=dvd:tsaf \
  -mf fps=30000/1001 \
  -lavcopts vpass=1:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=11000:vbitrate=8000:keyint=18:vstrict=0:aspect=$3 -ofps 30000/1001 \
  -o /dev/null "mf://$1*.png" &&
mencoder -ovc lavc -of mpeg -mpegopts format=dvd:tsaf \
  -mf fps=30000/1001 \
  -lavcopts vpass=2:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=11000:vbitrate=8000:keyint=18:vstrict=0:aspect=$3 -ofps 30000/1001 \
  -o ../${1}${2}.mpg "mf://$1*.png" &&
rm -v divx2pass.log &&
echo "Done!"



