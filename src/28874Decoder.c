/*
   28874Decoder - A decoder for the NV item 00028874
   Original code Copyright (c) 2019 VVE
   Edits Copyright (c) 2019 Andrea Mennillo

   Licensed under the MIT license - See LICENSE for details.
*/

#include <stdio.h>
#include <fcntl.h>

void main(int argc, char* argv[]) {
  
FILE* in;
unsigned char buf[65536];
unsigned int band[6];
unsigned int bclass[6];
unsigned int ulclass[6];
unsigned int ant[6];
char ast;
unsigned int i,ifsiz,item8,item16,item32,fptr=0,descok=0,st,ulca,numcom=0,maxstr=0;

if (argv[1] == NULL) {
  printf("\nNo input filename specified\n");
  return;
}
in = fopen(argv[1],"rb");
if (in == NULL) {
  printf("\nCannot open file %s\n",argv[1]);
  return;
}
fseek(in,0,SEEK_END);
ifsiz=ftell(in);
fseek(in,0,SEEK_SET);
printf("Input file size: %d bytes\n",ifsiz);

fread(&item16,1,2,in);
item16&=0xffff;
fptr+=2;
printf ("Format verson: %d\n", item16);
fread(&item16,1,2,in);
item16&=0xffff;
fptr+=2;
printf ("Number of descriptors: %d\n", item16);
printf("\n");

while (fptr<ifsiz) {

	fread(&item16,1,2,in);
	item16&=0xffff;
	fptr+=2;
	if (item16 == 333) {
	for(i=0;i<6;i++) band[i]=0;
	for(i=0;i<6;i++) bclass[i]=0;
	for(i=0;i<6;i++) ulclass[i]=0;
	for(i=0;i<6;i++) ant[i]=0;
	descok=0;
	for (i=0;i<6;i++) {
		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		if (item16 != 0) {
			band[i]=item16;
			descok=1;
		}
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		bclass[i]=item8;
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		ant[i]=item8;
		fread(&item32,1,4,in);
		fptr+=4;
		fread(&item32,1,3,in);
		fptr+=3;
	}
	if (descok == 0) {
		printf("Incorrect format: no any downlink carrier in combo\n");
		goto emerexit;
	}
	continue;
	}	
	if (item16 == 334) {
		ulca=0;
		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		fread(&buf,1,8,in);
		fptr+=8;
		for(i=0;i<6;i++) ulclass[i]=0;
		for(i=0;i<6;i++) {
			if (item16 == band[i]) {
				if (bclass[i] >= 0) {
					ulclass[i]=item8;
					if (item8 > 2) ulca=1;
					break;
				}
			}
		}

		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		fread(&buf,1,8,in);
		fptr+=8;
		if (item16 != 0) {
		for(i=0;i<6;i++) {
			if (item16 == band[i]) {
				if (bclass[i] >= 0) {
					ulclass[i]=item8;
					ulca++;
					break;
				}
			}
		}
		}
		fread(&buf,1,44,in);
		fptr+=44;
		descok=1;
		st=0;
		for(i=0;i<6;i++) {
			if (band[i] == 0) {
				descok=0;
				continue;
			}
			if (i != 0) printf("-");
			if (ulca > 0) ast='*'; else ast=' ';
			printf("%d",band[i]);
			printf("%c",bclass[i]+0x40);
			if(ant[i]!=0)
			printf("%d",ant[i]);
			if (ulclass[i] != 0) printf("%c",ulclass[i]+0x40);
			st+=((bclass[i]==1)?1:(bclass[i]-1))*ant[i];
			if (st > maxstr) maxstr=st;
		}
		printf(" %d%c\n",st,ast);
		numcom++;
	continue;
	}
  if (item16 == 201) {
	for(i=0;i<6;i++) band[i]=0;
	for(i=0;i<6;i++) bclass[i]=0;
	for(i=0;i<6;i++) ulclass[i]=0;
	for(i=0;i<6;i++) ant[i]=0;
	descok=0;
	for (i=0;i<6;i++) {
		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		if (item16 != 0) {
			band[i]=item16;
			descok=1;
		}
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		bclass[i]=item8;
		fread(&item8,1,1,in);
        item8&=0xff;
		fptr++;
		ant[i]=item8;
	}
	if (descok == 0) {
		printf("Incorrect format: no any downlink carrier in combo\n");
		goto emerexit;
	}
		continue;
	}	
	if (item16 == 202) {
		ulca=0;
		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		fread(&buf,1,1,in);
		fptr++;
		for(i=0;i<6;i++) ulclass[i]=0;
		for(i=0;i<6;i++) {
			if (item16 == band[i]) {
				if (bclass[i] >= 0) {
					ulclass[i]=item8;
					if (item8 > 2) ulca=1;
					break;
				}
			}
		}

		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		fread(&buf,1,1,in);
		fptr++;
		if (item16 != 0) {
		for(i=0;i<6;i++) {
			if (item16 == band[i]) {
				if (bclass[i] >= 0) {
					ulclass[i]=item8;
					ulca++;
					break;
				}
			}
		}
		}
		fread(&buf,1,16,in);
		fptr+=16;
		descok=1;
		st=0;
		for(i=0;i<6;i++) {
			if (band[i] == 0) {
				descok=0;
				continue;
			}
			if (i != 0) printf("-");
			if (ulca > 0) ast='*'; else ast=' ';
			printf("%d",band[i]);
			printf("%c",bclass[i]+0x40);
			if(ant[i]!=0)
			printf("%d",ant[i]);
			if (ulclass[i] != 0) printf("%c",ulclass[i]+0x40);
			st+=((bclass[i]==1)?1:(bclass[i]-1))*ant[i];
			if (st > maxstr) maxstr=st;
		}
		printf(" %d%c\n",st,ast);
		numcom++;
	continue;
	}
	if (item16 == 137) {
	for(i=0;i<6;i++) band[i]=0;
	for(i=0;i<6;i++) bclass[i]=0;
	for(i=0;i<6;i++) ulclass[i]=0;
	for(i=0;i<6;i++) ant[i]=0;
	descok=0;
	for (i=0;i<6;i++) {
		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		if (item16 != 0) {
			band[i]=item16;
			ant[i]=2;
			descok=1;
		}
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		bclass[i]=item8;
	}
	if (descok == 0) {
		printf("Incorrect format: no any downlink carrier in combo\n");
		goto emerexit;
	}
		continue;
	}	
	if (item16 == 138) {
		ulca=0;
		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		for(i=0;i<6;i++) ulclass[i]=0;
		for(i=0;i<6;i++) {
			if (item16 == band[i]) {
				if (bclass[i] >= 0) {
					ulclass[i]=item8;
					if (item8 > 2) ulca=1;
					break;
				}
			}
		}

		fread(&item16,1,2,in);
		item16&=0xffff;
		fptr+=2;
		fread(&item8,1,1,in);
		item8&=0xff;
		fptr++;
		if (item16 != 0) {
		for(i=0;i<6;i++) {
			if (item16 == band[i]) {
				if (bclass[i] >= 0) {
					ulclass[i]=item8;
					ulca++;
					break;
				}
			}
		}
		}
		fread(&buf,1,12,in);
		fptr+=12;
		descok=1;
		st=0;
		for(i=0;i<6;i++) {
			if (band[i] == 0) {
				descok=0;
				continue;
			}
			if (i != 0) printf("-");
			if (ulca > 0) ast='*'; else ast=' ';
			printf("%d",band[i]);
			printf("%c",bclass[i]+0x40);
			if(ant[i]!=0)
			printf("%d",ant[i]);
			if (ulclass[i] != 0) printf("%c",ulclass[i]+0x40);
			st+=((bclass[i]==1)?1:(bclass[i]-1))*ant[i];
			if (st > maxstr) maxstr=st;
		}
		printf(" %d%c\n",st,ast);
		numcom++;
	continue;
	}  
	printf("Incorrect format: incorrect descriptor type %d (137, 138, 201, 202, 333 or 334 expected). File offset=%x.\n",item16,fptr-2);
}
printf("\n");
printf("Number of combos: %d\n",numcom);
printf("Max streams per combo: %d\n",maxstr);
emerexit:
fclose(in);
printf("\n");
}
