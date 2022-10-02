#include "dynamic_program.h"

unsigned fibFromTopToBottom(std::vector<unsigned>& fibArray, unsigned N) {
	if (N == 1 || N == 2) {
		fibArray[N - 1] = 1;
		return 1;
	}

	if (fibArray[N - 1] != 0) {
		return fibArray[N - 1];
	}

	fibArray[N - 1] = fibFromTopToBottom(fibArray, N - 1) + fibFromTopToBottom(fibArray, N - 2);

	return fibArray[N - 1];
}

unsigned fib(unsigned N) {
	if (N < 1) {
		return 0;
	}

	std::vector<unsigned> fibArray(N, 0);

	return fibFromTopToBottom(fibArray, N);
}

unsigned fibDP(unsigned N) {
	if (N < 1) {
		return 0;
	}

	if (N < 3) {
		return 1;
	}

	unsigned fib_last = 1;
	unsigned fib = 1;
	for (unsigned n = 3; n <= N; n++) {
		unsigned fib_new = fib_last + fib;
		fib_last = fib;
		fib = fib_new;
	}

	return fib;
}

int coinsFromTopToBottom(std::vector<int>& coins, int amount) {

	const std::vector<int> k = { 1,2,5 };

	if (amount < 0) {
		return -1;
	}

	if (coins[amount] < (amount+1)) {
		return coins[amount];
	}

	int ans = (amount + 1);
	for (size_t i = 0; i < k.size(); i++) {
		int tempAns = coinsFromTopToBottom(coins, amount - k[i]);
		if (tempAns == -1) {
			continue;
		}
		ans = std::min({ (tempAns + 1), ans });
	}
	
	if (ans == (amount + 1)) {
		coins[amount] = -1;
	}
	else {
		coins[amount] = ans;
	}
	return ans;
}

int coins(int amount) {

	if (amount < 0) {
		return -1;
	}

	// k1 k2 k3 = 1 2 5.
	std::vector<int> coins(amount + 1, amount + 1);

	coins[0] = 0; coins[1] = 1; coins[2] = 1; coins[5] = 1;

	int ans = coinsFromTopToBottom(coins, amount);

	return ans;
}

int coinsDP(int amount) {
	if (amount < 0) {
		return -1;
	}
	
	std::vector<int> k = { 1,2,5 };
	std::vector<int> coins(amount + 1, amount + 1);
	coins[0] = 0; coins[1] = 1; coins[2] = 1; coins[3] = 2; coins[4] = 2; coins[5] = 1;

	for (size_t i = 6; i < coins.size(); i++) {
		int ans = amount + 1;
		for (int j : k) {
			int tempAns = coins[i - j];
			if (tempAns == -1) {
				continue;
			}
			ans = std::min({ (tempAns + 1), ans });
		}
		if (ans == (amount + 1)) {
			coins[i] = -1;
		}
		else {
			coins[i] = ans;
		}
	}

	return coins[amount];
}

unsigned lis(const std::vector<unsigned>& seq) {

	std::vector<unsigned> dp(seq.size(), 1);

	for (size_t i = 0; i < seq.size(); i++) {
		unsigned length = 1;
		for (int j = 0; j < i; j++) {
			if (seq[j] < seq[i]) {
				length = std::max({ length, dp[j] + 1 });
			}
		}
		dp[i] = length;
	}

	unsigned length = 1;
	for (size_t i = 0; i < seq.size(); i++) {
		length = std::max({ length, dp[i] });
	}
	return length;
}

unsigned minDis(const std::string& s1, const std::string& s2) {
	int i = (s1.length() - 1), j = (s2.length() - 1);

	std::vector<std::vector<unsigned>> memo(i + 1, std::vector<unsigned>(j + 1, static_cast<unsigned>(std::max({ s1.length()+1,s2.length()+1 }))));

	return minDisMemo(s1, s2, memo, i, j);
}

unsigned minDisMemo(const std::string& s1, const std::string& s2, std::vector<std::vector<unsigned>>& memo, int i, int j) {

	// one string meets the end.
	if (i < 0) {
		return j + 1;
	}
	if (j < 0) {
		return i + 1;
	}

	// look up the memo.
	if (memo[i][j] != static_cast<unsigned>(std::max({ s1.length() + 1,s2.length() + 1 }))) {
		return memo[i][j];
	}

	// skip is always preferred.
	if (s1[i] == s2[j]) {
		memo[i][j] = minDisMemo(s1, s2, memo, i - 1, j - 1);
		return memo[i][j];
	}


	memo[i][j] = std::min({ minDisMemo(s1,s2,memo,i,j - 1) + 1,  // add.
		minDisMemo(s1,s2,memo,i - 1,j) + 1 ,  // delete.
		minDisMemo(s1,s2,memo,i - 1,j - 1) + 1 });  // change.
	return memo[i][j];
}

unsigned minDisDP(const std::string& s1, const std::string& s2) {
	
	// dp table.
	std::vector<std::vector<unsigned>> dp(s1.length() + 1, std::vector<unsigned>(s2.length() + 1, 0));

	// base case.
	for (size_t i = 0; i < (s1.length() + 1); i++) {
		dp[i][0] = i;
	}
	for (size_t j = 1; j < (s2.length() + 1); j++) {
		dp[0][j] = j;
	}

	// state change.
	for (size_t i = 1; i < (s1.length() + 1); i++) {
		for (size_t j = 1; j < (s2.length() + 1); j++) {
			if (s1[i-1] == s2[j-1]) {  // skip is always preferred.
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				dp[i][j] = std::min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1});
			}
		}
	}

	return dp[s1.length()][s2.length()];
}

unsigned brokenEgg(unsigned eggK, unsigned floorN) {

	// memo
	std::vector<std::vector<unsigned>> eggMemo(eggK + 1, std::vector<unsigned>(floorN + 1, floorN + 1));

	return brokenEggMemo(eggMemo, eggK, floorN);
}

unsigned brokenEggMemo(std::vector<std::vector<unsigned>>& eggMemo, unsigned eggK, unsigned floorN) {

	// memo
	if (eggMemo[eggK][floorN] != eggMemo[0].size()) {
		return eggMemo[eggK][floorN];
	}

	// base case
	if (eggK == 1) {
		eggMemo[1][floorN] = floorN;
		return floorN;
	}
	if (floorN == 0) {
		eggMemo[eggK][0] = 0;
		return 0;
	}

	/* state change*/
	// method 1.
	unsigned ans = eggMemo[0].size();
	//for (size_t j = 1; j <= floorN; j++) {
	//	unsigned tempAns = std::max({ brokenEggMemo(eggMemo, eggK - 1, j - 1),  // if broken.
	//		brokenEggMemo(eggMemo, eggK, floorN - j) });  // if not broken.
	//	ans = std::min({ ans, tempAns + 1 });
	//}
	// method 2. binary search methods.
	unsigned floorLow = 1, floorHigh = floorN;
	while (floorLow <= floorHigh) {
		unsigned floorMid = (floorLow + floorHigh) / 2;
		unsigned broken = brokenEggMemo(eggMemo, eggK - 1, floorMid - 1);
		unsigned unbroken = brokenEggMemo(eggMemo, eggK, floorN - floorMid);
		if (broken > unbroken) {
			floorHigh = floorMid - 1;
			ans = std::min({ ans, broken + 1 });
		}
		else {
			floorLow = floorMid + 1;
			ans = std::min({ ans, unbroken + 1 });
		}
	}

	eggMemo[eggK][floorN] = ans;
	return ans;
}

unsigned brokenEggDP(unsigned eggK, unsigned floorN) {

	// dp table. (egg number, try times). maximum try times = floorN.
	unsigned maxTimes = floorN / eggK;
	std::vector<std::vector<unsigned>> eggDP(eggK + 1, std::vector<unsigned>(maxTimes, 0));

	// base case.
	for (size_t i = 1; i < eggK + 1; i++) {
		eggDP[i][1] = 1;
	}
	for (size_t j = 0; j < maxTimes; j++) {
		eggDP[1][j] = j;
	}

	// state change.
	for (size_t j = 2; j < maxTimes; j++) {
		for (size_t i = 2; i < (eggK + 1); i++) {
			eggDP[i][j] = eggDP[i - 1][j - 1] + eggDP[i][j - 1] + 1;
			if (eggDP[i][j] >= floorN && i == eggK) {
				return j;
			}
		}
	}
}

unsigned lpsDP(const std::string& str) {

	// dp table. (start and end pointer of the subsequence.)
	std::vector<std::vector<unsigned>> dp(str.length(), std::vector<unsigned>(str.length(), 0));

	// base case.
	for (size_t i = 0; i < str.length(); i++) {
		dp[i][i] = 1;
	}

	// state change.
	for (int i = str.length() - 2; i >= 0; i--) {
		for (int j = i + 1; j < str.length(); j++) {
			if (str[i] == str[j]) {
				dp[i][j] = dp[i + 1][j - 1] + 2;
			}
			else {
				dp[i][j] = std::max({ dp[i + 1][j], dp[i][j - 1] });
			}
		}
	}

	return dp[0][str.length() - 1];
}

int psDP(const std::vector<unsigned>& piles) {

	// dp table.
	std::vector<std::vector<std::tuple<unsigned, unsigned>>> 
		dp(piles.size(), std::vector<std::tuple<unsigned, unsigned>>(piles.size(), std::make_tuple(0, 0)));

	// base case.
	for (size_t i = 0; i < piles.size(); i++) {
		dp[i][i] = std::make_tuple(piles[i], 0);
	}

	// state change.
	for (size_t di = 1; di < piles.size(); di++) {
		for (size_t i = 0; i < piles.size() - di; i++) {
			unsigned left = std::get<1>(dp[i + 1][i + di]) + piles[i];
			unsigned right = std::get<1>(dp[i][i + di - 1]) + piles[i + di];

			if (left > right) {
				dp[i][i + di] = std::make_tuple(std::get<1>(dp[i + 1][i + di]) + piles[i], std::get<0>(dp[i + 1][i + di]));
			}
			else {
				dp[i][i + di] = std::make_tuple(std::get<1>(dp[i][i + di - 1]) + piles[i + di], std::get<0>(dp[i][i + di - 1]));
			}
		}
	}

	int ans = static_cast<int>(std::get<0>(dp[0][piles.size() - 1])) -
		static_cast<int>(std::get<1>(dp[0][piles.size() - 1]));
	return ans;
}
