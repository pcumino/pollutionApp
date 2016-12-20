#!/bin/bash
. ./app.config

echo "number of sensors: $numberOfSensors";

COUNTER=1;
unit=1;
while [ $COUNTER -le $numberOfSensors ]; do
	sleep 0.1

(curl $orionIPaddress:$orionPort/v2/entities/StreetFixed$COUNTER/attrs -s -S --header 'X-Auth-Token: $authToken' --header 'Content-Type: application/json' -X PATCH -d @-) <<EOF
{
    "aircondition":{
        "type": "Float",
        "value": "$((RANDOM % 100))"
    },
    "temperature":{
        "type": "Float",
        "value": "$((25+RANDOM % 10))"
    }
}
EOF
	echo " updating StreetFixed$COUNTER";

	COUNTER=$(($COUNTER+$unit))
done;
echo "\ndone";
