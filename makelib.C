#include "TFile.h"

void makelib() {
    TFile tfile("test.oanalysisfile.root", "READ");
    tfile.MakeProject("liboanalysis", "*", "update+");
    return;
}
