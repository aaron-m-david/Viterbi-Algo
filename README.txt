Aaron David
Viterbi Algorithm

How to compile:
The code can be compiled using the provided makefile.

How to test:
A testing script is provided that can be ran by running './test_main'.
The script takes no arguments and assumes the program has already been compiled with the provided makefile.
Expected results can be seen in the 'expected_results' directory and the actual output of the program 
    can be seen in the 'my_results' directory.
Differences between the what was expected vs the actual output can be seen in the 'diff' directory.
    Note: If there are no differences between the two files, the diff file will be empty.

Further Testing:
Additional tests can be added by adding:
    A file named 't0{num}.in' where {num} is replaced with the number of the test to the 'tests' directory
    Adding a corresponding output file to 'expected_results' named 't{num}.out' where num is replaced with the number of the test

Test Descriptions:
Test descriptions and written verification for each test can be found in the 'test_descriptions' directory.

Project Description:
main.cpp implements an approach to Viterbi's Algorithm that finds the most likely path given a HMM and a set of observations seen.
The executable 'a.out' expects no command line arguments. It reads from stdin as follows:
    Integer n representing number of states in HMM
    Initial starting probabilities for those states // doubles
    Followed by n lines expecting transition probabilities from state i to state j
        EXAMPLE OF HMM WITH 2 STATES: First Line: (State 1 -> State 1) (State 1 -> State 2)
                                     Second Line: (State 2 -> State 1) (State 2 -> State 2)
    Integer n representing number of observations that can be seen
    Followed by n lines of emmission probabilities
        EXAMPLE OF HMM WITH 2 POSSIBLE OBSERVATIONS: First Line: (State 1 -> Obs 1) (State 1 -> Obs 2)
                                                    Second Line: (State 2 -> Obs 1) (State 2 -> Obs 2)
    Integer n representing number of observed observations
    n observations to read in // ints
Output:
    Prints the matrix of maximum probabilities up to each state at each observation
        followed by a newline followed by the Viterbi Path
Possible Concerns and How They Were Treated:
    Possible Underflow:
        Underflow was a large concern when writing the algorithm. It can be assumed that with very large HMMs
            and very large sets of seen observations that underflow is inevitable. 
        Solution: Store all probabilities as long doubles.
            While maybe not the most elegant solution it is very simple and can represent very small numbers.
            In the future, it might be worthwhile using logarithm to represent even smaller probabilities.
    Transition/Emmission Probs of 0:
        I chose to assume the user understands the risk of probabilities of 0 being passed in unintentionally,
            opposed to implementing Laplace Smoothing as part of Viterbi's algorithm / preprocessing of the HMM.
 
