example-readoaanalysis
============

This package provides a simple example for new T2K students to read ND280 OA analysis files using only ROOT and no other external libraries.

There are two steps involved. First you must generate the libraries needed to read the oaAnalysis file. This is done with the [TFile::MakeProject](http://root.cern.ch/root/html/TFile.html) method. This is done by running the makelib.C script:

    root -l makelib.C+

The trailing "+" forces ROOT to compile the script before running it (which is optional but is good practice). 
The "-l" option prevents the annoying ROOT splash screen.
This script should create a directory "liboaanalysis" containing the header files and library that you will need.
If it worked you should see that it contains a file "liboaanalysis/liboaanalysis.so". You are now ready to analyse an oaAnalysis file.

You can run the example analysis code with:

    root -l run.C

This loads the libraries that we have just created and then runs the analysis script "analysis.C". 
Notice that this time we omitted the trailing "+". 
This is because there is you need to load the library before you can successfully compile the analysis script.
This cyclic dependency makes compilation impossible.
"analysis.C" contains a simple analysis script that loops over global recon objects and prints information to stdout.

Congratulations, you have successfully run your first oaAnalysis analysis!



