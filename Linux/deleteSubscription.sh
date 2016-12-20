#!/bin/bash
source app.config
echo "Type subscription:"
read TEXT

curl -X DELETE "$orionIPaddress:$orionPort/v2/subscriptions/$TEXT -s -S --header 'X-Auth-Token: $authToken'" | python -mjson.tool;

# List all subscriptions:
# curl -X GET "130.206.114.133:1026/v2/subscriptions" | python -mjson.tool >> deleteSomeSubs.sh