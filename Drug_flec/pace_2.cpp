#include "Spatial_Cell.h"
#include <math.h>
#include <array>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
        double dt               = 0.01;
        int count               = 0;
        int out_interval        = int(1.0 / dt);
        double voltage_rest     = -70;
        double stim_current     = 12.5;
        double stim_duration    = 5;
        double pre_rest         = 4000;
        double bcl              = atof(argv[1]);
        int iter                = atoi(argv[2]);
        double delay_rest       = 5000;
        double T_total          = pre_rest + bcl * iter + delay_rest;

        std::string tub_flag    = argv[3];
        int flag_AF             = atoi(argv[4]); // 0: nSR; 1: cAF 
        int flag_female         = atoi(argv[5]); // 0: male; 1: female 

        std::string str1        = "pool_tubule/";
        std::string str2        = "nSR_Male/";
        std::string str3        = "tub_input_ver2_";
        std::string str4        = ".txt";
        std::string tubular_map_file;
        // Initiate the cell dimensions and tubular map for Male/Female and nSR/cAF 
        int nx_cru                      = 55;
        int ny_cru                      = 17;
        int nz_cru                      = 11;
        
        // 1: Dense 2: Intermediate 3: Sparse 
        if(flag_female == 0 && flag_AF == 0)
        {
                nx_cru                  = 55;
                ny_cru                  = 17;
                str2                    = "nSR_Male/";
        }else if(flag_female == 1 && flag_AF == 0)
        {
                nx_cru                  = 50;
                ny_cru                  = 13;
                str2                    = "nSR_Female/";
        }else if(flag_female == 0 && flag_AF == 1)
        {
                nx_cru                  = 61;
                ny_cru                  = 20;
                str2                    = "cAF_Male/";
        }else if(flag_female == 1 && flag_AF == 1)
        {
                nx_cru                  = 55;
                ny_cru                  = 16;
                str2                    = "cAF_Female/";
        }else
        {
                cout << "Wrong flag inputs!" << endl;
        }

        tubular_map_file    = str1 + str2 + str3 + tub_flag + str4;

        Spatial_Cell cell(dt, 0, 0, bcl, tubular_map_file, flag_AF, flag_female, nx_cru, ny_cru, nz_cru);

        int AP_set_id = 0;
        std::vector<double> AP_set;
        int AP_count = 0;
        string AP_file          = "./pool_AP/AP_";
        string AP_file_end      = ".txt";
        AP_file.append(argv[1]);
        AP_file.append(AP_file_end);
        // std::cout << AP_file << std::endl;

        std::ifstream inAP(AP_file.c_str());    // "./pool_AP/AP_3hz.txt"
        std::string APline;

        double tmp = 0;

        while (std::getline(inAP, APline))
        {
                std::stringstream ssAP(APline);
                ssAP >> tmp;
                AP_set.push_back(tmp);
                // std::cout << AP_set[AP_count] << std::endl;
                ++AP_count;
        }

	for (double t = 0; t < T_total; t += dt)
	{
		cell.dt = dt;
		double stim   = -80.0;
                if ( t < pre_rest )
                {
                        stim    = AP_set[0];
                } else if ( int(t/dt) < int( T_total/dt - delay_rest /dt))
                {
                        AP_set_id = int((t-pre_rest)/dt) % int(bcl/dt);
                        stim    = AP_set[AP_set_id];
                } else{
                        // stim    = AP_set[AP_count-1];
                        stim    = AP_set[AP_set_id]; // Xianwei
                }
                
                cell.pace(stim);

		std::string nnn;
		if (count % out_interval == 0) {
			cell.output_Cai(nnn);
		}

                if (t > pre_rest + bcl*iter - 4000 && count % out_interval == 0)
                {
			cell.output_binary(nnn);
		}

                if( (t > T_total - delay_rest - 0.5 * dt) && (t < T_total - delay_rest + 0.5 * dt) )
                {
                        cell.sc.get_steady_state();
                        cell.cc.get_steady_state();  
                }

		count ++;
	}
	return 0;
}

