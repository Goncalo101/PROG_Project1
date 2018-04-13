Changes:
-Function: -capitalize now uses the STL function called transform to put a string with chars in uppercase;
-Function: -checkWordInVector now uses the STL function count to check if the user inputted word is in the dictionary wordList;
-Deletion: -deleted one version of searchWithWildcard that used a vector and a string as arguments;
	       -deleted findWord - wordMatch now uses the STL function find;
