FROM ubuntu:focal

# setup timezone
RUN echo 'Etc/UTC' > /etc/timezone && \
    ln -s /usr/share/zoneinfo/Etc/UTC /etc/localtime \
    # install dependencies
    && apt-get update && apt-get install -y --no-install-recommends \
    # gcc compiler
    build-essential \
    # dev tools
    git \
    cmake \
    # UI text editor
    gedit \
    # CLI text editor
    nano \
    # pretty backtrace printing on segfault
    libdw-dev \
    # to enable git clone
    ca-certificates \
    # install Google Test
    && git clone https://github.com/google/googletest.git /tmp/googletest \
    && mkdir /tmp/googletest/build \
    && cd /tmp/googletest/build \
    && cmake .. \
    && make -j$(nproc) \
    && make install \
    && rm -rf /tmp/googletest \
    # remove unused folders
    && rm -rf /var/cache/apt/archives /var/lib/apt/lists