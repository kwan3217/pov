iter=$1
shift 1
for i in `seq 1 $iter`
do
  screen $@
  sleep 1
done
top
