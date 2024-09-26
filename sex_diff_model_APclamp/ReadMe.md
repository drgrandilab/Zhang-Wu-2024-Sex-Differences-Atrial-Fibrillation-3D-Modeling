C++ code for Zhang, Wu et al. Enhanced Ca2+-Driven Arrhythmias in Female Patients with Atrial Fibrillation: Insights from Computational Modeling. Baseline simulation
_____________________________________________________________________________________________________
### Contents:

* ```ReadMe.md```:					this file  

* ```Makefile```:					the default make file  
* ```build```:						folder of object files  
* ```run.slurm```:					the command file in slurm-managed system   

* ```pace_2.cpp```:					the main function with inputs: basic-cycle-length in ms, number of pacing beats, tubular structure type: 1: Dense; 2: Intermediate; 3: Sparse, sympton: 0: nSR; 1: cAF, sex: 0: male; 1: female 
* ```lib_cell```: 					folder with all the functions  
* ```pool_tubule```: 				folder of input fles of tubular structures  
* ```pool_ryr```: 					folder of input fles of ryanodine receptors heterogeneity  
* ```pool_csq```:	 				folder of input fles of calsequestrin heterogeneity  
* ```pool_AP```:	 				folder of input fles of action potential  

* ```global_result```:				folder of output files (whole-cell averaged ion concentrations and ion currents)  
* ```BinaryFiles```: 				folder of output binary files (local CRU calcium concentration)  

* ```steady_state_output```: 		folder of files with varible values at the end of pacing period   
_____________________________________________________________________________________________________
### Sample command in the terminal command line:
```bash
make
mkdir -p global_result # create folders for data ouput
mkdir -p BinaryFiles
mkdir -p steady_state_output
./pace_2 1000 28 2 0 0
```   
_____________________________________________________________________________________________________

### References:

Xianwei Zhang, Yixuan Wu, Charlotte Smith, William E Louch, Stefano Morotti, Dobromir Dobrev, Eleonora Grandi, Haibo Ni. Enhanced Ca2+-Driven Arrhythmias in Female Patients with Atrial Fibrillation: Insights from Computational Modeling. JACC: Clinical Electrophysiology. https://doi.org/10.1016/j.jacep.2024.07.020

Zhang, Xianwei, Haibo Ni, Stefano Morotti, Charlotte E. R. Smith, Daisuke Sato, William E. Louch, Andrew G. Edwards, and Eleonora Grandi. Mechanisms of Spontaneous Ca2+ Release-Mediated Arrhythmia in a Novel 3D Human Atrial Myocyte Model: I. Transverse-Axial Tubule Variation. The Journal of Physiology. https://doi.org/10.1113/JP283363.

Zhang, Xianwei, Charlotte E. R. Smith, Stefano Morotti, Andrew G. Edwards, Daisuke Sato, William E. Louch, Haibo Ni, and Eleonora Grandi. Mechanisms of Spontaneous Ca2+ Release-Mediated Arrhythmia in a Novel 3D Human Atrial Myocyte Model: II. Ca2+-Handling Protein Variation. The Journal of Physiology.  https://doi.org/10.1113/JP283602.

Please cite the above papers when using this model.