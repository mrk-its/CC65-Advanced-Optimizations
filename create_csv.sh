(
    START_REV=0307d69d99d50425e93dd94517bec9c6cc947141
    echo - $(cat baseline.txt | grep -e '[0-9][0-9]-') | sed 's/ /,/g';
    for i in $(seq 21 -1 0); do
      REV_RANGE="$START_REV..HEAD~$i baseline.txt";
      echo $(git diff $REV_RANGE | grep llvm-mos:|cut -f 2 -d ':' | cut -b 1-11) $(git diff $REV_RANGE baseline.txt | grep ticks | cut -f 2 -d ':');
    done | uniq -w 40 |sed 's/ /,/g'
) | tee baseline.csv
