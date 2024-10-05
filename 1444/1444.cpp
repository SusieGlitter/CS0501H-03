#include <bits/stdc++.h>
#include "evil.hpp"
using namespace std;

int main(){
    int T;
    freopen("1444.in","r",stdin);
    cin >> T ;
    while (T--) {
        int type;
        cin >> type;

        int test_0_st, test_0_ed, test_0_val;
        cin >> test_0_st >> test_0_ed >> test_0_val;
        Evil test_0_0(test_0_st, test_0_ed, test_0_val);

        if (type == 0){
            test_0_0.Print();
            Evil test_0_1;
            test_0_1.Print();
        }
        if(type == 1){
            Evil test_1_1;
            test_1_1 = test_0_0;
            test_1_1.Print(); 
        }
        if(type == 2){
            for(int i = test_0_st;i <= test_0_ed;++i) test_0_0[i] = i;
            test_0_0[test_0_st-1] = test_0_st-1;
            cout << test_0_0[test_0_st-1] << " " << test_0_0[test_0_ed+1] <<" ";
            test_0_0.Print();
        }
        if(type == 3){
            test_0_0++;
            test_0_0++;
            test_0_0.Print();

            ++test_0_0; ++test_0_0;
            test_0_0.Print();
        }
        if(type == 4){
            cout << test_0_0;
        }
    }
    return 0;
}