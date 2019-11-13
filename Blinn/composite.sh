for i in Frames/SuperTrajectory_*
do 
    subi=`basename $i .png`
    n=${subi:16:4}
    echo $n
    montage Frames/SuperTrajectory_$n.png Prototype/frame$n.png -tile 2x1 -geometry x720+0+0 Frames/comp$n.png
done

