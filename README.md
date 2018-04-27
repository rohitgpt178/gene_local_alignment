## BSE322A - Bioinformatics & Computational Biology
## Programming Assignment

Dated: 29th March 2018 \
Rohit Gupta (150594)

### Algorithm Implemented : Local Alignments in sequences with Affine Gap Penalty

### Input Format -
* Line 1 : match_reward mismatch_penalty gap_start_penalty gap_continuation_penalty
* Line 2 : sequence 1
* Line 3 : sequence 2

### Output Format -
* The code outputs all details along with local alignments at stdout.

### Running instructions -
Run the following commands to get alignments from input1.txt(in folder input).
> make \
> ./align < input/input1.txt

**NOTE** : The program does not output all possible optimal local alignments. It outputs an optimal alignment for each occurence of max_score in scoring matrix.
