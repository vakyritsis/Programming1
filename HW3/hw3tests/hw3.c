/* 
 * ONOMATEPWNYMO 1: Vasilhs Kyritsis
 * ONOMATEPWNYMO 2: Axilleas Galanis
 */
#include<stdio.h>
#include"hw3.h"
#include<stdlib.h>
#include<string.h>

struct subject{
    int course_number;
    char professor_name[MAX_NAME_LEN];
    int students_number;
};
struct class{
    int capacity;
    struct subject *pointers_array[WORKING_HOURS][WORKING_DAYS];
};

int check_teacher(struct class class_array[],struct subject * sbj,int day,int hour,int duration) {
    int i,j;
    
    for(i=0; i < MAX_ROOMS; i++){
        for(j=0; j < duration; j++){
            if(class_array[i].pointers_array[hour+j][day] == NULL){
                continue;
            }
            if(strcmp(class_array[i].pointers_array[hour+j][day]->professor_name,sbj->professor_name) != 0) {
            }
            else{
                return 0;
            }
        }
    }
    return 1;
}
        
void initializing(struct subject subject_array[], struct class class_array[]){//synarthsh pou arxikopoiei ta periexomena twn dyo pinakwn pou dhlwthikan sthn arxh ths main me 0-NULL
    int i,j,k;
    for(i=0;i<MAX_COURSES;i++){
        subject_array[i].course_number=0;
        for (j=0;j<MAX_NAME_LEN;j++) {
            subject_array[i].professor_name[j]='\0';
        }
        subject_array[i].students_number=0;
    }
    for(i=0;i<MAX_ROOMS;i++){
        class_array[i].capacity=0;
        for(j=0;j<WORKING_HOURS;j++){
            for(k=0;k<WORKING_DAYS;k++){
                class_array[i].pointers_array[j][k]=NULL;
            }
        }
    }
}

struct subject *search_lesson(struct subject subject_array[], int given_number){
    int i,found_lesson=0,full_matrix=0;
    for(i=0;i<MAX_COURSES;i++){
        if(subject_array[i].course_number==given_number){
            found_lesson=1;
            return(&subject_array[i]);
            break;
        }
    }
    if(found_lesson==0){
        for(i=0;i<MAX_COURSES;i++){
            if(subject_array[i].course_number==0){
                full_matrix=1;
                return(&subject_array[i]);
                break;
            }
        }
    }
    if(full_matrix==0){
        return(NULL);
    }
    return(0);
}

int add_lesson(struct subject subject_array[],int course_number,int students_number,char professor_name[]){
    struct subject *ptr=search_lesson(subject_array,course_number);
    
    if(ptr==NULL){
        return(-1);
    }
    else if((*ptr).course_number!=0){
        return(0);
    }
    else if((*ptr).course_number==0){
        (*ptr).course_number=course_number;
        (*ptr).students_number=students_number;
        strcpy((*ptr).professor_name,professor_name);
        return(1);
    }
    return(0);
}

void print_subject(struct subject subject_array[MAX_COURSES]){
    int i;
    for(i=0;i<MAX_COURSES;i++){
        if(subject_array[i].course_number!=0){
        printf("[%d] %s %d\n", subject_array[i].course_number, subject_array[i].professor_name, subject_array[i].students_number); 
        }
    }
}
    
int prg_lesson(struct class class_array[], struct subject *ptr, int duration){
    int i,j,k,m,n,done=0,vacant = 0;
    
    if(ptr==NULL){
        return -1;
    }
    for(i=0; i < MAX_ROOMS;i++) {
        if(ptr->students_number <= class_array[i].capacity){
            for(j=0; j <= WORKING_HOURS-duration; j++) {
                for(k=0; k < WORKING_DAYS; k++){ 
                    if(class_array[i].pointers_array[j][k] == NULL){
                        vacant = 0;
                        for(m=0; m < duration; m++) {
                            if(class_array[i].pointers_array[j+m][k] == NULL){
                                vacant++;
                            }
                        }
                        if(vacant == duration) {
                            done = check_teacher(class_array,ptr,k,j,duration);
                            if(done == 1) {
                                for(n = 0; n < duration; n++) {
                                    class_array[i].pointers_array[j+n][k] = ptr;
                                }
                                return(i);
                            }
                        }
                    }
                }
            }
        }
    }
    return (-1);
}
    
void class_schedule (struct class ptr){
    int i,j,a=4*WORKING_DAYS,DD=10;
    char days[]={"MON TUE WED THU FRI "}; 
    
    strcpy(days+a-1,"\0");
    printf("\nCapacity: %d\n", ptr.capacity);
    printf("       %s\n\n", days);
    for(i=0;i<WORKING_HOURS;i++){
        printf("%d:00  ",DD);
        DD++;
        for(j=0;j<WORKING_DAYS;j++){
            if(ptr.pointers_array[i][j]==NULL){
                printf(" -  ");
            }
            else{
                printf("%-4d", ptr.pointers_array[i][j]->course_number);
            }
        }
        printf("\n");
    }
}

void schedule (struct class class_array[]){
    int i;
    for(i=0;i<MAX_ROOMS;i++){
        if(class_array[i].capacity!=0){
        class_schedule(class_array[i]);
        }
    }
}

int delete_subject (struct subject subject_array[], int given_number, struct class class_array[]){
    int i,j,k,l,a;
    for(i=0;i<MAX_COURSES;i++){
        if(subject_array[i].course_number==given_number){
            for(j=0;j<MAX_ROOMS;j++){
                for(k=0;k<WORKING_HOURS;k++){
                    for(l=0;l<WORKING_DAYS;l++){
                        if(class_array[j].pointers_array[k][l]!=NULL){
                            if(class_array[j].pointers_array[k][l]->course_number==given_number){
                                class_array[j].pointers_array[k][l]=NULL;
                            }
                        }
                    }
                }
            }
            subject_array[i].course_number=0;
            for (a=0;a<MAX_NAME_LEN;a++) {
            subject_array[i].professor_name[a]='\0';
            }
            subject_array[i].students_number=0;
        return 1;
        }
    }
    return 0;
}
       
int main (int argc, char *argv[]) {
    struct subject subject_array[MAX_COURSES],*ptr;
    struct class class_array[MAX_ROOMS];
    int i,course_number,students_number,return_of_add_lesson,given_number,duration,done,a,d;
    char choice, professor_name[MAX_NAME_LEN];
    
    initializing(subject_array,class_array);
    if(argc>2){
        for(i=2;i<=argc;i++){
            if(atoi(argv[i-1])<0 || atoi(argv[i-1])>atoi(argv[i]) || argc-1<1){
                printf("Incorrect command-line arguments!\n");
                return 0;
            } else break;
        }
    }
    else if(argc==2){
            if(atoi(argv[1])<0  || argc-1>1){
                printf("Incorrect command-line arguments!\n");
                return 0;
            } 
    }
    for(i=1;i<argc;i++){
        class_array[i-1].capacity=atoi(argv[i]);
    }
    do{
        
        print_menu();
        scanf(" %c",&choice);
        switch (choice){
            case 'q':{return 0;
                break;
            }
            case 'a':{
                for (i=0;i<MAX_NAME_LEN;i++) {
                professor_name[i]='\0';
                }
                printf("professor course students: ");
                scanf("%s %d %d", professor_name,&course_number,&students_number);
                return_of_add_lesson=add_lesson(subject_array,course_number,students_number,professor_name);
                if(return_of_add_lesson==0){
                    printf("%d exists\n", course_number);
                }
                else  if(return_of_add_lesson==1){
                    printf("%d added\n", course_number);
                }
                else  if(return_of_add_lesson==-1){
                    printf("No space\n");
                }
                break;
            }
            case 'c' :{
                print_subject(subject_array);
                break;
                
            }
            case 's' :{
                ptr=NULL;
                done=0;
                a=0;
                printf("course duration: ");
                scanf("%d %d", &given_number,&duration);
                if(duration<1){//duration<5 always
                    printf("Invalid duration\n");
                }
                for(i=0;i<MAX_COURSES;i++){
                    if(subject_array[i].course_number==given_number){
                        done=1;
                        ptr=&subject_array[i];
                        break;
                    }
                    
                }
                if(done==0){
                    printf("%d not found\n", given_number);
                }////////
                    else{
                        a=prg_lesson(class_array,ptr,duration);//sf
                        if(a==-1){
                            printf("%d not scheduled\n",given_number);
                        }
                        else{
                           printf("%d scheduled in %d\n",given_number,a);
                        }
                    }
                    break;
                }
            case 'p' :{
                schedule(class_array);
                break;
            }
            case 'r' :{
                printf("course: ");
                scanf("%d", &given_number);
                d=delete_subject(subject_array,given_number,class_array);
                if(d==0){
                    printf("%d not deleted\n", given_number);
                }
                else{
                    printf("%d deleted\n", given_number);
                }
                break;
            }
        }
     }
    
    while(1);
    
    return 0;
}
