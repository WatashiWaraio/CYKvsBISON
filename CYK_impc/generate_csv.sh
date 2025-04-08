for i in $(seq 50 50 499)
do
    echo -n "$i,"
done
echo 500

for iteracion in {1..10}
do
    col=""
    for i in {1..9}
    do
        col+=$(cat "./expressions_$i.txt" | time ./analizador 2>&1 | head -n1 | cut -d ' ' -f 3 | sed 's/elapsed/,/' | sed 's/0://')
    done
    col+=$(cat "./expressions_10.txt" | time ./analizador 2>&1 | head -n1 | cut -d ' ' -f 3 | sed 's/elapsed//' | sed 's/0://')

    echo $col
done
