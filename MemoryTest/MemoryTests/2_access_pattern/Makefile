all:
	gcc mm-ijk.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=6    -o IJK-EXE6
	gcc mm-ijk.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=256  -o IJK-EXE256
	gcc mm-ijk.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=512  -o IJK-EXE512
	gcc mm-ijk.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=1024 -o IJK-EXE1024
	gcc mm-jki.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=6    -o JKI-EXE6
	gcc mm-jki.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=256  -o JKI-EXE256
	gcc mm-jki.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=512  -o JKI-EXE512
	gcc mm-jki.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=1024 -o JKI-EXE1024
	gcc mm-kij.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=6    -o KIJ-EXE6
	gcc mm-kij.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=256  -o KIJ-EXE256
	gcc mm-kij.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=512  -o KIJ-EXE512
	gcc mm-kij.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=1024 -o KIJ-EXE1024
opt-ok:
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=6    -o IJK2-EXE6
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=256  -o IJK2-EXE256
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=512  -o IJK2-EXE512
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=1024 -o IJK2-EXE1024
opt:
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=6    -o IJK2-EXE6
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=256  -o IJK2-EXE256
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=512  -o IJK2-EXE512
	gcc mm-ijk2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=1024 -o IJK2-EXE1024
	gcc mm-jki2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=6    -o JKI2-EXE6
	gcc mm-jki2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=256  -o JKI2-EXE256
	gcc mm-jki2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=512  -o JKI2-EXE512
	gcc mm-jki2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=1024 -o JKI2-EXE1024
	gcc mm-kij2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=6    -o KIJ2-EXE6
	gcc mm-kij2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=256  -o KIJ2-EXE256
	gcc mm-kij2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=512  -o KIJ2-EXE512
	gcc mm-kij2.c -I../tools ../tools/measure.c ../tools/sampler.c -DN=1024 -o KIJ2-EXE1024

clean:
	rm -rf *EXE*
