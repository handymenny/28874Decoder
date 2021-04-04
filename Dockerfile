# Use Alpine: https://hub.docker.com/_/alpine
FROM alpine:3.13

WORKDIR /app

# Copy binaries
COPY . .

# Install required packages to build, build and then remove build tools
RUN apk add --no-cache make gcc libc-dev \
    && cd src/ \
    && make \
    && apk del make gcc libc-dev

ENTRYPOINT [ "./src/28874Decoder" ]
