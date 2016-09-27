#! /bin/bash

function usage()
{
	echo "Usage: ./fast.sh <plugin-name> <pluginClass-name>"
	exit
}

function rename
{
	mv $PLANTILLA.frag $1.frag
	mv $PLANTILLA.vert $1.vert
	mv $PLANTILLA.cpp $1.cpp
	mv $PLANTILLA.h $1.h
	mv $PLANTILLA.pro $1.pro
}

function replace
{
	sed -i -- "s/$PLANTILLA/$PLUGIN_NAME/g" *
	sed -i -- "s/$PLANTILLA_CLASS/$CLASS_NAME/g" *
	UPPER=$(echo $CLASS_NAME | tr '[:lower:]' '[:upper:]')
	sed -i -- "s/$PLANTILLA_UPPER/$UPPER/g" *
}

# check if arguments are correct
if [ "$#" -ne 2 ]
then
    usage
fi

# define variables
PLUGIN_NAME=$1
CLASS_NAME=$2
PLANTILLA=plantilla
PLANTILLA_CLASS=Plantilla
PLANTILLA_UPPER=PLANTILLA

# start operations
echo "SUBDIRS += $PLUGIN_NAME" >> plugins.pro

mkdir $PLUGIN_NAME
cd $PLUGIN_NAME
cp -p ../$PLANTILLA/* .
rename $PLUGIN_NAME
replace
chmod +w $PLUGIN_NAME/*

echo "Creation of $PLUGIN_NAME ended successfully"
exit

