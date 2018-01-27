#!/bin/bash

decodeURL() {
	com=$(bash url_encode_decode.sh urldecode "$com")
}
writeSerial() {
	echo "$arg1" > /dev/ttyACM0
        echo "<h1>Command $arg1 sent to /dev/ttyACM0!</h1>"
	sleep 1
	readSerial;
}
readSerial() {
	if [ ! -f serialdata ]; then
		echo '' > serialdata
		echo "Created serialdata file."
	fi
	readarray ary < serialdata
	blank=$'"\n"'
	if [ "$ary" != "$blank" ]; then
		for i in "${ary[@]}"; do 
			line=$(echo "$i" | grep "DEBUG" | cut -d ':' -f 3)
			if [ -n "$line" ]; then
				echo "$line" >> temp
			fi
		done
		if [ -f temp ]; then
			readdata=$(cat temp)
		fi
		if [ -z "$readdata" ]; then
			echo "<h1>No data returned.</h1>"
		else
			echo "<h1>Response: $readdata</h1>"
		fi
		readdata=''
		echo '' > serialdata
		temp=$(ls temp 2> /dev/null)
		if [ -n temp ] && [ -f temp ]; then
			rm temp
		fi
	fi
}
blink() {
	echo /2/1/13/2/ > /dev/ttyACM0
	sleep 1
	echo /2/1/13/1/ > /dev/ttyACM0
	echo "<h1>Blunk!</h1>"
}
echo "Content-Type: text/html"
echo ''
echo 'NicRover control interface<br><br>'

com="$QUERY_STRING"
convert=$(echo "$com" | greop "%2F")
if [ -n "$convert" ]; then
	decodeURL;
fi
echo "$com" > /dev/ttyACM0
echo "<h1>Command sent. com=$com</h1>"
