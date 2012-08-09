#!/usr/bin/perl

$frames=36;

$filein="Blank340x1020.png";
for($i=0;$i<$frames;$i++) {
  $fileF=sprintf("Frames/CIPSCamera%03d.png",$i*4+0);
  $fileA=sprintf("Frames/CIPSCamera%03d.png",$i*4+1);
  $fileL=sprintf("Frames/CIPSCamera%03d.png",$i*4+2);
  $fileR=sprintf("Frames/CIPSCamera%03d.png",$i*4+3);

  $fileout=sprintf("png:Frames/CipsCameraComp%02d.png",$i);
  @args=("-verbose","-geometry","+85+0!",$fileF,$filein,"-depth","8","/tmp/Out1.png");
  print("composite @args\n");
  system "composite",@args;
  @args=("-verbose","-geometry","+85+680!",$fileA,"/tmp/Out1.png","-depth","8","/tmp/Out2.png");
  print("composite @args\n");
  system "composite",@args;
  @args=("-verbose","-geometry","+0+340!",$fileR,"/tmp/Out2.png","-depth","8","/tmp/Out3.png");
  print("composite @args\n");
  system "composite",@args;
  @args=("-verbose","-geometry","+170+340!",$fileL,"/tmp/Out3.png","-depth","8",$fileout);
  print("composite @args\n");
  system "composite",@args;
  @args=("-verbose",$fileout,"-resize","680x1020!",$fileout);
  print("convert @args\n");
  system "convert",@args;
}
