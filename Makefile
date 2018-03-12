all: pbsamstream

#hdf5/build/lib/libhdf5.a:
#	cd hdf5 ;\
#    mkdir build ;\
#    ./configure --enable-cxx --prefix=$(PWD)/build ; \
#    make -j 8 ;\
#    make install
#
#htslib/libhts.a:
#	cd htslib; make -j 8 
#
zlib/build/lib/libz.a:
	cd zlib; \
    mkdir -p build; \
    ./configure --prefix=build; \
    make -j 8; \
    make install
#
#blasr/pbbam/libpbbam.so: hdf5/build/lib/libhdf5.a zlib/build/lib/libz.a htslib/libhts.a
#	cd blasr ; \
#  cd libcpp; ./configure; make -j 2; \
#  cd ..; \
#  mkdir -p build ; \
#  cd build; \
#  cmake -GNinja -DHDF5_LIBRARIES=$(PWD)/hdf5/build/lib \
#                -DHDF5_INCLUDE_DIRS=$(PWD)/hdf5/build/include \
#                -DHTSlib_INCLUDE_DIR=$(PWD)/blasr/pbbam/third-party/htslib/htslib/ \
#                -DHTSlib_LIBRARY=$(PWD)/blasr/pbbam/third-party/htslib/htslib/ \
#                -DZLIB_INCLUDE_DIRS=$(PWD)/zlib/build/include \
#                -DZLIB_LIBRARIES=$(PWD)/zlib/build/lib ..; \
#  ninja



pbsamstream: PBSamStream.cpp htslib/libhts.a
	g++ -std=c++11 -g -I. -Ihtslib PBSamStream.cpp -o pbsamstream -L libs -l pbbam -l pbdata -L htslib -lhts -lz -lpthread
