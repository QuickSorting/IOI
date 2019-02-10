#include <bits/stdc++.h>

using namespace std;

long long getR(long long RGB) { return (RGB >> 16) & 0xFF; }

long long getG(long long RGB) { return (RGB >> 8) & 0xFF; }

long long getB(long long RGB) { return RGB & 0xFF; }

const long long N = 507;

long long picture[N][N];

void solve(){
	long long h, w;
	long long r = 0, g = 0, b = 0, diff_r = 0, diff_g = 0, diff_b = 0;
	long long mn_sum = 255 * 3, mx_sum = 0;

	cin >> h >> w;

	for(long long i = 0; i <= h+1; i++){
		for(long long j = 0; j <= w+1; j++){
			picture[i][j] = 0;
		}
	}

	for(long long i = 1; i <= h; i++){
		for(long long j = 1; j <= w; j++){
			cin >> picture[i][j];
		}
	}

	for(long long i = 1; i <= h; i++){
		for(long long j = 1; j <= w; j++){
			long long c = picture[i][j];

			r += getR(c);
			g += getG(c);
			b += getB(c);

			long long curr_sum = getR(c) + getG(c) + getB(c);

			mn_sum = min(mn_sum, curr_sum);
			mx_sum = max(mx_sum, curr_sum);

			vector<long long> neigh;

			neigh.push_back(picture[i][j-1]);
			neigh.push_back(picture[i][j+1]);
			neigh.push_back(picture[i-1][j]);
			neigh.push_back(picture[i+1][j]);

			for(long long color: neigh){
				diff_r += abs(getR(color) - getR(c));
				diff_g += abs(getG(color) - getG(c));
				diff_b += abs(getB(color) - getB(c));
			}
		}
	}

	r /= h*w;
	g /= h*w;
	b /= h*w;

	diff_r /= h*w;
	diff_g /= h*w;
	diff_b /= h*w;

	int mn = min(r, min(g, b)), mx = max(r, max(g, b));

	int sum_diff = diff_r + diff_g + diff_b;
	int sum = r + g + b;

	if(sum_diff >= 250){
		cout << "3\n";
	}
	else{
		if(mn >= 100){
			if(mx_sum - mn_sum >= 620){
				cout << "1\n";
				return ;
			}

			if(mx - mn > 70){
				cout << "4\n";
			}
			else{
				if(r >= g){
					cout << "1\n";
				}
				else{
					cout << "4\n";
				}
			}
		}
		else{
			if(sum_diff >= 70){
				cout << "2\n";
			}
			else{
				cout << "4\n";
			}
		}
	}

	//cout << r << " " << g << " " << b << "\n";

	//cout << diff_r << " " << diff_g << " " << diff_b << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long t;

	//string x, y;

	//cin >> x >> y;

	//freopen("style-3-1.in", "r", stdin);

	cin >> t;

	//t = 1;

	while(t--){
		solve();
	}

	return 0;
}