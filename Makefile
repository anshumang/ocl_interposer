app:
	g++ -I /opt/nvidia/4.2/cuda/include/ -o test_app.out test_app.c -L/usr/lib64 -lOpenCL
