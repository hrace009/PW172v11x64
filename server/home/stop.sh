#!/bin/sh

echo -e "[${txtgrn} OK ${txtnrm}] Stop Log Service"
pkill -9 logservices
echo -e "[${txtgrn} OK ${txtnrm}] Stop Link"
pkill -9 glinkd
echo -e "[${txtgrn} OK ${txtnrm}] Stop Auth"
pkill -9 authd
echo -e "[${txtgrn} OK ${txtnrm}] Stop Delivery"
pkill -9 gdeliveryd
echo -e "[${txtgrn} OK ${txtnrm}] Stop Anti Cheat"
pkill -9 gacd
echo -e "[${txtgrn} OK ${txtnrm}] Stop Game Service"
pkill -9 gs
echo -e "[${txtgrn} OK ${txtnrm}] Stop Faction"
pkill -9 gfactiond
echo -e "[${txtgrn} OK ${txtnrm}] Stop Unique Name"
pkill -9 uniquenamed
echo -e "[${txtgrn} OK ${txtnrm}] Stop Data Base"
pkill -9 gamedbd
echo -e "[${txtgrn} OK ${txtnrm}] Stop Java"
pkill -9 java
echo -e "[${txtgrn} OK ${txtnrm}] Stop mono"
pkill -9 mono

pkill -9 license
