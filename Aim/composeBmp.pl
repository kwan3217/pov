#!/usr/bin/perl

for($i=2;$i<3;$i++) {
  $file1=sprintf("AimChase/AimChase%04d.png",$i);
  if(!(-f $file1)) {
    $file1="Blank512x384.png";
  }
  $file2=sprintf("AimCipsComp/AimCipsComp%04d.png",$i);
  if(!(-f $file2)) {
    $file2="Blank512x384.png";
  }
  $file3=sprintf("AimSide/AimSide%04d.png",$i);
  if(!(-f $file3)) {
    $file3="Blank512x384.png";
  }
  $file4=sprintf("AimTop/AimTopComp%04d.png",$i);
  if(!(-f $file4)) {
    $file4="Blank512x384.png";
  }
  $fileout=sprintf("png:Frames/AimQuad%04d.png",$i);
  @args=("-geometry","512x384","-tile","2x2",$file1,$file2,$file3,$file4,"-depth","8",$fileout);
  print("montage @args \n");
  system "montage",@args;
}
