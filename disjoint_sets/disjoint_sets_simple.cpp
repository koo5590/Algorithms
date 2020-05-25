//https://www.acmicpc.net/source/18955564
int parent[N];

int find(int u) {
	if (par[u] == u) return u;
	return par[u] = find(par[u]);
}

void merge(int u, int v) {
	u = find(u);
	v = find(v);
	par[u] = v;
}
