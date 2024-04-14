#!/bin/bash

apt update  -y
apt install -y    \
  autoconf        \
  libtool         \
  build-essential \
  zlib1g-dev      \
  libbz2-dev      \
  git             \
  tmux            \
  python3-pip     \
  wget

growpart /dev/nvme0n1 p1
resize2fs /dev/nvme0n1p1

pip3 install awscli

# {
# CUDA
if [ $(lspci  | grep -c NVIDIA) -eq 1 ]
then
  pushd /tmp
  apt install -y linux-headers-$(uname -r)
  wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.1-1_all.deb
  dpkg -i cuda-keyring_1.1-1_all.deb
  apt -y update
  apt -y install cuda
  popd
fi

mkdir -p /opt/
cd /opt/

git clone https://github.com/cr-marcstevens/hashclash.git

cd hashclash
./build.sh

