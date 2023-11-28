/*
 * ONOMATEPWNYMO: Spyros Barbakos 02937	
 * ONOMATEPWNYMO: Vasilis Kyritsis 02999
  *
*/
#include<stdio.h>
#include<math.h>

#include"hw1.h"
#define DSTRING printf("\n##\n");

int toNum(char letter){
	return(letter-64);
}
void range(double studentsInfo[][4]){ //g
    int low, high, counter=0,i;  
    do{
        printf("\nEnter grade range: ");
        scanf(" %d-%d",&low,&high);
		}while(low>=high || low<0||low>10|| high<0||high>10);

    for(i=0;i<NUM_STUDENTS;i++){
        if(high==10){
          if(studentsInfo[i][3]>=low && studentsInfo[i][3]<=high){
            counter++;
            }
        }else{
            if(studentsInfo[i][3]>=low && studentsInfo[i][3]<high){
            counter++;
            }
        } 
    }   
    printf("\n%d",counter);
    DSTRING
}
void printInfo(double studentsInfo[][4]){ //i
	  int low, high,i;	
		do{
            printf("\nEnter index range: ");
            scanf(" %d-%d",&low,&high);
		}while(low>=high || low<0||low>NUM_STUDENTS-1|| high<0||high>NUM_STUDENTS-1);

		for(i=low;i<high+1;i++){
			printf("\n%03d:%4.0lf,%4.0lf,%4.0lf,%6.2lf",i,studentsInfo[i][0],studentsInfo[i][1],studentsInfo[i][2],studentsInfo[i][3]);
		}
	DSTRING
}

void histogram(int studentsDivision[]){
    int i,j,x,init; //to x ekfrazei tis monades h tis dekades
    char k=')';
    if(NUM_STUDENTS<100){
        x=1;
        init=0;
    }else{
        x=10;
        init=10;
    }
    for(i=0;i<10;i++){
        if(i==9){
            k=']';
        }
        printf("[%2d,%2d%c: ",i,i+1,k);
        for(j=init;j<studentsDivision[i];j=j+x){
            printf("*");
        }
        printf("\n");
    }
    DSTRING
}

int main (int argc, char *argv[]) {

    int choiceNum,i,j,corr,wrong,dash,isNotValid=0,studentsAnswers[NUM_STUDENTS][NUM_QUESTIONS], studentsDivision[10]={0};

    double grade,y,penalty,divergence,meanValue,studentsInfo[NUM_STUDENTS][4],sumOfGrades;
	char correctAnswers[NUM_QUESTIONS],placeHolder,menuChoice;

	do{
		printf("\nEnter number of choices (1-%d): ",toNum(MAX_CHOICE)-toNum(MIN_CHOICE)+1);
		scanf("%d",&choiceNum);
	}while(choiceNum<=0||choiceNum>toNum(MAX_CHOICE)-toNum(MIN_CHOICE)+1);

    printf("\nEnter answer key: ");
	for(i=0;i<NUM_QUESTIONS;i++){
        
		do{
			scanf(" %c",&placeHolder);
			if(isNotValid){
				printf("\nError. Enter value %c-%c: ",MIN_CHOICE,MIN_CHOICE+choiceNum-1);
			}
		}while((isNotValid=toNum(placeHolder)<toNum(MIN_CHOICE)||toNum(placeHolder)>toNum(MIN_CHOICE)+choiceNum-1));

		isNotValid=0; //make it default
		correctAnswers[i]=placeHolder;
	}

    printf("\nEnter wrong answer penalty: ");
	do{
		scanf(" %lf",&penalty);
		if(penalty>0){
			printf("\nError. Enter non-positive value: ");
		}
	}while(penalty>0);

	for(i=0;i<NUM_STUDENTS;i++){
		printf("\nEnter student choices: ");
		for(j=0;j<NUM_QUESTIONS;j++){
			do{
				if(isNotValid){
					printf("\nError. Enter valid choice: ");
				}
				scanf(" %c",&placeHolder);

			}while((isNotValid=(toNum(placeHolder)<toNum(MIN_CHOICE)||(toNum(placeHolder)>toNum(MIN_CHOICE)+choiceNum-1))&&placeHolder!='-'));
			studentsAnswers[i][j]=toNum(placeHolder);
		}
	}
	sumOfGrades=0;
	for(i=0;i<NUM_STUDENTS;i++){
        corr=0;
        wrong=0;
        dash=0;
        grade=0;
        for(j=0;j<NUM_QUESTIONS;j++){
            if(studentsAnswers[i][j]==toNum(correctAnswers[j])){
                corr++;
            }else if(studentsAnswers[i][j]== toNum('-')){
                dash++;
            }else{
                wrong++;
            }
        }
        grade=((corr+(wrong*penalty))*10)/NUM_QUESTIONS;
        studentsInfo[i][0]=corr;
        studentsInfo[i][1]=wrong;
        studentsInfo[i][2]=dash;

        if(grade>0){
            studentsInfo[i][3]=grade;
            sumOfGrades+=grade;
        }else{
            studentsInfo[i][3]=0;
        }
    }
    //calculate mean value
    meanValue=sumOfGrades/NUM_STUDENTS;
    //calculate divergence, to y einai mia vohthitikh metavlith
    y=0;
    for(i=0;i<NUM_STUDENTS;i++){
        y+=pow((studentsInfo[i][3]-meanValue),2);
    }
    divergence=sqrt(y/NUM_STUDENTS);

    for(i=0;i<NUM_STUDENTS;i++){
        studentsDivision[(int)floor(studentsInfo[i][3])]++;
        if(studentsInfo[i][3]==10){
            studentsDivision[9]++;
        }
    }

    while(1){
		printf("\n[M/m] Print mean\n[S/s] Print standard deviation\n[G/g] Print grade range\n[I/i] Print student info in range\n[H/h] Draw histogram\n[Q/q] Quit\n");
        scanf(" %c",&menuChoice);
        switch(menuChoice){
            case 'M':

            case 'm':
                printf("\n%.2lf",meanValue);
                DSTRING
                break;
            case 'q':

            case 'Q':
                return 0;
                break;
            case 's':

            case 'S':
                printf("\n%.2lf",divergence);
								DSTRING
                break;
            case 'G':

            case 'g':
                range(studentsInfo);
				break;
			case 'I':

			case 'i':
				printInfo(studentsInfo);
				break;
            case 'h':

            case'H':
                histogram(studentsDivision);
                break;
            default:
                printf("\nError. Invalid option.");
                break;
           }
    }
	return 0;
}
