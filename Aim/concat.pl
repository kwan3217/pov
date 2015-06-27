#!/usr/bin/perl

$num_frames24=1858;

for($orig_frame_num=0;$orig_frame_num<$num_frames24;$orig_frame_num++) {
  printf("ln -s ../FramesPanels/AimPanels%04d.png Frames/Aim%04d.png\n",$orig_frame_num,$orig_frame_num);
}
for($orig_frame_num=0;$orig_frame_num<$num_frames24;$orig_frame_num++) {
  printf("ln -s ../FramesNoLines/AimPanels%04d.png Frames/Aim%04d.png\n",$orig_frame_num,$orig_frame_num+$num_frames24*1);
}
for($orig_frame_num=0;$orig_frame_num<$num_frames24;$orig_frame_num++) {
  printf("ln -s ../FramesWithLines/AimPanels%04d.png Frames/Aim%04d.png\n",$orig_frame_num,$orig_frame_num+$num_frames24*2);
}
