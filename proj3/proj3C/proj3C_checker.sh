#!/bin/bash

: <<'END_COMMENT'
This script checks your proj3C.c and proj3C_hastable.c. It checks for correct output,
handling of input, memory leaks, etc.

To use this checker make sure all files are in the directory including testHash.c.

END_COMMENT


score=0

echo "Note most recent score report could be your grade for the project out (score/10)"
echo "SCORE=$score"

## Make sure to have these 6 files
echo "/*----- Looking for required source files -----*/:"
echo "/*----- Looking for proj3C.c -----*/:"
if [[ ! -f proj3C.c ]] ; then
   echo "Cannot find file proj3C.c"
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

echo "/*----- Looking for proj3C_hashtable.c -----*/:"
if [[ ! -f proj3C_hashtable.c ]] ; then
   echo "Cannot find file proj3C_hashtable.c"
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

echo "/*----- Looking for proj3C_hashtable.h -----*/:"
if [[ ! -f proj3C_hashtable.h ]] ; then
   echo "Cannot find file proj3C_hashtable.h"
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

echo "/*----- Looking for wordlist1.txt -----*/:"
if [[ ! -f wordlist1.txt ]] ; then
   echo "Cannot find file wordlist1.txt "
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

echo "/*----- Looking for wordlist2.txt -----*/:"
if [[ ! -f wordlist2.txt ]] ; then
   echo "Cannot find file wordlist2.txt "
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

echo "/*----- Looking for Makefile -----*/:"
if [[ ! -f Makefile && ! -f makefile ]] ; then
   echo "Cannot find file Makefile"
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

score=$(echo "$score + 1" | bc)
echo "UPDATED SCORE=$score"

## Run make
echo "/*----- Running your Makefile -----*/:"
rm -f proj3C
make all

if [[ ! -f proj3C ]] ; then
   echo "Make FAILED: No proj3C executable"
   exit 1
fi

score=$(echo "$score + 1" | bc)
echo "UPDATED SCORE=$score"

## Look for testHash.c
echo "/*----- Looking for testHash.c -----*/:"
if [[ ! -f testHash.c ]] ; then
   echo "Cannot find file testHash.c "
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

## Run testHash as test
if [[ -f test ]] ; then
   rm test
fi

echo "/*----- Building testHash.c as test -----*/:"
gcc testHash.c proj3C_hashtable.c -o test

if [[ ! -f test ]] ; then
   echo "Unsuccessful bulid of testHash.c as test"
   echo "FAILED"
   echo "SCORE=$score"
   exit 1
fi

echo "/*----- Running test -----*/:"
output=$(./test > test_output.txt 2>&1)

echo "/*----- Checking for hash table memory allocation -----*/:"
if [[ $? -ne 0 ]]; then
    echo "Unit test output:"
    cat test_output.txt
    echo "Unit test FAILED: Failed to allocate hash table memory"
    echo "FAILED"
    echo "SCORE=$score"
    exit 1
fi

##if grep -q "ERROR" test_output.txt; then
##    echo "Unit test (testHash.c) failed, see file test_output.txt for run result"
##fi

echo "/*----- Checking initialize() -----*/:"
if grep -q "ERROR in initialize" test_output.txt; then
  echo "Error: ERROR in initialize"
    echo "FAILED"
    echo "SCORE=$score"
    exit 1
else
  score=$(echo "$score + 1" | bc)
    echo "UPDATED SCORE=$score"
fi

echo "/*----- Checking hash() -----*/:"
if grep -q "ERROR in hash" test_output.txt; then
  echo "Error: ERROR in hash"
    echo "FAILED"
    echo "SCORE=$score"
    exit 1
else
  score=$(echo "$score + 1" | bc)
    echo "UPDATED SCORE=$score"
fi

echo "/*----- Checking insert() -----*/:"
if grep -q "ERROR in insert" test_output.txt; then
  echo "Error: ERROR in insert"
    echo "FAILED"
    echo "SCORE=$score"
    exit 1
else
  score=$(echo "$score + 1" | bc)
    echo "UPDATED SCORE=$score"
fi

echo "/*----- Checking get() -----*/:"
if grep -q "ERROR in get" test_output.txt; then
  echo "Error: ERROR in get"
    echo "FAILED"
    echo "SCORE=$score"
    exit 1
else
  score=$(echo "$score + 1" | bc)
    echo "UPDATED SCORE=$score"
fi

echo "/*----- Checking calculateLoadFactor() -----*/:"
if grep -q "ERROR in loadFactor" test_output.txt; then
  echo "Error: ERROR in calculateLoadFactor"
    echo "FAILED"
    echo "SCORE=$score"
    exit 1
else
  score=$(echo "$score + 1" | bc)
    echo "UPDATED SCORE=$score"
fi

rm test

echo "/*----- Interactively testing proj3C -----*/:"
output=$(./proj3C << EOF
f
wordlist2.txt
dfa
blue
tangerine
3

EOF
)

IFS=$'\n' read -d '' -r -a output_lines <<< "$output"

expected_lines=(
    "Enter the filename (or leave blank to quit): Failed to open file 'f'. Please try again."
  "Enter the filename (or leave blank to quit): Tokenizing file 'wordlist2.txt' and building hash bucket...done."
  "Load factor: x.xx"
  "Number of unique words: xxx"
  "Maximum number of nodes in a slot: xx"
  "Enter a word to search (or leave blank to quit): Word 'dfa' not found."
  "Enter a word to search (or leave blank to quit): Word 'blue' found at line number(s): 2 64 84 "
  "Enter a word to search (or leave blank to quit): Word 'tangerine' found at line number(s): 39 "
  "Enter a word to search (or leave blank to quit): Word '3' not found."
  "Enter a word to search (or leave blank to quit): "
)


hehe=1

echo "/*----- Validating output -----*/:"
echo "/*----- Validating wordlist2.txt load and search -----*/:"
for i in "${!expected_lines[@]}"; do

  ## echo "|${expected_lines[$i]}|" | od -c
  ## echo "|${expected_lines[$i]}|"

  # Check the load factor line with a pattern
  if [[ "${expected_lines[$i]}" == Load\ factor:* ]]; then
    if [[ ! "${output_lines[$i]}" =~ ^Load\ factor:\ [0-9]+\.[0-9]+$ ]]; then
      echo "ERROR unexpected output: Test failed at line $((i+1))"
      echo "Expected pattern: 'Load factor: <numeric>'"
      echo "Got: ${output_lines[$i]}"
      hehe=0
      exit 1
    fi
  ## Check the unique words line with a pattern
  elif [[ "${expected_lines[$i]}" == Number\ of\ unique\ words:* ]]; then
    if [[ ! "${output_lines[$i]}" =~ ^Number\ of\ unique\ words:\ [0-9]+$ ]]; then
      echo "ERROR unexpected output: Test failed at line $((i+1))"
      echo "Expected pattern: 'Number of unique words: <numeric>'"
      echo "Got: ${output_lines[$i]}"
      hehe=0
      exit 1
    fi
  ## Check the max node count line with a pattern
  elif [[ "${expected_lines[$i]}" == Maximum\ number\ of\ nodes\ in\ a\ slot:* ]]; then
    if [[ ! "${output_lines[$i]}" =~ ^Maximum\ number\ of\ nodes\ in\ a\ slot:\ [0-9]+$ ]]; then
      echo "ERROR unexpected output: Test failed at line $((i+1))"
      echo "Expected pattern: 'Maximum number of nodes in a slot: <numeric>'"
      echo "Got: ${output_lines[$i]}"
      hehe=0
      exit 1
    fi
  # Compare other lines strictly
  elif [[ "${output_lines[$i]}" != "${expected_lines[$i]}" ]]; then
    echo "ERROR unexpected output: Test failed at line $((i+1))"
    echo "Expected: ${expected_lines[$i]}"
    echo "Got: ${output_lines[$i]}"
    hehe=0
    exit 1 ## Remove
  fi
done

if [[ $hehe -eq 1 ]]; then
    score=$(echo "$score + 0.5" | bc)
fi


echo "UPDATED SCORE=$score"

output=$(./proj3C << EOF
wordlist2.txt
Red
Blue
Green
Yellow
Orange
Purple
Pink
Brown
Black
White
Gray
Silver
Gold
Magenta
Cyan
Turquoise
Navy
Maroon
Indigo
Olive
Teal
Coral
Plum
Beige
Ivory
Mauve
Ruby
Emerald
Sapphire
Lilac
Turmeric
Rust
Fuchsia
Aqua
Peach
Mint
Rose
Bronze
Tangerine
Jade
Orchid
Slate
Mustard
Sand
Pewter
Apricot
Raspberry
Violet
Champagne
Marigold
Coral
Mocha
Pearl
Denim
Cinnamon
Paprika
Pumpkin
Celadon
Honeydew
Chartreuse
Cappuccino
Ginger
Red
Blue
Green
Yellow
Orange
Purple
Pink
Brown
Black
White
Gray
Silver
Gold
Magenta
Cyan
Turquoise
Honeydew
Chartreuse
Cappuccino
Ginger
Red
Blue
Green
Yellow
Orange
Purple
Pink
Cyan
Turquoise
Navy
Maroon
Indigo
Olive
Teal
Coral
Plum
Beige
Cyan

EOF
)


expected_out="Enter the filename (or leave blank to quit): Tokenizing file 'wordlist2.txt' and building hash bucket...done.
Load factor: x.xx
Number of unique words: xxx
Maximum number of nodes in a slot: xx
Enter a word to search (or leave blank to quit): Word 'red' found at line number(s): 1 63 83 
Enter a word to search (or leave blank to quit): Word 'blue' found at line number(s): 2 64 84 
Enter a word to search (or leave blank to quit): Word 'green' found at line number(s): 3 65 85 
Enter a word to search (or leave blank to quit): Word 'yellow' found at line number(s): 4 66 86 
Enter a word to search (or leave blank to quit): Word 'orange' found at line number(s): 5 67 87 
Enter a word to search (or leave blank to quit): Word 'purple' found at line number(s): 6 68 88 
Enter a word to search (or leave blank to quit): Word 'pink' found at line number(s): 7 69 89 
Enter a word to search (or leave blank to quit): Word 'brown' found at line number(s): 8 70 
Enter a word to search (or leave blank to quit): Word 'black' found at line number(s): 9 71 
Enter a word to search (or leave blank to quit): Word 'white' found at line number(s): 10 72 
Enter a word to search (or leave blank to quit): Word 'gray' found at line number(s): 11 73 
Enter a word to search (or leave blank to quit): Word 'silver' found at line number(s): 12 74 
Enter a word to search (or leave blank to quit): Word 'gold' found at line number(s): 13 75 
Enter a word to search (or leave blank to quit): Word 'magenta' found at line number(s): 14 76 
Enter a word to search (or leave blank to quit): Word 'cyan' found at line number(s): 15 77 90 100 
Enter a word to search (or leave blank to quit): Word 'turquoise' found at line number(s): 16 78 91 
Enter a word to search (or leave blank to quit): Word 'navy' found at line number(s): 17 92 
Enter a word to search (or leave blank to quit): Word 'maroon' found at line number(s): 18 93 
Enter a word to search (or leave blank to quit): Word 'indigo' found at line number(s): 19 94 
Enter a word to search (or leave blank to quit): Word 'olive' found at line number(s): 20 95 
Enter a word to search (or leave blank to quit): Word 'teal' found at line number(s): 21 96 
Enter a word to search (or leave blank to quit): Word 'coral' found at line number(s): 22 51 97 
Enter a word to search (or leave blank to quit): Word 'plum' found at line number(s): 23 98 
Enter a word to search (or leave blank to quit): Word 'beige' found at line number(s): 24 99 
Enter a word to search (or leave blank to quit): Word 'ivory' found at line number(s): 25 
Enter a word to search (or leave blank to quit): Word 'mauve' found at line number(s): 26 
Enter a word to search (or leave blank to quit): Word 'ruby' found at line number(s): 27 
Enter a word to search (or leave blank to quit): Word 'emerald' found at line number(s): 28 
Enter a word to search (or leave blank to quit): Word 'sapphire' found at line number(s): 29 
Enter a word to search (or leave blank to quit): Word 'lilac' found at line number(s): 30 
Enter a word to search (or leave blank to quit): Word 'turmeric' found at line number(s): 31 
Enter a word to search (or leave blank to quit): Word 'rust' found at line number(s): 32 
Enter a word to search (or leave blank to quit): Word 'fuchsia' found at line number(s): 33 
Enter a word to search (or leave blank to quit): Word 'aqua' found at line number(s): 34 
Enter a word to search (or leave blank to quit): Word 'peach' found at line number(s): 35 
Enter a word to search (or leave blank to quit): Word 'mint' found at line number(s): 36 
Enter a word to search (or leave blank to quit): Word 'rose' found at line number(s): 37 
Enter a word to search (or leave blank to quit): Word 'bronze' found at line number(s): 38 
Enter a word to search (or leave blank to quit): Word 'tangerine' found at line number(s): 39 
Enter a word to search (or leave blank to quit): Word 'jade' found at line number(s): 40 
Enter a word to search (or leave blank to quit): Word 'orchid' found at line number(s): 41 
Enter a word to search (or leave blank to quit): Word 'slate' found at line number(s): 42 
Enter a word to search (or leave blank to quit): Word 'mustard' found at line number(s): 43 
Enter a word to search (or leave blank to quit): Word 'sand' found at line number(s): 44 
Enter a word to search (or leave blank to quit): Word 'pewter' found at line number(s): 45 
Enter a word to search (or leave blank to quit): Word 'apricot' found at line number(s): 46 
Enter a word to search (or leave blank to quit): Word 'raspberry' found at line number(s): 47 
Enter a word to search (or leave blank to quit): Word 'violet' found at line number(s): 48 
Enter a word to search (or leave blank to quit): Word 'champagne' found at line number(s): 49 
Enter a word to search (or leave blank to quit): Word 'marigold' found at line number(s): 50 
Enter a word to search (or leave blank to quit): Word 'coral' found at line number(s): 22 51 97 
Enter a word to search (or leave blank to quit): Word 'mocha' found at line number(s): 52 
Enter a word to search (or leave blank to quit): Word 'pearl' found at line number(s): 53 
Enter a word to search (or leave blank to quit): Word 'denim' found at line number(s): 54 
Enter a word to search (or leave blank to quit): Word 'cinnamon' found at line number(s): 55 
Enter a word to search (or leave blank to quit): Word 'paprika' found at line number(s): 56 
Enter a word to search (or leave blank to quit): Word 'pumpkin' found at line number(s): 57 
Enter a word to search (or leave blank to quit): Word 'celadon' found at line number(s): 58 
Enter a word to search (or leave blank to quit): Word 'honeydew' found at line number(s): 59 79 
Enter a word to search (or leave blank to quit): Word 'chartreuse' found at line number(s): 60 80 
Enter a word to search (or leave blank to quit): Word 'cappuccino' found at line number(s): 61 81 
Enter a word to search (or leave blank to quit): Word 'ginger' found at line number(s): 62 82 
Enter a word to search (or leave blank to quit): Word 'red' found at line number(s): 1 63 83 
Enter a word to search (or leave blank to quit): Word 'blue' found at line number(s): 2 64 84 
Enter a word to search (or leave blank to quit): Word 'green' found at line number(s): 3 65 85 
Enter a word to search (or leave blank to quit): Word 'yellow' found at line number(s): 4 66 86 
Enter a word to search (or leave blank to quit): Word 'orange' found at line number(s): 5 67 87 
Enter a word to search (or leave blank to quit): Word 'purple' found at line number(s): 6 68 88 
Enter a word to search (or leave blank to quit): Word 'pink' found at line number(s): 7 69 89 
Enter a word to search (or leave blank to quit): Word 'brown' found at line number(s): 8 70 
Enter a word to search (or leave blank to quit): Word 'black' found at line number(s): 9 71 
Enter a word to search (or leave blank to quit): Word 'white' found at line number(s): 10 72 
Enter a word to search (or leave blank to quit): Word 'gray' found at line number(s): 11 73 
Enter a word to search (or leave blank to quit): Word 'silver' found at line number(s): 12 74 
Enter a word to search (or leave blank to quit): Word 'gold' found at line number(s): 13 75 
Enter a word to search (or leave blank to quit): Word 'magenta' found at line number(s): 14 76 
Enter a word to search (or leave blank to quit): Word 'cyan' found at line number(s): 15 77 90 100 
Enter a word to search (or leave blank to quit): Word 'turquoise' found at line number(s): 16 78 91 
Enter a word to search (or leave blank to quit): Word 'honeydew' found at line number(s): 59 79 
Enter a word to search (or leave blank to quit): Word 'chartreuse' found at line number(s): 60 80 
Enter a word to search (or leave blank to quit): Word 'cappuccino' found at line number(s): 61 81 
Enter a word to search (or leave blank to quit): Word 'ginger' found at line number(s): 62 82 
Enter a word to search (or leave blank to quit): Word 'red' found at line number(s): 1 63 83 
Enter a word to search (or leave blank to quit): Word 'blue' found at line number(s): 2 64 84 
Enter a word to search (or leave blank to quit): Word 'green' found at line number(s): 3 65 85 
Enter a word to search (or leave blank to quit): Word 'yellow' found at line number(s): 4 66 86 
Enter a word to search (or leave blank to quit): Word 'orange' found at line number(s): 5 67 87 
Enter a word to search (or leave blank to quit): Word 'purple' found at line number(s): 6 68 88 
Enter a word to search (or leave blank to quit): Word 'pink' found at line number(s): 7 69 89 
Enter a word to search (or leave blank to quit): Word 'cyan' found at line number(s): 15 77 90 100 
Enter a word to search (or leave blank to quit): Word 'turquoise' found at line number(s): 16 78 91 
Enter a word to search (or leave blank to quit): Word 'navy' found at line number(s): 17 92 
Enter a word to search (or leave blank to quit): Word 'maroon' found at line number(s): 18 93 
Enter a word to search (or leave blank to quit): Word 'indigo' found at line number(s): 19 94 
Enter a word to search (or leave blank to quit): Word 'olive' found at line number(s): 20 95 
Enter a word to search (or leave blank to quit): Word 'teal' found at line number(s): 21 96 
Enter a word to search (or leave blank to quit): Word 'coral' found at line number(s): 22 51 97 
Enter a word to search (or leave blank to quit): Word 'plum' found at line number(s): 23 98 
Enter a word to search (or leave blank to quit): Word 'beige' found at line number(s): 24 99 
Enter a word to search (or leave blank to quit): Word 'cyan' found at line number(s): 15 77 90 100 
Enter a word to search (or leave blank to quit): "


echo "$output" > tmp_output.txt
echo "$expected_out" > tmp_expected.txt


# Use diff to compare the two
diff_result=$(diff <(tail -n 50 tmp_output.txt) <(tail -n 50 tmp_expected.txt))

echo "/*----- Validating wordlist2.txt insertions with massive search -----*/:"
# Check if diff_result is empty
if [ -z "$diff_result" ]; then
  score=$(echo "$score + 1.5" | bc)
else
  echo "ERROR: mass inertion and get output does not match.
  Go look at the book or online to decipher the diff command. Differences are:"
  echo "$diff_result"
fi

echo "UPDATED SCORE=$score"

# Remove temporary files
rm tmp_output.txt tmp_expected.txt

output2=$(valgrind ./proj3C 2>&1 << EOF
f
wordlist2.txt
dfa
Red
Blue
Green
Yellow
Orange
Purple
Pink
Brown
Black
White
Gray
Silver
Gold
Magenta
Cyan
Turquoise
Navy
Maroon
Indigo
Olive
Teal
Coral
Plum
Beige
Ivory
Mauve
Ruby
Emerald
Sapphire
Lilac
Turmeric
Rust
Fuchsia
Aqua
Peach
Mint
Rose
Bronze
Tangerine
Jade
Orchid
Slate
Mustard
Sand
Pewter
Apricot
Raspberry
Violet
Beige
tangerine
Sapphire
Red
Blue
Green
Yellow
Orange
Purple
Pink
Brown
Black
White
Gray
Silver
Gold
Magenta
Cyan
Turquoise
Honeydew
Chartreuse
Cappuccino
Ginger
Red
Champagne
Marigold
Coral
Mocha
Pearl
Denim
Cinnamon
Paprika
Pumpkin
Celadon
Honeydew
Chartreuse
Cappuccino
Ginger
Red
Blue
Green
Yellow
Orange
Purple
Pink
Brown
Black
White
Gray
Silver
Gold
Magenta
Cyan
Turquoise
Honeydew
Chartreuse
Cappuccino
Ginger
Red
Blue
Green
Yellow
Orange
Purple
Pink
Cyan
Turquoise
Navy
Maroon
Indigo
Olive
Teal
Coral
Plum
Beige
Cyan
3

EOF
)

# Check if "no leaks are possible" is in output
if echo "$output2" | grep -q "no leaks are possible"; then
  score=$(echo "$score + 1" | bc)
else
  echo "ERROR Memory leaks detected."
fi



echo "UPDATED SCORE=$score"
echo "IF THIS SCRIPT DID NOT GIVE ANY ERRORS GOOD JOB YOU ARE DONE"