#include <bits/stdc++.h>

using namespace std;

const long long N = 1e5 + 7;

vector<long long> adj[N], price[N];

struct for_d{
	long long di, line1, line2;

	for_d(long long _di = 0, long long _line1 = 0, long long _line2 = 0){
		di = _di;
		line1 = _line1;
		line2 = _line2;
	}
};

for_d d[N];
bool used[N];

long long dp[N];

void dfs2(long long u, long long mx){
	used[u] = true;
	dp[u] = max(d[u].line1, mx);

	//cout << u << " u mx "<< mx << "\n";
	//cout << d[u].line1 << " || " << d[u].line2 << "\n\n";

	for(long long i = 0; i < adj[u].size(); i++){
		long long to = adj[u][i];
		long long p = price[u][i];

		if(used[to]){
			continue;
		}

		if(d[u].line1 == d[to].line1 + p){
			dfs2(to, max(d[u].line2, mx) + p);
		}
		else{
			dfs2(to, max(d[u].line1, mx) + p);
		}
	}
}

void dfs(long long u){
	used[u] = true;
	d[u] = for_d(0, 0, 0);

	for(long long i = 0; i < adj[u].size(); i++){
		long long to = adj[u][i];
		long long p = price[u][i];

		if(used[to]){
			continue;
		}
		
		dfs(to);

		d[u].di = max(d[u].di, d[u].line1 + d[to].line1 + p);
		d[u].di = max(d[u].di, d[to].di);
		
		if(p + d[to].line1 > d[u].line1){
			d[u].line2 = d[u].line1;
			d[u].line1 = p + d[to].line1;
		}
		else{
			if(p + d[to].line1 > d[u].line2){
				d[u].line2 = p + d[to].line1;
			}
		}
	}
}

long long dfs3(long long u){
	used[u] = true;

	long long mn = dp[u];

	for(long long to: adj[u]){
		if(used[to]){
			continue;
		}

		mn = min(mn, dfs3(to));
	}	

	return mn;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n, m, l;

	cin >> n >> m >> l;

	for(long long i = 0; i < m; i++){
		long long u, v, t;

		cin >> u >> v >> t;

		adj[u].push_back(v);
		adj[v].push_back(u);
		price[u].push_back(t);
		price[v].push_back(t);
	}

	long long res = 0;

	for(long long i = 0; i < n; i++){
		if(!used[i]){
			dfs(i);
		}
		res = max(res, d[i].di);
		//cout << i << " = " << d[i].di << " " << d[i].line1 << " " << d[i].line2 << "\n";
 	}

	for(long long i = 0; i < n; i++){
		used[i] = false;
	}

	for(long long i = 0; i < n; i++){
		if(!used[i]){
			dfs2(i, 0);
		}
		//cout << i << " = " << dp[i] << "\n";
	}

	for(long long i = 0; i < n; i++){
		used[i] = false;
	}

	vector<long long> mn_v;

	for(long long i = 0; i < n; i++){
		if(!used[i]){
			mn_v.push_back(dfs3(i));
			//cout << mn_v.back() << " back\n";
		}
	}

	sort(mn_v.begin(), mn_v.end());

	long long k = mn_v.size();

	if(k > 1){
		res = max(res, mn_v[k-1] + mn_v[k-2] + l);
		if(k > 2){
			res = max(res, mn_v[k-2] + mn_v[k-3] + 2*l);
		}
	}

	cout << res << "\n";

	return 0;
}
/*
7 6 1
0 1 7
0 2 3
1 3 4
1 4 0
1 5 2
5 6 1
*/