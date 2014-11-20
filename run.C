#include "TSystem.h"
#include "TROOT.h"
#include "TVector2.h"

int run() {
    TVector2 _dummyvector; // hack to fix problem loading library with v10r11p23 and prod6 input file
    gSystem->Load("liboaanalysis/liboaanalysis.so");
    gROOT->ProcessLine(".L analysis.C+");
    return analysis();
}

