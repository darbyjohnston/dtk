#!/bin/sh

for f in $1/*.svg
do
        base=$(basename -s .svg $f)
        bin/dtkresource/dtkresource $f $1/${base} ${base}_svg
done

