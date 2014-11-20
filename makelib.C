#include "TFile.h"

void makelib() {
    TFile tfile("test.oaanalysisfile.root", "READ");
    tfile.MakeProject("liboaanalysis", "*", "update+");
    return;
}
