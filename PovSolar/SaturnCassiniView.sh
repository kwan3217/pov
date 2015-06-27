#!/bin/sh
echo "Rendering..."
megapov +iSaturnCassiniView.pov +d +w4096 +h4096 +a0.001 +j0 +r2 +oSaturnCassiniViewBig.png
echo "Blurring..."
convert SaturnCassiniViewBig.png -gaussian 6x2 SaturnCassiniViewBlur.png
echo "Shrinking..."
convert SaturnCassiniViewBlur.png -resize 1024x1024 SaturnCassiniView.png 
cp SaturnCassiniView.png ~/public_html
cp SaturnCassiniView.html ~/public_html
echo "Done"
mozilla file:///home/chrisj/public_html/SaturnCassiniView.html
