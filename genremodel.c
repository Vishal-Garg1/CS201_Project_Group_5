#include<stdio.h>
#include<stdlib.h>

// to store names of movies
typedef struct name{
    char a[60];
}name;

void genreModel(int movie,int user){
    char ch;  // random character
    char genreNames[200]="Action Adventure Animation Biography Comedy Crime Documentary Drama Family Fantasy History Horror Music Musical Mystery Romance Sci-Fi Short Sport Thriller War ";  // genre list
    float genre[21];  // to store genre ratings of user
    printf("Please rate the given genres on a scale of 0-10\n");
    int j=0;
    // printing genre names and taking ratings
    for(int i=0;i<21;i++){
        ch='a';
        while(ch!=' '){
            ch=genreNames[j];
            printf("%c",ch);
            j++;
        }
        printf(":");
        scanf("%f",&genre[i]);	
    }
    float contentBased[movie];     // stores comtent based ratings of all movies
    name movieList[movie];      // to store movie names  
    FILE *fptr=fopen("names.txt","r");  // opening file having names of all movies
    // storing movie names in movieList
    for(int i=0;i<movie;i++){
        int j=0;
        while(ch!='\n'){
            fscanf(fptr,"%c",&ch);
            movieList[i].a[j]=ch;
            j++;
        }
        ch='a';
    }
    fclose(fptr);
    fptr=fopen("movgen.txt","r");    // opening file having movies vs genre data for all movies
    // calculating content based ratings of given user for all movies
    for(int i=0;i<movie;i++){
        contentBased[i]=0;
        float points;
        for(int j=0;j<21;j++){
            fscanf(fptr,"%f",&points);
            contentBased[i]+=genre[j]*points;
        }
    }
    int numberOfRecommendations;  // number of movies to be recommended
    printf("How many movies do you want to be recommended (choose between 1 and %d) :",movie);
    scanf("%d",&numberOfRecommendations);
    int top[numberOfRecommendations];
    int max;   // to store max rating
    // finding top recommendations
    for(int j=0;j<numberOfRecommendations;j++){
        max=0;
        for(int i=0;i<movie;i++){
            if(max<contentBased[i]){
                max=contentBased[i];
                top[j]=i;
            }
        }
        contentBased[top[j]]=0;
    }
    // printing top recommendations
    printf("Top %d recommended movies are : \n",numberOfRecommendations);
    for(int i=0;i<numberOfRecommendations;i++){
        int j=0;
        ch='b';
        printf("%d. ",i+1);
        while(ch!='\n'){
            ch=movieList[top[i]].a[j];
            printf("%c",ch);
            j++;
        }
    }
    printf("NOTE : This list is in decreasing order of recommendations\n");
    return;
}

int main(){
    int movie;   // number of movies
    int user;    // number of users
    FILE *fptr=fopen("number.txt","r");    // opening number.txt file
    fscanf(fptr,"%d",&movie);       // getting number of movies from file
    fscanf(fptr,"%d",&user);        // getting number of users from file
    fclose(fptr);
    genreModel(movie,user); 
    return 0;
}