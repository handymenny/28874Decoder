# Use Alpine: https://hub.docker.com/_/alpine
FROM alpine:3.13

WORKDIR /app

# Copy binaries
COPY . .

# Install required packages to build and build
RUN apk add --no-cache make gcc libc-dev \
    && cd src/ \
    && make

ENTRYPOINT [ "./src/28874Decoder" ]
