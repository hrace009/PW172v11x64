#!/bin/bash

ServerDir=home
GsLogFileDir=$ServerDir
GsLogFileName=GameService_Log

if [ ! -d /$ServerDir/logs/ ]; then
mkdir /$ServerDir/logs/
fi
echo -e "=== [${txtred} START ${txtnrm}] Log Service ==="
cd /$ServerDir/logservice; ./logservice logservice.conf > /$ServerDir/logs/logservice.log &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""

echo -e "=== [${txtred} START ${txtnrm}] Auth ==="
cd /$ServerDir/gauthd; ./gauthd gamesys.conf > /$ServerDir/logs/gauthd.log &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2

echo -e "=== [${txtred} START ${txtnrm}] Unique Name ==="
cd /$ServerDir/uniquenamed; ./uniquenamed gamesys.conf > /$ServerDir/logs/uniquenamed.log &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2

echo -e "=== [${txtred} START ${txtnrm}] Data Base ==="
cd /$ServerDir/gamedbd; ./gamedbd gamesys.conf > /$ServerDir/logs/gamedbd.log &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2
echo -e "=== [${txtred} START ${txtnrm}] Anti Cheat ==="
cd /$ServerDir/gacd; ./gacd gamesys.conf > /$ServerDir/logs/gacd.log &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2
echo -e "=== [${txtred} START ${txtnrm}] Faction ==="
cd /$ServerDir/gfactiond; ./gfactiond gamesys.conf > /$ServerDir/logs/gfactiond.log &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2
echo -e "=== [${txtred} START ${txtnrm}] Delivery ==="
cd /$ServerDir/gdeliveryd; ./gdeliveryd gamesys.conf > /$ServerDir/logs/gdeliveryd.log &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2
echo -e "=== [${txtred} START ${txtnrm}] Link ==="
cd /$ServerDir/glinkd; ./glinkd gamesys.conf 1 >> /$ServerDir/logs/glink1.log 2>&1 &
cd /$ServerDir/glinkd; ./glinkd gamesys.conf 2 >> /$ServerDir/logs/glink1.log 2>&1 &
cd /$ServerDir/glinkd; ./glinkd gamesys.conf 3 >> /$ServerDir/logs/glink1.log 2>&1 &
cd /$ServerDir/glinkd; ./glinkd gamesys.conf 4 >> /$ServerDir/logs/glink1.log 2>&1 &
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2
echo -e "=== [${txtred} START ${txtnrm}] Game Service ==="
cd /$ServerDir/gamed; 
echo -e "=== [${txtgrn} OK ${txtnrm}] ==="
echo -e ""
#sleep 2
./gs gs01 gs.conf gmserver.conf gsalias.conf is61 is62 is78 > /home/logs/gs.log &
echo "Instances started"

#sleep 2

cd ~/pwadmin; ./pwadmin start &

