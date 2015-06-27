start=0
end=13151

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
  inkscape --export-png=vtol30/VTOL${i}.png svg30/VTOL${i}.svg
done
