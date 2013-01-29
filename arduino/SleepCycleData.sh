#!/bin/sh

# data file name from arguments
if [ $# -ne 1 ]; then
  echo "error: This program needs one data file.."
  echo "usage:\n\r\t$0 [data file]" 1>&2
  exit 1;
elif [ ! -e $1 ]; then
  echo "error: This file is NOT exist.."
  exit 1;
elif [ ! -f $1 ]; then
  echo "error: This file is NOT normal file.."
  exit 1;
elif [ ! -r $1 ]; then
  echo "error: This file is NOT readable.."
  exit 1;
fi

# temporary file
date=`date +"%Y%m%d%H%M%S"`
file="/tmp/${date}_TMPLOG.txt"
work="/tmp/${date}_TMPLOG_work.txt"

touch $file
touch $work
if [ ! -w $file ]; then
  echo "error: Temporary file is NOT writable ..[$file]"
  echo "       Temporary directory is not exist or you have no perssion.. (?)"
  echo "       Please fix it.."
  exit 1;
elif [ ! -w $work ]; then
  echo "error: Temporary file is NOT writable ..[$file]"
  echo "       Temporary directory is not exist or you have no perssion.. (?)"
  echo "       Please fix it.."
  exit 1;
fi

cat $1 > $work 2>/dev/null

if type -P nkf > /dev/null; then
  nkf -Lu --overwrite $work
else
  echo "error: nkf is NOT found..(necessary converting linefeed code CRLF to LF)"
  exit 1;
fi


# data format
# YYMMddHHmmX
#  YY: year
#  MM: month
#  dd: day of month
#  HH: hour
#  mm: minute
#  ss: second
#   X: detected motion
#      1: detected
#      0: not detected

totalPer1sec() {
  # pick up validation data
  grep '^13[0-9]\{11\}' $work |\
    sed -e "s/\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\)/20\1\/\2\/\3 \4:\5:\6,\7/g" > $file
}

totalPer10sec() {
  # pick up validation data
  grep '^13[0-9]\{11\}' $work |\
    sed -e "s/\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\)[0-9]\([0-9]\)/20\1\/\2\/\3 \4:\5:\60,\7/g" > $file
}

totalPer1min() {
  # pick up validation data
  grep '^13[0-9]\{11\}' $work |\
    sed -e "s/\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)[0-9]\{2\}\([0-9]\)/20\1\/\2\/\3 \4:\5:00,\6/g" > $file
}

totalPer1min

cat $file > $work 2>/dev/null

# group totalization
# grouping target: 1st group, and 2nd group is totaled
awk -F"," '{group[$1]+=$2}END{for(name in group){print name","group[name]}}' $file | sort > $work

echo "Totalization is completed.." >&2
echo "Temporary file is already removed.." >&2
cat $work

rm -fr $work 2>/dev/null
rm -fr $file 2>/dev/null

