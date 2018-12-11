for deg in 3 4 5; do
	for seed in 1 2 3 4 5; do
		for prob in 20 40 60 80 100; do
			./rwa input/y/Y.${deg}_seed=${seed}.net input/y/Y.${deg}.${prob}_seed=${seed}.trf 20 20 3 1 >${deg}_${seed}_${prob}.out
		done
	done
done
