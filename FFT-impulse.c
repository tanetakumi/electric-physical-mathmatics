//FFT for impulse response  
//2020.7.4  written by Norihiko Nishizawa
//


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int P, N, s;
double ar[2100000], ai[2100000], PI, br[2100000], bi[2100000];

void fft(int s);

void main(){

	FILE *expdata, *outdata;
	int i;
	double ac, phase;
	//初期設定	
	PI = 3.14159265358974;
	P = 14;
	N = pow(2, P);

	char filename[25] = "impulse-00.csv";

	if ((expdata = fopen(filename, "r")) == NULL){
		printf("出力ファイルがオープンできません。\n");
		exit(1);
	}

	for (i = 0; i <= 12500-1; i++){
		fscanf(expdata, "%Le", &ar[i]);
		ai[i] = 0;
		br[i] = ar[i]; bi[i] = ai[i];
		//ar[i] = pow(ar[i], 0.5);
	}

	fclose(expdata);

	
	for (i = 12500; i <= N; i++){

		ar[i] = 0; ai[i] = 0;

	}
	

	s = 0;

	fft(s);

	filename[9] = 99;

	if ((outdata = fopen(filename, "w")) == NULL){
		printf("出力ファイルがオープンできません。\n");
		exit(1);
	}

	for (i = 0; i <= N - 1; i++){

		ac = ar[i] * ar[i] + ai[i] * ai[i];

		ac = pow(ac, 0.5);

		phase = atan2(ai[i], ar[i]);

		fprintf(outdata,"%d,%lf,%lf,%lf,%lf,%lf\n",i,br[i],ar[i],ai[i],phase,ac);

	}
	fclose(outdata);



}

//フーリエ変換
void fft(int s)
{
	int nn1,nn2,l,i,j,q,l1,l2;
	double aw,aa,ab,ac,ad,a1,a2;
	nn1=N-1;
	nn2=N/2;
	l=nn2;
	for(j=1; j<=nn1-1; j++){
		if(j<l){
			aw=ar[l];ar[l]=ar[j];ar[j]=aw;
			aw=ai[l];ai[l]=ai[j];ai[j]=aw;
		}
		i=nn2;
		while(i<l+1){
			l=l-i;i=i/2;
		}
		l=l+i;
	}
	for(l=1; l<=P; l++){
		l1=pow(2,l);l2=l1/2;
		aa=1;ab=0;
		ac=cos(PI/l2);ad=-sin(PI/l2);
		if(s==1){
			ad=-ad;
		}

		for(i=0; i<=l2-1; i++){
			for(j=i; j<=nn1; j=j+l1){
				q=j+l2;
				a1=ar[q]*aa-ai[q]*ab;
				a2=ai[q]*aa+ar[q]*ab;
				ar[q]=ar[j]-a1;
				ai[q]=ai[j]-a2;
				ar[j]=ar[j]+a1;
				ai[j]=ai[j]+a2;
			}
			aw=aa*ac-ab*ad;ab=ab*ac+aa*ad;aa=aw;
		}
	}
}