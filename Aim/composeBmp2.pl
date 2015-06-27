#!/usr/bin/perl

for($i=110;$i<190;$i++) {
  $file1=sprintf("Frames/AimChase%03d.tga",$i);
  if(!(-f $file1)) {
    $file1="Blank512x384.png";
  }
  $file2=sprintf("Frames/AimCipsComp%03d.tga",$i);
  if(!(-f $file2)) {
    $file2="Blank512x384.png";
  }
  $file3=sprintf("Frames/AimSide%03d.tga",$i);
  if(!(-f $file3)) {
    $file3="Blank512x384.png";
  }
  $file4=sprintf("Frames/AimTopComp%03d.tga",$i);
  if(!(-f $file4)) {
    $file4="Blank512x384.png";
  }
  $fileout=sprintf("tga:Frames/Aim%03d.tga",$i);
  @args=("-geometry","512x384","-tile","2x2",$file1,$file2,$file3,$file4,"-depth","8",$fileout);
  print("montage @args \n");
  system "montage",@args;
}
