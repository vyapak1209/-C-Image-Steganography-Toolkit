
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define SSIZE 5000000
#include "strToBin.h"
#include "bingen.h"
#include "random.h"

int main()
{
	int n,i, size, string_length, message_len, key_len, choice; 
	int k=0; // binary string index
	int j=1; // binval scroller
	int buffer_size = 1024;
	int temp_string_length;
	unsigned int data_key = random_number(300, 2700000);
	unsigned int temp_data_key;
	char str[10000];
    char *binary_string;
	char *binval;
	char key[10];
	char binary_data_key[33];
	char binary_string_length[33];
	char sname[25];
	char tname[25];
	unsigned char buffer[buffer_size];	
	temp_data_key=data_key;
	
	for(i=31;i>=0;i--)
	{
		binary_data_key[i]=(temp_data_key%2)+48;
		temp_data_key=temp_data_key/2;
	}
	binary_data_key[32]='\0';
    	
    //FILE *fp1 = fopen("Black.bmp", "rb+"); // Importing image file using file handling.
    FILE *fp3 = fopen("original_data_bin.txt", "wb+"); // opening text file to save binary data of Original image.
    //FILE *fp4 = fopen("img_lsb_original.txt", "wb+"); // opening text file to save LSB data of Original file.
    //FILE *fp6 = fopen("img_lsb_mod.txt", "wb+"); // opening text file to save LSB data of Result file.
    FILE *image = fopen("result_image.bmp", "wb+");  // opening an empty image file of bmp format
    FILE *fp7 = fopen("result_image.txt", "wb+"); // opening text file to save binary data of Resultant image.
    //FILE *fp9 = fopen("readtext.txt", "r");
    
    printf("\t\t\t\t Image Steganography using LSB Substitution Technique\t\t\t\t\n");
    printf("Press 1 to Embed data.\n");
    scanf("%d", &choice);
    
    printf("Enter Image File Name: ");
    scanf("%s", &sname);
    FILE *fp1 = fopen(sname, "rb+");
    printf("Enter Text file to be embedded: ");
    scanf("%s", &tname);
    FILE *fp9 = fopen(tname, "r");
    
    printf("Enter Encryption Pin: ");
    scanf("%s", key);
    
    if(fp9 == NULL)
	{
    	perror("Error opening file");
    	return(-1);
	}
	
	if(!feof(fp9))
	{
		fgets(str, 1000, fp9);
		//printf("%s", str);
	}
    
	message_len = strlen(str);
	key_len = strlen(key);
	
	char* encrypted = malloc(message_len+1);
	
	for(i=0; i<message_len; i++){ 
			encrypted[i] = str[i]^key[i % key_len];
		}
	
	encrypted[message_len] = '\0';
    
	binary_string = stringToBinary(encrypted);
    
	printf("\n");
	string_length = strlen(binary_string);
	temp_string_length=string_length;
	//printf("No. of bits: %d \n", string_length);
	//printf("\n%s\n", binary_string);
	//printf("\ndata key is %d", data_key);
	
	for(i=31;i>=0;i--){
		binary_string_length[i]=(temp_string_length%2)+48;
		temp_string_length=temp_string_length/2;
	}
	binary_string_length[32]='\0';
	
    int f=0;
    while(!feof(fp1))
   {
      n  = fread(buffer, 1, buffer_size, fp1); // Computing no. of bytes in the image file
   for(i=0; i<n; i++)
{
	
	binval = toBinary(buffer[i]); // storing every byte in binval in binary form
	fprintf(fp3, "%s ", binval); // saving original binary data in text file
	//fputc(binval[7], fp4); // saving Original LSBs in text file.

//---------------------Manipulating LSBs of Pixel data--------------------------------------------//
	if(j>=200 && j<232){
		binval[7] = binary_data_key[j-200];
	}
	if(j>=232 && j<264){
		binval[7] = binary_string_length[j-232];
	}
	
	if((j>data_key) && (j<=(data_key+string_length)))
{
	binval[7] = binary_string[k];
	//fputc(binval[7], fp6);
	k++;	
}
	j++;
	fprintf(fp7, "%s ", binval);
	fputc(toChars(binval), image); // OutWriting the manipulated data back to an image.
	size++;
}
//-----------------------------------------------------------------------------------------------//

 
}
   printf("\nSize of the file = %d Kbs\n", size/1024);
   
	fclose(fp1);
    fclose(fp3);
    //fclose(fp4);
    //fclose(fp6);
    fclose(image);
 	fclose(fp7);
   
   return 0;
}


