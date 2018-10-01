for pop in 50 100 500
do
	for gen in 50 100 500
	do
		for seed in 111 222 333 444 555
		do
		./gen input/synth1/synth1-train.csv input/synth1/synth1-test.csv $seed $pop $gen 1 0.9 2 >out_${pop}_${gen}_${seed}.csv 2>/dev/null
		done
	done
done
