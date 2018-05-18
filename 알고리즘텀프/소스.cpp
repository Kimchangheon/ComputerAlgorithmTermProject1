#include <stdio.h>
#include "balance.h"
#include <string.h>

int main() {

	int a[2] = { 0 };//저울 A에올릴 배열
	int b[2] = { 0 };//저울 B에 올릴 배열
	int c[2] = { 0 };//C에올릴배열
	int d[101] = { 0 };//찾은 정상동전들을 저장할 배열
	int e[101] = { 0 };//찾은 불량동전들을 저장할 배열
	int f[101] = { 0 };//equal이 나온 동전의 인덱스를 저장하는 배열
	int f1[101] = { 0 };//equal이 나온 동전의 인덱스를 저장하는 배열2
	int f2[101] = { 0 };
	int f3[101] = { 0 };
	int result_a[101] = { 0 };
	int i = 0; //i는 최초생성된 코인이 들어가있는 배열의 인덱스
	int j = 0;//저울을이용해서 찾은 정상동전을 저장할 배열의 인덱스
	int k = 0;//저울을이용해서 찾은 불량동전을 저장할 배열의 인덱스
	int l = 0;//저울을이용해서 찾은 equal이 나온 동전의 인덱스를 저장할 배열의 인덱스
	int l1 = 0, l2 = 0, l3 = 0;
	int len = 0; // equal 배열의 크기를 알려주는 변수
	int temp;


	//불량동전을 초기화한다. 이때 불량동전의 발생 확률 = 10
	initialize(30);

	a[1] = -1; b[1] = -1; c[1] = -1; // 배열의 끝을 -1로 설정
	for (i = 1; i < 100; i += 3) { // 1차단계 33번 비교 후 e배열의 값을 a로 옮겨줌
		a[0] = i; b[0] = i + 1; c[0] = i + 2;
		switch (balance(a, b, c))
		{
		case ONE:
			d[j++] = i;
			e[k++] = i + 1;
			e[k++] = i + 2; break;
		case TWO:
			d[j++] = i + 1;
			e[k++] = i;
			e[k++] = i + 2; break;
		case THREE:
			d[j++] = i + 2;
			e[k++] = i;
			e[k++] = i + 1; break;
		case EQUAL_ONETWO:
			d[j++] = i;
			d[j++] = i + 1;
			e[k++] = i + 2;  break;
		case EQUAL_TWOTHREE:
			d[j++] = i + 1;
			d[j++] = i + 2;
			e[k++] = i; break;
		case EQUAL_ONETHREE:
			d[j++] = i;
			d[j++] = i + 2;
			e[k++] = i + 1;  break;
		case EQUAL_ALL:
			f[l++] = i;
			f[l++] = i + 1;
			f[l++] = i + 2; break;
		}
	}

	for (i = 0; i < 101; i++) {
		if (e[i] == 0) {
			temp = i;
			e[i] = -1;
			break;
		}
	}

	b[0] = -1; c[0] = -1;

	if (balance(e, b, c) != SUCCESS) {
		e[temp] = 0; e[temp + 1] = -1; //34번째- 비교하지않았던 인덱스0을 불량동전 배열에 넣고 비교

		if (balance(e, b, c) != SUCCESS) {
			e[temp + 1] = 0;

			for (i = 0; i < 99; i += 9) { // EQUAL 값들을 모아놓은 배열을 한번 더 분류하는 작업
				a[0] = f[i]; b[0] = f[i + 3]; c[0] = f[i + 6];
				if (a[0] == 0 || b[0] == 0 || c[0] == 0) { break; }
				switch (balance(a, b, c)) {
				case ONE:
					d[j++] = f[i]; d[j++] = f[i + 1]; d[j++] = f[i + 2];
					e[k++] = f[i + 3]; e[k++] = f[i + 4]; e[k++] = f[i + 5];
					e[k++] = f[i + 6]; e[k++] = f[i + 7]; e[k++] = f[i + 8];
					break;
				case TWO:
					d[j++] = f[i + 3]; d[j++] = f[i + 4]; d[j++] = f[i + 5];
					e[k++] = f[i]; e[k++] = f[i + 1]; e[k++] = f[i + 2];
					e[k++] = f[i + 6]; e[k++] = f[i + 7]; e[k++] = f[i + 8];
					break;
				case THREE:
					d[j++] = f[i + 6]; d[j++] = f[i + 7]; d[j++] = f[i + 8];
					e[k++] = f[i]; e[k++] = f[i + 1]; e[k++] = f[i + 2];
					e[k++] = f[i + 3]; e[k++] = f[i + 4]; e[k++] = f[i + 5];
					break;
				case EQUAL_ONETWO:
					d[j++] = f[i]; d[j++] = f[i + 1]; d[j++] = f[i + 2];
					d[j++] = f[i + 3]; d[j++] = f[i + 4]; d[j++] = f[i + 5];
					e[k++] = f[i + 6]; e[k++] = f[i + 7]; e[k++] = f[i + 8];
					break;
				case EQUAL_TWOTHREE:
					d[j++] = f[i + 3]; d[j++] = f[i + 4]; d[j++] = f[i + 5];
					d[j++] = f[i + 6]; d[j++] = f[i + 7]; d[j++] = f[i + 8];
					e[k++] = f[i]; e[k++] = f[i + 1]; e[k++] = f[i + 2];
					break;
				case EQUAL_ONETHREE:
					d[j++] = f[i]; d[j++] = f[i + 1]; d[j++] = f[i + 2];
					d[j++] = f[i + 6]; d[j++] = f[i + 7]; d[j++] = f[i + 8];
					e[k++] = f[i + 3]; e[k++] = f[i + 4]; e[k++] = f[i + 5];
					break;
				case EQUAL_ALL:
					f1[l1++] = f[i]; f1[l1++] = f[i + 1]; f1[l1++] = f[i + 2];
					f1[l1++] = f[i + 3]; f1[l1++] = f[i + 4]; f1[l1++] = f[i + 5];
					f1[l1++] = f[i + 6]; f1[l1++] = f[i + 7]; f1[l1++] = f[i + 8];
					break;
				}
			}
			d[j] = -1; e[k] = -1; f1[l1] = -1; b[0] = -1; c[0] = -1;

			if (balance(e, b, c) != SUCCESS) {
				e[k] = 0; d[j] = 0; f1[l1] = 0;

				for (i = 0; i < 99; i += 9) { // EQUAL 값들을 모아놓은 배열을 한번 더 분류하는 작업
					a[0] = f1[i]; b[0] = f1[i + 3]; c[0] = f1[i + 6];
					if (a[0] == 0 || b[0] == 0 || c[0] == 0) { break; }
					switch (balance(a, b, c)) {
					case ONE:
						d[j++] = f1[i]; d[j++] = f1[i + 1]; d[j++] = f1[i + 2];
						e[k++] = f1[i + 3]; e[k++] = f1[i + 4]; e[k++] = f1[i + 5];
						e[k++] = f1[i + 6]; e[k++] = f1[i + 7]; e[k++] = f1[i + 8];
						break;
					case TWO:
						d[j++] = f1[i + 3]; d[j++] = f1[i + 4]; d[j++] = f1[i + 5];
						e[k++] = f1[i]; e[k++] = f1[i + 1]; e[k++] = f1[i + 2];
						e[k++] = f1[i + 6]; e[k++] = f1[i + 7]; e[k++] = f1[i + 8];
						break;
					case THREE:
						d[j++] = f1[i + 6]; d[j++] = f1[i + 7]; d[j++] = f1[i + 8];
						e[k++] = f1[i]; e[k++] = f1[i + 1]; e[k++] = f1[i + 2];
						e[k++] = f1[i + 3]; e[k++] = f1[i + 4]; e[k++] = f1[i + 5];
						break;
					case EQUAL_ONETWO:
						d[j++] = f1[i]; d[j++] = f1[i + 1]; d[j++] = f1[i + 2];
						d[j++] = f1[i + 3]; d[j++] = f1[i + 4]; d[j++] = f1[i + 5];
						e[k++] = f1[i + 6]; e[k++] = f1[i + 7]; e[k++] = f1[i + 8];
						break;
					case EQUAL_TWOTHREE:
						d[j++] = f1[i + 3]; d[j++] = f1[i + 4]; d[j++] = f1[i + 5];
						d[j++] = f1[i + 6]; d[j++] = f1[i + 7]; d[j++] = f1[i + 8];
						e[k++] = f1[i]; e[k++] = f1[i + 1]; e[k++] = f1[i + 2];
						break;
					case EQUAL_ONETHREE:
						d[j++] = f1[i]; d[j++] = f1[i + 1]; d[j++] = f1[i + 2];
						d[j++] = f1[i + 6]; d[j++] = f1[i + 7]; d[j++] = f1[i + 8];
						e[k++] = f1[i + 3]; e[k++] = f1[i + 4]; e[k++] = f1[i + 5];
						break;
					case EQUAL_ALL:
						f2[l2++] = f1[i]; f2[l2++] = f1[i + 1]; f2[l2++] = f1[i + 2];
						f2[l2++] = f1[i + 3]; f2[l2++] = f1[i + 4]; f2[l2++] = f1[i + 5];
						f2[l2++] = f1[i + 6]; f2[l2++] = f1[i + 7]; f2[l2++] = f1[i + 8];
						break;
					}
				}
				d[j] = -1; e[k] = -1; f2[l2] = -1; b[0] = -1; c[0] = -1;

				if (balance(e, b, c) != SUCCESS) {
					e[k] = 0; d[j] = 0; f2[l2] = 0;

					for (i = 0; i < 99; i++) { // f1의 값을 전부다 e에 붙임
						if (f2[i] == 0) {
							e[k + i] = -1;
							break;
						}
						e[k + i] = f2[i];
					}
				}
				else if (balance(e, b, c) == SUCCESS) {
					d[j] = -1; e[k] = -1; f2[l2] = -1; b[0] = -1; c[0] = -1;
					return 0;
				}
			}

			else {
				d[j] = -1; e[k] = -1; f2[l2] = -1; b[0] = -1; c[0] = -1;
				printf("\n\n");
				return 0;
			}


			for (i = 0; i < 101; i++) {
				printf("%d ", e[i]);
			}
			printf("\n\n");

			balance(e, b, c);
		}
	}



	printf("\n\n");
	for (i = 0; i < 101; i++) {
		printf("%d ", d[i]);
	}
	printf("\n\n");
	for (i = 0; i < 101; i++) {
		printf("%d ", e[i]);
	}
	printf("\n\n");
	for (i = 0; i < 101; i++) {
		printf("%d ", f[i]);
	}
	printf("\n\n");
	for (i = 0; i < 101; i++) {
		printf("%d ", f1[i]);
	}
	printf("\n\n");
	for (i = 0; i < 101; i++) {
		printf("%d ", f2[i]);
	}
	printf("\n\n");
	for (i = 0; i < 101; i++) {
		printf("%d ", f3[i]);
	}
	printf("\n\n");



	getchar();
	return 0;
}