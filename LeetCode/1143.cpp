class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        // dp[i][j] = text1[i], text2[j] 的 LCS
        auto dp = vector<vector<int>>(n1 + 1, vector<int>(n2 + 1, 0));
        for(int i = 1; i <= n1; ++i)
            for(int j = 1; j <= n2; ++j)
                // 如果兩者相等，最大長度為兩者 - 1 的最大長度 + 1
                if(text1[i - 1] == text2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                // 否則為兩者其中一者 - 1 的最大值
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        return dp[n1][n2];
    }
};