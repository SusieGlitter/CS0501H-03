#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <ctime>

#include "exceptions.hpp"
#include "list.hpp"
#include "class-bint.hpp"
#include "class-integer.hpp"
#include "class-matrix.hpp"

const int MAXN = 50005;

enum Color{// Provided by Lhtie 2022.2

#include "class-integer.hpp"
#include "class-matrix.hpp"
#include "class-bint.hpp"
#include "list.hpp"

#include <iostream>
#include <list>

const int N = 5e4;

template<typename T>
bool equal(const std::list<T> &x, const sjtu::list<T> &y) {
    if (x.size() != y.size())
        return false;

    typename std::list<T>::const_iterator itx = x.cbegin();
    typename sjtu::list<T>::const_iterator ity = y.cbegin();
    for (; itx != x.cend() && ity != y.cend(); ++itx, ++ity)
        if (!(*itx == *ity))
            return false;

    return true;
}

bool testConstructors() {
    std::list<int> ans;
    sjtu::list<int> myList;

    if (ans.size() != myList.size())
        return false;
    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    sjtu::list<int> *otherList = new sjtu::list<int>(myList);
    if (!equal(ans, *otherList)) {
        delete otherList;
        return false;
    }
    delete otherList;
    if (!equal(ans, myList))
        return false;

    return true;
}

bool testAssignment() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        ans.push_back(N - i);
        myList.push_back(N - i);
    }

    myList = myList;
    if (!equal(ans, myList))
        return false;

    sjtu::list<int> otherList;
    otherList = myList;
    if (!equal(ans, otherList))
        return false;

    return true;
}

bool testPush() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        if (rand()%2){
            ans.push_back(i);
            myList.push_back(i);
        } else {
            ans.push_front(i);
            myList.push_front(i);
        }
    }

    return equal(ans, myList);
}

bool testPop() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    for (int i = 0; i < rand()%N; ++i){
        if (rand()%2){
            ans.pop_front();
            myList.pop_front();
        } else {
            ans.pop_back();
            myList.pop_back();
        }
    }

    return equal(ans, myList);
}

bool testIterator() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    std::list<int>::iterator ansIt = ans.begin();
    sjtu::list<int>::iterator myIt = myList.begin();
    for (int i = 0; i < N / 4; ++i){
        if (*(ansIt++) != *(myIt++))
            return false;
        if (*(++ansIt) != *(++myIt))
            return false;
    }
    for (int i = 0; i < N / 8; ++i){
        if (*(ansIt--) != *(myIt--))
            return false;
        if (*(--ansIt) != *(--myIt))
            return false;
    }

    sjtu::list<Diamond::Matrix<double>> mtxList;
    int rows = 123, cols = 987, val = 456;
    mtxList.push_back(Diamond::Matrix<double>(rows, cols, val));
    sjtu::list<Diamond::Matrix<double>>::iterator mtxIt = mtxList.begin();
    if (mtxIt->RowSize() != rows || mtxIt->ColSize() != cols || (*mtxIt)[0][0] != val)
        return false;

    sjtu::list<int>::const_iterator cIt(myIt);
    sjtu::list<int>::iterator otherIt = myIt;
    if (cIt != myIt || myIt != cIt || myIt != otherIt)
        return false;
    myIt++;
    if (cIt == myIt || myIt == cIt || myIt == otherIt)
        return false;

    return true;
}

bool testBint() {
    std::list<Util::Bint> ans;
    sjtu::list<Util::Bint> myList;
    Util::Bint large = Util::Bint(rand());

    for (int i = 0; i < N / 30; ++i){
        ans.push_back(Util::Bint(i) * large);
        myList.push_back(Util::Bint(i) * large);
    }

    return equal(ans, myList);
}

bool testInteger() {
    std::list<Integer> ans;
    sjtu::list<Integer> myList;

    for (int i = 0; i < N; ++i){
        ans.push_back(Integer(N - i));
        myList.push_back(Integer(N - i));
    }

    return equal(ans, myList);
}

bool testMatrix() {
    using Matrix = Diamond::Matrix<double>;
    std::list<Matrix> ans;
    sjtu::list<Matrix> myList;

    for (int i = 0; i < N / 30; ++i){
        ans.push_back(Matrix(2, 3, i) * Matrix(3, 4, i));
        myList.push_back(Matrix(2, 3, i) * Matrix(3, 4, i));
    }

    return equal(ans, myList);
}

bool testElementAccess() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
        if (ans.front() != myList.front() || ans.back() != myList.back())
            return false;
    }
    return true;
}

bool testCapacityInfo() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < rand()%N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }
    if (ans.empty() != myList.empty() || ans.size() != myList.size())
        return false;

    myList.clear();
    return myList.empty() && myList.size() == 0;
}

bool testInsert() {
    std::list<int> ans;
    sjtu::list<int> myList;

    for (int i = 0; i < N; ++i){
        if (rand()%2) {
            ans.insert(ans.begin(), i);
            myList.insert(myList.begin(), i);
        } else {
            ans.insert(ans.end(), i);
            myList.insert(myList.end(), i);
        }
    }

    return equal(ans, myList);
}

bool testErase() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        ans.push_back(i);
        myList.push_back(i);
    }

    for (int i = 0; i < rand()%N; ++i)
        if (rand()%2){
            if (*ans.erase(ans.begin()) != *myList.erase(myList.begin()))
                return false;
        } else {
            ans.erase(--ans.end());
            myList.erase(--myList.end());
        }

    return equal(ans, myList);
}

bool testException() {
    sjtu::list<int> myList, otherList;
    int ans = 0;

    try{ myList.pop_back(); } catch (...) { ans++; }
    try{ myList.pop_front(); } catch (...) { ans++; }
    try{ myList.front(); } catch (...) { ans++; }
    try{ myList.back(); } catch (...) { ans++; }
    sjtu::list<int>::iterator it = myList.end(), oit = otherList.end();
    try{ *it; } catch (...) { ans++; }
    try{ it--; } catch (...) { ans++; }
    try{ it++; } catch (...) { ans++; }
    try{ myList.erase(it); } catch (...) { ans++; }
    try{ myList.insert(oit, 0); } catch (...) { ans++; }

    return ans == 9;
}

bool testMerge() {
    std::list<int> ans1, ans2;
    sjtu::list<int> myList1, myList2;

    ans1.merge(ans2), myList1.merge(myList2);
    if (!equal(ans1, myList1))
        return false;

    for (int i = 0; i < N; ++i){
        ans1.push_back(i * 2);
        myList1.push_back(i * 2);
        ans2.push_back(i * 3);
        myList2.push_back(i * 3);
    }

    ans1.merge(ans2), myList1.merge(myList2);
    return equal(ans1, myList1);
}

bool testReverse(){
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        int x = rand();
        ans.push_back(x);
        myList.push_back(x);
    }

    ans.reverse(), myList.reverse();
    return equal(ans, myList);
}

bool testSort(){
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        int x = rand();
        ans.push_back(x);
        myList.push_back(x);
    }

    ans.sort(), myList.sort();
    return equal(ans, myList);
}

bool testUnique() {
    std::list<int> ans;
    sjtu::list<int> myList;
    for (int i = 0; i < N; ++i){
        int x = rand() % 2;
        ans.push_back(x);
        myList.push_back(x);
    }

    ans.unique(), myList.unique();
    return equal(ans, myList);
}

int main(){
    srand(time(NULL));
    bool (*testList[])() = {
            testConstructors, testAssignment, testPush, testPop, testIterator,
            testBint, testInteger, testMatrix, testElementAccess, testCapacityInfo,
            testInsert, testErase, testException, testMerge, testReverse, testSort, testUnique
    };
    const char* Messages[] = {
            "Test 1: Testing default & copy constructors and destructor...",
            "Test 2: Testing operator= ...",
            "Test 3: Testing push_front & push_back...",
            "Test 4: Testing pop_front & pop_back...",
            "Test 5: Testing iterator operations...",
            "Test 6: Testing class-bint...",
            "Test 7: Testing class-integer...",
            "Test 8: Testing class-Matrix...",
            "Test 9: Testing front() & back()...",
            "Test 10: Testing information of capacity...",
            "Test 11: Testing insert()...",
            "Test 12: Testing erase()...",
            "Test 13: Testing exception throw...",
            "Test 14: Testing merge()...",
            "Test 15: Testing reverse()...",
            "Test 16: Testing sort()...",
            "Test 17: Testing unique()..."
    };

    bool okay = true;
    for (int i = 0; i < sizeof(testList) / sizeof(testList[0]); ++i) {
        printf("%s", Messages[i]);
        if (testList[i]()){
            printf("Passed\n");
        } else {
            okay = false;
            printf("Failed\n");
        }
    }

    if (okay)
        printf("Congratulations, you have passed all tests!\n");
    else printf("Unfortunately, you failed in some of the tests.\n");
    return 0;
}
	Red, Green, Blue, Normal
};

class TestCore{
private:
	const char *title;
	const int id, total;
	long dfn;
	int counter, enter;
public:
	TestCore(const char *title, const int &id, const int &total) : title(title), id(id), total(total), dfn(clock()), counter(0), enter(0) {
	}
	void init() {
		static char tmp[200];
		sprintf(tmp, "Test %d: %-55s", id, title);
		printf("%-65s", tmp);
	}
	void showMessage(const char *s, const Color &c = Normal) {
	}
	void showProgress() {
	}
	void pass() {
		showMessage("PASSED", Green);
		printf("PASSED");
	}
	void fail() {
		showMessage("FAILED", Red);
		printf("FAILED");
	}
	~TestCore() {
		puts("");
		fflush(stdout);
	}
};

template<typename T>
bool equal(const std::list<T> &x, const sjtu::list<T> &y) {
    if (x.size() != y.size())
        return false;

    typename std::list<T>::const_iterator itx = x.cbegin();
    typename sjtu::list<T>::const_iterator ity = y.cbegin();
    for (; itx != x.cend() && ity != y.cend(); ++itx, ++ity)
        if (!(*itx == *ity))
            return false;

    return true;
}

class Int{
public:
	static int born;
    static int dead;
	int val;

	Int(int val) : val(val) {
		born++;
	}

	Int(const Int &rhs) {
		val = rhs.val;
		born++;
	}

	Int & operator = (const Int &rhs) {
		born++; dead++;
        val = rhs.val;
        return *this;
	}

	bool operator == (const Int &rhs) const {
		return val == rhs.val;
	}
    bool operator != (const Int &rhs) const {
		return val != rhs.val;
	}
	friend bool operator < (const Int &lhs, const Int &rhs) {
		return lhs.val > rhs.val;
	}

	~Int() {
		dead++;
	}
};

int Int::born = 0;
int Int::dead = 0;

int rands() {
    int r = int (rand() << 15) + int ( rand() );
    return r;
}

const std::vector<int> & generator(int n = MAXN) {
	static std::vector<int> raw;
	raw.clear();
	for (int i = 0; i < n; i++) {
		raw.push_back(rands());
	}
	return raw;
}

void tester1() {
        TestCore console("test 1 ...", 1, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
    auto mirr = generator(MAXN/20);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2) stdlist.push_back(tmp), mylist.push_back(tmp);
            else stdlist.push_front(tmp), mylist.push_front(tmp);
        }

        std::list<Int> ministd;
        sjtu::list<Int> minimy;
        for (int i = 0;i < 10;i++) ministd.push_back(Int(mirr[i])), minimy.push_back(Int(mirr[i]));
        for (int i = 10;i < mirr.size();i++) {
            Int tmp = Int(mirr[i]);
            int pos = rands() % (ministd.size());
            auto stdit = ministd.begin();
            auto myit = minimy.begin();
            for (int j = 0;j < pos;j++) ++stdit, ++myit;
            if (*stdit != *myit) {
                console.fail();
                return;
            }
            if (rands() % 4) ministd.insert(stdit, tmp), minimy.insert(myit, tmp);
            else if (!ministd.empty()) ministd.erase(stdit), minimy.erase(myit);
        }

		stdlist.sort(), ministd.sort();
		mylist.sort(), minimy.sort();
		
        stdlist.merge(ministd), mylist.merge(minimy);

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }

	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester2() {
        TestCore console("test 2...", 2, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        Int::born = Int::dead = 0;
        std::list<Int> stdlist1, stdlist2;
        sjtu::list<Int> mylist1, mylist2;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2) stdlist1.push_back(tmp), mylist1.push_back(tmp);
            else stdlist2.push_back(tmp), mylist2.push_back(tmp);
        }
        stdlist1.sort(), mylist1.sort();
        stdlist2.sort(), mylist2.sort();

        stdlist1.merge(stdlist2), mylist1.merge(mylist2);
        stdlist1.merge(stdlist2), mylist1.merge(mylist2);

        stdlist1.unique(), mylist1.unique();

        if (!equal(stdlist1, mylist1)){
            console.fail();
            return;
        }

	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester3() {
        TestCore console("test 3...", 3, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        std::list<Int>::iterator stdit = stdlist.begin();
        sjtu::list<Int>::iterator myit = mylist.begin();
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            stdit = stdlist.insert(stdit, tmp);
            myit = mylist.insert(myit, tmp);
            int gap = rands() % 100;
            int ins = (rands() % 2);
            for (int j = 0;j < gap;j++) {
                if (!ins && (stdit == stdlist.begin() || myit == mylist.begin())) break;
                if (ins && (stdit == stdlist.end() || myit == mylist.end())) break;
                if (!ins) --stdit, --myit;
                else ++stdit, ++myit;
            }
            stdlist.insert(stdit, tmp), mylist.insert(myit, tmp);
        }

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }

        int ins = (rands() % 10) + 3;
        stdit = stdlist.begin(), myit = mylist.begin();
        while (true) {
            if (stdit == stdlist.end() || myit == mylist.end()) break;
            stdit = stdlist.erase(stdit);
            myit = mylist.erase(myit);
            bool flag = 0;
            for (int i = 0;i < ins;i++) {
                if (stdit == stdlist.end() || myit == mylist.end()){
                    flag = 1; break;
                }
                ++stdit, ++myit;
            }
            if (flag) break;
        }

        if (!equal(stdlist, mylist)) {
            console.fail();
            return;
        }

	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

void tester4() {
        TestCore console("test 4...", 4, 2 * MAXN);
	console.init();
	auto ret = generator(MAXN/3);
	try{
        std::list<Int> stdlist;
        sjtu::list<Int> mylist;
        for (int i = 0; i < ret.size();i++) {
            Int tmp = Int(ret[i]);
            if (rands() % 2)  stdlist.push_front(tmp), mylist.push_front(tmp);
            else stdlist.push_back(tmp), mylist.push_back(tmp);

            if (!(rands() % 20)) stdlist.reverse(), mylist.reverse();
        }

        if (!equal(stdlist, mylist)){
            console.fail();
            return;
        }

        while (!stdlist.empty() && !mylist.empty()){
            int gap = rands() % stdlist.size();
            auto stdit = stdlist.begin();
            auto myit = mylist.begin();
            for (int i = 0; i < gap;i++) ++stdit, ++myit;
            if (*stdit != *myit) {
                console.fail();
                return;
            }
            if (rands() % 2) stdlist.pop_front(), mylist.pop_front();
            else stdlist.pop_back(), mylist.pop_back();
        }
        if (!stdlist.empty() || !mylist.empty()) {
            console.fail();
            return;
        }

	} catch(...) {
		console.showMessage("Unknown error occured.", Blue);
		return;
	}
	console.pass();
}

int main() {
    srand(time(NULL));
	tester1();
	tester2();
	tester3();
	tester4();
	return 0;
}
