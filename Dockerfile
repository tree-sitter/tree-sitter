FROM ubuntu:trusty

# install
#   - gcc and clang
#   - GYP dependencies
#   - git for script
RUN sudo apt-get -y update\
  && sudo apt-get -y install software-properties-common\
  && sudo add-apt-repository ppa:ubuntu-toolchain-r/test\
  && sudo apt-get -y update\
  && sudo apt-get -y install gcc-5 g++-5 clang\
  && sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 20\
  && sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 20\
  && sudo update-alternatives --config gcc\
  && sudo update-alternatives --config g++\
  && sudo apt-get -y install python make\
  && sudo apt-get -y install git-core

# clone, build and test
RUN git clone https://github.com/tree-sitter/tree-sitter.git\
  && cd tree-sitter\
  && git submodule update --init --recursive\
  && export CXX="g++-5"\
  && scan-build script/configure\
  && script/ci
