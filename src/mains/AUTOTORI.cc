/***************************************************************************//**
\file AUTOTORI.cc
\brief Automatically generates file with tori of many (given) actions

*                                                                              *
* AUTOTORI.cc                                                                  *
*                                                                              *
* C++ code written by Walter Dehnen, 1994/95,                                  *
*                     Paul McMillan, 2007                                      *
* e-mail:  paul@astro.lu.se                                                    *
* github:  https://github.com/PaulMcMillan-Astro/Torus                         *
*                                                                              *
*******************************************************************************/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#include "Torus.h"
#include "LogPot.h"
#include "MiyamotoNagaiPot.h"
#include "PJM_cline.h"

using std::cerr;



int main(int argc,char *argv[])
{
  int      flag,err=0;
  clock_t cpu0 = clock();
  double   dJ=0.003;
  Actions  J,oJ;
  Torus    *T;
  ifstream from;
  ofstream to;
  Potential *Phi;
  T = new Torus;
//---------------------------------------------------------------------------
  if(argc<3 || argc>6){
    cerr <<"Input: potential actions outlist (dJ=) (err=)\n\n"
	 <<"actions are given as a file with the actions JR Jz Jphi as first 3 "
	 << "entries in each line\n"
	 <<"This programme is a good way of finding tori.\n"
	 <<"\nN.B. In the lite package this code does not output to file\n";
    exit(1);
  }
//---------------------------------------------------------------------------
//===========================================================================
// 1. Get target potential
 
  cerr << "Using default potential - Logarithmic with vc=220 km/s, q=0.8\n"
       << "If you want something different, programme it in\n";
  Phi = new LogPotential(220.*Units::kms,0.8,0.);
  

  my_open(from,argv[2]);
  //TorusList Tlist(argv[3],"o");
  for(int i=4;i!=argc;i++) {
    bool understood=false;
    if(parse_comm_line(argv[i],"dJ=",dJ)) understood=true;
    if(parse_comm_line(argv[i],"err=",err)) understood=true;
    if(!understood) {
      cerr << "Input "<<argv[i]<<" not understood\n"; exit(1);
    }
  }

  int nout = how_many_lines(from), nignore=0;
  if((nignore =entrys_in_line(from)-3) != 0) {
    if(nignore<0) {
      cerr << "too few entries per line\n"; exit(1);
    }
    cerr << "assuming that the first three entries per line are actions\n";
  }
  

  for(int i=0;i!=nout;i++) {
    from >> J;
    double dummy;
    for(int j=0;j!=nignore;j++) from >> dummy;
    flag = T->AutoFit(J,Phi,dJ,700,300,15,5,24,200,24,err);
    
    std::cout << J << ", flag = " << flag << "\n" << std::flush;
    // Output. 
    // flag = 0  -> success
    // flag = -1 -> catastrophic breakage
    // flag = -2 -> target < dH <2*target
    // flag = -3 -> 2*target < dH
    // flag = -4 -> angle fit failed
    std::stringstream tor; tor << "t" << i+1;
  }
  cerr << "time taken in seconds: " 
       << double(clock()-cpu0)/double(CLOCKS_PER_SEC) << "\n";
}




