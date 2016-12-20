#!/bin/bash
# 130.206.114.133:1026
. ./app.config
HOST=$orionIPaddress
PORT=$orionPort

appHOST=$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1')
appPORT=3000

echo ".:REGISTERING APP:."
echo "Enter the app host [$appHOST]: "
read input
if [ ! -z "$input" ]; then
    appHOST=$input
fi
echo "Enter the app port [$appPORT]: "
read input
if [ ! -z "$input" ]; then
    appPORT=$input
fi

echo "Orion location: $orionIPaddress:$orionPort";
echo "App running on $appHOST:$appPORT\n";
i=0;
unit=1;
while [ $i -le $numberOfSensors ]
    do
        result=$(curl $HOST:$POSR/v2/entities/StreetFixed$i?options=values&attrs=aircondition,position,temperature -s -S --header 'X-Auth-Token: $authToken' --header 'Accept: application/json');
        if echo "$result" | grep -q "error"; then
            echo "";
        else
            echo "subscribe to StreetFixed$i:";
    (curl -v $HOST:1026/v2/subscriptions -s -S --header 'Content-Type: application/json' -d @- | python -mjson.tool) <<EOF
    {
        "description": "Notifying subscriber when StreetFixed$i aircondition and temperature value changes.",
        "subject": {
            "entities": [
            {
                "id": "StreetFixed$i",
                "type": "StreetFixed"
            }
            ],
            "condition": {
                "attrs": ["aircondition","temperature"]
            }
        },
        "notification": {
            "http": {
                "url": "http://$appHOST:$appPORT"
            },
            "attrs": ["aircondition","temperature","position"]
        },
        "expires": "2040-01-01T14:00:00.00Z",
        "throttling": 5
    }
EOF
            echo "\n\n";
        fi
        i=$(($i+$unit));
    done

# < HTTP/1.1 201 Created
# < Connection: Keep-Alive
# < Content-Length: 0
# < Location: /v2/subscriptions/5844b42bffee4e888d0f9c2a
# < Fiware-Correlator: 70f4b16a-ba81-11e6-8a51-080027d6394e
# < Date: Mon, 05 Dec 2016 00:26:19 GMT
