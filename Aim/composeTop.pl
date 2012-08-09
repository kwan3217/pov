#!/usr/bin/perl

$fileMap=sprintf("AimTop/AimTopMap.png",$i);
for($i=0;$i<1500;$i++) {
  $fileInFrame=sprintf("AimTop/AimTop%04d.png",$i);
  $fileOutFrame=sprintf("png:AimTop/AimTopComp%04d.png",$i);
  @args=($fileInFrame,$fileMap,$fileOutFrame);
  print("@args\n");
  system "composite",@args;
}

