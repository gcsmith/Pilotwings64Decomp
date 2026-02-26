FROM ubuntu:24.04

# Create directory for mount
RUN mkdir /pw64
WORKDIR /pw64

# Install required packages
ENV DEBIAN_FRONTEND=noninteractive

COPY packages.txt ./
RUN apt-get update && \
    apt-get install -y $(cat packages.txt | tr '\n' ' ') && \
    rm -rf /var/lib/apt/lists/*

COPY requirements.txt ./
RUN pip3 install -r requirements.txt --break-system-packages

# Set up user (if they don't exist)
ARG login=pilot
ARG uid=1001
RUN id -u $uid &>/dev/null || adduser --system --uid $uid --group $login

# Set entrypoint
RUN echo "#!/bin/bash\nexec \"\$@\"" > /entrypoint.sh && chmod +x /entrypoint.sh
USER $uid
ENTRYPOINT ["/entrypoint.sh"]