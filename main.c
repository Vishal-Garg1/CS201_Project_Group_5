#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// to store names of movies
typedef struct name{
    char a[60];
}name;

// computes mod of a function
float mod(float input){
    if(input<0){
        input=-input;
    }
    return input;
}

// function to add a movie 
void addMovie(int movie,int user){
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
        sum[i]=0;
        for(int j=0;j<21;j++){
            fscanf(fptr,"%f",&genCompare);
            genCompare=mod(genCompare-genre[j]);
            sum[i]+=genCompare;
        }
    }
    float minsum=100;
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
    int size=9002*sizeof(char);
    fseek(fptr,index*size,SEEK_SET);
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

void addUserInRatingModel(int movie,int user,int movies,float *rate){
    float genre[21];
    for(int j=0;j<21;j++){
        genre[j]=0;
    }
    int bin;
    FILE *fptr=fopen("genre10.txt","r");
    for(int i=0;i<movies;i++){
        for(int j=0;j<21;j++){
            fscanf(fptr,"%d",&bin);
            if(bin==1){
                genre[j]+=rate[i];
            }
        }
    }
    fclose(fptr);
    float maximum=0;
    for(int j=0;j<21;j++){
        if(maximum<genre[j])   maximum=genre[j];
    }
    for(int j=0;j<21;j++){
        genre[j]=(genre[j]*10)/maximum;
    }
    float sum[movie];
    float temp;
    fptr=fopen("movgen.txt","r");
    for(int i=0;i<movie;i++){
        sum[i]=0;
        for(int j=0;j<21;j++){
            fscanf(fptr,"%f",&temp);
            temp=genre[j]*temp;
            sum[i]+=temp;
        }
    }
    fclose(fptr);
    int max=0;
    for(int i=0;i<movie;i++){
        if(max<sum[i])   max=sum[i];
    }
    for(int i=0;i<movie;i++){
        sum[i]=(sum[i]*10)/max;
    }
    fptr=fopen("newUser.txt","a");
    for(int i=0;i<movie;i++){
        fprintf(fptr,"%f ",sum[i]);
    }
    fprintf(fptr,"\n");
    fclose(fptr);
    user++;
    fptr=fopen("number.txt","w");
    fprintf(fptr,"%d\n%d\n",movie,user);
    return;
}

void addUserInGenreModel(int movie,int user,float *genre){
    float sum[movie];
    float temp;
    FILE *fptr=fopen("movgen.txt","r");
    for(int i=0;i<movie;i++){
        sum[i]=0;
        for(int j=0;j<21;j++){
            fscanf(fptr,"%f",&temp);
            temp=genre[j]*temp;
            sum[i]+=temp;
        }
    }
    fclose(fptr);
    int max=0;
    for(int i=0;i<movie;i++){
        if(max<sum[i])   max=sum[i];
    }
    for(int i=0;i<movie;i++){
        sum[i]=(sum[i]*10)/max;
    }
    fptr=fopen("newUser.txt","a");
    for(int i=0;i<movie;i++){
        fprintf(fptr,"%f ",sum[i]);
    }
    fprintf(fptr,"\n");
    fclose(fptr);
    user++;
    fptr=fopen("number.txt","w");
    fprintf(fptr,"%d\n%d\n",movie,user);
    fclose(fptr);
    return;
}

// recommendations based on movie ratings given by user
void ratingModel(int movie,int user){  
    printf("Please rate these movies on a scale of 0-10 (write rating and press enter)\n");
    int movies=10;
    float givenRating[10]={8.1,8.4,8.2,8.1,8,8.1,8.2,8.2,8.2,7.8};  // imdb ratings of below movies
    float rate[10];   // to store ratings given by user
    printf("pk :");
    scanf("%f",&rate[0]);
    printf("dangal :");
    scanf("%f",&rate[1]);
    printf("Gangs of Wasseypur :");
    scanf("%f",&rate[2]);
    printf("barfi! :");
    scanf("%f",&rate[3]);
    printf("Bajrangi Bhaijaan :");
    scanf("%f",&rate[4]);
    printf("Zindagi Na Milegi Dobara :");
    scanf("%f",&rate[5]);
    printf("Drishyam :");
    scanf("%f",&rate[6]);
    printf("bhaag Milkha bhaag :");
    scanf("%f",&rate[7]);
    printf("oh my god :");
    scanf("%f",&rate[8]);
    printf("sanju :");
    scanf("%f",&rate[9]);
    addUserInRatingModel(movie,user,movies,rate);
    user=1000;
    for(int i=0;i<10;i++){
        rate[i]/=givenRating[i];   // normalising to compare
    }
    float matrix[movies][user];      //10 movies vs users data
    FILE *fptr=fopen("movuse.txt","r");  //file having 10 movies vs users data
    // storing data into matrix
    for(int i=0;i<movies;i++){
        for(int j=0;j<user;j++){
            fscanf(fptr,"%f",&matrix[i][j]);
        }
    }
    fclose(fptr);
    name movieList[movie];     // will contain names of all movies
    fptr=fopen("names.txt","r");  // file having names of all movies
    char ch='a';   // random character used later
    // storing names in movieList
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
    float compare[movies][user];  //storing difference of users ratings from current user ratings
    float sum[user];    // to store sum of all differences of a particular user
    //storing sum of all differences of a particular user
    for(int i=0;i<user;i++){
        sum[i]=0;
        for(int j=0;j<movies;j++){
            compare[j][i]=mod(rate[j]-matrix[j][i]);
            sum[i]+=compare[j][i];
        }
    }
    float min=10;     // to store minimum of sum[i]
    int idx=0;        // to store index(i) of minimum of sum[i]
    // calculating min
    for(int i=0;i<user;i++){
        if(sum[i]<min){
            min=sum[i];
            idx=i;
        }
    }
    fptr=fopen("new.txt","r");       // opening normalised ratings file
    float highest[movie];       // stores the ratings of highest matching user
    int size=9*sizeof(char);   // size for a value in file new.txt
    fseek(fptr,size*idx,SEEK_CUR);     // skipping bits to get to idx
    int newSize=(user-1)*size+2;   // size to skip for going to next value of idx
    // scanning idx user's ratings and storing in highest[i]
    for(int i=0;i<movie-1;i++){
        fscanf(fptr,"%f",&highest[i]);
        fseek(fptr,newSize,SEEK_CUR);
    }
    fscanf(fptr,"%f",&highest[movie-1]);
    fclose(fptr);
    float max;    // maximum of highest[i]
    int numberOfRecommendations;
    int top[numberOfRecommendations];  // to store maximum values of highest[i]
    printf("How many movies do you want to be recommended (choose between 1 and %d) :",movie);
    scanf("%d",&numberOfRecommendations);
    // getting maximum values of highest[i]
    for(int j=0;j<numberOfRecommendations;j++){
        max=0;  // initialising max to 0
        for(int i=0;i<movie;i++){
            if(max<highest[i]){
                max=highest[i];
                top[j]=i;
            }
        }
        highest[top[j]]=0;
    }
    printf("top %d recommended movies are : \n",numberOfRecommendations);
    // printing the names of top recommended movies
    for(int i=0;i<numberOfRecommendations;i++){
        int j=0;
        ch='a';
        printf("%d. ",i+1);
        while(ch!='\n'){
            ch=movieList[top[i]].a[j];
            printf("%c",ch);
            j++;
        }
    }
    printf("NOTE : This list is in decreasing order of recommendations");
    return;
}

// recommendations based on genre ratings given by user
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
    addUserInGenreModel(movie,user,genre);
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
    //
    int choice;
    printf("1. If you want to add a movie enter 1.\n");
    printf("2. If you want to get recommendations by rating 10 movies enter 2.\n");
    printf("3. If you want to get recommendations by rating genres enter 3.\n");
    scanf("%d",&choice);
    char charac;
    switch(choice){
        case 1:   
            scanf("%c",&charac);
            addMovie(movie,user);       //for adding new movie
            break;
        case 2:   
            ratingModel(movie,user);    //for rating model of getting rcommendations
            break;
        case 3:   
            genreModel(movie,user);       //for genre model of getting rcommendations
            break;
        default:  printf("wrong input\n");
    }
    return 0;
}