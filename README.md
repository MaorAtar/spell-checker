# Hash Table and Spell Checker

## Overview
This project implements a **Hash Table** to demonstrate hashing efficiency and a simple **Spell Checker** to identify and suggest corrections for misspelled words.

## Features
- **Hashing Functions**:
  - Constant: Fixed value.
  - Accumulate: Sums ASCII values.
  - Improved: Polynomial hash function.

- **Hash Table**:
  - Collision handling with chaining.
  - Operations: Insert, Search, Delete.

- **Dictionary Loader**:
  - Loads `dictionary.txt` for efficient lookups.

- **Spell Checker**:
  - Checks word existence.
  - Suggests corrections using common strategies:
    - Splitting
    - Replacing
    - Removing
    - Inserting
    - Swapping letters

## Example
### Input:
soun

### Output:
Word not found. Did you mean:
- soon
- soul
- soup
