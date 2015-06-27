cd $1
cd 5
for i in `ls *[^.][^p][^n][^g]`
do
echo $i
convert -depth $2 -size 270x270 $3:$i $i.png && rm $i
done

cd ../4
for i in `ls *[^.][^p][^n][^g]`
do
echo $i
convert -depth $2 -size 270x270 $3:$i $i.png && rm $i
done

cd ../3
for i in `ls *[^.][^p][^n][^g]`
do
echo $i
convert -depth $2 -size 270x270 $3:$i $i.png && rm $i
done

cd ../2
for i in `ls *[^.][^p][^n][^g]`
do
echo $i
convert -depth $2 -size 270x270 $3:$i $i.png && rm $i
done

cd ../1
for i in `ls *[^.][^p][^n][^g]`
do
echo $i
convert -depth $2 -size 270x270 $3:$i $i.png && rm $i
done

