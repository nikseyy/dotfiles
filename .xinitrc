slstatus &
dunst &
flameshot &
picom &

nvidia-settings --load-config-only &
xrandr --output HDMI-0 --mode 2560x1080 --output DVI-D-0 --mode 2560x1080 --right-of HDMI-0 &
xrdb ~/.Xresources &
exec dwm
