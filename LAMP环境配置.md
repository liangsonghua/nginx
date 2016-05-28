# 一．安装gcc #

    gcc
    	cloog-ppl
    		ppl(libppl.so.7/libppl_c.so.2)
    	cpp
    mpfr(libmpfr.so.1)
    gcc-c++
    	libstdc++-devel
    mpfr-2.4.1-6.el6.i686.rpm和ppl-0.10.2-11.el6.i686.rpm


快捷键rz  sz：
rz、sz命令没找到？
安装lrzsz即可：

    shell># yum -y install lrzsz

# 二．安装zlib压缩库 #

    shell>## cd /home/liangsonghua/tar
    shell># tar –zxvf zlib-1.2.5.tar.gz
    shell># cd zlib-1.2.5
    shell># ./configure 	//这个配置编译命令不要加目录参数
    shell># make && make install

#  三．安装apache #

    shell># cd /home/liangsonghua/tar
    shell># tar -jxvf httpd-2.2.19.tar.bz2
    shell># cd httpd-2.2.19
     shell>#./configure --prefix=/usr/local/http2  \
    		--enable-modules=all \
    		--enable-mods-shared=all \
    		--enable-so
    shell># make && make install

## 启动Apache ##

    shell># /usr/local/http2/bin/apachectl start/stop/restart

## 测试apache ##

浏览器打开: http://虚拟机IP 
看到 "it works!",即为成功

## 配置虚拟主机 ##
1）配置host文件

	打开C:/windows/system32/drivers/etc/hosts 文件
	增加域名记录
	如：
	192.168.9.38	www.ec1.com
	192.168.9.38	www.ec2.com

2) 增加虚拟主机

	vi /usr/local/http2/conf/httpd.conf
	取消#  Include conf/extra/httpd-vhosts.conf


    vi /usr/local/http2/conf/extra/httpd-vhosts.conf

增加虚拟主机记录

    <VirtualHost *:80>
    	ServerAdmin webmaster@dummy-host.example.com
    	DocumentRoot "/usr/local/http2/htdocs/ec1"
    	ServerName www.ec1.com
    	ServerAlias www.dummy-host.example.com
    	ErrorLog "logs/dummy-host.example.com-error_log"
    	CustomLog "logs/dummy-host.example.com-access_log" common
    </VirtualHost>
    <VirtualHost *:80>
    	ServerAdmin webmaster@dummy-host2.example.com
       		DocumentRoot "/usr/local/http2/htdocs/ec2"
    	ServerName www.ec2.com
    	ErrorLog "logs/dummy-host2.example.com-error_log"
    	CustomLog "logs/dummy-host2.example.com-access_log" common
    </VirtualHost>
    <VirtualHost *:80>
       		DocumentRoot "/var/www/shop"
    	ServerName www.ec1.com
    </VirtualHost>


> 注意：/var/www/shop  以上三个目录var  www  shop 的其他用户必须有x可执行权限
 
 

3)添加测试内容

      	shell># cd /usr/local/http2/htdocs
     	shell># mkdir ec1 ec2
      	shell># echo this is ec1.com > ec1/index.html
      	shell># echo this is ec2.com > ec2/index.html

4）重启apache

    /usr/local/http2/bin/apachectl restart


5)浏览器打开www.ec1.com,和www.ec2.com
看到不同的网站内容，虚拟主机创建完毕！


**安装图形库,为编译PHP做准备**

libxml2-2.7.2.tar.gz
jpegsrc.v8b.tar.gz 
libpng-1.4.3.tar.gz      
freetype-2.4.1.tar.gz
gd-2.0.35.tar.gz

# 四．安装libxml2 #

		shell># cd /home/liangsonghua/tar
		shell># tar zxvf libxml2-2.7.2.tar.gz 
		shell># cd libxml2-2.7.2
		shell>#./configure --prefix=/usr/local/libxml2  \
		--without-zlib
		shell># make && make install

# 五．安装jpeg8 #

		shell># cd /home/liangsonghua/tar
		shell># tar -zxvf jpegsrc.v8b.tar.gz 
		shell># cd jpeg-8b 
		shell>#./configure --prefix=/usr/local/jpeg \
		--enable-shared --enable-static 
		shell># make && make install
		--enable-shared  
		--enable-static   静态方式函数处理，需要什么函数，马上include来

# 六．安装libpng #

		shell># cd /home/liangsonghua/tar
		shell># tar zxvf libpng-1.4.3.tar.gz 
		shell># cd libpng-1.4.3 
		shell>#./configure  
		shell># make && make install

#七．安装freetype(字体库) #

    shell># cd /home/liangsonghua/tar
    shell># tar zxvf freetype-2.4.1.tar.gz 
    shell># cd freetype-2.4.1
    shell>#./configure --prefix=/usr/local/freetype 
    shell># make && make install

# 八．安装GD库 #

    shell># cd /home/liangsonghua/tar
    shell># tar -zvxf gd-2.0.35.tar.gz 
    shell># mkdir -p /usr/local/gd 
    shell># cd gd-2.0.35 
    shell>#./configure --prefix=/usr/local/gd  \
    			--with-jpeg=/usr/local/jpeg/ 	\
    			--with-png --with-zlib \
    			--with-freetype=/usr/local/freetype
    shell># make && make install

# 九．安装 php5 #

    shell># cd /home/liangsonghua/tar
    shell># tar -jxvf php-5.3.6.tar.bz2
    shell># cd php-5.3.6
    shell>#./configure --prefix=/usr/local/php \
    			--with-apxs2=/usr/local/http2/bin/apxs \
    			--with-mysql=mysqlnd \
    			--with-pdo-mysql=mysqlnd \
    			--with-mysqli=mysqlnd \
    			--with-freetype-dir=/usr/local/freetype \
    			--with-gd=/usr/local/gd \
    			--with-zlib --with-libxml-dir=/usr/local/libxml2 \
    			--with-jpeg-dir=/usr/local/jpeg \
    			--with-png-dir \
    			--enable-mbstring=all \
    			--enable-mbregex \
    			--enable-shared
    shell># make && make install 

**复制php.ini配置文件到指定目录**

    shell># cp php.ini-development /usr/local/php/lib/php.ini
**配置Apache使其支持php**

    vi /usr/local/http2/conf/httpd.conf

1)	在httpd.conf(Apache主配置文件)中增加：<br/>

    AddType application/x-httpd-php .php

2)	找到下面这段话:

    <IfModule dir_module>
       DirectoryIndex index.html
    </IfModule><br/>

在index.html 前面添加index.php<br/>

3)	建立php测试网页

    vi /usr/local/apache2/htdocs/index.php	
 
输入如下内容:

    <?php
    phpinfo();
    ?>

4)	重启apache

    shell># /usr/local/http2/bin/apachectl restart

5)	再次浏览器查看http://虚拟机IP

如果看到php信息,工作就完成了!

# 十．安装MySQL #
## 1.安装cmake ##

    shell># cd /home/liangsonghua/tar
    shell># tar zxvf cmake-2.8.5.tar.gz
    shell># cd cmake-2.8.5
    shell># ./bootstrap
    shell># make && make install

## 2.编译安装MySQL ##

    shell># cd /home/liangsonghua/tar
    shell># tar zxvf mysql-5.5.17.tar.gz
    shell># cd mysql-5.5.17
    shell># cmake \
    -DCMAKE_INSTALL_PREFIX=/usr/local/mysql \
    -DMYSQL_DATADIR=/usr/local/mysql/data \
    -DDEFAULT_CHARSET=utf8 \
    -DDEFAULT_COLLATION=utf8_general_ci

报错就安装ncurses-devel

    shell># mount .....挂载光盘/
    
    shell># rpm -ivh ncurses-devel-5.7-3.20090208.el6.i686.rpm
    shell># rm -f CMakeCache.txt
    shell># cmake //重新cmake
    shell># make && make install
    shell># cp support-files/my-medium.cnf /etc/my.cnf

## 3.配置并初始化MySQL ##

    shell># useradd  mysql	
    shell># chmod +x /usr/local/mysql
    shell># chown -R mysql.mysql /usr/local/mysql 

初始化mysql数据库  

    shell># /usr/local/mysql/scripts/mysql_install_db \
    --user=mysql \
    --basedir=/usr/local/mysql \
    --datadir=/usr/local/mysql/data &

把mysql安装文件(除了data)的主人都改为root，避免数据库恢复为出厂设置。

    shell># chown -R root /usr/local/mysql
    shell># chown -R mysql /usr/local/mysql/data

& 后台运行mysql服务

    shell># /usr/local/mysql/bin/mysqld_safe --user=mysql &

测试数据库

    shell># /usr/local/mysql/bin/mysql –u root
    mysql> show databases;	

接上步,修改mysql密码(可不做此步,默认无密码)

    mysql> UPDATE user SET Password=password('123456') WHERE user='root';
    mysql> flush privileges;

## 4.配置开机自启动服务项 ##

    shell># cp 安装包解压目录/support-files/mysql.server /etc/init.d/mysqld
    shell># chmod +x /etc/init.d/mysqld
    shell># chkconfig --add mysqld
    shell># chkconfig mysqld on//设置开机自启动

配置文件路径：

    shell># vi /etc/rc.d/rc.local
    在  文件中增加启动相关服务的命令如下：
    /usr/local/http2/bin/apachectl start 
    /usr/local/mysql/bin/mysqld_safe --user=mysql &
    service vsftpd start
