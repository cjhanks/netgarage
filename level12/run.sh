
for i in {1..1000}
do
  array=()
  for i in {a..z} {A..Z} {0..9};
   do
     array[$RANDOM]=$i
  done

  length=$(($RANDOM % 16 + 3))
  printf %s ${array[@]::${length}} > level12.pass
  python3 run.py

  echo "========================="
  cat level12.pass
  echo ""
  cat password
  echo ""
  echo "-------------------------"
  md5sum level12.pass password

done
