#!/usr/bin/perl

$fileMap=sprintf("AimQuadLabel.png",$i);
for($i=2;$i<3;$i++) {
  $fileInFrame=sprintf("Frames/AimQuad%04d.png",$i);
  $fileOutFrame=sprintf("png:AimQuad%04d.png",$i);
  @args=($fileMap,$fileInFrame,$fileOutFrame);
  print("@args\n");
  system "composite",@args;
}
#for($i=0;$i<50;$i++) {
#  $fileInFrame=sprintf("Frames/AimQuad%04d.png",$i+100);
#  $fileOutFrame=sprintf("png:AimQuad%04d.png",$i+100);
#  @args=("-dissolve",sprintf("%d",100-$i*2),$fileMap,$fileInFrame,$fileOutFrame);
#  print("@args\n");
#  system "composite",@args;
#}

