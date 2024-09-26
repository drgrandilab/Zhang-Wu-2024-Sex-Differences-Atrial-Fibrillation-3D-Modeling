#include "RyR.hpp"
#include <iostream>

RyR::RyR(int RYR_Num, int BCSQN_local, int ID, int flag_AF, int flag_female, double Jmax_set)
	: random_num_RyR(0, ID), Jmax(Jmax_set)
{
        BCSQN = BCSQN_local;

	N_RyR = RYR_Num;
	RyR_1 = 0 + int (5.0 * random_num_RyR.gen_rand());
	RyR_2 = 0;
	RyR_3 = 0;

	tmp1 = 0;
	tmp2 = 0;
        
  AF    = flag_AF;
  female= flag_female; // Mon 03 Jan 2022 09:29:05 PM PST
}

RyR::~RyR() {}

double RyR::Update_RyR_stochastic(double dt, double Caj, double CaSRj) {

  double reduction;
  double fold;
	if (AF * female == 1) {
			reduction = 100.0;
			fold = 3.0;
		}
	else{
	  	reduction = 0.0;
	  	fold = 1.0;
		}
	   
  double rho = rhoinf * 1.0 / (1.0 + pow((KK-reduction) / CaSRj, hh));
	if (rho < 0.0000001)rho = 0.0000001;
	double MM = (sqrt(1 + 8 * rho * BCSQN) - 1) / (4 * rho * BCSQN);
	
  Po = (RyR_2 + RyR_3) / 100.0;

	double cp2 = Caj * Caj;
	double sgmd = cp2 * Caj / (Kcp * Kcp * Kcp + cp2 * Caj);
	double k12 = Ku * sgmd + pedk12;
	double k43 = Kb * fold * sgmd + pedk43;

	double k14 = MM / taub * BCSQN / BCSQN0;
	double k21 = 1 / tauc1;
	double k23 = MM / taub * BCSQN / BCSQN0;
	double k41 = 1 / tauu;
	double k34 = 1 / tauc2;
	double k32 = k41 * k12 * k23 * k34 / k43 / k21 / k14;

	int RyR_4 = N_RyR - RyR_1 - RyR_2 - RyR_3;
	Update_RyR_rates_stochastic_MN(RyR_1, k12 * dt, k14 * dt);
	int ryr12 = tmp1;
	int ryr14 = tmp2;
	Update_RyR_rates_stochastic_MN(RyR_2, k23 * dt, k21 * dt);	
	int ryr23 = tmp1;
	int ryr21 = tmp2;
	Update_RyR_rates_stochastic_MN(RyR_3, k34 * dt, k32 * dt);	
	int ryr34 = tmp1;
	int ryr32 = tmp2;	
	Update_RyR_rates_stochastic_MN(RyR_4, k41 * dt, k43 * dt);
	int ryr41 = tmp1;
	int ryr43 = tmp2;

	RyR_1 = RyR_1 - (ryr12 + ryr14) + (ryr21 + ryr41);
	RyR_2 = RyR_2 - (ryr21 + ryr23) + (ryr12 + ryr32);
	RyR_3 = RyR_3 - (ryr34 + ryr32) + (ryr43 + ryr23);

	return Po;
}

void RyR::Update_RyR_rates_stochastic_MN(int n, double p1, double p2)
{
	if (p1+p2 >= 1){
		std::cout << "Need smaller dt Update_RyR_rates_stochastic_MN()!!!! "<< std::endl;
		std::exit(0);
	}
	if (n < 0){
		std::cout << "Negative trials Update_RyR_rates_stochastic_MN()!!!! "<< std::endl;
		std::exit(0);
	}
	if (n == 0){
		tmp1 = 0;
		tmp2 = 0;
	}else{
	  double remaining_p = 1.0;
	  double p [2] = {p1, p2};
	  int j;
	  int dn = n;
	  int d  = 3;
	  int X [3] = {0, 0, 0};
	  for (j = 0; j < (d - 1); j++) {
	    X[j] = random_binomial(dn, p[j] / remaining_p);
	    dn = dn - X[j];
	    if (dn  <= 0) {
	      break;
	    }
	    remaining_p -= p[j];
	  }
	  if (dn > 0) {
	      X[d - 1] = dn;
	  }
	  tmp1 = X[0];
	  tmp2 = X[1];
	}
}

int RyR::random_binomial(int n, double p) {
  double q;

  if ((n == 0) || (p == 0.0))
    return 0;

  if (p <= 0.5) {
    return Update_RyR_rates_stochastic_python(n, p);
  }
  else {
    q = 1.0 - p;
    return n - Update_RyR_rates_stochastic_python(n, q);
  }  
}

int RyR::Update_RyR_rates_stochastic_python( int n, double p) {
	if (n <= 0) return 0;
	if (p >= 1) {
		//std::cout << p << std::endl;
		p = 1;
		return n;
	}
	if (n == 1) {
		if (random_num_RyR.gen_rand() <= p)
			return 1;
		else
			return 0;
	}


  double q, qn, np, px, U;
  int X, bound;


  q     = 1.0 - p;
  qn    = exp(n * log(q));
  np    = n * p;
  bound = (int)fmin(n, np + 10.0 * sqrt(np * q + 1));

  X     = 0;
  px    = qn;
  U     = random_num_RyR.gen_rand();

  while (U > px) {
    X++;
    if (X > bound) {
      X = 0;
      px = qn;
      U = random_num_RyR.gen_rand();
    } else {
      U -= px;
      px = ((n - X + 1) * p * px) / (X * q);
    }
  }
  return X;
}
