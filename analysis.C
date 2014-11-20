#include <iostream>
#include <string>
#include <stdexcept>

#include "TTree.h"
#include "TFile.h"

#include "liboaanalysis/ND__TGlobalReconModule.h"
#include "liboaanalysis/ND__TTrackerECALReconModule.h"

ND::TTrackerECALReconModule::TECALReconObject* matchECalGlobalToLocal(ND::TGlobalReconModule::TECALObject* gecal, TClonesArray* ecalObjects) {
    ND::TTrackerECALReconModule::TECALReconObject* lecal = 0;
    for (int ilocal = 0; ilocal < ecalObjects->GetEntries(); ++ilocal) {
        ND::TTrackerECALReconModule::TECALReconObject* l = dynamic_cast<ND::TTrackerECALReconModule::TECALReconObject*>(ecalObjects->At(ilocal));
        if(l->UniqueID == gecal->UniqueID) {
            lecal = l;
            break;
        }
    }
    return lecal;
}

void printBasicGlobalInfo(ND::TGlobalReconModule::TGlobalPID* globalObj) {
    //Print some basic information about the object
    int numtpc = globalObj->NTPCs;
    int numecal = globalObj->NECALs;
    std::cout << "Global Object " << globalObj->UniqueID << " : contains ";
    std::cout << numtpc << " tpc, "
              << numecal << " ecal."
              << std::endl;
    return;
}

void printBasicTpcInfo(ND::TGlobalReconModule::TGlobalPID* globalObj) {
    //Print some TPC information
    int numtpc = globalObj->NTPCs;
    for (int itpc = 0; itpc < numtpc; ++itpc) {
        ND::TGlobalReconModule::TTPCObject* tpcobj = dynamic_cast<ND::TGlobalReconModule::TTPCObject*>(globalObj->TPC->At(itpc));
        std::cout << "TPC track " << itpc << " : p=" << tpcobj->FrontMomentum << "MeV" << std::endl;
    }
    return;
}


void printBasicECalInfo(ND::TGlobalReconModule::TGlobalPID* globalObj, TClonesArray* ecalObjects) {
    //Print some ECal information
    int numecal = globalObj->NECALs;
    for (int iecal = 0; iecal < numecal; ++iecal) {
        ND::TGlobalReconModule::TECALObject* gecal = dynamic_cast<ND::TGlobalReconModule::TECALObject*>(globalObj->ECAL->At(iecal));
        //Global ECal object only contains a subset of the ECal information.
        //To get the full ECal information we need to get the "local" ECal object.
        ND::TTrackerECALReconModule::TECALReconObject* lecal = matchECalGlobalToLocal(gecal, ecalObjects);
        if (lecal) {
            double emenergy = lecal->EMEnergyFit_Result;
            double mipem = lecal->PID_LLR_MIP_EM;
            std::cout << "ECal cluster" << iecal << " :"
                      << " emenergy=" << emenergy 
                      << " LLR_MIP_EM=" << mipem
                      << std::endl;
        }
    }
}


int analysis() {

    //Open file and get the trees we want to analyse
    std::string filename = "test.oaanalysisfile.root";
    TFile tfile(filename.c_str(), "READ");
    if (!tfile.IsOpen()) {
        std::cout << "Error failed to open file " << filename << std::endl;
        return 1;
    }
    TTree* ecalTree = dynamic_cast<TTree*>(tfile.Get("ReconDir/TrackerECal"));
    TTree* globalTree = dynamic_cast<TTree*>(tfile.Get("ReconDir/Global"));
    if(!ecalTree || !globalTree) {
        std::cout << "Error failed to get trees." << std::endl;
        return 2;
    }

    //Set branch addresses
    TClonesArray* globalObjects = 0;
    TClonesArray* ecalObjects = 0;
    ecalTree->SetBranchAddress("ReconObject", &ecalObjects);
    globalTree->SetBranchAddress("PIDs", &globalObjects);

    //Loop over trees
    int nevents = globalTree->GetEntries();
    for (int ievent = 0; ievent < nevents; ++ievent) {
        std::cout << "Event :" << ievent << std::endl;
        //Load this event into memory
        ecalTree->GetEntry(ievent);
        globalTree->GetEntry(ievent);
        //Loop over global objects
        for(int iglobal = 0; iglobal < globalObjects->GetEntries(); ++iglobal) {
            ND::TGlobalReconModule::TGlobalPID* globalObj = dynamic_cast<ND::TGlobalReconModule::TGlobalPID*>(globalObjects->At(iglobal));
            if (!globalObj) {
                throw std::runtime_error("failed to retrieve global object from array.");
            }
            printBasicGlobalInfo(globalObj);
            printBasicTpcInfo(globalObj);
            printBasicECalInfo(globalObj, ecalObjects);
        }
    }
    
    return 0;
}
