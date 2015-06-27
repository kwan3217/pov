#!/usr/bin/perl

$frames=1500;

for($i=0;$i<$frames;$i++) {
  $filein=sprintf("Frames/AimAtt%04d.png",$i);
  if(!(-e $filein)) {
    $filein="Blank1024x768.png";
  }
  $fileF=sprintf("AimCips/AimCips%04d.png",$i);
  if(!(-e $fileF)) {
    $fileF="Blank256x256.png";
  }
  $fileA=sprintf("AimCips/AimCips%04d.png",$i+$frames);
  if(!(-e $fileA)) {
    $fileA="Blank256x256.png";
  }
  $fileL=sprintf("AimCips/AimCips%04d.png",$i+$frames*2);
  if(!(-e $fileL)) {
    $fileL="Blank256x256.png";
  }
  $fileR=sprintf("AimCips/AimCips%04d.png",$i+$frames*3);
  if(!(-e $fileR)) {
    $fileR="Blank256x256.png";
  }
  $fileSofie=sprintf("Frames/AimSofie%04d.png",$i);
  if(!(-e $fileSofie)) {
    $fileSofie="Blank512x384.png";
  }
  $fileout=sprintf("png:Frames/AimCipsComp%04d.png",$i);
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
