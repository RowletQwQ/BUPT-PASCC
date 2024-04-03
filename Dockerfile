FROM tclab/ucore-env

# Replace the default sources.list file with a new one
RUN echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse" > /etc/apt/sources.list && \
    echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://security.ubuntu.com/ubuntu/ jammy-security main restricted universe multiverse" >> /etc/apt/sources.list

RUN apt-get update -y && apt-get upgrade -y

RUN apt-get install build-essential -y

RUN apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev \
              gawk build-essential bison flex texinfo gperf libtool patchutils bc \
              zlib1g-dev libexpat-dev pkg-config  libglib2.0-dev libpixman-1-dev git tmux python3 -y

RUN apt-get install ninja-build -y

RUN wget -O qemu-7.0.0.tar.xz "https://cloud.tsinghua.edu.cn/f/8ba524dbede24ce79d06/?dl=1" --inet4-only

RUN tar xJf qemu-7.0.0.tar.xz

ENV PATH="/root/os-env/qemu-7.0.0/build/:$PATH"
ENV PATH="/root/os-env/qemu-7.0.0/build/riscv64-softmmu:$PATH"
ENV PATH="/root/os-env/qemu-7.0.0/build/riscv64-linux-user:$PATH"

RUN cd qemu-7.0.0 && ./configure --target-list=riscv64-softmmu,riscv64-linux-user && make -j$(nproc) && make install