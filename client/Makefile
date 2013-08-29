client:
	g++ -g -I /opt/nvidia/4.2/cuda/include/ -c -fPIC client.cpp -o client.o
	g++ -shared -Wl,-soname,libCLInterposerClient.so.1 -o libCLInterposerClient.so.1.0.1  client.o
