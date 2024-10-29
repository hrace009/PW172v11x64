mkdir dbhomewdb/data.fix
ls dbhomewdb/dbdata/ | awk '{ print "./dbtool -r -s dbhomewdb/dbdata/"$1" -d dbhomewdb/data.fix/"$1 }' | /bin/sh
rm -fr dbhomewdb/dbdata
rm -fr dbhomewdb/dblogs/*
mv dbhomewdb/data.fix dbhomewdb/dbdata
