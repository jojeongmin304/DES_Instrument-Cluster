FROM balenalib/raspberrypi4-64-debian:bookworm

RUN apt-get update && apt-get install -y \
    build-essential \
    software-properties-common \
    qt6-base-dev \
    qt6-tools-dev-tools \
    qt6-declarative-dev \
    qt6-multimedia-dev \
    libqt6multimedia6 \
    libqt6opengl6-dev \
    libqt6svg6-dev \
    libqt5x11extras5-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    cmake \
    g++ \
    rsync \
    ssh \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /project
