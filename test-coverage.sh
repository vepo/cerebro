#! /bin/bash

CDIR=`pwd`

for source_file in $(find src/**/ -name '*.cpp')
do
    echo $source_file
    cd $(dirname $source_file)
    gcov $(basename $source_file) --object-directory $CDIR/build/objects/${PWD##*/}
    cd -
done
lcov --coverage --directory . --output-file main_coverage.info
