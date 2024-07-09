# Movie recommendation system

The program which is to run is written in the 'main.c' file. Other files which need to be present to run the program are 'movgen.txt' , 'movuse.txt' , 'names.txt' , 'new.txt' , 'newUser.txt' , 'number.txt' , 'r.txt'.

To compile : gcc main.c
To run : ./a.out or ./a.exe

Program first asks user to enter 1, 2 or 3 based on what user wants (to add a movie , to get recommendations based on rating model or to get recommendations based on genre model respesctively).

If user chooses 1, first he has to give movie name, then its imdb rating, then its genre data and the movie will be added.

If user chooses 2, he has to first rate some movies on a scale of 0-10. Then he has to tell how many recommendations does he want and then he will get required number of recommendations.

If user chooses 3, he has to first rate some genres on a scale of 0-10. Then he has to tell how many recommendations does he want and then he will get required number of recommendations.

The program is user friendly, user will get to know himself what he needs to do.
