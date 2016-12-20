(curl 192.168.1.25:1026/v2/entities/StreetFixed1/attrs -s -S --header 'Content-Type: application/json' -X PATCH -d @- | python -mjson.tool) <<EOF
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
