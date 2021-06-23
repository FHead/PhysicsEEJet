
# EE Jet Analysis Code

## Installation

### Prerequisites

To start running, you will need a few things

1. CERN `ROOT` with `RooFit` enabled
   - we need to link to it
   - make sure `root-config` is in `PATH` variable
1. fastjet
   - go to fastjet.fr and install it somewhere!
   - make sure `fastjet-config` is in `PATH` variable
1. helper codes
   - go clone this https://github.com/FHead/fheadhelpercode somewhere
1. (optional) `pythia8` installation


### CompileRootMacro script

The script itself is in the `fheadhelpercode/RootMacros` directory

First make sure this script is in your `PATH` variable, then modify it to use the correct flags, directories, etc

You can see a bunch of `if/else` statement, add one for your machine and modify accordingly


### Compile stuff

Go to fheadhelpercode/RootMacros/Code and do 

```shell
bash Compile
```

Then come back here and go into `CommonCode`.  And do

```shell
make
```


## Samples

Then you need a bunch of samples.

Make a `Samples` folder and put the corresponding files as follows

```
Samples/
   ALEPH/
      *.root
   ALEPHMC/
      *.root
   HERWIG7/
      run_00/
         *.root
      run_01/
         *.root
      ...
   HERWIG715/
      run_00/
         *.root
      ...
   SHERPA/
      run_00/
         *.root
      ...
```

And then copy the `PurePythia91.root` into `MCStudies/23417_PythiaWholeEvent/` folder.  (or generate it with `make RunPythiaOnShell` if you have `pythia8` installed)

Ask Yi where to find the root files

Now we're ready to run things!


## Code overview

The code is modularized, with a two-layer folder convention.  The parent folder is the rough category of the code, and the subfolders are the units of code that each does something specific.  And then we link them together.  There are `makefile`s that helps with tasks that we need to run over and over again.

The most important ones to start with are the `MCStudies` folder which contains simulation-based jet calibration code, and `DataStudies` folder which does the data-simulation difference.  The `JetCorrection` folder contains all the calibration constants that are used by later code.  Since they are derived already, we do not usually need to run it again unless we want to rederive things with new jet clustering algorithm.

Then the actual analysis code is in `UnfoldingStudies`.  Looking into the `makefile`, we can see a number of steps.

1. `JetClustering`: from reconstructed particles we cluster jets and write into intermediate format
2. `UnfoldPreparation`: from the output of the previous step, we prepare input files for unfolding step
3. `NominalUnfold`: actual unfold!
4. `MCIterationScan`: optimize unfolding parameters for simulation-based samples
5. `DataIterationScan`: optimize for data
6. `LeadingJetCorrection`: derive leading jet corrections
7. `Systematics`: fill in all the different systematics and prepare for the final result
8. `FinalPlot`: make pretty plots!

To start and run, we should do

```shell
make RunAllQuick
```

and wait until it finishes.  If everything is set up correctly, we should see a bunch of pretty plots being generated!



