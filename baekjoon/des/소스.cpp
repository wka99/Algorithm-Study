#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int N, M;
vector<vector<int>> map(8, vector<int>(8));
vector<tuple<int, int, int>> cctv;
vector<int> dirs;

// 우, 하, 좌, 상 => 시계방향으로 이동할 수 있도록
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
void check(vector<vector<int>> &tmp, int x, int y, int dir) {
	int i = x;
	int j = y;
	while (i >= 0 && i < N&&j >= 0 && j < M) {
		if (map[i][j] == 6)
			break;
		tmp[i][j] = map[x][y];
		i += dx[dir];
		j += dy[dir];
	}
}
int solution(int idx) {
	if (idx == cctv.size()) {
		vector<vector<int>> tmp = map;
		for (int i = 0; i < cctv.size(); i++) {
			int type, x, y;
			tie(type, x, y) = cctv[i];
			if(type == 1){
				check(tmp, x, y, dirs[i]);
			}
			else if (type == 2) {
				check(tmp, x, y, dirs[i]);
				check(tmp, x, y, (dirs[i] + 2) % 4);
			}
			else if (type == 3) {
				check(tmp, x, y, dirs[i]);
				check(tmp, x, y, (dirs[i] + 1) % 4);
			}
			else if (type == 4) {
				check(tmp, x, y, dirs[i]);
				check(tmp, x, y, (dirs[i] + 1) % 4);
				check(tmp, x, y, (dirs[i] + 2) % 4);
			}
			else if (type == 5) {
				check(tmp, x, y, dirs[i]);
				check(tmp, x, y, (dirs[i] + 1) % 4);
				check(tmp, x, y, (dirs[i] + 2) % 4);
				check(tmp, x, y, (dirs[i] + 3) % 4);
			}
		}
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (tmp[i][j] == 0)
					cnt++;
			}
		}
		return cnt;
	}
	int result = 100;
	for (int i = 0; i < 4; i++) {
		dirs[idx] = i;
		int r = solution(idx + 1);
		result = min(r, result);
	}
	return result;
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] > 0 && map[i][j] < 6) {
				cctv.push_back({ map[i][j], i, j });
				dirs.push_back(0);
			}
		}
	}
	cout << solution(0) << endl;
}