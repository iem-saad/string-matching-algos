# string-matching-algos

Hi, So i was given a task in an assignment to make a GUI app using windows form C++ which searches string from given data files(attached in repo research.txt files). I completed this task and made a minimilistic UI. I've Implemented  following string matching algorithms.

* Brute Force Algorithm
* Rabin Karp Algorithm
* KMP Algorithm

I've implmeneted each and every algorithm in a simpler way. You can have a look at code for educational purposes but not with the intensions of plagiarism. `MyForm.h`
contains all the logic and implementation of the string matching algorithms. Also i am writing the complete question below which was asked in assignment for learning purpose.

If You find any bug or you have any question you can mail me at iem.saad@hotmail.com, i will be happy to help you ♥️


# question

Menu base GUI Application is the requirement. Implement Brute Force, RK and
KMP algorithm for String Matching. Details are:
Create a word search program. Where user can search a specific word or sequence of words from
the given list of files (Attached). It should work as (GUI Application)

Functionalities
* Program must find the position of search word or sequence of words from given files and
return name of file, row number and column number.

* Match whole word only [Unchecked]<br/>
  a. Program should return Pakistan, adampak, abnopakis, and pak against ‘pak’
  searched word because ‘pak’ is present in all of them. The length of return word
  and search word may differ.
* Match whole word only [Checked]<br/>
  a. Program should return only pak against ‘pak’ searched word. The length of return
  word and search word should be same.
* Match case [Unchecked]<br/>
  a. Program should return Bilal, bilaL, bIlaL against ‘bilal’. The upper and lower case
  should not be checked
* Match case [Checked]<br/>
  a. Program should only return bilal against bilal and BilaL against BilaL. The upper
  and lower case should be checked against each character.

# some running snapshots ⏬
![brute-force](https://user-images.githubusercontent.com/54322326/129972575-f750a631-6a97-41a7-a601-d894afb62e58.JPG)
![kmp](https://user-images.githubusercontent.com/54322326/129972582-f5d4af35-b391-49af-a984-6c67ae56fd64.JPG)
![rabin-karp](https://user-images.githubusercontent.com/54322326/129972587-51045534-e7e5-42b5-b677-d012e54bee37.JPG)
