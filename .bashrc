#
# ~/.bashrc
#

# If not running interactively, don't do anything
shopt -s autocd
HISTSIZE= HISTFILESIZE=

[[ $- != *i* ]] && return
PS1='\[\e[0m\]\w \[\e[0m\]>\[\e[0m\] '

alias yt-dlp='yt-dlp -o ~/videos/"%(title)s.%(ext)s"'
alias nf='neofetch --ascii ~/text/nfascii --gap '-250' --colors 4 4 7 4 7 7'
alias neofetch='neofetch --ascii ~/text/nfascii --gap '-250' --colors 4 4 7 4 7 7'
alias ls='ls --color=auto'
alias aria2c='aria2c --enable-dht=true --file-allocation=none'
alias lss='sudo du -h --max-depth=1 . | sort -rh'

eval "$(dircolors -p | \
    sed 's/ 4[0-9];/ 01;/; s/;4[0-9];/;01;/g; s/;4[0-9] /;01 /' | \
    dircolors /dev/stdin)"

neofetch
export PATH=/home/anon/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl
