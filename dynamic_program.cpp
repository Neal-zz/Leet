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

	// look up the dp table.
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
	std::vector<std::vector<unsigned>> dp(s1.length() + 1, std::vector<unsigned>(s2.length() + 1, 0));

	for (size_t i = 0; i < (s1.length() + 1); i++) {
		dp[i][0] = i;
	}
	for (size_t j = 1; j < (s2.length() + 1); j++) {
		dp[0][j] = j;
	}

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






