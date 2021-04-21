# Base image with gcc compiler and cmake.
FROM mazurov/cern-root
ARG version="0.01"
LABEL author="Edward Shields"
LABEL description="Hydra build"
LABEL version="${version}"

# Set workdir.
WORKDIR /usr/src

# Copy everything to workdir.
COPY . toygen

# Move to workdir.
# TODO: Add a build.
RUN if [[ -d /usr/src/toygen/build ]]; then rm -rf /usr/src/toygen/build; fi \
    && mkdir /usr/src/toygen/build \
    && cd /usr/src/toygen/build \
    && cmake .. \
    && make \
    && cd .. 