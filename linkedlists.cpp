#include <bits/stdc++.h>
using namespace std;

struct Linkedlist {
    int val;
    Linkedlist *next;
    Linkedlist(int x) : val(x), next(NULL) {}
};

struct dListNode {
    int val;
    dListNode *next;
    dListNode *prev;
    dListNode(int x) : val(x), next(NULL), prev(NULL) {}
};

class Solution {
public:
    string roman(int num) {
        vector<int> nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> syms = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        string result = "";
        for (int i = 0; i < nums.size(); i++) {
            while (num >= nums[i]) {
                result += syms[i];
                num -= nums[i];
            }
        }
        return result;
    }

    string pre(vector<string>& s) {//create substring from the string
        if (s.empty()) return "";
        sort(s.begin(), s.end());
        string first = s[0];
        string last = s[s.size() - 1];
        int i = 0;
        while (i < first.size() && i < last.size() && first[i] == last[i]) {
            i++;
        }
        return first.substr(0, i);
    }

    Linkedlist* removenfromlast(Linkedlist* head, int n) {
        Linkedlist* dummy = new Linkedlist(0);
        dummy->next = head;
        Linkedlist* first = dummy;
        Linkedlist* second = dummy;

        for (int i = 0; i < n + 1; i++) {
            if (first == nullptr) return head; // n > length
            first = first->next;
        }

        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }

        Linkedlist* toDelete = second->next;
        second->next = second->next->next;
        delete toDelete;

        Linkedlist* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
    Linkedlist* mergedlist(Linkedlist* l1,Linkedlist* l2){
        Linkedlist* dummy=new Linkedlist(head);
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        ListNode* tail=dummy;
        while(l1!=nullptr || l2!=nullptr){
            if(l1->val<l2->val){
                tail->next=l1;
                l1=l1->next;
            }else{
                tail->next=l2;
                l2=l2->next;
            }
            tail=tail->next;
        }
        if (l1 != nullptr) {
            tail->next = l1;
        } else {
            tail->next = l2;
        }
        return dummy->next;
    }
    Linkedlist* swapalternative(){

    }
};

// ✅ Helper function to print the list
void printList(Linkedlist* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Solution sol;
    Linkedlist* head = new Linkedlist(1);
    head->next = new Linkedlist(2);
    head->next->next = new Linkedlist(3);
    head->next->next->next = new Linkedlist(4);
    head->next->next->next->next = new Linkedlist(5);

    return 0;
}
