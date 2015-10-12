example-readoaanalysis
============

This package provides a simple example for new T2K students to read [ND280 OA analysis files](http://hep.lancs.ac.uk/nd280Doc/stable/invariant/oaAnalysis/) using only [ROOT](https://root.cern.ch) and no other external libraries.

Compiling and Running the Example Analysis
------------

Before you start you will need an oaAnalysis input file. The scripts are hard coded to look for a file named "test.oaanalysisfile.root" in the current working directory. You should make sure this file exists, or edit the scripts to point to a real file before proceeding.

There are two steps involved. First you must generate the libraries needed to read the oaAnalysis file. This is done with the [TFile::MakeProject](http://root.cern.ch/root/html/TFile.html) method. This is done by running the makelib.C script:

    root -l makelib.C

The "-l" option prevents the annoying ROOT splash screen.
This script should create a directory "liboaanalysis" containing the header files and library that you will need.
If it worked you should see that it contains a file "liboaanalysis/liboaanalysis.so". You are now ready to analyse an oaAnalysis file.

You can run the example analysis code with:

    root -l run.C

This script loads the libraries that were generated in the previous step, compiles "analysis.C" and runs the method "analysis()". "analysis.C" contains a simple analysis script that loops over global recon objects and prints information to stdout.

Congratulations, you have successfully run your first oaAnalysis analysis!

Reading Files Interactively
------------
You can also read analysis files in an interactive ROOT session.

    root -l 
    
To view to file contents in a GUI, in an interactive session do:

    [0] gSystem->Load("liboaanalysis/liboaanalysis.so"); // load libraries
    [1] TBrowser b;

From the [TBrowser](https://root.cern.ch/doc/master/classTBrowser.html) window you can double click on the analysis file to open it.

You can make simple plots using the [TTree::Draw](https://root.cern.ch/doc/master/classTTree.html) command.

    [2] TFile* f = new TFile("test.oaanalysisfile.root");
    [3] TTree* t = (TTree*) f->Get("ReconDir/TrackerECal");
    [4] t->Draw("ReconObject.PID_LLR_MIP_EM");

