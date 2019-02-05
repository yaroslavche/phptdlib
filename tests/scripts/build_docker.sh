#!/usr/bin/env sh

os=$1
linktype=$2
imagename=$3

DOCKERFILE=$TRAVIS_BUILD_DIR/tests/scripts/Dockerfile.$os-$linktype
#IMAGENAME=phptdlib/$os-$linktype

docker build -f $DOCKERFILE -t $imagename $TRAVIS_BUILD_DIR