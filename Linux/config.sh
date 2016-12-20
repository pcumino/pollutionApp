#!/bin/bash

. ./app.config

read -p "Username: " USER
read -p "Password: " PASSWORD
echo ""

RESP=`curl -s -d "{\"username\": \"$USER\", \"password\":\"$PASSWORD\"}" -H "Content-type: application/json" https://orion.lab.fiware.org/token`;
echo "";
echo ">your token: \t"$RESP;
echo "";
sed -i.bak 's/^\(authToken=\).*/\1'\"$RESP\"';/' app.config;

# clear;
echo $orionIPaddress
echo "Enter the Orion server IP address [$orionIPaddress]: "
read TEXT
if [ ! -z "$TEXT" ]; then
	sed -i.bak 's/^\(orionIPaddress=\).*/\1'\"$TEXT\"';/' app.config;
	orionIPaddress=$TEXT;
fi

echo "Enter port [$orionPort]: "
read TEXT
if [ ! -z "$TEXT" ]; then
	sed -i.bak 's/^\(orionPort=\).*/\1'\"$TEXT\"';/' app.config;
	orionPort=$TEXT
fi

echo "Orion location: $orionIPaddress:$orionPort";
