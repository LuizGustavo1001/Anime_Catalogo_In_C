# Anime_Catalogo_In_C
Anime Catalog in c++ using double linked list, that can: show an interval, find with a filter, write/ overwrite and remove animes.

➔User: Luiz Gustavo De Almeida Lopes
➔GitHub: github.com/LuizGustavo1001

About the Project

➔ C++ Project based on an Anime Catalog that comes from a
.csv file and will be stored in a Double Linked List with Name,
Number of Seasons, Number of Episodes, Release Year, Finish
Date*, Principal Genre and Status** with the possibility of:

1) Show an Interval or Print the entire Catalog in alphabetic
order of name or genre, latest releases order or without
filters.

2) Filter the Catalog by: Name, Number of Seasons, Number of
Episodes, Release or Finish Year, Genre and Status.

3) Write or Overwrite an anime with the option to save the
changes in the list and file***.

4) Remove an anime.
   
*If the anime isn’t finished yet, Finish Year = 0.
**Status can be “In Progress” or “Finished”.
***The inserted data correspond the state of the anime until the insert
day on the catalog.

Functions
➔ Quick Sort
Sort the catalog by Alphabetic order of Name or Gender and
Latest Releases.
Each one of the Quick sorts will have and assist partition to
help the process of sorting.
The datas from the list are transferred to an dynamic
allocated vector to assist the process of sorting by the desired filter.
Assist function of Quick Sort: “Troca”-> assist the partitions of
the vector.

➔ Menu
A simple function that shows to the user the options that he
owns to execute on the program, initially.

➔ MensagemErro
When the user digit an unavailable interval of options, this
function will be called to show the error to the user and
returns to the menu of the program.

➔ Main
Should capture the entries that the user digited and call
another function to execute what the user wants.

➔ Available Genres At the moment of the release:

1) Ação (Action)
2) Aventura (Adventure)
3) Comédia (Comedy)
4) Corrida (Race)
5) Drama (Drama)
6) Esporte (Sports)
7) Romance (Romance)
8) Slice of Life (Slice of Life)
9) Supernatural (Supernatural)
10)Terror (Terror)
   
Possible Future Changes:

➔Use multiple filters;
➔Sort the list directly from the list class, without using the
assist vector;
