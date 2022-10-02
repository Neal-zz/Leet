#pragma once
#include <vector>
#include <algorithm>  // std::max
#include <string>
#include <iostream>
#include <tuple>  // std::make_tuple

/* fibonacci.*/
unsigned fibFromTopToBottom(std::vector<unsigned>& fibArray, unsigned N);
unsigned fib(unsigned N);

unsigned fibDP(unsigned N);

/* coins number.*/
int coinsFromTopToBottom(std::vector<int>& coins, int amount);
int coins(int amount);

int coinsDP(int amount);

/* longest increasing subsequence.*/
unsigned lis(const std::vector<unsigned>& seq);

/* minimun distance.*/
unsigned minDisMemo(const std::string& s1, const std::string& s2, std::vector<std::vector<unsigned>>& memo, int i, int j);
unsigned minDis(const std::string& s1, const std::string& s2);

unsigned minDisDP(const std::string& s1, const std::string& s2);

/* broken egg.*/
unsigned brokenEggMemo(std::vector<std::vector<unsigned>>& eggMemo, unsigned eggK, unsigned floorN);
unsigned brokenEgg(unsigned eggK, unsigned floorN);

unsigned brokenEggDP(unsigned eggK, unsigned floorN);

/* longest palindrome subsequence.*/
unsigned lpsDP(const std::string& str);

/* piles selection.*/
int psDP(const std::vector<unsigned>& piles);


