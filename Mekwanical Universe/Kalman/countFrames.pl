#!/usr/bin/perl

use Getopt::Long;

$fps=24;
$start=0;
$infn='';
$digits=3;
$result = GetOptions(
"fps|f=i" => \$fps, # numeric
"file|n=s" => \$infn,
"start|s=i" => \$start,
"digits|d=i" => \$digits);
if($start>0) {
  $start++;
}

open(INF,"<",$infn) or die "Couldn't open input file $infn\n";

while(<INF>) {
  if($_=~/\s*#local\s+ShotTime\s*=\s*array\s*\[([0-9]+)]\s*{([^}]*)}/) {
    @shots=split(/\s*,\s*/,$2);
    $acc=0;
    foreach $i (@shots) {
      $acc+=$i;
    }
    for($i=0;$i<$acc*$fps;$i++) {
      $pat=sprintf("%%0%dd ",$digits);
      printf($pat,$i+$start);
    }
    print "\n";
  }
}
