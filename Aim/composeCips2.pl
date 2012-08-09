#!/usr/bin/perl

for($i=140;$i<160;$i++) {
  $filein=sprintf("Frames/AimAtt%03d.tga",$i);
  if(!(-e $filein)) {
    $filein="Blank1024x768.tga";
  }
  $fileF=sprintf("Frames/AimCips%04d.tga",$i);
  if(!(-e $fileF)) {
    $fileF="Blank256x256.tga";
  }
  $fileA=sprintf("Frames/AimCips%04d.tga",$i+300);
  if(!(-e $fileA)) {
    $fileA="Blank256x256.tga";
  }
  $fileL=sprintf("Frames/AimCips%04d.tga",$i+600);
  if(!(-e $fileL)) {
    $fileL="Blank256x256.tga";
  }
  $fileR=sprintf("Frames/AimCips%04d.tga",$i+900);
  if(!(-e $fileR)) {
    $fileR="Blank256x256.tga";
  }
#  $fileSofie=sprintf("Frames/AimSofie%03d.tga",$i);
#  if(!(-e $fileSofie)) {
    $fileSofie="Blank512x384.tga";
#  }
  $fileout=sprintf("tga:Frames/AimCipsComp%03d.tga",$i);
  @args=("-geometry","256x256+512+128",$fileF,$filein,"-depth","8","/tmp/Out1.png");
  print("@args\n");
  system "composite",@args;
  @args=("-geometry","256x256+0+128",$fileA,"/tmp/Out1.png","-depth","8","/tmp/Out2.png");
  print("@args\n");
  system "composite",@args;
  @args=("-geometry","256x256+256+0",$fileL,"/tmp/Out2.png","-depth","8","/tmp/Out3.png");
  print("@args\n");
  system "composite",@args;
  @args=("-geometry","256x256+256+256",$fileR,"/tmp/Out3.png","-depth","8","/tmp/Out4.png");
  print("@args\n");
  system "composite",@args;
  @args=("-geometry","512x384+512+384",$fileSofie,"/tmp/Out4.png","-depth","8",$fileout);
  print("@args\n");
  system "composite",@args;
}
