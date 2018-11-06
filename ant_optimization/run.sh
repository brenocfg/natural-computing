for ants in 100 200 300 400; do
	for seed in 111 222 333 444 555 666 777 888 999 1111; do
		./aco input/graph2.txt 0.05 ${ants} 100 $seed >>out_graph2_${ants}_100_0.05_${seed}.csv
	done
done

for ants in 100 400 700 1000; do
	for decay in 0.01 0.05 0.1 0.3 0.5; do
		for seed in 111 222 333 444 555 666 777 888 999 1111; do
			./aco input/graph1.txt $decay $ants 1000 $seed >>out_graph1_${ants}_1000_${decay}_${seed}.csv
		done
	done
done

for ants in 100 400 700 1000; do
	for seed in 111 222 333 444 555; do
		./aco input/graph3.txt 0.05 $ants 1000 $seed >>out_graph3_${ants}_1000_0.05_${seed}.csv
	done
done
