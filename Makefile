all: htslib/libhts.a \
  blasr_libcpp/build/liblibcpp.a \
  pbbam/build/lib/libpbbam.a \
	hdf5/build/lib/libhdf5.a \
  zlib/build/lib/libz.a \
  pbsamstream 

hdf5/build/lib/libhdf5.a:
	mkdir -p $(PWD)/hdf5/build
	export CXXFLAGS="-std=c++11"
	cd hdf5/ && \
  mkdir -p cmake_build && \
  cd cmake_build && \
  cmake ..  -DCMAKE_CXX_STANDARD=11 \
            -DHDF5_BUILD_CPP_LIB:BOOL=ON \
            -DCMAKE_INSTALL_PREFIX:PATH=$(PWD)/hdf5/build \
            -DCMAKE_C_COMPILER=`which gcc` \
            -DCMAKE_CPP_COMPILER=`which g++` && \
  make -j 8 VERBOSE=1 && \
  make install

htslib/libhts.a:
	cd htslib; \
    autoheader; \
    autoconf; \
    ./configure --disable-bz2 --disable-lzma --disable-libcurl --disable-s3; \
    make -j 4

zlib/build/lib/libz.a:
	cd zlib && ./configure --prefix=$(PWD)/zlib/build && make && make install

boost_1_66_0/bootstrap.sh:
	wget https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz
	tar xvf boost_1_66_0.tar.gz
	touch $@

boost_1_66_0/stage/lib/libboost_program_options.a: boost_1_66_0/bootstrap.sh
	cd boost_1_66_0 && ./bootstrap.sh --with-libraries=program_options && ./b2 --prefix=$PWD/build -j 8

#
# This needs nijna. Crymoji.
#
blasr_libcpp/build/liblibcpp.a: boost_1_66_0/stage/lib/libboost_program_options.a hdf5/build/lib/libhdf5.a htslib/libhts.a
	cp libcpp_CMakeLists.txt blasr_libcpp/CMakeLists.txt
	export CPPFLAGS="-std=c++11 -ldl "
	cd blasr_libcpp; \
   rm -rf build; \
   mkdir -p build; cd build; \
   cmake -GNinja \
     -DCMAKE_C_COMPILER=`which gcc` \
     -DCMAKE_CPP_COMPILER=`which g++` \
     -D CMAKE_CXX_STANDARD=11 \
     -D CMAKE_VERBOSE_MAKEFILE:BOOL=ON \
     -D HTSLIB_LIBRARIES=$(PWD)/htslib/libhts.a \
     -D HTSLIB_INCLUDE_DIRS=$(PWD)/htslib \
     -D PacBioBAM_build_tests=False \
     -D HDF5_LIBRARIES=$(PWD)/hdf5/build/lib \
     -D HDF5_INCLUDE_DIRS=$(PWD)/hdf5/build/include \
     -D BOOST_ROOT=$(PWD)/boost_1_66_0/ \
        .. ; \
   ninja -v -j 8


zlib/build/lib/libz.a:
	cd zlib; \
    mkdir -p build; \
    ./configure --prefix=build; \
    make -j 8; \
    make install

pbbam/build/lib/libpbbam.a: hdf5/build/lib/libhdf5.a boost_1_66_0/stage/lib/libboost_program_options.a
	cd pbbam/; \
   rm -rf build; \
   mkdir -p build; cd build; \
   cmake   -D HTSLIB_LIBRARIES=$(PWD)/htslib/libhts.a \
   -DCMAKE_C_COMPILER=`which gcc` \
   -DCMAKE_CPP_COMPILER=`which g++` \
   -D CMAKE_CXX_STANDARD=11 \
   -D HDF5_LIBRARIES=$(PWD)/hdf5/build/lib \
   -D HDF5_INCLUDE_DIRS=$(PWD)/hdf5/build/include \
   -D HTSLIB_INCLUDE_DIRS=$(PWD)/htslib \
   -D PacBioBAM_build_tests=False \
   -D BOOST_ROOT=$(PWD)/boost_1_66_0/ .. ; \
   make VERBOSE=1 -j 8

pbsamstream: PBSamStream.cpp htslib/libhts.a pbbam/build/lib/libpbbam.a zlib/build/lib/libz.a blasr_libcpp/build/liblibcpp.a
	g++ -static -std=c++11 -g -I $(PWD)/boost_1_66_0 -I. -Ihtslib PBSamStream.cpp -o pbsamstream -I blasr_libcpp -L blasr_libcpp/build -I pbbam/include -L pbbam/build/lib -l pbbam -L htslib -llibcpp -lhts -ldl -lpthread -L zlib/build/lib -lz
