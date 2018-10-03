#Testing population size/number of generations combinations
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

for prob in 0.9 0.8 0.6
do
	for seed in 111 222 333 444 555
	do
		./gen input/synth1/synth1-train.csv input/synth1/synth1-test.csv $seed 500 100 1 $prob 2 >out_${prob}_${seed}.csv 2>/dev/null
	done
done

for size in 2 5 10
do
	for seed in 111 222 333 444 555
	do
		./gen input/synth1/synth1-train.csv input/synth1/synth1-test.csv $seed 500 100 1 0.8 $size >out_${size}_${seed}.csv 2>/dev/null
	done
done

for elit in 0 1
do
	for seed in 111 222 333 444 555
	do
		./gen input/synth1/synth1-train.csv input/synth1/synth1-test.csv $seed 500 100 $elit 0.8 5 >out_${elit}_${seed}.csv 2>/dev/null
	done
done
