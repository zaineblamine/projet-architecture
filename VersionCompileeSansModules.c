#include "sys/alt_stdio.h"
#include <stdio.h>
void sleep_ms(int milisec)
{
    int i;
    int k;
    for (i = 0; i < milisec; i++) {
        for (k = 0; k < 1000; k++) {
             __asm("nop");
        }
    }
}
int main(void)
{
	/* Decleration of hardware */
	volatile int*Bouton=(int*)0x9030;	//Adresse de la ligne des boutons
	int*Display=(int*)0x9020;	//Adresse du registre data
	int s=0,m=0;
	int lookup[]={64/*0*/,121/*1*/,36/*2*/,48/*3*/,25/*4*/,18/*5*/,3/*6*/,120/*7*/,0/*8*/,24/*9*/}; //Lookup table for seven segment
	int units,tens,unitm,tenm;
	int print0,print1,print2,print3,printfinal;
	int i=-1;//i paire demarrage, i impaire pause
	int pause=0;

    while(1)
    {
    //--------------------------initialisation-----------------------------------
        if(((*Bouton)&1)==0 ){
            print0=lookup[0];
            print1=lookup[0];
            print2=lookup[0];
            print3=lookup[0];

            print1=print1<<7;
            print2=print2<<14;
            print3=print3<<21;
            printfinal= (print3|print2|print1|print0);
            *(Display)=printfinal;
        }
    //--------------------------fin initialisation---------------------------------
        while((*Bouton&1)==1){
            while((*Bouton&2)==1){};
            i++;//bouton2 apuié
            while(s<60&&m<60&&(i%2==0)){
                sleep_ms(1000);
                s++;
                units = s%10;
                tens   = s/10;
                unitm = m%10;
                tenm   = m/10;
                print0=lookup[units];
                print1=lookup[tens];
                print2=lookup[unitm];
                print3=lookup[tenm];
                print1=print1<<7;
                print2=print2<<14;
                print3=print3<<21;
                printfinal= (print3|print2|print1|print0);
                *(Display)=printfinal;
                if(s==59) {
                    s=0;
                    m++;
                    if(m==59) {m=0;}
                }
                if((*Bouton&2)==0){i++;}//pause	=>sort de la boucle
                if((*Bouton&4)==0){
                    sleep_ms(100);
                    if(m<59){
                        m++;
                        units = s%10;
                        tens   = s/10;
                        unitm = m%10;
                        tenm   = m/10;
                        print0=lookup[units];
                        print1=lookup[tens];
                        print2=lookup[unitm];
                        print3=lookup[tenm];
                        print1=print1<<7;
                        print2=print2<<14;
                        print3=print3<<21;
                        printfinal= (print3|print2|print1|print0);
                        *(Display)=printfinal;
                    }
                    else{
						m=0;
						units = s%10;
						tens   = s/10;
						unitm = m%10;
						tenm   = m/10;
						print0=lookup[units];
						print1=lookup[tens];
					   	print2=lookup[unitm];
						print3=lookup[tenm];
                        print1=print1<<7;
						print2=print2<<14;
						print3=print3<<21;
						printfinal= (print3|print2|print1|print0);
                        *(Display)=printfinal;
                    }
                }
                if((*Bouton&8)==0){
               		sleep_ms(100);
                    if(m>0) {
                        m--;
                        units = s%10;
                        tens   = s/10;
                        unitm = m%10;
						tenm   = m/10;
                        print0=lookup[units];
                        print1=lookup[tens];
                        print2=lookup[unitm];
                        print3=lookup[tenm];
                        print1=print1<<7;
                        print2=print2<<14;
                        print3=print3<<21;
                        printfinal= (print3|print2|print1|print0);
                        *(Display)=printfinal;}
                    else {
                        m=0;
                        units = s%10;
                        tens   = s/10;
                        unitm = m%10;
                        tenm   = m/10;
                        print0=lookup[units];
                        print1=lookup[tens];
                        print2=lookup[unitm];
                        print3=lookup[tenm];
                        print1=print1<<7;
                        print2=print2<<14;
                        print3=print3<<21;
                        printfinal= (print3|print2|print1|print0);
                        *(Display)=printfinal;
                    }
                }
            }
        }//end while
    }
}
