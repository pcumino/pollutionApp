#!/bin/bash
source app.config
clear;
echo "Creating new entities"
HOST=$orionIPaddress
PORT=$orionPort

echo "Default server and port $HOST:$PORT"
# read -p "Set new server and port? [y/n]" -n 1 -r
echo    # (optional) move to a new line
# if [[ $REPLY =~ ^[Yy]$ ]]
#     then
#     echo "Set the server HOST: "
#     read HOST
#     echo "Set the server port: "
#     read PORT
# fi
# echo "Server and port set as $HOST:$PORT"

echo "How many sensors to be added?"
read TEXT
if [ ! -z "$TEXT" ]; then
    sed -i.bak 's/^\(numberOfSensors=\).*/\1'\"$TEXT\"';/' app.config;
fi
echo $HOST:$PORT
COUNTER=1

while [  $COUNTER -le $numberOfSensors ]; do
    AIRCONDITION=$((RANDOM % 100));
    TEMPERATURE=$((25+RANDOM % 10));
    LAT=$(bc <<< "scale=3; $(printf '1.44%2d' $(( $RANDOM % 100000)))");
    LON=$(bc <<< "scale=3; $(printf '48.44%2d' $(( $RANDOM % 100000)))");

    curl $HOST:$PORT/v2/entities -s -S --header 'X-Auth-Token: $authToken' --header 'Content-Type: application/json' -d @- <<EOF
    {
        "id": "StreetFixed$COUNTER",
        "type": "StreetFixed",
        "aircondition":{
            "type": "float",
            "value": "$AIRCONDITION"
        },
        "temperature":{
            "type": "float",
            "value": "$TEMPERATURE"
        },
        "position":{
            "type": "float",
            "value": "-$LAT,-$LON"
        }
    }
EOF
let COUNTER=COUNTER+1 
done

sh getDataFromOrion.sh
