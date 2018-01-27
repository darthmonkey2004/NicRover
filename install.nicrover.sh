#!/bin/bash

setupTether() {
	if [ ! -d cwm-tether ]; then
		mkdir cwm-tether
	fi
	if [ ! -f "$HOME/cwm-tether/cwm-tether.tgz" ]; then
		cd cwm-tether
		wget "http://download.clockworkmod.com/tether/tether-linux.tgz" -O cwm-tether.tgz
		tar -xvzf cwm-tether.tgz
	fi
	cd "$HOME/cwm-tether/Tether/node"
	sudo ./configure
	sudo make
	cd "$HOME/cwm-tether/Tether/linux"
	sudo ./run.sh&disown
}
setupIpWebCam() {
	if [ ! -f "$HOME/ipcam.conf" ]; then
		read -p "Enter mobile ip address: " ipcam_ip
		echo "ipcam_ip=$ipcam_ip" > "$HOME/ipcam.conf"
		read -p "Enter IP Webcam port number: " ipcam_port
		echo "ipcam_port=$ipcam_port" >> "$HOME/ipcam.conf"
		read -p "Enter video width: " ipcam_width
		echo "ipcam_width=$ipcam_width" >> "$HOME/ipcam.conf"
		read -p "Enter video height: " ipcam_height
		echo "ipcam_height=$ipcam_height" >> "$HOME/ipcam.conf"
		read -p "Enter FPS: " ipcam_fps
		echo "ipcam_fps=$ipcam_fps" >> "$HOME/ipcam.conf"
		read -p "Enter audio codec (Default 'wav'): " ipcam_acodec
		echo "ipcam_acodec=$ipcam_acodec" >> "$HOME/ipcam.conf"
		read -p "Enter choice: 'a:audio, v:video, or av:audio/video: (default av):" ipcam_cap_stream
		echo "ipcam_cap_stream=$ipcam_cap_stream" >> "$HOME/ipcam.conf"
		read -p "Enter video device: (default=/dev/video0): " ipcam_dev
		echo "ipcam_dev=$ipcam_dev" >> "$HOME/ipcam.conf"
		read -p "Select a version: 1:free, 2:pro : " choice
		if [ "$choice" = "1" ] || [ "$choice" = "free" ]; then
			version="com.pas.webcam"
		elif [ "$choice" = "2" ] || [ "$choice" = "pro" ]; then
			version="com.pas.webcam.pro"
		fi
		echo "version=$version" > "$HOME/ipcam.conf"
		source "$HOME/ipcam.conf"
	fi
}
setupTether;
setupIpWebCam;
