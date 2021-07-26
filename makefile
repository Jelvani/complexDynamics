CC = g++

KERNEL_NAME = real_os

CFLAGS = -fopenmp


mandelbrot: mandelbrot.cpp
	$(CC) $(CFLAGS) $^ -o $@

julia: julia.cpp
	$(CC) $(CFLAGS) $^ -o $@

image: *.pgm
	mogrify -format png *.pgm