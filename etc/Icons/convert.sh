#!/bin/sh

for f in $1/*.svg
do
        base=$(basename -s .svg $f)
        bin/dtkresource/Debug/dtkresource.exe $f $1/${base} ${base}_svg
done

