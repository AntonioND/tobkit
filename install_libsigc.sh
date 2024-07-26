#!/bin/bash

pushd libsigc++

git clean -fxd

TMPDIR=`mktemp -d`
OUTDIR=/opt/blocksds/external/libsigc++

export PATH=$PATH:/opt/wonderful/toolchain/gcc-arm-none-eabi/bin/

./configure --prefix=$TMPDIR --host=arm-none-eabi

make -j`nproc` install

rm -rf ${OUTDIR}

mkdir -p ${OUTDIR}
mkdir -p ${OUTDIR}/include
mkdir -p ${OUTDIR}/lib

cp COPYING ${OUTDIR}
cp ${TMPDIR}/lib/libsigc-2.0.a ${OUTDIR}/lib
cp -r ${TMPDIR}/include/sigc++-2.0/sigc++ ${OUTDIR}/include
cp ${TMPDIR}/lib/sigc++-2.0/include/sigc++config.h ${OUTDIR}/include

popd
