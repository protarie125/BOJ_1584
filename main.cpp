#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using dqii = deque<pii>;

constexpr auto inf = 987654321;

const auto& dx = vi{ -1,1,0,0 };
const auto& dy = vi{ 0,0,-1,1 };

int solve(const vvi& f) {
	auto dist = vvi(501, vi(501, inf));
	dist[0][0] = 0;

	auto q = dqii{};
	q.push_front({ 0, 0 });

	auto isGoal = bool{ false };
	while (!q.empty()) {
		auto now = q.front();
		q.pop_front();

		if (500 == now.first && 500 == now.second) {
			isGoal = true;
			break;
		}

		for (auto d = 0; d < 4; ++d) {
			const auto& nx = now.first + dx[d];
			const auto& ny = now.second + dy[d];

			if (nx < 0 || 500 < nx ||
				ny < 0 || 500 < ny) {
				continue;
			}

			if (2 == f[ny][nx]) {
				continue;
			}

			if (1 == f[ny][nx]) {
				const auto& newDist = dist[now.second][now.first] + 1;
				if (newDist < dist[ny][nx]) {
					dist[ny][nx] = newDist;
					q.push_back({ nx, ny });
				}
			}
			else {
				const auto& newDist = dist[now.second][now.first];
				if (newDist < dist[ny][nx]) {
					dist[ny][nx] = newDist;
					q.push_front({ nx, ny });
				}
			}
		}
	}

	if (!isGoal) {
		return -1;
	}

	return dist[500][500];
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto f = vvi(501, vi(501, 0));

	int n; cin >> n;
	while (0 < (n--)) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		const auto& l = x1 < x2 ? x1 : x2;
		const auto& r = x1 < x2 ? x2 : x1;
		const auto& t = y1 < y2 ? y1 : y2;
		const auto& b = y1 < y2 ? y2 : y1;

		for (auto y = t; y <= b; ++y) {
			for (auto x = l; x <= r; ++x) {
				f[y][x] = 1;
			}
		}
	}

	int m; cin >> m;
	while (0 < (m--)) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		const auto& l = x1 < x2 ? x1 : x2;
		const auto& r = x1 < x2 ? x2 : x1;
		const auto& t = y1 < y2 ? y1 : y2;
		const auto& b = y1 < y2 ? y2 : y1;

		for (auto y = t; y <= b; ++y) {
			for (auto x = l; x <= r; ++x) {
				f[y][x] = 2;
			}
		}
	}

	const auto& ans = solve(f);
	cout << ans;

	return 0;
}