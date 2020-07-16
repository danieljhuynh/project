# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific aliases and functions
[ -n "$SSH_CONNECTION" ] && unset SSH_ASKPASS
export GIT_ASKPASS=

# For memory leak checking
export VALGRIND_LIB=/home/djhuynh/valgrind-3.14.0/.in_place

alias zip='zip -ry'
alias cp='cp -rf'

#checking GIT owners
alias gbo='git for-each-ref --format='\''%(committerdate) %09 %(authorname) %09 %(refname)'\'' | grep remotes'

#goto product directory:
alias cdp='cd $(echo $PWD|sed -e "s/^\(.*\/s[0-9][0-9][a-z]\).*/\1/g")'
#goto reldir directory:
alias cdr='cd $(find $(echo $PWD|sed -e "s/^\(.*\/s[0-9][0-9][a-z]\).*/\1/g") -name reldir -type d)'
#goto reldir/exe directory:
alias cdx='cd $(find $(echo $PWD|sed -e "s/^\(.*\/s[0-9][0-9][a-z]\).*/\1/g") -name exe -type d)'
#goto reldir/lib directory:
alias cli='cd $(find $(echo $PWD|sed -e "s/^\(.*\/s[0-9][0-9][a-z]\).*/\1/g") -name lib -type d)'
#goto reldir/log directory:
alias clo='cd $(find $(echo $PWD|sed -e "s/^\(.*\/s[0-9][0-9][a-z]\).*/\1/g") -name log -type d)'
#goto reldir/pat directory:
alias cpa='cd $(find $(echo $PWD|sed -e "s/^\(.*\/s[0-9][0-9][a-z]\).*/\1/g") -name reldir -type d); cd pat'
#goto reldir/src directory:
alias cds='cd $(find $(echo $PWD|sed -e "s/^\(.*\/s[0-9][0-9][a-z]\).*/\1/g") -name reldir -type d); cd src'
