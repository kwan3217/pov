#!/bin/sh

for i in `ls *.ini`
do
  megapov $i $@
done

