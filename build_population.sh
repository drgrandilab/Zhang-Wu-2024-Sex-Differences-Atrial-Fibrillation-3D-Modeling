declare -a rate_array=("05hz" "1hz" "2hz" "3hz" "4hz" "5hz")
declare -a bcl_array=("2000" "1000" "500" "333.34" "250" "200")
declare -a beat_num_array=("14" "28" "56" "84" "112" "140")
declare -a flag1_array=("nSR" "cAF")
declare -a flag2_array=("M" "F")

for flag1_id in 0
do
	mkdir ${flag1_array[$flag1_id]}
	cd ${flag1_array[$flag1_id]}
	for flag2_id in 0 1
	do
		mkdir ${flag2_array[$flag2_id]}
		cd ${flag2_array[$flag2_id]}
		# for tub_id in 1 10 20
		for tub_id in 2
		do
			mkdir T${tub_id}
			cd T${tub_id}
		    for rate_id in 0 1
			# for rate_id in 
			do
				 cp ../../../sex_diff_model_APclamp ${rate_array[$rate_id]} -r
				 cd ${rate_array[$rate_id]}
				 sed -i "2s/nSR/${flag1_array[$flag1_id]}/" run.slurm
				 sed -i "2s/M/${flag2_array[$flag2_id]}/" run.slurm
				 sed -i "2s/T1/T${tub_id}/" run.slurm
				 sed -i "2s/03HZ/${rate_array[$rate_id]}/" run.slurm
				 sed -i "15s/1000 28 2 0 0/${bcl_array[$rate_id]} ${beat_num_array[$rate_id]} ${tub_id} ${flag1_id} ${flag2_id}/" run.slurm
				 # sed -i "14s/14/${beat_num_array[$rate_id]}/" run.slurm
				 # sed -i "14s/1/${tub_id}/" run.slurm
				 # sed -i "14s/0 0/${flag1_id} ${flag2_id}/" run.slurm
				 cd ..
			done
			cd ..
		done
		cd ..
	done
	cd ..
done
