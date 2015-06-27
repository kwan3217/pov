#!/usr/bin/perl

use strict;

#Slurp the file, so that we can do multi-line matches
my $content=do {local ($/);<>};

my $fps=0;
my $numShots=0;
if($content=~/#(declare|local)\s+fps\s*=\s*([0-9]+)\s*;/) {
  $fps=$2;
}
my @ShotTime;
if($content=~/#(declare|local)\s+ShotTime\s*=\s*array\s*\[([0-9]+)]\s*\{([^}]*)\}/) {
  $numShots=$2;
  @ShotTime=split(/\s*,\s*/,$3);
}

my $scene=0;
my $shot=0;
my $frame=0;
my @FNUMS=();
for(my $i=0;$i<$numShots;$i++) {
  if($ShotTime[$i]>=0) {
    my $thisFNUM=sprintf("FNUM_%03d_%03d",$scene,$shot);
    my $thisFRAMES=sprintf("FRAMES_%03d_%03d",$scene,$shot);
    my $thisInc=sprintf("Scene%03d_Shot%03d.inc",$scene,$shot);
    print($thisFNUM." =");
    push(@FNUMS,$thisFNUM);
    my $nFrame=$ShotTime[$i]*$fps;
    for(my $j=0;$j<$nFrame;$j++) {
      printf(" %04d",$j+$frame);
    }
    print("\n");
    printf('%s := $(addprefix $(FRAMEDIR)/Frame,$(%s))'."\n",$thisFRAMES,$thisFNUM);
    printf('%s := $(addsuffix .png,$(%s))'."\n",$thisFRAMES,$thisFRAMES);
    print('$('.$thisFRAMES.'): $(FRAMEDIR)/%.png : Kalman.ini '.$thisInc."\n\n");
#    print("\t".'megapov Kalman.ini +sf$(patsubst $(FRAMEDIR)/Frame%.png,%,$@) +ef$(patsubst $(FRAMEDIR)/Frame%.png,%,$@) > /dev/null 2>&1'."\n\n");
    $frame=$frame+$nFrame;
    $shot++;
  } else {
    $shot=0;
    $scene++;
  }    
}

printf("FNUM =");
foreach my $i (@FNUMS) {
  printf(" \$(%s)",$i);
}
printf("\n\n");


