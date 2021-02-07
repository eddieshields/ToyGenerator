# Base image with gcc compiler and cmake.
FROM rikorose/gcc-cmake 
ARG version="0.01"
LABEL author="Edward Shields"
LABEL description="Hydra build"
LABEL version="${version}"

# Get ROOT build.
FROM mazurov/cern-root

# Set workdir.
WORKDIR /usr/src

# Copy everything to workdir.
COPY . toygen

# Move to workdir.
# TODO: Add a build.
RUN ls /usr/src/toygen/external \
    && if [[ -d /usr/src/toygen/build ]]; then rm -rf /usr/src/toygen/build; fi \
    && mkdir /usr/src/toygen/build \
    && cd /usr/src/toygen/build \