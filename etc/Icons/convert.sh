#!/bin/sh

for f in $1/*.svg
do
    for dpi in 96 192
    do
        base=$(basename -s .svg $f)
        png=${base}_${dpi}dpi.png
        inkscape $f -o $png -d $dpi
        bin/dtkresource/Debug/dtkresource.exe $png $1/${base}_${dpi}.h ${base}_${dpi}_png
    done
done

