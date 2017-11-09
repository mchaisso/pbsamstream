INCLUDES= -I blasr/libcpp \
 -I blasr/pbbam/include \
 -I blasr/pbbam/third-party/htslib/htslib

pbsamstream: PBSamStream.cpp
	g++ -g $(INCLUDES) PBSamStream.cpp -o pbsamstream -L blasr/pbbam/build/lib -l pbbam -L blasr/libcpp/pbdata -l pbdata -L blasr/pbbam/third-party/htslib/build -lhts -lz -lpthread
