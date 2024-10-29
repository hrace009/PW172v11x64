### SERVER PERFECT WORLD 1.6.2 by Deadraky (C)2022 

# WARNING!!! Debian 11 operating system is required for correct operation!

# install on ubuntu 11
```
dpkg --add-architecture i386
apt update && apt -y upgrade
apt -y install mc screen htop openjdk-11-jre mono-complete exim4 p7zip* libpcap-dev curl wget ipset net-tools tzdata ntpdate mariadb-server mariadb-client
apt -y install make gcc g++ libssl-dev:i386 libssl-dev libcrypto++-dev libpcre3 libpcre3-dev libpcre3:i386 libpcre3-dev:i386 libtesseract-dev libx11-dev:i386 libx11-dev gcc-multilib libc6-dev:i386 build-essential gcc-multilib g++-multilib libtemplate-plugin-xml-perl libxml2-dev libxml2-dev:i386 libxml2:i386 libstdc++6:i386 libmariadb-dev-compat:i386 libmariadb-dev:i386

apt -y install make gcc g++ libssl-dev libssl-dev libcrypto++-dev libpcre3 libpcre3-dev libpcre3 libpcre3-dev libtesseract-dev libx11-dev libx11-dev gcc-multilib libc6-dev build-essential gcc-multilib g++-multilib libtemplate-plugin-xml-perl libxml2-dev libxml2-dev libxml2 libstdc++6 libmariadb-dev-compat libmariadb-dev

apt install -y php libapache2-mod-php php-cli php-fpm php-json php-pdo php-zip php-gd  php-mbstring php-curl php-xml php-pear php-bcmath php-cgi php-mysqli php-common php-phpseclib php-mysql

mysql_secure_installation
apt install -y phpmyadmin
```
