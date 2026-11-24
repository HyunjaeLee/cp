FROM mcr.microsoft.com/devcontainers/base:ubuntu26.04

USER root

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        g++ \
        clangd \
        python3 \
        python-is-python3 \
    && rm -rf /var/lib/apt/lists/*

USER vscode
