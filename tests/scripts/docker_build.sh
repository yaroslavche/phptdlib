#!/usr/bin/env sh

tag=$1
from_image=$2
target_image=$3

DOCKERFILE=$TRAVIS_BUILD_DIR/tests/scripts/Dockerfile.$tag

if [ "$JOBS_IN_PARALLEL" = "" ] ; then
    JOBS_IN_PARALLEL=1
fi

docker build \
    -f $DOCKERFILE \
    -t $target_image \
    --build-arg FROM_IMAGE=$from_image \
    --build-arg JOBS_IN_PARALLEL=$JOBS_IN_PARALLEL \
    $TRAVIS_BUILD_DIR
