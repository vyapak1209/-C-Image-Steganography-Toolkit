#define SSIZE 5000000
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "strToBin.h"
#include "bingen.h"
#include "random.h"
int main(){
	
	int n,i,x,k,y,g,z,j,l,flag,key_len, choice; 
		k=y=g=z=flag=0;
		j=l=1;
	int data_key = 0;
	int string_length=0;
	int buffer_size = 1024;
	char *binval;
	char key[10];
	char data[33];
	char fname[25];
	char bintostr[10000];
	unsigned char buffer[buffer_size];	
	
	printf("\t\t\t\tImage Steganography using LSB Substitution technique\t\t\t\t\n");
	printf("Press 1 to Extract data.\n");
	scanf("%d", &choice);

	printf("Enter Image file name: ");
	scanf("%s", &fname);
	
	FILE *fp8 = fopen(fname, "rb+");
	
	printf("Enter Encryption Pin: ");
	scanf("%s", &key);
	

	while(!feof(fp8))
   {
      n = fread(buffer, 1, buffer_size, fp8); 
   for(i=0; i<n; i++)
{
	
	binval = toBinary(buffer[i]); 
	if(l>=200 && l<232){
		data[l-200]=binval[7];
		z++;
			if(z==32){
			for(z=0; z<32; z++){
				data_key = data_key + ((data[z]-48)*pow(2,31-z));

			}
			z=0;
		//printf("Data Key : %d\n",data_key);
		}
			
	}
	

if(l>=232 && l<264){
		data[l-232]=binval[7];
		z++;
				if(z==32){
			for(z=0; z<32; z++){
				string_length = string_length + ((data[z]-48)*pow(2,31-z));

			}
			z=0;
		//printf("Data Key : %d\n",string_length);
		flag=1;
		}
	}
	

	if(flag==1){
			if((l>data_key) && (l<=(data_key+string_length)))
{
	//printf("%c", binval[7]);
	bintostr[g] = binval[7];
	g++;
}
	}

	
	l++;
}
//-----------------------------------------------------------------------------------------------//

} 	
	fclose(fp8);
	key_len = strlen(key);  
	printf("\n\nExtracted Data: ");
	char *output = malloc((sizeof(char) * (string_length/8) + 1));
	char *ex_str = malloc((sizeof(char)* (string_length/8)+1));
	y=0;
int sum;
	for(i=0;i<(string_length/8);i++){
			sum= (bintostr[i*8+7]-48)*1;
			sum= sum + ((bintostr[i*8+6]-48)*2);
			sum= sum + ((bintostr[i*8+5]-48)*4);
			sum= sum + ((bintostr[i*8+4]-48)*8);
			sum= sum + ((bintostr[i*8+3]-48)*16);
			sum= sum + ((bintostr[i*8+2]-48)*32);
			sum= sum + ((bintostr[i*8+1]-48)*64);
			sum= sum + ((bintostr[i*8+0]-48)*128);
			
	//printf("%c", sum);
	output[y] = sum;
	y++;
	}
	
	output[y] = '\0';
	
	for(x=0; x<string_length/8; x++){
		ex_str[x] = output[x] ^ key[x % key_len];
	}
	ex_str[x] = '\0';
	printf("\n%s", ex_str);
	FILE *fp1 = fopen("Extracted_text.txt", "w");
	fprintf(fp1, "%s", ex_str);
	
return 0;
}
