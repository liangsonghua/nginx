#nginx配置
./configure --prefix=/usr/local/nginx \
  --with-pcre=/home/pidan/tar/pcre-8.37 \
  --with-openssl=/usr/local/openssl \
  --pid-path=/usr/local/nginx/logs/nginx.pid  \

#php配置
./configure --prefix=/usr/local/php \
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
	--enable-shared \
	--enable-fpm 


cp /home/pidan/tar/php-5.3.6/php.ini-development /usr/local/php/lib/php.ini

