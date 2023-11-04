#include<stdio.h>
#include<stdlib.h>

// computes mod of a function
float mod(float input){
    if(input<0){
        input=-input;
    }
    return input;
}

// function to add a movie 
void addMovie(int movie,int  user){
    movie++;
    FILE *fptr=fopen("names.txt","a");  // opening the file having movie names
    char ch='a'; // a character used later
    float r;  // to store rating of new movie
    printf("To add a movie, you have to enter the movie name, its imdb rating and its genre list :\n");
    printf("Enter the movie name: ");
    // saving the movie name to names.txt
    do{
        scanf("%c",&ch);
        fprintf(fptr,"%c",ch);
    } while(ch!='\n');
    fclose(fptr);
    fptr=fopen("number.txt","w");
    fprintf(fptr,"%d\n%d\n",movie,user);
    fclose(fptr);
    printf("imdb rating :");
    scanf("%f",&r);
    fptr=fopen("r.txt","a");
    fprintf(fptr,"%f\n",r);
    fclose(fptr);
    char genreNames[200]="Action Adventure Animation Biography Comedy Crime Documentary Drama Family Fantasy History Horror Music Musical Mystery Romance Sci-Fi Short Sport Thriller War ";  //used to print genres one by one
    float genre[21];  // to make genre rating of the particular movie
    printf("enter 1 if movie has that genre otherwise 0 :\n");
    int j=0;
    int num=0;  // num counts number of genre
    // taking 0 or 1 against genre name
    for(int i=0;i<21;i++){
        ch='a';
        while(ch!=' '){
            ch=genreNames[j];
            printf("%c",ch);
            j++;
        }
        printf(":");
        scanf("%f",&genre[i]);
        if(genre[i]!=0)  num++;
        genre[i]*=r;  // multipying genre with rating
    }
    fptr=fopen("movgen.txt","a");    // opening movies vs genre file
    for(int i=0;i<21;i++){
        genre[i]/=num;     // dividing genre rating by number of genre
        fprintf(fptr,"%f ",genre[i]);
    }
    fprintf(fptr,"\n");   // storing genre vs movie ratings
    fclose(fptr);
    fptr=fopen("movgen.txt","r");  
    movie--;     // movie before this addition
    float sum[movie];   
    float genCompare;
    // computing sum of differences og genre for all movies
    for(int i=0;i<movie;i++){
        for(int j=0;j<21;j++){
            fscanf(fptr,"%f",&genCompare);
            genCompare=mod(genCompare-genre[j]);
            sum[i]+=genCompare;
        }
    }
    float minsum=0;
    int index=0;
    // computing minimum sum and movie having it
    for(int i=0;i<movie;i++){
        if(minsum>sum[i]){
            minsum=sum[i];
            index=i;
        }
    }
    fclose(fptr);
    float rating[1000];
    fptr=fopen("new.txt","r");
    int size=9001*sizeof(char);
    fseek(fptr,index*size-sizeof(char),SEEK_CUR);
    // storing rating of minimum sum movie
    for(int i=0;i<1000;i++){
        fscanf(fptr,"%f",&rating[i]);
    }
    fclose(fptr);
    // writing rating of new movie
    fptr=fopen("new.txt","a");
    for(int i=0;i<1000;i++){
        fprintf(fptr,"%f ",rating[i]);
    }
    fprintf(fptr,"\n");
    fclose(fptr);
    printf("Your movie is added successfully.\n");
    return;
}

int main(){
    int movie;   // number of movies
    int user;    // number of users
    FILE *fptr=fopen("number.txt","r");    // opening number.txt file
    fscanf(fptr,"%d",&movie);       // getting number of movies from file
    fscanf(fptr,"%d",&user);        // getting number of users from file
    fclose(fptr);
    addMovie(movie,user);
}