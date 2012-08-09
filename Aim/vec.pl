#!/usr/bin/perl

$last=-1;
while(<>) {
  if(/\S*\s(\d\d):(\d\d):(\d\d),\s*(\S*),\s*(\S*),\s*(\S*)/) {
    $this=$1*3600+$2*60+$3;
    if($last<$this) {
      print "{".$this .",". $4 .",". $5 .",". $6 ."}\n";
      $last=$this;
    }
  }
}
