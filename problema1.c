/**
 *Oncioiu Anamaria Raluca, grupa 313CA
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct adr { unsigned int adresa; int masca; } ADR;


/*functia returneaza o adresa IP, sub forma unui intreg*/
unsigned int adr_int_lung(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
	unsigned int adresa;
	
	adresa = d*1 + c*(1<<8) + b*(1<<16) + a*(1<<24);
	
	return adresa;
}


/*functia intoarce octetii din reprezentarea unei adrese*/
void adr_to_ip(unsigned int n)
{
	unsigned int a, b, c, d;
	
	d = n % 256;
	n /= 256;
	
	c = n % 256;
	n /= 256;
	
	b = n % 256;
	n /= 256;
	
	a = n;
	
	printf("%u.%u.%u.%u", a, b, c, d);
}


/*se calculeaza masca unei adrese ip sub forma unui intreg lung*/
unsigned int construieste_masca(unsigned int n)
{
	unsigned int masca;

	masca = ((((unsigned)1<<31)-1)|((unsigned)1<<31)) - (((unsigned)1<<(32 - n))-1);
	
	return masca;
}


/*se verifica daca adresa IP este valida*/
ADR construieste_adresa(char *adresa)
{
	int i, j = 0, w[5], k = 0;
	char v[10];
	ADR ip;
		
	for(i = 0; i < strlen(adresa); i++)
		if(isalpha(adresa[i]))
		{
			fprintf(stderr, "Eroare. Textul ''%s'' nu este o adresa IP.", adresa);
			exit(1);
		}
		else
			{
				if(isdigit(adresa[i]))
					v[j++] = adresa[i];
				else
					if(((adresa[i] == '.' || adresa[i] == '/') && isdigit(adresa[i+1])) || adresa[i+1] == '\0')
				{
					v[j] = '\0';
					w[k++] = atoi(v);
					memset(v, sizeof(v), 0);
					j = 0;	
				}
				else
				{
					fprintf(stderr, "Eroare. Textul ''%s'' nu este o adresa IP.", adresa);
					exit(1);
				}
			}
	if(k != 5 || w[4] > 32)
	{
		fprintf(stderr, "Eroare. Textul ''%s'' nu este o adresa IP.", adresa);
		exit(1);
	}
	
	for(i = 0; i < 4; i++)
		if(w[i] > 255)
		{
			fprintf(stderr, "Eroare. Textul ''%s'' nu este o adresa IP.", adresa);
			exit(1);
		}
	
	ip.adresa = adr_int_lung(w[0], w[1], w[2], w[3]);
	ip.masca = w[4];
	
	adr_to_ip(ip.adresa);
	printf("/%d\n", ip.masca); 
	
	return ip;
}


/*se calculeaza adresa de retea din care face parte o adresa IP*/
ADR adresa_retea(ADR ip)
{
	ADR retea;
	
	retea.adresa = ip.adresa & construieste_masca(ip.masca);
	retea.masca = ip.masca;
	
	adr_to_ip(retea.adresa);
	printf("/%d\n", retea.masca); 
	
	return retea;
}


/*se calculeaza adresa de broadcast din care face parte o adresa IP*/
void adresa_broadcast(ADR retea)
{
	ADR bdcast;
	
	bdcast.adresa = retea.adresa | (((((unsigned)1<<31)-1)|((unsigned)1<<31)) - 
			(((((unsigned)1<<31)-1)|((unsigned)1<<31)) - (((unsigned)1<<(32 - retea.masca))-1)));
	bdcast.masca = retea.masca;
	
	adr_to_ip(bdcast.adresa);
	printf("/%d\n", bdcast.masca);
}


int main()
{
	
	char adresa[100];
	ADR ip, retea;
	
	fgets(adresa, 100, stdin);
	
	ip = construieste_adresa(adresa);
	
	retea = adresa_retea(ip);	
		
	adresa_broadcast(retea);
		
	return 0;
}
