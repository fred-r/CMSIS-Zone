#!/bin/bash
GENTOOL="node ./tools/mini_codegen"
SRC="handlebars"
SRCS="./$SRC/*_template.*"
DEST="handlebars_gen"
DATA="./STM32L5.fzone.json"


# MAIN
rm -rf $DEST
mkdir -p $DEST

for f in `ls $SRCS`
do
	echo "Processing $f"
	res=`echo $f | sed s/_template// | sed s/$SRC/$DEST/`
	$GENTOOL --template $f --data $DATA --output $res
done