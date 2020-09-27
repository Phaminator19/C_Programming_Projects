#include <msp430g2553.h> //this is the microcontroller board from the TI Launchpad
#include <string.h>
#define numCols 10

unsigned int i;
char morse[][numCols]= {
  (".-"),("-..."),("-.-."),("-.."),("."),("..-."),("--."),("...."),(".."),(".---"),
  ("-.-"),(".-.."),("--"),("-."),("---"),(".--."),("--.-"),
  (".-."),("..."),("-"),("..-"),("...-"),(".--"),("-..-"),
  ("-.--"),("--.."),
  (".----"),("..---"),("...--"),("....-"),("....."),("-...."),
  ("--..."),("---.."),("----."),("-----")};

void dot();
void reset();
void dash();
void compareChars(char c1);
void ReadMorseAlphabet(char morseCode);
void morse_codes_sequence();
void wordSpace();


char str[] = "Go Knights";

void main(){
    WDTCTL = WDTPW + WDTHOLD;
            P1DIR |=0x41;
            P1OUT &= 0xBE;
    for (;;){
        morse_codes_sequence();
}
}


void compareChars(char c1){
int j;
if (c1 >= 'A'&& c1 <= 'Z')
  {
    c1 += 32;
  }
switch(c1){
case 'a':
    for (j = 0; j < numCols; j++){
        if (morse[0][j] != '\0'){
        ReadMorseAlphabet(morse[0][j]);
        }
        }
        break;
case 'b':
    for (j = 0; j < numCols; j++){
        if (morse[1][j] != '\0'){
            ReadMorseAlphabet(morse[1][j]);
        }
        }
        break;
case 'c':
    for (j = 0; j < numCols; j++){
        if (morse[2][j] != '\0'){
            ReadMorseAlphabet(morse[2][j]);
           }
           }
        break;
case 'd':
    for (j = 0; j < numCols; j++){
        if (morse[3][j] != '\0'){
            ReadMorseAlphabet(morse[3][j]);
           }
           }
        break;
case 'e':
    for (j = 0; j < numCols; j++){
        if (morse[4][j] != '\0'){
            ReadMorseAlphabet(morse[4][j]);
           }
           }
        break;
case 'f':
    for (j = 0; j < numCols; j++){
        if (morse[5][j] != '\0'){
            ReadMorseAlphabet(morse[5][j]);
           }
           }
        break;
case 'g':
    for (j = 0; j < numCols; j++){
        if (morse[6][j] != '\0'){
            ReadMorseAlphabet(morse[6][j]);
           }
           }
        break;
case 'h':
    for (j = 0; j < numCols; j++){
        if (morse[7][j] != '\0'){
        ReadMorseAlphabet(morse[7][j]);
           }
           }
        break;
case 'i':
    for (j = 0; j < numCols; j++){
    if (morse[8][j] != '\0'){
    ReadMorseAlphabet(morse[8][j]);
           }
           }
        break;
case 'j':
    for (j = 0; j < numCols; j++){
    if (morse[9][j] != '\0'){
    ReadMorseAlphabet(morse[9][j]);
           }
           }
        break;
case 'k':
    for (j = 0; j < numCols; j++){
    if (morse[10][j] != '\0'){
    ReadMorseAlphabet(morse[10][j]);
           }
           }
        break;
case 'l':
    for (j = 0; j < numCols; j++){
        if (morse[11][j] != '\0'){
        ReadMorseAlphabet(morse[11][j]);
               }
               }
            break;
case 'm':
    for (j = 0; j < numCols; j++){
        if (morse[12][j] != '\0'){
        ReadMorseAlphabet(morse[12][j]);
               }
               }
            break;
case 'n':
    for (j = 0; j < numCols; j++){
        if (morse[13][j] != '\0'){
        ReadMorseAlphabet(morse[13][j]);
               }
               }
            break;
case 'o':
    for (j = 0; j < numCols; j++){
        if (morse[14][j] != '\0'){
        ReadMorseAlphabet(morse[14][j]);
               }
               }
            break;
case 'p':
    for (j = 0; j < numCols; j++){
        if (morse[15][j] != '\0'){
        ReadMorseAlphabet(morse[15][j]);
               }
               }
            break;
case 'q':
    for (j = 0; j < numCols; j++){
        if (morse[16][j] != '\0'){
        ReadMorseAlphabet(morse[16][j]);
               }
               }
            break;
case 'r':
    for (j = 0; j < numCols; j++){
        if (morse[17][j] != '\0'){
        ReadMorseAlphabet(morse[17][j]);
               }
               }
            break;
case 's':
    for (j = 0; j < numCols; j++){
        if (morse[18][j] != '\0'){
        ReadMorseAlphabet(morse[18][j]);
               }
               }
            break;
case 't':
    for (j = 0; j < numCols; j++){
        if (morse[19][j] != '\0'){
        ReadMorseAlphabet(morse[19][j]);
               }
               }
            break;
case 'u':
    for (j = 0; j < numCols; j++){
        if (morse[20][j] != '\0'){
        ReadMorseAlphabet(morse[20][j]);
               }
               }
            break;
case 'v':
    for (j = 0; j < numCols; j++){
        if (morse[21][j] != '\0'){
        ReadMorseAlphabet(morse[21][j]);
               }
               }
            break;
case 'w':
    for (j = 0; j < numCols; j++){
        if (morse[22][j] != '\0'){
        ReadMorseAlphabet(morse[22][j]);
               }
               }
            break;
case 'x':
    for (j = 0; j < numCols; j++){
        if (morse[23][j] != '\0'){
        ReadMorseAlphabet(morse[23][j]);
               }
               }
            break;
case 'y':
    for (j = 0; j < numCols; j++){
        if (morse[24][j] != '\0'){
        ReadMorseAlphabet(morse[24][j]);
               }
               }
            break;
case 'z':
    for (j = 0; j < numCols; j++){
        if (morse[25][j] != '\0'){
        ReadMorseAlphabet(morse[25][j]);
               }
               }
            break;
case '1':
    for (j = 0; j < numCols; j++){
        if (morse[26][j] != '\0'){
        ReadMorseAlphabet(morse[26][j]);
               }
               }
            break;
case '2':
    for (j = 0; j < numCols; j++){
        if (morse[27][j] != '\0'){
        ReadMorseAlphabet(morse[27][j]);
               }
               }
            break;
case '3':
    for (j = 0; j < numCols; j++){
        if (morse[28][j] != '\0'){
        ReadMorseAlphabet(morse[28][j]);
               }
               }
            break;
case '4':
    for (j = 0; j < numCols; j++){
        if (morse[29][j] != '\0'){
        ReadMorseAlphabet(morse[29][j]);
               }
               }
            break;
case '5':
    for (j = 0; j < numCols; j++){
        if (morse[30][j] != '\0'){
        ReadMorseAlphabet(morse[30][j]);
               }
               }
            break;
case '6':
    for (j = 0; j < numCols; j++){
        if (morse[31][j] != '\0'){
        ReadMorseAlphabet(morse[31][j]);
               }
               }
            break;
case '7':
    for (j = 0; j < numCols; j++){
        if (morse[32][j] != '\0'){
        ReadMorseAlphabet(morse[32][j]);
               }
               }
            break;
case '8':
    for (j = 0; j < numCols; j++){
        if (morse[33][j] != '\0'){
        ReadMorseAlphabet(morse[33][j]);
               }
               }
            break;
case '9':
    for (j = 0; j < numCols; j++){
        if (morse[34][j] != '\0'){
        ReadMorseAlphabet(morse[34][j]);
               }
               }
            break;
case '0':
    for (j = 0; j < numCols; j++){
        if (morse[35][j] != '\0'){
        ReadMorseAlphabet(morse[35][j]);
               }
               }
            break;
case ' ':
   wordSpace();
   break;

default:
    break;
}}

void ReadMorseAlphabet(char morseCode){
    switch (morseCode){
    case '.':
        dot();
        break;
    case '-':
        dash();
        break;
    default:
        break;
}
}

void dot(){
    P1OUT ^= 0x40;
    for(i=1; i<= 20000; i++);
    P1OUT ^= 0x40;
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
}

void dash()
{
    P1OUT ^= 0x40;
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    P1OUT ^= 0x40;
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
}

void reset()
{
    P1OUT ^= 0x01;
    for(i=1; i<= 20000; i++);
    P1OUT ^= 0x01;
}

void morse_codes_sequence()
{
    int j;
    reset();
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    while (str[i] != '\0'){
    for (i =0; i < strlen(str); i++){
    compareChars(str[i]);
    for(i=1; i<= 60000; i++);
    i = j;
    j++;
    }
    }
}

void wordSpace()
{
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
    for(i=1; i<= 20000; i++);
}





