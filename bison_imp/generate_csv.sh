for i in $(seq 1500000 500000 5900000)
do
    echo -n "$i,"
done
echo 6000000

for iteracion in {1..10}
do
    col=""
    for i in {1..9}
    do
        col+=$(cat "./expressions_$i.txt" | time ./bison_imp/analizador 2>&1 | head -n1 | cut -d ' ' -f 3 | sed 's/elapsed/,/' | sed 's/0://')
    done
    col+=$(cat "./expressions_10.txt" | time ./bison_imp/analizador 2>&1 | head -n1 | cut -d ' ' -f 3 | sed 's/elapsed//' | sed 's/0://')

    echo $col
done
