#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//char raw_array[256] = "jnsnfankjd\nhndfgmsdf\n$GPGGA,134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,-16.27,M,08,AAAA*60\n,dfssfsfd,\n$fgsdfdjgfsfsd,\nWSSSjnsnfankjd\nhndfgmsdf\n$GPGGA,134658.00,5106.9792,N,11402.3003\n";

char raw_array[256] = "dgfddgddf\nasddas\njhsfdfh$GPGGA,101135.00,4051.23849,N,02917.39727,E,1,07,1.32,95.7,M,,42,218,37*7E\nasdads";


typedef struct gpgga
{	
	char section[120];
	
	char sentenceIdentifier[7];		//1
	float time;						//2
	double latitude;				//3
	char latitudeDir;				//4
	double longtitude;				//5
	char longtitudeDir;				//6
	char fix_quality;				//7
	int numberOfSatellites;			//8
	float horizontal_dilution;		//9
	double altitude;				//10
}GPGGA;

void gps_parser(char* rawData, int len, GPGGA *newO);				/// Asama asama goruntulemek icin yorumlarý kaldiriniz

int main()
{
	GPGGA DATALAR;
	
	gps_parser(raw_array, strlen(raw_array), &DATALAR);

	printf("--->>>>  Struct	\n\n");
	printf("Tur:			%s\n", DATALAR.sentenceIdentifier);
	printf("UTC time:		%.2f\n", DATALAR.time);
	printf("Latitude:		%.4lf\n", DATALAR.latitude);
	printf("LatitudeDir:		%c\n", DATALAR.latitudeDir);
	printf("Longitude:		%.4lf\n", DATALAR.longtitude);
	printf("LongitudeDir:		%c\n", DATALAR.longtitudeDir);
	printf("Fix Quality:		%c\n", DATALAR.fix_quality);
	printf("Number Of SAT:		%d\n", DATALAR.numberOfSatellites);
	printf("Horizontal Dil:		%.1f\n", DATALAR.horizontal_dilution);
	printf("Altitude:		%.2lf\n", DATALAR.altitude);

	return 0;
}
void gps_parser(char* rawData, int len, GPGGA *obje)				/// Asama asama goruntulemek icin yorumlarý kaldiriniz
{														/// Remove comments for show process step by step
	char key[7] = "$GPGGA";
//	printf("-->>>>>>>>>>> 	raw data\n\n");
//	printf("%s\n", rawData);
//	printf("-->>>>>>>>>>> 	key\n");
//	printf("--- %s\n\n\n\n", key);
	
	// anahtarý bulma
	char *p;
	p = strstr(rawData, key);
	
//	printf("--->>>> since the key is found\n");
//	printf("%s\n\n\n\n", p);

	int i=0;	
	while (p[i] != '\n' && i< 255)
	{
		obje->section[i] = p[i];
		i++;
	}
//	printf("--->>>>  section\n");
//	printf("%s\n\n\n\n", obje.section);
	

	char* token = strtok(obje->section, ",");
	strcpy(obje->sentenceIdentifier, token);
	
	token = strtok(NULL, ",");
	obje->time = (float)atof(token);
	
	token = strtok(NULL, ",");
	obje->latitude = (double)atof(token);
	
	token = strtok(NULL, ",");
	obje->latitudeDir = *token;
	
	token = strtok(NULL, ",");
	obje->longtitude = (double)atof(token);
	
	token = strtok(NULL, ",");
	obje->longtitudeDir = *token;
	
	token = strtok(NULL, ",");
	obje->fix_quality = *token;
	
	token = strtok(NULL, ",");
	obje->numberOfSatellites = (int)atoi(token);
	
	token = strtok(NULL, ",");
	obje->horizontal_dilution = (float)atoi(token);
	
	token = strtok(NULL, ",");
	obje->altitude = (double)atof(token);

}
