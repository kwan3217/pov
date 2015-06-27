#!/bin/bash
start=0
end=14525

while getopts ":s:e:" options
do
  case $options in
    s ) 
      start=$OPTARG
      ;;
    e ) 
      end=$OPTARG
      ;;
  esac
done
shift $(($OPTIND - 1))

for i in `number $start $end 5`
do 
  #Make composite HD No-HUD frame
  ip1=`echo $i+1 | bc`
  bg=`head sky.txt -n $ip1 | tail -n 1` 
  convert -size 1280x720 xc:$bg Mars/Mars${i}.png -composite Anim/Phoenix${i}.png -composite png24:NoHudHD/Frame${i}.png

  #Scale it to SD
  convert NoHudHD/Frame${i}.png -crop 960x720+160+0 -scale 640x480 png24:NoHudSD/Frame${i}.png

  cmdHD="NoHudHD/Frame${i}.png"
  cmdSD="NoHudSD/Frame${i}.png"
  #Add Clock HUD
  if [ -f Clock/clock${i}.png ]
  then
    cmdHD="$cmdHD Clock/clock${i}.png -geometry +20+20 -composite"
    cmdSD="$cmdSD Clock/clock${i}.png -geometry +20+20 -composite"
  fi

  #Add EightBall HUD
  if [ -f EightBall/EightBall${i}.png ]
  then
    cmdHD="$cmdHD EightBall/EightBall${i}.png -geometry 120x120+1140+20 -composite"
    cmdSD="$cmdSD EightBall/EightBall${i}.png -geometry 120x120+500+20 -composite"
  fi

  #Add VTOL HUD
  if [ -f vtol/VTOL${i}.png ]
  then
    cmdHD="$cmdHD vtol/VTOL${i}.png -geometry +1060+500 -composite"
    cmdSD="$cmdSD vtol/VTOL${i}.png -geometry +420+260 -composite"
  fi

  convert $cmdHD png24:FramesHD/Frame${i}.png
  convert $cmdSD png24:FramesSD/Frame${i}.png

  echo $i
done
