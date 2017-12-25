// http://poj.org/problem?id=2251
// 这是原题，不过。。因为POJ不支持C++11,所以就算把代码复制粘贴好也不能送上去评测

#include "c_algorithm_module.h"
#include <stdio.h>
#include <stdbool.h>

#define maxn (30)
int a, b, t;
char s[maxn][maxn][maxn];

typedef struct Node {
	int r, c, h;
} Node;

inline bool inside(Node v) {
	return
		v.r >= 0 && v.r < a &&
		v.c >= 0 && v.c < b &&
		v.h >= 0 && v.h < t &&
		s[v.h][v.r][v.c] != '#';
}
inline int encoder(int h, int r, int c) { return h * (a*b) + r * b + c; }

int walk(int v, int i) {
	const static int dr[] = { -1, 0, 1, 0, 0, 0 };
	const static int dc[] = { 0, -1, 0, 1, 0, 0 };
	const static int dh[] = { 0, 0, 0, 0, 1, -1 };
	const Node next = { v % (a*b) / b + dr[i], v % b + dc[i], v / (a*b) + dh[i] };
	if (inside(next)) return encoder(next.h, next.r, next.c);
	else return NIL;
}

int nexfOf(int v, int e) {
	for (int e1 = e+1; e1 < 6; e1++) {
		if (walk(v, e1) != NIL)
			return e1;
	}
	return NIL;
};

int firstOf(int v) {
	return nextOf(v, -1);
}

int main() {
	int start, dest;

	while (scanf_s("%d%d%d", &t, &a, &b) == 3 && t) {				//长宽高

		for (int i = 0; i < t; i++)
			for (int j = 0; j < a; j++) {
				scanf_s("%s", s[i][j], 1024);
				for (int k = 0; k < b; k++)
					if (s[i][j][k] == 'S') { start = encoder(i, j, k); }
					else if (s[i][j][k] == 'E') { dest = encoder(i, j, k); }
			}

		const int ans =
			AM_bfsStep(start, dest, firstOf, nexfOf, walk);
		if (ans != NIL) printf("Escaped in %d minute(s).\n", ans);
		else printf("Trapped!\n");
	}
	return 0;
}