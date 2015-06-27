#!/bin/sh
source /etc/profile
source ~/.profile
whereis megapov
echo "Rendering..."
d=`date -u +%Y%m%d%H%M%S`
/usr/codebase/c/megapov-1.0/build_unix/megapov +iSaturnCassiniView.pov +w4096 +h4096 +oSaturnCassiniViewBig.png -d -ul +gaSCVFrames/SCV$d.txt +l..
echo "Blurring..."
convert SaturnCassiniViewBig.png -gaussian 6x2 SaturnCassiniViewBlur.png
echo "Shrinking..."
convert SaturnCassiniViewBlur.png -resize 1024x1024 SaturnCassiniView.png 
cp SaturnCassiniView.png ~/public_html
cp SaturnCassiniView.png SCVFrames/SaturnCassiniView$d.png
cp SaturnCassiniView.html ~/public_html
echo "Done"
