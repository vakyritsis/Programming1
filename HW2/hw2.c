/*
 * ONOMATEPWNYMO 1: Σπύρος Μπαρμπάκος 02937
 * ONOMATEPWNYMO 2: Βασίλης Κυρίτσης 02999
 */
#include <stdio.h>
#include "hw2.h"
#include <ctype.h>
#include <string.h>
/**/
int main(int argc, char* argv[]) {
	init_stack_size();
	return hw2_main(argc, argv);
}

/**/
void histogram(char charArray[][MAX_WORD_LEN], int plithosLexewn[]){
	int i,j,lastWord,xiliades,ekatontades,dekades,monades,rest;
	for(i=0;i<MAX_WORDS;i++){
			if(plithosLexewn[i]==0){
				lastWord=i;
				break;
			}
	}
	printf("\n");
	for(i=0;i<lastWord;i++){
		xiliades=plithosLexewn[i]/1000;
		rest=plithosLexewn[i]%1000;
		ekatontades=rest/100;
		rest=rest%100;
		dekades=rest/10;
		rest=rest%10;
		monades=rest;

	printf("%24s: ",charArray[i]);
	for(j=0;j<xiliades;j++){
		printf("$");
	}
	for(j=0;j<ekatontades;j++){
		printf("#");
	}
	for(j=0;j<dekades;j++){
		printf("@");
	}
	for(j=0;j<monades;j++){
		printf("*");
	}
	printf("\n");
}
}
void calculateWordCounter(char *pointersArray[][MAX_WORDS], int plithosLexewn[]){
	int i,j,lastPointer=0;
	for(i=0;i<MAX_WORDS;i++){
		if(pointersArray[0][i]==NULL){
			lastPointer=i;
			break;
		}
	}
	if(lastPointer==0){
		lastPointer=MAX_WORDS;
	}
	for(j=0;j<lastPointer;j++){
		plithosLexewn[(int)((pointersArray[0][j]-pointersArray[0][0])/MAX_WORD_LEN)]++;
	}
}
void printText(char *pointersArray[][MAX_WORDS], int linelen){
	int hasSynonym=0,synonymLength=0,i,k,endReached=0,firstLetter=1,charCounter=0,wordCounter=0,punctationMark=0,wordLength=0;
	char placeholder[MAX_WORD_LEN];
	char synonym[MAX_WORD_LEN];
	printf("\n");
	printf("\n");
	while(endReached==0){
		wordLength=0;
		for(i=0;i<MAX_WORD_LEN;i++){
			placeholder[i]='\0';
		}
		for(i=0;i<MAX_WORD_LEN;i++){
			synonym[i]='\0';
		}
		if(pointersArray[0][wordCounter]==NULL){
			break;
		}
		for(i=0;i<MAX_WORD_LEN;i++){
			if((pointersArray[0][wordCounter])[i]==0){
				break;
			}
			placeholder[i]=(pointersArray[0][wordCounter])[i];
			wordLength++;
		}

		if(pointersArray[1][wordCounter]!=NULL){
			synonymLength=1;
			hasSynonym=1;
			synonym[0]='(';
			k=0;
			for(i=1;i<MAX_WORD_LEN;i++){
				synonym[i]=(pointersArray[1][wordCounter])[k];
				synonymLength++;
				if(synonym[i]==0){
					synonym[i]=')';
					synonymLength++;
					break;
				}
				k++;
			}
		}
		if(firstLetter==1){
			placeholder[0]=toupper(placeholder[0]);
			firstLetter=0;
			if(hasSynonym){
				synonym[1]=toupper(synonym[1]);
			}
		}
		if(punctationMark){
			placeholder[0]=toupper(placeholder[0]);
			if(hasSynonym){
				synonym[1]=toupper(synonym[1]);
			}
			punctationMark=0;
		}
		if(placeholder[0]=='.'||placeholder[0]=='!'||placeholder[0]=='?'){
			punctationMark=1;
		}
		if(hasSynonym){
			if((charCounter+wordLength+synonymLength)<=linelen){
				if(charCounter==0){
					printf("%s",placeholder);
				}else{
					printf(" %s",placeholder);
					charCounter++;
				}
				printf(" %s",synonym);
				wordCounter++;
				charCounter=charCounter+wordLength+synonymLength;
			}else if((charCounter+wordLength)<linelen&&(charCounter+wordLength+synonymLength)>=linelen){
				printf(" %s",placeholder);
				printf("\n");
				printf("%s",synonym);
				charCounter=synonymLength;
				wordCounter++;
			}else{
				printf("\n");
				printf("%s",placeholder);
				printf(" %s",synonym);
				charCounter=wordLength+synonymLength;
				wordCounter++;
			}
			hasSynonym=0;
		}else{
		if((charCounter+wordLength)<linelen){
			if(charCounter==0){
				printf("%s",placeholder);
			}else{
				printf(" %s",placeholder);
				charCounter++;
			}
			wordCounter++;
			charCounter=charCounter+wordLength;
		}else{
			printf("\n");
			printf("%s",placeholder);
			charCounter=wordLength;
			wordCounter++;
		}
	}
}
}
void initTheArrays(char charArray[][MAX_WORD_LEN], char *pointersArray[][MAX_WORDS]){
	char placeholder[MAX_WORD_LEN];
	int i,j,k,l,wordsCounter=0,pointersCounter,wordExists=0,returnOfScanf;
	for(i=0;i<MAX_WORD_LEN;i++){
		placeholder[i]=0;
	}
	for(i=0;i<MAX_WORDS;i++){
    wordExists=0;
		for(k=0;k<MAX_WORD_LEN;k++){
			placeholder[k]='\0';
		}
		returnOfScanf=scanf("%s",placeholder);
    if(returnOfScanf!=1){
			break;
		}

    for(k=0;k<MAX_WORD_LEN;k++){
			placeholder[k]=tolower(placeholder[k]);
		}
    for(j=0;j<wordsCounter;j++){
      if(strcmp(charArray[j],placeholder)==0){
        pointersArray[0][pointersCounter]=charArray[j];
        pointersCounter++;
        wordExists=1;
      }
    }

    if(wordExists==0){
      for(l=0;l<MAX_WORD_LEN;l++){
        charArray[wordsCounter][l]=placeholder[l];
      }
      pointersArray[0][pointersCounter]=charArray[wordsCounter];
      wordsCounter++;
      pointersCounter++;
    }
  }
}

void printSynonyms(char *pointersArray[][MAX_WORDS],char synonymList[][MAX_WORD_LEN*2]){
	int i,j,k,lastLetterOfFirstWord;
	char placeholder[MAX_WORD_LEN];

	for(i=0;i<MAX_SYNONYMS;i++){
		if(synonymList[i][0]==0){
			break;
		}
		for(j=0;j<MAX_WORD_LEN;j++){
			placeholder[j]='\0';
		}

		for(j=0;j<MAX_WORD_LEN*2;j++){
			if(synonymList[i][j]=='\0'){
				lastLetterOfFirstWord=j;
				break;
			}
		}
		for(j=0;j<lastLetterOfFirstWord;j++){
			placeholder[j]=synonymList[i][j];
		}
		for(k=0;k<MAX_WORDS;k++){
			if(pointersArray[0][k]==NULL){
				break;
			}
			if(strcmp(pointersArray[0][k],placeholder)==0){
				pointersArray[1][k]=&synonymList[i][lastLetterOfFirstWord+1];
				}
			}
		}
	}

int hw2_main(int argc, char* argv[]) {
	char synonyms[MAX_FILENAME_LEN];
	int i,j;
	int plithos[MAX_WORDS];
	char charArray[MAX_WORDS][MAX_WORD_LEN];
	char synonymList[MAX_SYNONYMS][MAX_WORD_LEN*2];
	char *pointersArray[2][MAX_WORDS];
	int options[3];
	for(i=0;i<3;i++){
		options[i]=0;
	}
	for(i=0;i<MAX_WORDS;i++){
		plithos[i]=0;
	}
	for(i=0;i<MAX_WORDS;i++){
		for(j=0;j<MAX_WORD_LEN;j++){
			charArray[i][j]=0;
		}
	}
	for(i=0;i<2;i++){
		for(j=0;j<MAX_WORDS;j++){
			pointersArray[i][j]=NULL;
		}
	}

	initTheArrays(charArray,pointersArray);
	calculateWordCounter(pointersArray,plithos);

	for(i=0;i<argc;i++){
		if(i!=0){
			if((strcmp(argv[i],"-h")!=0&&strcmp(argv[i],"-r")!=0&&strcmp(argv[i],"-p")!=0)){
				printf("Incorrect command-line arguments!\n");
				return 0;
			}
		}

		if(strcmp(argv[i],"-h")==0){
			options[0]=1;
		}

		if(strcmp(argv[i],"-r")==0){
			for(j=0;j<MAX_WORD_LEN;j++){
				synonyms[j]=argv[i+1][j];
			}
			i++;
			options[1]=1;
		}

		if(strcmp(argv[i],"-p")==0){
			options[2]=1;
		}
}

	if(options[0]==1){
		histogram(charArray,plithos);
	}
	if(options[1]==1){
		read_synonyms(synonyms,synonymList);
		printSynonyms(pointersArray,synonymList);
	}
	if(options[2]==1){
		printText(pointersArray,MAX_LINE_LEN);
	}
	printf("\n");
	return 0;
}
