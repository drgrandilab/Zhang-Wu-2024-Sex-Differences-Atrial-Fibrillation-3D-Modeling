declare -a rate_array=("05hz" "1hz" "2hz" "3hz" "4hz" "5hz")
declare -a bcl_array=("2000" "1000" "500" "333.34" "250" "200")
declare -a beat_num_array=("14" "28" "56" "84" "112" "140")
declare -a flag1_array=("nSR" "cAF")
declare -a flag2_array=("M" "F")

for flag1_id in 0 
do
	cd ${flag1_array[$flag1_id]}
	for flag2_id in 0 1
	do
		cd ${flag2_array[$flag2_id]}
		# for tub_id in 1 10 20
		for tub_id in 2
		do
			cd T${tub_id}
		    for rate_id in 0 1 2 3 4 5
			# for rate_id in 2 3
			#for rate_id in 3
			do
				cd ${rate_array[$rate_id]}
				sbatch run.slurm
				cd ..
			done
			cd ..
		done
		cd ..
	done
	cd ..
done
