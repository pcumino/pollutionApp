#!/bin/bash
source app.config
i=0;
while [ $i -le $numberOfSensors ]
do
	curl -X DELETE "$orionIPaddress:$orionPort/v2/entities/StreetFixed$i -s -S --header 'X-Auth-Token: $authToken'" | python -mjson.tool;
	i=$[$i+1];
done