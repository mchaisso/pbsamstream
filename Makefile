all: htslib/libhts.a \
  blasr_libcpp/build/liblibcpp.a \
  pbbam/build/lib/libpbbam.a \
	hdf5/build/lib/libhdf5.a \
  pbsamstream 

hdf5/build/lib/libhdf5.a:
	cd hdf5/ ;\
    ./configure --enable-cxx --prefix=$(PWD)/hdf5/build ; \
    make -j 8 ;\
    make install

htslib/libhts.a:
	cd htslib; \
    autoheader; \
    autoconf; \
    ./configure --disable-bz2 --disable-lzma --disable-curl --disable-s3; \
    make -j 8

#
# This needs nijna. Crymoji.
#
blasr_libcpp/build/liblibcpp.a:
	cd blasr_libcpp; \
   mkdir -p build; cd build; \
   cmake -GNinja  -D HTSLIB_LIBRARIES=$(PWD)/htslib/libhts.a -D HTSLIB_INCLUDE_DIRS=$(PWD)/htslib -D PacBioBAM_build_tests=False  -D HDF5_LIBRARIES=$(PWD)/hdf5/build/lib -D HDF5_INCLUDE_DIRS=$(PWD)/hdf5/build/include .. ; \
   ninja


zlib/build/lib/libz.a:
	cd zlib; \
    mkdir -p build; \
    ./configure --prefix=build; \
    make -j 8; \
    make install

pbbam/build/lib/libpbbam.a: hdf5/build/lib/libhdf5.a
	cd pbbam/; \
   mkdir -p build; cd build; \
   cmake   -D HTSLIB_LIBRARIES=$(PWD)/htslib/libhts.a -D HTSLIB_INCLUDE_DIRS=$(PWD)/htslib -D PacBioBAM_build_tests=False .. ; \
   make VERBOSE=1 -j 8 

pbsamstream: PBSamStream.cpp htslib/libhts.a pbbam/build/lib/libpbbam.a zlib/build/lib/libz.a curl/build/lib/libcurl.a 
	g++ -static -std=c++11 -g -I. -Ihtslib PBSamStream.cpp -o pbsamstream -I blasr_libcpp -L blasr_libcpp/build -I pbbam/include -L pbbam/build/lib -l pbbam -L htslib    -lpthread -llibcpp -lhts -lz -L openssl -lssl -lcrypto  -ldl
