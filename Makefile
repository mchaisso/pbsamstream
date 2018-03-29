all: htslib/libhts.a \
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
    ./configure --disable-bz2 --disable-lzma ; \
    make -j 8

boost_1_66_0/bootstrap.sh:
	wget https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz
	tar xvf boost_1_66_0.tar.gz
	touch $@

boost_1_66_0/stage/lib/libboost_program_options.a: boost_1_66_0/bootstrap.sh
	cd boost_1_66_0 && ./bootstrap.sh --without-libraries=python && ./b2 --prefix=$PWD/build -j 4

#
# This needs nijna. Crymoji.
#
blasr_libcpp/build/liblibcpp.a:
	cd blasr_libcpp; \
   mkdir build; cd build; \
   cmake -GNinja  -D HTSLIB_LIBRARIES=$(PWD)/htslib/libhts.a -D HTSLIB_INCLUDE_DIRS=$(PWD)/htslib -D BOOST_ROOT=$(PWD)/boost -D PacBioBAM_build_tests=False  -D HDF5_LIBRARIES=$(PWD)/hdf5/build/lib -D HDF5_INCLUDE_DIRS=$(PWD)/hdf5/build/include  .. ; \
   ninja -j 4


zlib/build/lib/libz.a:
	cd zlib; \
    mkdir -p build; \
    ./configure --prefix=build; \
    make -j 8; \
    make install

pbbam/build/lib/libpbbam.a: hdf5/build/lib/libhdf5.a boost/lib/libboost_program_options.a
	cd pbbam/; \
   mkdir build; cd build && \
   cmake   -D HTSLIB_LIBRARIES=$(PWD)/htslib/libhts.a -D HTSLIB_INCLUDE_DIRS=$(PWD)/htslib -D BOOST_ROOT=$(PWD)/boost -D PacBioBAM_build_tests=False .. && \
   make VERBOSE=1 -j 8 


pbsamstream: PBSamStream.cpp htslib/libhts.a pbbam/build/lib/libpbbam.a zlib/build/lib/libz.a blasr_libcpp/build/liblibcpp.a
	g++ -std=c++11 -g -I. -Ihtslib -Iboost/include PBSamStream.cpp -o pbsamstream -I blasr_libcpp -L blasr_libcpp/build -I pbbam/include -L libs -L pbbam/build/lib -l pbbam -L htslib  -lhts -lz -lpthread -llibcpp
