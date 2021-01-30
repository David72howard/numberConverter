//David Howard
//February 15, 2018
//CSCI 304 Section 2
/*This program takes a Octal, Hex, or Decimal value and computes all three
values in a accumulator. This program allows the user to set the mode
as well as clear the accumulator and quit the program.*/

#include <stdio.h>
#include <string.h>

short get_operand(char mode);

unsigned short get_binary_op(char *bin){ //convert binary in bin; return value
  //variables
  int power_of_two = 1;
  int result = 0;
  int i;
  int j = 0;

  for(i = strlen(bin) + 1; i > 0; i--){
      
    if(bin[strlen(bin) - j] == '1'){
        
      result += power_of_two;
    }
      
    power_of_two *= 2;
      
    j++;
      
  }

  return result / 2;
}
void convert_to_binary(short acc, char *bin){ //format acc in binary for output

  char arr[20] = "0000000000000000"; // <-
  unsigned short uacc;
  int remaine;
  int len = 0;
  int i;

  uacc = (unsigned short) acc;
  while((acc > 0) || (acc < 0)){
    remaine = acc % 2;
    if((remaine == 1) || (remaine == -1)){
      arr[len] = '1';
    }
    acc /= 2;
    len++;
  }

    for(i = 15; i >= 0; i--){
      bin[15 - i] = arr[i];          // <- not transfering to bin correctly
    }
 bin[16] = '\0';
}

void add(short *acc, char mode){ //add to accumulator; detect over/underflow

//variables
char and_bin;//[20];
short other;
short temporary;
  if((mode == 'B') || (mode == 'b')){
    other = get_operand(and_bin);
  }
  else{
    other = get_operand(mode);
    }
  temporary = *acc;
  *acc = *acc + other;
  if(other < 0 && *acc > 0 && temporary < 0){
    printf("\nPositive Overflow Error");
  }
  else if(other > 0 && *acc < 0 && temporary > 0){
    printf("\n Negative Overflow Error");
   }
  }

void subtract(short *acc, char mode){ //sub from accumulator; detect over/underflow

  //variables
  char and_bin;//[20];
  short other;
  short temporary;
    if((mode == 'B') || (mode == 'b')){
      other = get_operand(and_bin);
    }
    else{
      other = get_operand(mode);
      }
    temporary = *acc;
    *acc = *acc - other;
    if(other < 0 && *acc > 0 && temporary < 0){
      printf("\nPositive Overflow Error");
    }
    else if(other > 0 && *acc < 0 && temporary > 0){
      printf("\n Negative Overflow Error");
     }
}

short get_operand(char mode){ //read in value in mode; return value
//Variables
short acc;
char bin[20];
 switch(mode){
   case 'b' :
              printf("\nEnter binary value: ");
              scanf("%s", bin);
              printf("%s\n", bin);
              acc = get_binary_op(bin);
              break;
   case 'o' :
              printf("\nEnter octal value: ");
              scanf("%ho", &acc);
              printf("%ho\n", acc);
              // print_acc(acc);
              break;
   case 'h' :
              printf("\nEnter hex value: ");
              scanf("%hX", &acc);
              printf("%hX\n", acc);
              // print_acc(acc);
              break;
   case 'd' :
              printf("\nEnter decimal value: ");
              scanf("%hd", &acc);
              printf("%hd\n", acc);
              break;

 }

 return acc;

}

void print_acc(short acc){ // print out accumulator values//add short acc
  char bin[20];
  convert_to_binary(acc, bin);

  printf("\n********************************\n");
  printf  ("* Accumulator:                 *\n");
  printf  ("*   Binary : %s  *\n", bin);
  printf  ("*   Hex    : %04hX              *\n", acc );
  printf  ("*   Octal  : %06ho            *\n", acc );
  printf  ("*   Decimal: %-10hd        *\n", acc );
  printf  ("********************************\n");

}

char print_menu(){ // print menu and get option //  call appropriate function

  char option[10];
  char selection;

  printf("\nPlease select one of the following options: \n");

  printf("\nB Binary Mode            & AND with Accumulator        + Add to Accumulator");

  printf("\nO Octal Mode             | OR with Accumulator         - Subtract from Accumulator\n");

  printf("H Hexidecimal Mode       ^ XOR with Accumulator        N Negate Accumulator\n");

  printf("D Decimal Mode           ~Complement Accumulator\n\n");

  printf("C Clear Accumulator      < Shift Accumulator Left\n");

  printf("S Set Accumulator        > Shift Accumulator Right\n\n");

  printf("Q Quit \n");

  printf("\noption: ");

  scanf("%s", &option[0]);

  printf("%s\n", option);

  selection = option[0];

  if(strlen(option) > 1){

    selection = 'g';

  }

  return selection;
}

int main(){

  char mode = 'd';
  int quit = 0;
  short acc = 0;
  char selection;
  int first_value;
  int second_value;
  char bin[20];
  char and_bin[20];



  // print_acc(acc);

   while(!quit){

    print_acc(acc);
    selection = print_menu();

    switch(selection){

       case 'B' :
       case 'b' :
                  printf("Mode is Binary \n\n");
                  mode = 'b';
                  break;

       case 'O' :
       case 'o' :
                  printf("Mode is Octal \n\n");
                  mode = 'o';
                  break;

       case 'H' :
       case 'h' :
                  printf("Mode is Hexadecimal \n\n");
                  mode = 'h';
                  break;

       case 'D' :
       case 'd' :
                  printf("Mode is Decimal \n\n");
                  mode = 'd';
                  break;

       case '&' :
             first_value = acc;
             second_value = get_operand(mode);
             acc = first_value & second_value;

        break;

       case '|' :
            first_value = acc;
            second_value = get_operand(mode);
            acc = first_value | second_value;
        break;

       case '^' :
            first_value = acc;
            second_value = get_operand(mode);
            acc = first_value ^ second_value;
         break;

       case '~' :
                  acc = ~acc;
                  break;
       case '>' :
                  printf("Enter number of positions to right shift accumulator: ");
                  scanf("%d", &first_value);
                  acc = acc >> first_value;
                  break;
       case '<' :
                  printf("Enter number of positions to left shift accumulator: ");
                  scanf("%d", &first_value);
                  acc = acc << first_value;
                  break;

       case '-' :
                  subtract(&acc, mode);
                  break;
       case '+' :
                  add(&acc, mode);
                  break;
       case 'N' :
       case 'n' :
                  acc = -acc;
                  break;

       case 'C' :
       case 'c' :
                  acc = 0;
                  break;

       case 'S' :
       case 's' :
                  acc = get_operand(mode);
                  break;
       case 'Q' :
       case 'q' :
                  quit = 1;
                  break;
       default :
                  printf("Invalid option: %c\n", selection);
     }

  }

 return 0;
}
