cd $1
convert -depth $2 -size 1350x675 $3:${1}0 ${1}0.png
rm ${1}0
rm ${1}1
rm ${1}2
rm ${1}3
rm ${1}4
bzip2 ${1}5

