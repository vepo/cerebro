#! /bin/bash -e

CDIR=`pwd`

for object_file in $(find build/**/ -name '*.o')
do
    gcov $object_file --relative-only
done
lcov -c --directory build/objects --output-file main_coverage.info
